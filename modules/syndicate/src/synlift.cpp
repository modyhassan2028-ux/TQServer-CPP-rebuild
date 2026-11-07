#include "modules/syndicate/src/synlift.h"

namespace tq {

uint64_t SynLift_1417224f0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A) {
    uint64_t rax = 0, rbx = 0, rbp = 0, rsi = 0, rdi = 0, r10 = 0, r11 = 0, r12 = 0, r13 = 0, r14 = 0, r15 = 0;
    uint64_t rcx = rcxA, rdx = rdxA, r8 = r8A, r9 = r9A;
    bool f_zf = false, f_cf = false, f_sf = false, f_of = false;
    uint8_t xmm0[16] = {0}, xmm1[16] = {0}, xmm2[16] = {0}, xmm3[16] = {0}, xmm4[16] = {0}, xmm5[16] = {0};
    alignas(16) uint8_t stkFrame[0x400] = {0};
    uint64_t rsp = (uint64_t)(uintptr_t)(stkFrame + 0x200);
#define ML_CALL(t) g_fnLIFT_##t(rcx, rdx, r8, r9, ML_M8(rsp, 0x20), ML_M8(rsp, 0x28))
    r8 = ML_M8(rdx, 0x0);
    rax = ML_M8(r8, 0x10);
    ML_M8(rdx, 0x0) = rax;
    rax = ML_M8(r8, 0x10);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L7;
    ML_M8(rax, 0x8) = rdx;
L7:
    rax = ML_M8(rdx, 0x8);
    ML_M8(r8, 0x8) = rax;
    rax = ML_M8(rcx, 0x30);
{
    const uint64_t a = (uint64_t)(rdx) & ~0ULL, b = (uint64_t)(ML_M8(rax, 0x8)) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L16;
    ML_M8(rax, 0x8) = r8;
    ML_M8(r8, 0x10) = rdx;
    ML_M8(rdx, 0x8) = r8;
    return rax;
L16:
    rax = ML_M8(rdx, 0x8);
{
    const uint64_t a = (uint64_t)(rdx) & ~0ULL, b = (uint64_t)(ML_M8(rax, 0x10)) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L23;
    ML_M8(rax, 0x10) = r8;
    ML_M8(r8, 0x10) = rdx;
    ML_M8(rdx, 0x8) = r8;
    return rax;
L23:
    ML_M8(rax, 0x0) = r8;
    ML_M8(r8, 0x10) = rdx;
    ML_M8(rdx, 0x8) = r8;
    return rax;
#undef ML_CALL
    return rax;
}

uint64_t SynLift_141722680(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A) {
    uint64_t rax = 0, rbx = 0, rbp = 0, rsi = 0, rdi = 0, r10 = 0, r11 = 0, r12 = 0, r13 = 0, r14 = 0, r15 = 0;
    uint64_t rcx = rcxA, rdx = rdxA, r8 = r8A, r9 = r9A;
    bool f_zf = false, f_cf = false, f_sf = false, f_of = false;
    uint8_t xmm0[16] = {0}, xmm1[16] = {0}, xmm2[16] = {0}, xmm3[16] = {0}, xmm4[16] = {0}, xmm5[16] = {0};
    alignas(16) uint8_t stkFrame[0x400] = {0};
    uint64_t rsp = (uint64_t)(uintptr_t)(stkFrame + 0x200);
#define ML_CALL(t) g_fnLIFT_##t(rcx, rdx, r8, r9, ML_M8(rsp, 0x20), ML_M8(rsp, 0x28))
    r8 = ML_M8(rdx, 0x0);
    rax = ML_M8(r8, 0x10);
    ML_M8(rdx, 0x0) = rax;
    rax = ML_M8(r8, 0x10);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x49)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L7;
    ML_M8(rax, 0x8) = rdx;
L7:
    rax = ML_M8(rdx, 0x8);
    ML_M8(r8, 0x8) = rax;
    rax = ML_M8(rcx, 0x30);
{
    const uint64_t a = (uint64_t)(rdx) & ~0ULL, b = (uint64_t)(ML_M8(rax, 0x8)) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L16;
    ML_M8(rax, 0x8) = r8;
    ML_M8(r8, 0x10) = rdx;
    ML_M8(rdx, 0x8) = r8;
    return rax;
L16:
    rax = ML_M8(rdx, 0x8);
{
    const uint64_t a = (uint64_t)(rdx) & ~0ULL, b = (uint64_t)(ML_M8(rax, 0x10)) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L23;
    ML_M8(rax, 0x10) = r8;
    ML_M8(r8, 0x10) = rdx;
    ML_M8(rdx, 0x8) = r8;
    return rax;
L23:
    ML_M8(rax, 0x0) = r8;
    ML_M8(r8, 0x10) = rdx;
    ML_M8(rdx, 0x8) = r8;
    return rax;
#undef ML_CALL
    return rax;
}

uint64_t SynLift_1417227e0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A) {
    uint64_t rax = 0, rbx = 0, rbp = 0, rsi = 0, rdi = 0, r10 = 0, r11 = 0, r12 = 0, r13 = 0, r14 = 0, r15 = 0;
    uint64_t rcx = rcxA, rdx = rdxA, r8 = r8A, r9 = r9A;
    bool f_zf = false, f_cf = false, f_sf = false, f_of = false;
    uint8_t xmm0[16] = {0}, xmm1[16] = {0}, xmm2[16] = {0}, xmm3[16] = {0}, xmm4[16] = {0}, xmm5[16] = {0};
    alignas(16) uint8_t stkFrame[0x400] = {0};
    uint64_t rsp = (uint64_t)(uintptr_t)(stkFrame + 0x200);
#define ML_CALL(t) g_fnLIFT_##t(rcx, rdx, r8, r9, ML_M8(rsp, 0x20), ML_M8(rsp, 0x28))
    r8 = ML_M8(rdx, 0x0);
    rax = ML_M8(r8, 0x10);
    ML_M8(rdx, 0x0) = rax;
    rax = ML_M8(r8, 0x10);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x1d)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L7;
    ML_M8(rax, 0x8) = rdx;
L7:
    rax = ML_M8(rdx, 0x8);
    ML_M8(r8, 0x8) = rax;
    rax = ML_M8(rcx, 0x30);
{
    const uint64_t a = (uint64_t)(rdx) & ~0ULL, b = (uint64_t)(ML_M8(rax, 0x8)) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L16;
    ML_M8(rax, 0x8) = r8;
    ML_M8(r8, 0x10) = rdx;
    ML_M8(rdx, 0x8) = r8;
    return rax;
L16:
    rax = ML_M8(rdx, 0x8);
{
    const uint64_t a = (uint64_t)(rdx) & ~0ULL, b = (uint64_t)(ML_M8(rax, 0x10)) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L23;
    ML_M8(rax, 0x10) = r8;
    ML_M8(r8, 0x10) = rdx;
    ML_M8(rdx, 0x8) = r8;
    return rax;
L23:
    ML_M8(rax, 0x0) = r8;
    ML_M8(r8, 0x10) = rdx;
    ML_M8(rdx, 0x8) = r8;
    return rax;
#undef ML_CALL
    return rax;
}

__attribute__((weak)) uint64_t (*g_fnLIFT_1418233c0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t) = nullptr;
uint64_t SynLift_141722ef0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A) {
    uint64_t rax = 0, rbx = 0, rbp = 0, rsi = 0, rdi = 0, r10 = 0, r11 = 0, r12 = 0, r13 = 0, r14 = 0, r15 = 0;
    uint64_t rcx = rcxA, rdx = rdxA, r8 = r8A, r9 = r9A;
    bool f_zf = false, f_cf = false, f_sf = false, f_of = false;
    uint8_t xmm0[16] = {0}, xmm1[16] = {0}, xmm2[16] = {0}, xmm3[16] = {0}, xmm4[16] = {0}, xmm5[16] = {0};
    alignas(16) uint8_t stkFrame[0x400] = {0};
    uint64_t rsp = (uint64_t)(uintptr_t)(stkFrame + 0x200);
#define ML_CALL(t) g_fnLIFT_##t(rcx, rdx, r8, r9, ML_M8(rsp, 0x20), ML_M8(rsp, 0x28))
    rsp -= 8; ML_M8(rsp, 0) = rbx;
    rsp = rsp - (0x20ULL);
{
    const uint64_t a = (uint64_t)(ML_M8(rcx, 0x0)) & ~0ULL, b = (uint64_t)(0x0ULL) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    rbx = rcx;
    if (!f_zf) goto L6;
    rax = ML_CALL(1418233c0);
L6:
    rcx = ML_M8(rbx, 0x8);
{
    const uint64_t a = (uint64_t)(ML_M1(rcx, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L12;
    rsp = rsp + (0x20ULL);
    { const uint64_t v = ML_M8(rsp, 0); rsp += 8; rbx = v; }
    return ML_CALL(1418233c0);   // tail call
L12:
    rax = ML_M8(rcx, 0x10);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L27;
    rcx = ML_M8(rax, 0x0);
{
    const uint64_t a = (uint64_t)(ML_M1(rcx, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L23;
    ;
L19:
    rax = rcx;
    rcx = ML_M8(rcx, 0x0);
{
    const uint64_t a = (uint64_t)(ML_M1(rcx, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L19;
L23:
    ML_M8(rbx, 0x8) = rax;
    rsp = rsp + (0x20ULL);
    { const uint64_t v = ML_M8(rsp, 0); rsp += 8; rbx = v; }
    return rax;
L27:
    rcx = ML_M8(rcx, 0x8);
{
    const uint64_t a = (uint64_t)(ML_M1(rcx, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L37;
L30:
    rax = ML_M8(rcx, 0x10);
{
    const uint64_t a = (uint64_t)(ML_M8(rbx, 0x8)) & ~0ULL, b = (uint64_t)(rax) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L37;
    ML_M8(rbx, 0x8) = rcx;
    rcx = ML_M8(rcx, 0x8);
{
    const uint64_t a = (uint64_t)(ML_M1(rcx, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L30;
L37:
    ML_M8(rbx, 0x8) = rcx;
    rsp = rsp + (0x20ULL);
    { const uint64_t v = ML_M8(rsp, 0); rsp += 8; rbx = v; }
    return rax;
#undef ML_CALL
    return rax;
}

uint64_t SynLift_141722fc0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A) {
    uint64_t rax = 0, rbx = 0, rbp = 0, rsi = 0, rdi = 0, r10 = 0, r11 = 0, r12 = 0, r13 = 0, r14 = 0, r15 = 0;
    uint64_t rcx = rcxA, rdx = rdxA, r8 = r8A, r9 = r9A;
    bool f_zf = false, f_cf = false, f_sf = false, f_of = false;
    uint8_t xmm0[16] = {0}, xmm1[16] = {0}, xmm2[16] = {0}, xmm3[16] = {0}, xmm4[16] = {0}, xmm5[16] = {0};
    alignas(16) uint8_t stkFrame[0x400] = {0};
    uint64_t rsp = (uint64_t)(uintptr_t)(stkFrame + 0x200);
#define ML_CALL(t) g_fnLIFT_##t(rcx, rdx, r8, r9, ML_M8(rsp, 0x20), ML_M8(rsp, 0x28))
    rsp -= 8; ML_M8(rsp, 0) = rbx;
    rsp = rsp - (0x20ULL);
{
    const uint64_t a = (uint64_t)(ML_M8(rcx, 0x0)) & ~0ULL, b = (uint64_t)(0x0ULL) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    rbx = rcx;
    if (!f_zf) goto L6;
    rax = ML_CALL(1418233c0);
L6:
    rcx = ML_M8(rbx, 0x8);
{
    const uint64_t a = (uint64_t)(ML_M1(rcx, 0x1d)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L12;
    rsp = rsp + (0x20ULL);
    { const uint64_t v = ML_M8(rsp, 0); rsp += 8; rbx = v; }
    return ML_CALL(1418233c0);   // tail call
L12:
    rax = ML_M8(rcx, 0x10);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x1d)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L27;
    rcx = ML_M8(rax, 0x0);
{
    const uint64_t a = (uint64_t)(ML_M1(rcx, 0x1d)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L23;
    ;
L19:
    rax = rcx;
    rcx = ML_M8(rcx, 0x0);
{
    const uint64_t a = (uint64_t)(ML_M1(rcx, 0x1d)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L19;
L23:
    ML_M8(rbx, 0x8) = rax;
    rsp = rsp + (0x20ULL);
    { const uint64_t v = ML_M8(rsp, 0); rsp += 8; rbx = v; }
    return rax;
L27:
    rcx = ML_M8(rcx, 0x8);
{
    const uint64_t a = (uint64_t)(ML_M1(rcx, 0x1d)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L37;
L30:
    rax = ML_M8(rcx, 0x10);
{
    const uint64_t a = (uint64_t)(ML_M8(rbx, 0x8)) & ~0ULL, b = (uint64_t)(rax) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L37;
    ML_M8(rbx, 0x8) = rcx;
    rcx = ML_M8(rcx, 0x8);
{
    const uint64_t a = (uint64_t)(ML_M1(rcx, 0x1d)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L30;
L37:
    ML_M8(rbx, 0x8) = rcx;
    rsp = rsp + (0x20ULL);
    { const uint64_t v = ML_M8(rsp, 0); rsp += 8; rbx = v; }
    return rax;
#undef ML_CALL
    return rax;
}

uint64_t SynLift_141723090(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A) {
    uint64_t rax = 0, rbx = 0, rbp = 0, rsi = 0, rdi = 0, r10 = 0, r11 = 0, r12 = 0, r13 = 0, r14 = 0, r15 = 0;
    uint64_t rcx = rcxA, rdx = rdxA, r8 = r8A, r9 = r9A;
    bool f_zf = false, f_cf = false, f_sf = false, f_of = false;
    uint8_t xmm0[16] = {0}, xmm1[16] = {0}, xmm2[16] = {0}, xmm3[16] = {0}, xmm4[16] = {0}, xmm5[16] = {0};
    alignas(16) uint8_t stkFrame[0x400] = {0};
    uint64_t rsp = (uint64_t)(uintptr_t)(stkFrame + 0x200);
#define ML_CALL(t) g_fnLIFT_##t(rcx, rdx, r8, r9, ML_M8(rsp, 0x20), ML_M8(rsp, 0x28))
    rsp -= 8; ML_M8(rsp, 0) = rbx;
    rsp = rsp - (0x20ULL);
{
    const uint64_t a = (uint64_t)(ML_M8(rcx, 0x0)) & ~0ULL, b = (uint64_t)(0x0ULL) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    rbx = rcx;
    if (!f_zf) goto L6;
    rax = ML_CALL(1418233c0);
L6:
    rcx = ML_M8(rbx, 0x8);
{
    const uint64_t a = (uint64_t)(ML_M1(rcx, 0x49)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L12;
    rsp = rsp + (0x20ULL);
    { const uint64_t v = ML_M8(rsp, 0); rsp += 8; rbx = v; }
    return ML_CALL(1418233c0);   // tail call
L12:
    rax = ML_M8(rcx, 0x10);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x49)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L27;
    rcx = ML_M8(rax, 0x0);
{
    const uint64_t a = (uint64_t)(ML_M1(rcx, 0x49)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L23;
    ;
L19:
    rax = rcx;
    rcx = ML_M8(rcx, 0x0);
{
    const uint64_t a = (uint64_t)(ML_M1(rcx, 0x49)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L19;
L23:
    ML_M8(rbx, 0x8) = rax;
    rsp = rsp + (0x20ULL);
    { const uint64_t v = ML_M8(rsp, 0); rsp += 8; rbx = v; }
    return rax;
L27:
    rcx = ML_M8(rcx, 0x8);
{
    const uint64_t a = (uint64_t)(ML_M1(rcx, 0x49)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L37;
L30:
    rax = ML_M8(rcx, 0x10);
{
    const uint64_t a = (uint64_t)(ML_M8(rbx, 0x8)) & ~0ULL, b = (uint64_t)(rax) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L37;
    ML_M8(rbx, 0x8) = rcx;
    rcx = ML_M8(rcx, 0x8);
{
    const uint64_t a = (uint64_t)(ML_M1(rcx, 0x49)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L30;
L37:
    ML_M8(rbx, 0x8) = rcx;
    rsp = rsp + (0x20ULL);
    { const uint64_t v = ML_M8(rsp, 0); rsp += 8; rbx = v; }
    return rax;
#undef ML_CALL
    return rax;
}

uint64_t SynLift_141723a50(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A) {
    uint64_t rax = 0, rbx = 0, rbp = 0, rsi = 0, rdi = 0, r10 = 0, r11 = 0, r12 = 0, r13 = 0, r14 = 0, r15 = 0;
    uint64_t rcx = rcxA, rdx = rdxA, r8 = r8A, r9 = r9A;
    bool f_zf = false, f_cf = false, f_sf = false, f_of = false;
    uint8_t xmm0[16] = {0}, xmm1[16] = {0}, xmm2[16] = {0}, xmm3[16] = {0}, xmm4[16] = {0}, xmm5[16] = {0};
    alignas(16) uint8_t stkFrame[0x400] = {0};
    uint64_t rsp = (uint64_t)(uintptr_t)(stkFrame + 0x200);
#define ML_CALL(t) g_fnLIFT_##t(rcx, rdx, r8, r9, ML_M8(rsp, 0x20), ML_M8(rsp, 0x28))
    rsp -= 8; ML_M8(rsp, 0) = rbx;
    rsp = rsp - (0x20ULL);
{
    const uint64_t a = (uint64_t)(ML_M8(rcx, 0x0)) & ~0ULL, b = (uint64_t)(0x0ULL) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    rbx = rcx;
    if (!f_zf) goto L6;
    rax = ML_CALL(1418233c0);
L6:
    rcx = ML_M8(rbx, 0x8);
{
    const uint64_t a = (uint64_t)(ML_M1(rcx, 0x1b)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L12;
    rsp = rsp + (0x20ULL);
    { const uint64_t v = ML_M8(rsp, 0); rsp += 8; rbx = v; }
    return ML_CALL(1418233c0);   // tail call
L12:
    rax = ML_M8(rcx, 0x10);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x1b)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L27;
    rcx = ML_M8(rax, 0x0);
{
    const uint64_t a = (uint64_t)(ML_M1(rcx, 0x1b)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L23;
    ;
L19:
    rax = rcx;
    rcx = ML_M8(rcx, 0x0);
{
    const uint64_t a = (uint64_t)(ML_M1(rcx, 0x1b)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L19;
L23:
    ML_M8(rbx, 0x8) = rax;
    rsp = rsp + (0x20ULL);
    { const uint64_t v = ML_M8(rsp, 0); rsp += 8; rbx = v; }
    return rax;
L27:
    rcx = ML_M8(rcx, 0x8);
{
    const uint64_t a = (uint64_t)(ML_M1(rcx, 0x1b)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L37;
L30:
    rax = ML_M8(rcx, 0x10);
{
    const uint64_t a = (uint64_t)(ML_M8(rbx, 0x8)) & ~0ULL, b = (uint64_t)(rax) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L37;
    ML_M8(rbx, 0x8) = rcx;
    rcx = ML_M8(rcx, 0x8);
{
    const uint64_t a = (uint64_t)(ML_M1(rcx, 0x1b)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L30;
L37:
    ML_M8(rbx, 0x8) = rcx;
    rsp = rsp + (0x20ULL);
    { const uint64_t v = ML_M8(rsp, 0); rsp += 8; rbx = v; }
    return rax;
#undef ML_CALL
    return rax;
}

uint64_t SynLift_141724870(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A) {
    uint64_t rax = 0, rbx = 0, rbp = 0, rsi = 0, rdi = 0, r10 = 0, r11 = 0, r12 = 0, r13 = 0, r14 = 0, r15 = 0;
    uint64_t rcx = rcxA, rdx = rdxA, r8 = r8A, r9 = r9A;
    bool f_zf = false, f_cf = false, f_sf = false, f_of = false;
    uint8_t xmm0[16] = {0}, xmm1[16] = {0}, xmm2[16] = {0}, xmm3[16] = {0}, xmm4[16] = {0}, xmm5[16] = {0};
    alignas(16) uint8_t stkFrame[0x400] = {0};
    uint64_t rsp = (uint64_t)(uintptr_t)(stkFrame + 0x200);
#define ML_CALL(t) g_fnLIFT_##t(rcx, rdx, r8, r9, ML_M8(rsp, 0x20), ML_M8(rsp, 0x28))
    r8 = ML_M8(rdx, 0x10);
    rax = ML_M8(r8, 0x0);
    ML_M8(rdx, 0x10) = rax;
    rax = ML_M8(r8, 0x0);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L7;
    ML_M8(rax, 0x8) = rdx;
L7:
    rax = ML_M8(rdx, 0x8);
    ML_M8(r8, 0x8) = rax;
    rax = ML_M8(rcx, 0x30);
{
    const uint64_t a = (uint64_t)(rdx) & ~0ULL, b = (uint64_t)(ML_M8(rax, 0x8)) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L16;
    ML_M8(rax, 0x8) = r8;
    ML_M8(r8, 0x0) = rdx;
    ML_M8(rdx, 0x8) = r8;
    return rax;
L16:
    rax = ML_M8(rdx, 0x8);
{
    const uint64_t a = (uint64_t)(rdx) & ~0ULL, b = (uint64_t)(ML_M8(rax, 0x0)) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L23;
    ML_M8(rax, 0x0) = r8;
    ML_M8(r8, 0x0) = rdx;
    ML_M8(rdx, 0x8) = r8;
    return rax;
L23:
    ML_M8(rax, 0x10) = r8;
    ML_M8(r8, 0x0) = rdx;
    ML_M8(rdx, 0x8) = r8;
    return rax;
#undef ML_CALL
    return rax;
}

uint64_t SynLift_141724950(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A) {
    uint64_t rax = 0, rbx = 0, rbp = 0, rsi = 0, rdi = 0, r10 = 0, r11 = 0, r12 = 0, r13 = 0, r14 = 0, r15 = 0;
    uint64_t rcx = rcxA, rdx = rdxA, r8 = r8A, r9 = r9A;
    bool f_zf = false, f_cf = false, f_sf = false, f_of = false;
    uint8_t xmm0[16] = {0}, xmm1[16] = {0}, xmm2[16] = {0}, xmm3[16] = {0}, xmm4[16] = {0}, xmm5[16] = {0};
    alignas(16) uint8_t stkFrame[0x400] = {0};
    uint64_t rsp = (uint64_t)(uintptr_t)(stkFrame + 0x200);
#define ML_CALL(t) g_fnLIFT_##t(rcx, rdx, r8, r9, ML_M8(rsp, 0x20), ML_M8(rsp, 0x28))
    r8 = ML_M8(rdx, 0x10);
    rax = ML_M8(r8, 0x0);
    ML_M8(rdx, 0x10) = rax;
    rax = ML_M8(r8, 0x0);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x49)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L7;
    ML_M8(rax, 0x8) = rdx;
L7:
    rax = ML_M8(rdx, 0x8);
    ML_M8(r8, 0x8) = rax;
    rax = ML_M8(rcx, 0x30);
{
    const uint64_t a = (uint64_t)(rdx) & ~0ULL, b = (uint64_t)(ML_M8(rax, 0x8)) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L16;
    ML_M8(rax, 0x8) = r8;
    ML_M8(r8, 0x0) = rdx;
    ML_M8(rdx, 0x8) = r8;
    return rax;
L16:
    rax = ML_M8(rdx, 0x8);
{
    const uint64_t a = (uint64_t)(rdx) & ~0ULL, b = (uint64_t)(ML_M8(rax, 0x0)) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L23;
    ML_M8(rax, 0x0) = r8;
    ML_M8(r8, 0x0) = rdx;
    ML_M8(rdx, 0x8) = r8;
    return rax;
L23:
    ML_M8(rax, 0x10) = r8;
    ML_M8(r8, 0x0) = rdx;
    ML_M8(rdx, 0x8) = r8;
    return rax;
#undef ML_CALL
    return rax;
}

uint64_t SynLift_1417249e0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A) {
    uint64_t rax = 0, rbx = 0, rbp = 0, rsi = 0, rdi = 0, r10 = 0, r11 = 0, r12 = 0, r13 = 0, r14 = 0, r15 = 0;
    uint64_t rcx = rcxA, rdx = rdxA, r8 = r8A, r9 = r9A;
    bool f_zf = false, f_cf = false, f_sf = false, f_of = false;
    uint8_t xmm0[16] = {0}, xmm1[16] = {0}, xmm2[16] = {0}, xmm3[16] = {0}, xmm4[16] = {0}, xmm5[16] = {0};
    alignas(16) uint8_t stkFrame[0x400] = {0};
    uint64_t rsp = (uint64_t)(uintptr_t)(stkFrame + 0x200);
#define ML_CALL(t) g_fnLIFT_##t(rcx, rdx, r8, r9, ML_M8(rsp, 0x20), ML_M8(rsp, 0x28))
    r8 = ML_M8(rdx, 0x10);
    rax = ML_M8(r8, 0x0);
    ML_M8(rdx, 0x10) = rax;
    rax = ML_M8(r8, 0x0);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x1d)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L7;
    ML_M8(rax, 0x8) = rdx;
L7:
    rax = ML_M8(rdx, 0x8);
    ML_M8(r8, 0x8) = rax;
    rax = ML_M8(rcx, 0x30);
{
    const uint64_t a = (uint64_t)(rdx) & ~0ULL, b = (uint64_t)(ML_M8(rax, 0x8)) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L16;
    ML_M8(rax, 0x8) = r8;
    ML_M8(r8, 0x0) = rdx;
    ML_M8(rdx, 0x8) = r8;
    return rax;
L16:
    rax = ML_M8(rdx, 0x8);
{
    const uint64_t a = (uint64_t)(rdx) & ~0ULL, b = (uint64_t)(ML_M8(rax, 0x0)) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L23;
    ML_M8(rax, 0x0) = r8;
    ML_M8(r8, 0x0) = rdx;
    ML_M8(rdx, 0x8) = r8;
    return rax;
L23:
    ML_M8(rax, 0x10) = r8;
    ML_M8(r8, 0x0) = rdx;
    ML_M8(rdx, 0x8) = r8;
    return rax;
#undef ML_CALL
    return rax;
}

uint64_t SynLift_141724c50(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A) {
    uint64_t rax = 0, rbx = 0, rbp = 0, rsi = 0, rdi = 0, r10 = 0, r11 = 0, r12 = 0, r13 = 0, r14 = 0, r15 = 0;
    uint64_t rcx = rcxA, rdx = rdxA, r8 = r8A, r9 = r9A;
    bool f_zf = false, f_cf = false, f_sf = false, f_of = false;
    uint8_t xmm0[16] = {0}, xmm1[16] = {0}, xmm2[16] = {0}, xmm3[16] = {0}, xmm4[16] = {0}, xmm5[16] = {0};
    alignas(16) uint8_t stkFrame[0x400] = {0};
    uint64_t rsp = (uint64_t)(uintptr_t)(stkFrame + 0x200);
#define ML_CALL(t) g_fnLIFT_##t(rcx, rdx, r8, r9, ML_M8(rsp, 0x20), ML_M8(rsp, 0x28))
    r8 = ML_M8(rdx, 0x10);
    rax = ML_M8(r8, 0x0);
    ML_M8(rdx, 0x10) = rax;
    rax = ML_M8(r8, 0x0);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x1d)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L7;
    ML_M8(rax, 0x8) = rdx;
L7:
    rax = ML_M8(rdx, 0x8);
    ML_M8(r8, 0x8) = rax;
    rax = ML_M8(rcx, 0x30);
{
    const uint64_t a = (uint64_t)(rdx) & ~0ULL, b = (uint64_t)(ML_M8(rax, 0x8)) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L16;
    ML_M8(rax, 0x8) = r8;
    ML_M8(r8, 0x0) = rdx;
    ML_M8(rdx, 0x8) = r8;
    return rax;
L16:
    rax = ML_M8(rdx, 0x8);
{
    const uint64_t a = (uint64_t)(rdx) & ~0ULL, b = (uint64_t)(ML_M8(rax, 0x0)) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L23;
    ML_M8(rax, 0x0) = r8;
    ML_M8(r8, 0x0) = rdx;
    ML_M8(rdx, 0x8) = r8;
    return rax;
L23:
    ML_M8(rax, 0x10) = r8;
    ML_M8(r8, 0x0) = rdx;
    ML_M8(rdx, 0x8) = r8;
    return rax;
#undef ML_CALL
    return rax;
}

uint64_t SynLift_141724cb0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A) {
    uint64_t rax = 0, rbx = 0, rbp = 0, rsi = 0, rdi = 0, r10 = 0, r11 = 0, r12 = 0, r13 = 0, r14 = 0, r15 = 0;
    uint64_t rcx = rcxA, rdx = rdxA, r8 = r8A, r9 = r9A;
    bool f_zf = false, f_cf = false, f_sf = false, f_of = false;
    uint8_t xmm0[16] = {0}, xmm1[16] = {0}, xmm2[16] = {0}, xmm3[16] = {0}, xmm4[16] = {0}, xmm5[16] = {0};
    alignas(16) uint8_t stkFrame[0x400] = {0};
    uint64_t rsp = (uint64_t)(uintptr_t)(stkFrame + 0x200);
#define ML_CALL(t) g_fnLIFT_##t(rcx, rdx, r8, r9, ML_M8(rsp, 0x20), ML_M8(rsp, 0x28))
    r8 = ML_M8(rdx, 0x0);
    rax = ML_M8(r8, 0x10);
    ML_M8(rdx, 0x0) = rax;
    rax = ML_M8(r8, 0x10);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x1d)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L7;
    ML_M8(rax, 0x8) = rdx;
L7:
    rax = ML_M8(rdx, 0x8);
    ML_M8(r8, 0x8) = rax;
    rax = ML_M8(rcx, 0x30);
{
    const uint64_t a = (uint64_t)(rdx) & ~0ULL, b = (uint64_t)(ML_M8(rax, 0x8)) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L16;
    ML_M8(rax, 0x8) = r8;
    ML_M8(r8, 0x10) = rdx;
    ML_M8(rdx, 0x8) = r8;
    return rax;
L16:
    rax = ML_M8(rdx, 0x8);
{
    const uint64_t a = (uint64_t)(rdx) & ~0ULL, b = (uint64_t)(ML_M8(rax, 0x10)) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L23;
    ML_M8(rax, 0x10) = r8;
    ML_M8(r8, 0x10) = rdx;
    ML_M8(rdx, 0x8) = r8;
    return rax;
L23:
    ML_M8(rax, 0x0) = r8;
    ML_M8(r8, 0x10) = rdx;
    ML_M8(rdx, 0x8) = r8;
    return rax;
#undef ML_CALL
    return rax;
}

uint64_t SynLift_141724ed0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A) {
    uint64_t rax = 0, rbx = 0, rbp = 0, rsi = 0, rdi = 0, r10 = 0, r11 = 0, r12 = 0, r13 = 0, r14 = 0, r15 = 0;
    uint64_t rcx = rcxA, rdx = rdxA, r8 = r8A, r9 = r9A;
    bool f_zf = false, f_cf = false, f_sf = false, f_of = false;
    uint8_t xmm0[16] = {0}, xmm1[16] = {0}, xmm2[16] = {0}, xmm3[16] = {0}, xmm4[16] = {0}, xmm5[16] = {0};
    alignas(16) uint8_t stkFrame[0x400] = {0};
    uint64_t rsp = (uint64_t)(uintptr_t)(stkFrame + 0x200);
#define ML_CALL(t) g_fnLIFT_##t(rcx, rdx, r8, r9, ML_M8(rsp, 0x20), ML_M8(rsp, 0x28))
    rsp -= 8; ML_M8(rsp, 0) = rbx;
    rsp = rsp - (0x20ULL);
{
    const uint64_t a = (uint64_t)(ML_M8(rcx, 0x0)) & ~0ULL, b = (uint64_t)(0x0ULL) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    rbx = rcx;
    if (!f_zf) goto L6;
    rax = ML_CALL(1418233c0);
L6:
    rcx = ML_M8(rbx, 0x8);
{
    const uint64_t a = (uint64_t)(ML_M1(rcx, 0x1d)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L12;
    rsp = rsp + (0x20ULL);
    { const uint64_t v = ML_M8(rsp, 0); rsp += 8; rbx = v; }
    return ML_CALL(1418233c0);   // tail call
L12:
    rax = ML_M8(rcx, 0x10);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x1d)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L27;
    rcx = ML_M8(rax, 0x0);
{
    const uint64_t a = (uint64_t)(ML_M1(rcx, 0x1d)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L23;
    ;
L19:
    rax = rcx;
    rcx = ML_M8(rcx, 0x0);
{
    const uint64_t a = (uint64_t)(ML_M1(rcx, 0x1d)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L19;
L23:
    ML_M8(rbx, 0x8) = rax;
    rsp = rsp + (0x20ULL);
    { const uint64_t v = ML_M8(rsp, 0); rsp += 8; rbx = v; }
    return rax;
L27:
    rcx = ML_M8(rcx, 0x8);
{
    const uint64_t a = (uint64_t)(ML_M1(rcx, 0x1d)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L37;
L30:
    rax = ML_M8(rcx, 0x10);
{
    const uint64_t a = (uint64_t)(ML_M8(rbx, 0x8)) & ~0ULL, b = (uint64_t)(rax) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L37;
    ML_M8(rbx, 0x8) = rcx;
    rcx = ML_M8(rcx, 0x8);
{
    const uint64_t a = (uint64_t)(ML_M1(rcx, 0x1d)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L30;
L37:
    ML_M8(rbx, 0x8) = rcx;
    rsp = rsp + (0x20ULL);
    { const uint64_t v = ML_M8(rsp, 0); rsp += 8; rbx = v; }
    return rax;
#undef ML_CALL
    return rax;
}

uint64_t SynLift_141725000(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A) {
    uint64_t rax = 0, rbx = 0, rbp = 0, rsi = 0, rdi = 0, r10 = 0, r11 = 0, r12 = 0, r13 = 0, r14 = 0, r15 = 0;
    uint64_t rcx = rcxA, rdx = rdxA, r8 = r8A, r9 = r9A;
    bool f_zf = false, f_cf = false, f_sf = false, f_of = false;
    uint8_t xmm0[16] = {0}, xmm1[16] = {0}, xmm2[16] = {0}, xmm3[16] = {0}, xmm4[16] = {0}, xmm5[16] = {0};
    alignas(16) uint8_t stkFrame[0x400] = {0};
    uint64_t rsp = (uint64_t)(uintptr_t)(stkFrame + 0x200);
#define ML_CALL(t) g_fnLIFT_##t(rcx, rdx, r8, r9, ML_M8(rsp, 0x20), ML_M8(rsp, 0x28))
    r8 = ML_M8(rdx, 0x10);
    rax = ML_M8(r8, 0x0);
    ML_M8(rdx, 0x10) = rax;
    rax = ML_M8(r8, 0x0);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x1b)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L7;
    ML_M8(rax, 0x8) = rdx;
L7:
    rax = ML_M8(rdx, 0x8);
    ML_M8(r8, 0x8) = rax;
    rax = ML_M8(rcx, 0x30);
{
    const uint64_t a = (uint64_t)(rdx) & ~0ULL, b = (uint64_t)(ML_M8(rax, 0x8)) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L16;
    ML_M8(rax, 0x8) = r8;
    ML_M8(r8, 0x0) = rdx;
    ML_M8(rdx, 0x8) = r8;
    return rax;
L16:
    rax = ML_M8(rdx, 0x8);
{
    const uint64_t a = (uint64_t)(rdx) & ~0ULL, b = (uint64_t)(ML_M8(rax, 0x0)) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L23;
    ML_M8(rax, 0x0) = r8;
    ML_M8(r8, 0x0) = rdx;
    ML_M8(rdx, 0x8) = r8;
    return rax;
L23:
    ML_M8(rax, 0x10) = r8;
    ML_M8(r8, 0x0) = rdx;
    ML_M8(rdx, 0x8) = r8;
    return rax;
#undef ML_CALL
    return rax;
}

uint64_t SynLift_141725060(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A) {
    uint64_t rax = 0, rbx = 0, rbp = 0, rsi = 0, rdi = 0, r10 = 0, r11 = 0, r12 = 0, r13 = 0, r14 = 0, r15 = 0;
    uint64_t rcx = rcxA, rdx = rdxA, r8 = r8A, r9 = r9A;
    bool f_zf = false, f_cf = false, f_sf = false, f_of = false;
    uint8_t xmm0[16] = {0}, xmm1[16] = {0}, xmm2[16] = {0}, xmm3[16] = {0}, xmm4[16] = {0}, xmm5[16] = {0};
    alignas(16) uint8_t stkFrame[0x400] = {0};
    uint64_t rsp = (uint64_t)(uintptr_t)(stkFrame + 0x200);
#define ML_CALL(t) g_fnLIFT_##t(rcx, rdx, r8, r9, ML_M8(rsp, 0x20), ML_M8(rsp, 0x28))
    r8 = ML_M8(rdx, 0x0);
    rax = ML_M8(r8, 0x10);
    ML_M8(rdx, 0x0) = rax;
    rax = ML_M8(r8, 0x10);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x1b)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L7;
    ML_M8(rax, 0x8) = rdx;
L7:
    rax = ML_M8(rdx, 0x8);
    ML_M8(r8, 0x8) = rax;
    rax = ML_M8(rcx, 0x30);
{
    const uint64_t a = (uint64_t)(rdx) & ~0ULL, b = (uint64_t)(ML_M8(rax, 0x8)) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L16;
    ML_M8(rax, 0x8) = r8;
    ML_M8(r8, 0x10) = rdx;
    ML_M8(rdx, 0x8) = r8;
    return rax;
L16:
    rax = ML_M8(rdx, 0x8);
{
    const uint64_t a = (uint64_t)(rdx) & ~0ULL, b = (uint64_t)(ML_M8(rax, 0x10)) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L23;
    ML_M8(rax, 0x10) = r8;
    ML_M8(r8, 0x10) = rdx;
    ML_M8(rdx, 0x8) = r8;
    return rax;
L23:
    ML_M8(rax, 0x0) = r8;
    ML_M8(r8, 0x10) = rdx;
    ML_M8(rdx, 0x8) = r8;
    return rax;
#undef ML_CALL
    return rax;
}

__attribute__((weak)) uint64_t (*g_fnLIFT_141724c50)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t) = nullptr;
__attribute__((weak)) uint64_t (*g_fnLIFT_141724cb0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t) = nullptr;
__attribute__((weak)) uint64_t (*g_fnLIFT_141724ed0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t) = nullptr;
__attribute__((weak)) uint64_t (*g_fnLIFT_1417f2fdc)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t) = nullptr;
__attribute__((weak)) uint64_t (*g_fnLIFT_1417f3154)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t) = nullptr;
__attribute__((weak)) uint64_t (*g_fnLIFT_141823270)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t) = nullptr;
__attribute__((weak)) uint64_t (*g_fnLIFT_141823288)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t) = nullptr;
__attribute__((weak)) uint64_t (*g_fnLIFT_1418233f8)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t) = nullptr;
uint64_t SynLift_141728290(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A) {
    uint64_t rax = 0, rbx = 0, rbp = 0, rsi = 0, rdi = 0, r10 = 0, r11 = 0, r12 = 0, r13 = 0, r14 = 0, r15 = 0;
    uint64_t rcx = rcxA, rdx = rdxA, r8 = r8A, r9 = r9A;
    bool f_zf = false, f_cf = false, f_sf = false, f_of = false;
    uint8_t xmm0[16] = {0}, xmm1[16] = {0}, xmm2[16] = {0}, xmm3[16] = {0}, xmm4[16] = {0}, xmm5[16] = {0};
    alignas(16) uint8_t stkFrame[0x400] = {0};
    uint64_t rsp = (uint64_t)(uintptr_t)(stkFrame + 0x200);
#define ML_CALL(t) g_fnLIFT_##t(rcx, rdx, r8, r9, ML_M8(rsp, 0x20), ML_M8(rsp, 0x28))
    rax = rsp;
    rsp -= 8; ML_M8(rsp, 0) = rdi;
    rsp -= 8; ML_M8(rsp, 0) = r12;
    rsp -= 8; ML_M8(rsp, 0) = r13;
    rsp = rsp - (0xa0ULL);
    ML_M8(rsp, 0x30) = 0xfffffffffffffffeULL;
    ML_M8(rax, 0x8) = rbx;
    ML_M8(rax, 0x10) = rbp;
    ML_M8(rax, 0x18) = rsi;
    r12 = r8;
    r13 = rdx;
    rbp = rcx;
    rsi = ML_M8(r8, 0x8);
{
    const uint64_t a = (uint64_t)(ML_M1(rsi, 0x1d)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L30;
    rdx = (uintptr_t)0x141825ca8;
    rcx = rax - 0x40;
    rax = ML_CALL(141823270);
    rcx = rsp + 0x38;
    rax = ML_CALL(1418233f8);
    rax = (uintptr_t)0x141824a60;
    ML_M8(rsp, 0x38) = rax;
    rdx = rsp + 0x78;
    rcx = rsp + 0x50;
    rax = ML_CALL(141823288);
    rax = (uintptr_t)0x141824ba0;
    ML_M8(rsp, 0x38) = rax;
    rdx = (uintptr_t)0x141881e50;
    rcx = rsp + 0x38;
    rax = ML_CALL(1417f3154);
L30:
    rcx = r8;
    rax = ML_CALL(141724ed0);
    r11 = ML_M8(rsi, 0x0);
{
    const uint64_t a = (uint64_t)(ML_M1(r11, 0x1d)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L37;
    rdi = ML_M8(rsi, 0x10);
    goto L46;
L37:
    rax = ML_M8(rsi, 0x10);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x1d)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L42;
    rdi = r11;
    goto L46;
L42:
    rcx = ML_M8(r12, 0x8);
    rdi = ML_M8(rcx, 0x10);
{
    const uint64_t a = (uint64_t)(rcx) & ~0ULL, b = (uint64_t)(rsi) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L93;
L46:
    rbx = ML_M8(rsi, 0x8);
{
    const uint64_t a = (uint64_t)(ML_M1(rdi, 0x1d)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L50;
    ML_M8(rdi, 0x8) = rbx;
L50:
    rax = ML_M8(rbp, 0x30);
{
    const uint64_t a = (uint64_t)(ML_M8(rax, 0x8)) & ~0ULL, b = (uint64_t)(rsi) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L55;
    ML_M8(rax, 0x8) = rdi;
    goto L60;
L55:
{
    const uint64_t a = (uint64_t)(ML_M8(rbx, 0x0)) & ~0ULL, b = (uint64_t)(rsi) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L59;
    ML_M8(rbx, 0x0) = rdi;
    goto L60;
L59:
    ML_M8(rbx, 0x10) = rdi;
L60:
    rdx = ML_M8(rbp, 0x30);
{
    const uint64_t a = (uint64_t)(ML_M8(rdx, 0x0)) & ~0ULL, b = (uint64_t)(rsi) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L76;
{
    const uint64_t a = (uint64_t)(ML_M1(rdi, 0x1d)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L67;
    rcx = rbx;
    goto L75;
L67:
    rcx = rdi;
    rax = ML_M8(rdi, 0x0);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x1d)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L75;
L71:
    rcx = rax;
    rax = ML_M8(rax, 0x0);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x1d)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L71;
L75:
    ML_M8(rdx, 0x0) = rcx;
L76:
    rdx = ML_M8(rbp, 0x30);
{
    const uint64_t a = (uint64_t)(ML_M8(rdx, 0x10)) & ~0ULL, b = (uint64_t)(rsi) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L130;
{
    const uint64_t a = (uint64_t)(ML_M1(rdi, 0x1d)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L83;
    rcx = rbx;
    goto L91;
L83:
    rcx = rdi;
    rax = ML_M8(rdi, 0x10);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x1d)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L91;
L87:
    rcx = rax;
    rax = ML_M8(rax, 0x10);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x1d)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L87;
L91:
    ML_M8(rdx, 0x10) = rcx;
    goto L130;
L93:
    ML_M8(r11, 0x8) = rcx;
    rax = ML_M8(rsi, 0x0);
    ML_M8(rcx, 0x0) = rax;
{
    const uint64_t a = (uint64_t)(rcx) & ~0ULL, b = (uint64_t)(ML_M8(rsi, 0x10)) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L100;
    rbx = rcx;
    goto L109;
L100:
    rbx = ML_M8(rcx, 0x8);
{
    const uint64_t a = (uint64_t)(ML_M1(rdi, 0x1d)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L104;
    ML_M8(rdi, 0x8) = rbx;
L104:
    ML_M8(rbx, 0x0) = rdi;
    rax = ML_M8(rsi, 0x10);
    ML_M8(rcx, 0x10) = rax;
    rax = ML_M8(rsi, 0x10);
    ML_M8(rax, 0x8) = rcx;
L109:
    rax = ML_M8(rbp, 0x30);
{
    const uint64_t a = (uint64_t)(ML_M8(rax, 0x8)) & ~0ULL, b = (uint64_t)(rsi) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L114;
    ML_M8(rax, 0x8) = rcx;
    goto L120;
L114:
    rax = ML_M8(rsi, 0x8);
{
    const uint64_t a = (uint64_t)(ML_M8(rax, 0x0)) & ~0ULL, b = (uint64_t)(rsi) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L119;
    ML_M8(rax, 0x0) = rcx;
    goto L120;
L119:
    ML_M8(rax, 0x10) = rcx;
L120:
    rax = ML_M8(rsi, 0x8);
    ML_M8(rcx, 0x8) = rax;
    rdx = rsi + 0x1c;
    r8 = rcx + 0x1c;
{
    const uint64_t a = (uint64_t)(r8) & ~0ULL, b = (uint64_t)(rdx) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (f_zf) goto L130;
    rcx = ML_M1(r8, 0x0);
    rax = ML_M1(rdx, 0x0);
    ML_M1(r8, 0x0) = (uint8_t)rax;
    ML_M1(rdx, 0x0) = (uint8_t)rcx;
L130:
{
    const uint64_t a = (uint64_t)(ML_M1(rsi, 0x1c)) & 0xFFULL, b = (uint64_t)(0x1ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L225;
    rax = ML_M8(rbp, 0x30);
{
    const uint64_t a = (uint64_t)(rdi) & ~0ULL, b = (uint64_t)(ML_M8(rax, 0x8)) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (f_zf) goto L224;
L135:
{
    const uint64_t a = (uint64_t)(ML_M1(rdi, 0x1c)) & 0xFFULL, b = (uint64_t)(0x1ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L224;
    rcx = ML_M8(rbx, 0x0);
{
    const uint64_t a = (uint64_t)(rdi) & ~0ULL, b = (uint64_t)(rcx) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L162;
    rcx = ML_M8(rbx, 0x10);
{
    const uint64_t a = (uint64_t)(ML_M1(rcx, 0x1c)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L149;
    ML_M1(rcx, 0x1c) = 0x1ULL;
    ML_M1(rbx, 0x1c) = 0x0ULL;
    rdx = rbx;
    rcx = rbp;
    rax = ML_CALL(141724c50);
    rcx = ML_M8(rbx, 0x10);
L149:
{
    const uint64_t a = (uint64_t)(ML_M1(rcx, 0x1d)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L153;
    rdi = rbx;
    goto L182;
L153:
    rax = ML_M8(rcx, 0x0);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x1c)) & 0xFFULL, b = (uint64_t)(0x1ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L187;
    rax = ML_M8(rcx, 0x10);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x1c)) & 0xFFULL, b = (uint64_t)(0x1ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L187;
    ML_M1(rcx, 0x1c) = 0x0ULL;
    rdi = rbx;
    goto L182;
L162:
{
    const uint64_t a = (uint64_t)(ML_M1(rcx, 0x1c)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L170;
    ML_M1(rcx, 0x1c) = 0x1ULL;
    ML_M1(rbx, 0x1c) = 0x0ULL;
    rdx = rbx;
    rcx = rbp;
    rax = ML_CALL(141724cb0);
    rcx = ML_M8(rbx, 0x0);
L170:
{
    const uint64_t a = (uint64_t)(ML_M1(rcx, 0x1d)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L174;
    rdi = rbx;
    goto L182;
L174:
    rax = ML_M8(rcx, 0x10);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x1c)) & 0xFFULL, b = (uint64_t)(0x1ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L206;
    rax = ML_M8(rcx, 0x0);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x1c)) & 0xFFULL, b = (uint64_t)(0x1ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L206;
    ML_M1(rcx, 0x1c) = 0x0ULL;
    rdi = rbx;
L182:
    rbx = ML_M8(rbx, 0x8);
    rax = ML_M8(rbp, 0x30);
{
    const uint64_t a = (uint64_t)(rdi) & ~0ULL, b = (uint64_t)(ML_M8(rax, 0x8)) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (f_zf) goto L224;
    goto L135;
L187:
    rax = ML_M8(rcx, 0x10);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x1c)) & 0xFFULL, b = (uint64_t)(0x1ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L197;
    rax = ML_M8(rcx, 0x0);
    ML_M1(rax, 0x1c) = 0x1ULL;
    ML_M1(rcx, 0x1c) = 0x0ULL;
    rdx = rcx;
    rcx = rbp;
    rax = ML_CALL(141724cb0);
    rcx = ML_M8(rbx, 0x10);
L197:
    rax = ML_M1(rbx, 0x1c);
    ML_M1(rcx, 0x1c) = (uint8_t)rax;
    ML_M1(rbx, 0x1c) = 0x1ULL;
    rax = ML_M8(rcx, 0x10);
    ML_M1(rax, 0x1c) = 0x1ULL;
    rdx = rbx;
    rcx = rbp;
    rax = ML_CALL(141724c50);
    goto L224;
L206:
    rax = ML_M8(rcx, 0x0);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x1c)) & 0xFFULL, b = (uint64_t)(0x1ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L216;
    rax = ML_M8(rcx, 0x10);
    ML_M1(rax, 0x1c) = 0x1ULL;
    ML_M1(rcx, 0x1c) = 0x0ULL;
    rdx = rcx;
    rcx = rbp;
    rax = ML_CALL(141724c50);
    rcx = ML_M8(rbx, 0x0);
L216:
    rax = ML_M1(rbx, 0x1c);
    ML_M1(rcx, 0x1c) = (uint8_t)rax;
    ML_M1(rbx, 0x1c) = 0x1ULL;
    rax = ML_M8(rcx, 0x0);
    ML_M1(rax, 0x1c) = 0x1ULL;
    rdx = rbx;
    rcx = rbp;
    rax = ML_CALL(141724cb0);
L224:
    ML_M1(rdi, 0x1c) = 0x1ULL;
L225:
    rcx = rsi;
    rax = ML_CALL(1417f2fdc);
    rax = ML_M8(rbp, 0x38);
{
    const uint64_t r = ((uint64_t)(rax) & ~0ULL) & ((uint64_t)(rax) & ~0ULL);
    f_zf = (r == 0); f_cf = false; f_sf = ((r & 0x8000000000000000ULL) != 0);
    f_of = false;
}
    if (f_zf) goto L232;
    rax = rax - 1;
    ML_M8(rbp, 0x38) = rax;
L232:
    rcx = rsp + 0x20;
    rax = ML_M8(r12, 0x0);
    ML_M8(rcx, 0x0) = rax;
    rax = ML_M8(r12, 0x8);
    ML_M8(rcx, 0x8) = rax;
    rax = ML_M8(rsp, 0x28);
    ML_M8(rsp, 0x28) = rax;
    rax = ML_M8(rbp, 0x0);
    ML_M8(rsp, 0x20) = rax;
    rcx = rsp + 0x20;
    rax = ML_M8(rcx, 0x0);
    ML_M8(r13, 0x0) = rax;
    rax = ML_M8(rcx, 0x8);
    ML_M8(r13, 0x8) = rax;
    rax = r13;
    r11 = rsp + 0xa0;
    rbx = ML_M8(r11, 0x20);
    rbp = ML_M8(r11, 0x28);
    rsi = ML_M8(r11, 0x30);
    rsp = r11;
    { const uint64_t v = ML_M8(rsp, 0); rsp += 8; r13 = v; }
    { const uint64_t v = ML_M8(rsp, 0); rsp += 8; r12 = v; }
    { const uint64_t v = ML_M8(rsp, 0); rsp += 8; rdi = v; }
    return rax;
#undef ML_CALL
    return rax;
}

__attribute__((weak)) uint64_t (*g_fnLIFT_141723a50)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t) = nullptr;
__attribute__((weak)) uint64_t (*g_fnLIFT_141725000)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t) = nullptr;
__attribute__((weak)) uint64_t (*g_fnLIFT_141725060)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t) = nullptr;
uint64_t SynLift_141728750(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A) {
    uint64_t rax = 0, rbx = 0, rbp = 0, rsi = 0, rdi = 0, r10 = 0, r11 = 0, r12 = 0, r13 = 0, r14 = 0, r15 = 0;
    uint64_t rcx = rcxA, rdx = rdxA, r8 = r8A, r9 = r9A;
    bool f_zf = false, f_cf = false, f_sf = false, f_of = false;
    uint8_t xmm0[16] = {0}, xmm1[16] = {0}, xmm2[16] = {0}, xmm3[16] = {0}, xmm4[16] = {0}, xmm5[16] = {0};
    alignas(16) uint8_t stkFrame[0x400] = {0};
    uint64_t rsp = (uint64_t)(uintptr_t)(stkFrame + 0x200);
#define ML_CALL(t) g_fnLIFT_##t(rcx, rdx, r8, r9, ML_M8(rsp, 0x20), ML_M8(rsp, 0x28))
    rax = rsp;
    rsp -= 8; ML_M8(rsp, 0) = rdi;
    rsp -= 8; ML_M8(rsp, 0) = r12;
    rsp -= 8; ML_M8(rsp, 0) = r13;
    rsp = rsp - (0xa0ULL);
    ML_M8(rsp, 0x30) = 0xfffffffffffffffeULL;
    ML_M8(rax, 0x8) = rbx;
    ML_M8(rax, 0x10) = rbp;
    ML_M8(rax, 0x18) = rsi;
    r12 = r8;
    r13 = rdx;
    rbp = rcx;
    rsi = ML_M8(r8, 0x8);
{
    const uint64_t a = (uint64_t)(ML_M1(rsi, 0x1b)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L30;
    rdx = (uintptr_t)0x141825ca8;
    rcx = rax - 0x40;
    rax = ML_CALL(141823270);
    rcx = rsp + 0x38;
    rax = ML_CALL(1418233f8);
    rax = (uintptr_t)0x141824a60;
    ML_M8(rsp, 0x38) = rax;
    rdx = rsp + 0x78;
    rcx = rsp + 0x50;
    rax = ML_CALL(141823288);
    rax = (uintptr_t)0x141824ba0;
    ML_M8(rsp, 0x38) = rax;
    rdx = (uintptr_t)0x141881e50;
    rcx = rsp + 0x38;
    rax = ML_CALL(1417f3154);
L30:
    rcx = r8;
    rax = ML_CALL(141723a50);
    r11 = ML_M8(rsi, 0x0);
{
    const uint64_t a = (uint64_t)(ML_M1(r11, 0x1b)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L37;
    rdi = ML_M8(rsi, 0x10);
    goto L46;
L37:
    rax = ML_M8(rsi, 0x10);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x1b)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L42;
    rdi = r11;
    goto L46;
L42:
    rcx = ML_M8(r12, 0x8);
    rdi = ML_M8(rcx, 0x10);
{
    const uint64_t a = (uint64_t)(rcx) & ~0ULL, b = (uint64_t)(rsi) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L93;
L46:
    rbx = ML_M8(rsi, 0x8);
{
    const uint64_t a = (uint64_t)(ML_M1(rdi, 0x1b)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L50;
    ML_M8(rdi, 0x8) = rbx;
L50:
    rax = ML_M8(rbp, 0x30);
{
    const uint64_t a = (uint64_t)(ML_M8(rax, 0x8)) & ~0ULL, b = (uint64_t)(rsi) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L55;
    ML_M8(rax, 0x8) = rdi;
    goto L60;
L55:
{
    const uint64_t a = (uint64_t)(ML_M8(rbx, 0x0)) & ~0ULL, b = (uint64_t)(rsi) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L59;
    ML_M8(rbx, 0x0) = rdi;
    goto L60;
L59:
    ML_M8(rbx, 0x10) = rdi;
L60:
    rdx = ML_M8(rbp, 0x30);
{
    const uint64_t a = (uint64_t)(ML_M8(rdx, 0x0)) & ~0ULL, b = (uint64_t)(rsi) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L76;
{
    const uint64_t a = (uint64_t)(ML_M1(rdi, 0x1b)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L67;
    rcx = rbx;
    goto L75;
L67:
    rcx = rdi;
    rax = ML_M8(rdi, 0x0);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x1b)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L75;
L71:
    rcx = rax;
    rax = ML_M8(rax, 0x0);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x1b)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L71;
L75:
    ML_M8(rdx, 0x0) = rcx;
L76:
    rdx = ML_M8(rbp, 0x30);
{
    const uint64_t a = (uint64_t)(ML_M8(rdx, 0x10)) & ~0ULL, b = (uint64_t)(rsi) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L130;
{
    const uint64_t a = (uint64_t)(ML_M1(rdi, 0x1b)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L83;
    rcx = rbx;
    goto L91;
L83:
    rcx = rdi;
    rax = ML_M8(rdi, 0x10);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x1b)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L91;
L87:
    rcx = rax;
    rax = ML_M8(rax, 0x10);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x1b)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L87;
L91:
    ML_M8(rdx, 0x10) = rcx;
    goto L130;
L93:
    ML_M8(r11, 0x8) = rcx;
    rax = ML_M8(rsi, 0x0);
    ML_M8(rcx, 0x0) = rax;
{
    const uint64_t a = (uint64_t)(rcx) & ~0ULL, b = (uint64_t)(ML_M8(rsi, 0x10)) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L100;
    rbx = rcx;
    goto L109;
L100:
    rbx = ML_M8(rcx, 0x8);
{
    const uint64_t a = (uint64_t)(ML_M1(rdi, 0x1b)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L104;
    ML_M8(rdi, 0x8) = rbx;
L104:
    ML_M8(rbx, 0x0) = rdi;
    rax = ML_M8(rsi, 0x10);
    ML_M8(rcx, 0x10) = rax;
    rax = ML_M8(rsi, 0x10);
    ML_M8(rax, 0x8) = rcx;
L109:
    rax = ML_M8(rbp, 0x30);
{
    const uint64_t a = (uint64_t)(ML_M8(rax, 0x8)) & ~0ULL, b = (uint64_t)(rsi) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L114;
    ML_M8(rax, 0x8) = rcx;
    goto L120;
L114:
    rax = ML_M8(rsi, 0x8);
{
    const uint64_t a = (uint64_t)(ML_M8(rax, 0x0)) & ~0ULL, b = (uint64_t)(rsi) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L119;
    ML_M8(rax, 0x0) = rcx;
    goto L120;
L119:
    ML_M8(rax, 0x10) = rcx;
L120:
    rax = ML_M8(rsi, 0x8);
    ML_M8(rcx, 0x8) = rax;
    rdx = rsi + 0x1a;
    r8 = rcx + 0x1a;
{
    const uint64_t a = (uint64_t)(r8) & ~0ULL, b = (uint64_t)(rdx) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (f_zf) goto L130;
    rcx = ML_M1(r8, 0x0);
    rax = ML_M1(rdx, 0x0);
    ML_M1(r8, 0x0) = (uint8_t)rax;
    ML_M1(rdx, 0x0) = (uint8_t)rcx;
L130:
{
    const uint64_t a = (uint64_t)(ML_M1(rsi, 0x1a)) & 0xFFULL, b = (uint64_t)(0x1ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L225;
    rax = ML_M8(rbp, 0x30);
{
    const uint64_t a = (uint64_t)(rdi) & ~0ULL, b = (uint64_t)(ML_M8(rax, 0x8)) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (f_zf) goto L224;
L135:
{
    const uint64_t a = (uint64_t)(ML_M1(rdi, 0x1a)) & 0xFFULL, b = (uint64_t)(0x1ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L224;
    rcx = ML_M8(rbx, 0x0);
{
    const uint64_t a = (uint64_t)(rdi) & ~0ULL, b = (uint64_t)(rcx) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L162;
    rcx = ML_M8(rbx, 0x10);
{
    const uint64_t a = (uint64_t)(ML_M1(rcx, 0x1a)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L149;
    ML_M1(rcx, 0x1a) = 0x1ULL;
    ML_M1(rbx, 0x1a) = 0x0ULL;
    rdx = rbx;
    rcx = rbp;
    rax = ML_CALL(141725000);
    rcx = ML_M8(rbx, 0x10);
L149:
{
    const uint64_t a = (uint64_t)(ML_M1(rcx, 0x1b)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L153;
    rdi = rbx;
    goto L182;
L153:
    rax = ML_M8(rcx, 0x0);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x1a)) & 0xFFULL, b = (uint64_t)(0x1ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L187;
    rax = ML_M8(rcx, 0x10);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x1a)) & 0xFFULL, b = (uint64_t)(0x1ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L187;
    ML_M1(rcx, 0x1a) = 0x0ULL;
    rdi = rbx;
    goto L182;
L162:
{
    const uint64_t a = (uint64_t)(ML_M1(rcx, 0x1a)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L170;
    ML_M1(rcx, 0x1a) = 0x1ULL;
    ML_M1(rbx, 0x1a) = 0x0ULL;
    rdx = rbx;
    rcx = rbp;
    rax = ML_CALL(141725060);
    rcx = ML_M8(rbx, 0x0);
L170:
{
    const uint64_t a = (uint64_t)(ML_M1(rcx, 0x1b)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L174;
    rdi = rbx;
    goto L182;
L174:
    rax = ML_M8(rcx, 0x10);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x1a)) & 0xFFULL, b = (uint64_t)(0x1ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L206;
    rax = ML_M8(rcx, 0x0);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x1a)) & 0xFFULL, b = (uint64_t)(0x1ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L206;
    ML_M1(rcx, 0x1a) = 0x0ULL;
    rdi = rbx;
L182:
    rbx = ML_M8(rbx, 0x8);
    rax = ML_M8(rbp, 0x30);
{
    const uint64_t a = (uint64_t)(rdi) & ~0ULL, b = (uint64_t)(ML_M8(rax, 0x8)) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (f_zf) goto L224;
    goto L135;
L187:
    rax = ML_M8(rcx, 0x10);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x1a)) & 0xFFULL, b = (uint64_t)(0x1ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L197;
    rax = ML_M8(rcx, 0x0);
    ML_M1(rax, 0x1a) = 0x1ULL;
    ML_M1(rcx, 0x1a) = 0x0ULL;
    rdx = rcx;
    rcx = rbp;
    rax = ML_CALL(141725060);
    rcx = ML_M8(rbx, 0x10);
L197:
    rax = ML_M1(rbx, 0x1a);
    ML_M1(rcx, 0x1a) = (uint8_t)rax;
    ML_M1(rbx, 0x1a) = 0x1ULL;
    rax = ML_M8(rcx, 0x10);
    ML_M1(rax, 0x1a) = 0x1ULL;
    rdx = rbx;
    rcx = rbp;
    rax = ML_CALL(141725000);
    goto L224;
L206:
    rax = ML_M8(rcx, 0x0);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x1a)) & 0xFFULL, b = (uint64_t)(0x1ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L216;
    rax = ML_M8(rcx, 0x10);
    ML_M1(rax, 0x1a) = 0x1ULL;
    ML_M1(rcx, 0x1a) = 0x0ULL;
    rdx = rcx;
    rcx = rbp;
    rax = ML_CALL(141725000);
    rcx = ML_M8(rbx, 0x0);
L216:
    rax = ML_M1(rbx, 0x1a);
    ML_M1(rcx, 0x1a) = (uint8_t)rax;
    ML_M1(rbx, 0x1a) = 0x1ULL;
    rax = ML_M8(rcx, 0x0);
    ML_M1(rax, 0x1a) = 0x1ULL;
    rdx = rbx;
    rcx = rbp;
    rax = ML_CALL(141725060);
L224:
    ML_M1(rdi, 0x1a) = 0x1ULL;
L225:
    rcx = rsi;
    rax = ML_CALL(1417f2fdc);
    rax = ML_M8(rbp, 0x38);
{
    const uint64_t r = ((uint64_t)(rax) & ~0ULL) & ((uint64_t)(rax) & ~0ULL);
    f_zf = (r == 0); f_cf = false; f_sf = ((r & 0x8000000000000000ULL) != 0);
    f_of = false;
}
    if (f_zf) goto L232;
    rax = rax - 1;
    ML_M8(rbp, 0x38) = rax;
L232:
    rcx = rsp + 0x20;
    rax = ML_M8(r12, 0x0);
    ML_M8(rcx, 0x0) = rax;
    rax = ML_M8(r12, 0x8);
    ML_M8(rcx, 0x8) = rax;
    rax = ML_M8(rsp, 0x28);
    ML_M8(rsp, 0x28) = rax;
    rax = ML_M8(rbp, 0x0);
    ML_M8(rsp, 0x20) = rax;
    rcx = rsp + 0x20;
    rax = ML_M8(rcx, 0x0);
    ML_M8(r13, 0x0) = rax;
    rax = ML_M8(rcx, 0x8);
    ML_M8(r13, 0x8) = rax;
    rax = r13;
    r11 = rsp + 0xa0;
    rbx = ML_M8(r11, 0x20);
    rbp = ML_M8(r11, 0x28);
    rsi = ML_M8(r11, 0x30);
    rsp = r11;
    { const uint64_t v = ML_M8(rsp, 0); rsp += 8; r13 = v; }
    { const uint64_t v = ML_M8(rsp, 0); rsp += 8; r12 = v; }
    { const uint64_t v = ML_M8(rsp, 0); rsp += 8; rdi = v; }
    return rax;
#undef ML_CALL
    return rax;
}

__attribute__((weak)) uint64_t (*g_fnLIFT_1417224f0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t) = nullptr;
__attribute__((weak)) uint64_t (*g_fnLIFT_141722ef0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t) = nullptr;
__attribute__((weak)) uint64_t (*g_fnLIFT_141724870)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t) = nullptr;
uint64_t SynLift_14172b160(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A) {
    uint64_t rax = 0, rbx = 0, rbp = 0, rsi = 0, rdi = 0, r10 = 0, r11 = 0, r12 = 0, r13 = 0, r14 = 0, r15 = 0;
    uint64_t rcx = rcxA, rdx = rdxA, r8 = r8A, r9 = r9A;
    bool f_zf = false, f_cf = false, f_sf = false, f_of = false;
    uint8_t xmm0[16] = {0}, xmm1[16] = {0}, xmm2[16] = {0}, xmm3[16] = {0}, xmm4[16] = {0}, xmm5[16] = {0};
    alignas(16) uint8_t stkFrame[0x400] = {0};
    uint64_t rsp = (uint64_t)(uintptr_t)(stkFrame + 0x200);
#define ML_CALL(t) g_fnLIFT_##t(rcx, rdx, r8, r9, ML_M8(rsp, 0x20), ML_M8(rsp, 0x28))
    rax = rsp;
    rsp -= 8; ML_M8(rsp, 0) = rdi;
    rsp -= 8; ML_M8(rsp, 0) = r12;
    rsp -= 8; ML_M8(rsp, 0) = r13;
    rsp = rsp - (0xa0ULL);
    ML_M8(rsp, 0x30) = 0xfffffffffffffffeULL;
    ML_M8(rax, 0x8) = rbx;
    ML_M8(rax, 0x10) = rbp;
    ML_M8(rax, 0x18) = rsi;
    r12 = r8;
    r13 = rdx;
    rbp = rcx;
    rsi = ML_M8(r8, 0x8);
{
    const uint64_t a = (uint64_t)(ML_M1(rsi, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L30;
    rdx = (uintptr_t)0x141825ca8;
    rcx = rax - 0x40;
    rax = ML_CALL(141823270);
    rcx = rsp + 0x38;
    rax = ML_CALL(1418233f8);
    rax = (uintptr_t)0x141824a60;
    ML_M8(rsp, 0x38) = rax;
    rdx = rsp + 0x78;
    rcx = rsp + 0x50;
    rax = ML_CALL(141823288);
    rax = (uintptr_t)0x141824ba0;
    ML_M8(rsp, 0x38) = rax;
    rdx = (uintptr_t)0x141881e50;
    rcx = rsp + 0x38;
    rax = ML_CALL(1417f3154);
L30:
    rcx = r8;
    rax = ML_CALL(141722ef0);
    r11 = ML_M8(rsi, 0x0);
{
    const uint64_t a = (uint64_t)(ML_M1(r11, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L37;
    rdi = ML_M8(rsi, 0x10);
    goto L46;
L37:
    rax = ML_M8(rsi, 0x10);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L42;
    rdi = r11;
    goto L46;
L42:
    rcx = ML_M8(r12, 0x8);
    rdi = ML_M8(rcx, 0x10);
{
    const uint64_t a = (uint64_t)(rcx) & ~0ULL, b = (uint64_t)(rsi) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L93;
L46:
    rbx = ML_M8(rsi, 0x8);
{
    const uint64_t a = (uint64_t)(ML_M1(rdi, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L50;
    ML_M8(rdi, 0x8) = rbx;
L50:
    rax = ML_M8(rbp, 0x30);
{
    const uint64_t a = (uint64_t)(ML_M8(rax, 0x8)) & ~0ULL, b = (uint64_t)(rsi) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L55;
    ML_M8(rax, 0x8) = rdi;
    goto L60;
L55:
{
    const uint64_t a = (uint64_t)(ML_M8(rbx, 0x0)) & ~0ULL, b = (uint64_t)(rsi) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L59;
    ML_M8(rbx, 0x0) = rdi;
    goto L60;
L59:
    ML_M8(rbx, 0x10) = rdi;
L60:
    rdx = ML_M8(rbp, 0x30);
{
    const uint64_t a = (uint64_t)(ML_M8(rdx, 0x0)) & ~0ULL, b = (uint64_t)(rsi) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L76;
{
    const uint64_t a = (uint64_t)(ML_M1(rdi, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L67;
    rcx = rbx;
    goto L75;
L67:
    rcx = rdi;
    rax = ML_M8(rdi, 0x0);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L75;
L71:
    rcx = rax;
    rax = ML_M8(rax, 0x0);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L71;
L75:
    ML_M8(rdx, 0x0) = rcx;
L76:
    rdx = ML_M8(rbp, 0x30);
{
    const uint64_t a = (uint64_t)(ML_M8(rdx, 0x10)) & ~0ULL, b = (uint64_t)(rsi) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L130;
{
    const uint64_t a = (uint64_t)(ML_M1(rdi, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L83;
    rcx = rbx;
    goto L91;
L83:
    rcx = rdi;
    rax = ML_M8(rdi, 0x10);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L91;
L87:
    rcx = rax;
    rax = ML_M8(rax, 0x10);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L87;
L91:
    ML_M8(rdx, 0x10) = rcx;
    goto L130;
L93:
    ML_M8(r11, 0x8) = rcx;
    rax = ML_M8(rsi, 0x0);
    ML_M8(rcx, 0x0) = rax;
{
    const uint64_t a = (uint64_t)(rcx) & ~0ULL, b = (uint64_t)(ML_M8(rsi, 0x10)) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L100;
    rbx = rcx;
    goto L109;
L100:
    rbx = ML_M8(rcx, 0x8);
{
    const uint64_t a = (uint64_t)(ML_M1(rdi, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L104;
    ML_M8(rdi, 0x8) = rbx;
L104:
    ML_M8(rbx, 0x0) = rdi;
    rax = ML_M8(rsi, 0x10);
    ML_M8(rcx, 0x10) = rax;
    rax = ML_M8(rsi, 0x10);
    ML_M8(rax, 0x8) = rcx;
L109:
    rax = ML_M8(rbp, 0x30);
{
    const uint64_t a = (uint64_t)(ML_M8(rax, 0x8)) & ~0ULL, b = (uint64_t)(rsi) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L114;
    ML_M8(rax, 0x8) = rcx;
    goto L120;
L114:
    rax = ML_M8(rsi, 0x8);
{
    const uint64_t a = (uint64_t)(ML_M8(rax, 0x0)) & ~0ULL, b = (uint64_t)(rsi) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L119;
    ML_M8(rax, 0x0) = rcx;
    goto L120;
L119:
    ML_M8(rax, 0x10) = rcx;
L120:
    rax = ML_M8(rsi, 0x8);
    ML_M8(rcx, 0x8) = rax;
    rdx = rsi + 0x28;
    r8 = rcx + 0x28;
{
    const uint64_t a = (uint64_t)(r8) & ~0ULL, b = (uint64_t)(rdx) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (f_zf) goto L130;
    rcx = ML_M1(r8, 0x0);
    rax = ML_M1(rdx, 0x0);
    ML_M1(r8, 0x0) = (uint8_t)rax;
    ML_M1(rdx, 0x0) = (uint8_t)rcx;
L130:
{
    const uint64_t a = (uint64_t)(ML_M1(rsi, 0x28)) & 0xFFULL, b = (uint64_t)(0x1ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L225;
    rax = ML_M8(rbp, 0x30);
{
    const uint64_t a = (uint64_t)(rdi) & ~0ULL, b = (uint64_t)(ML_M8(rax, 0x8)) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (f_zf) goto L224;
L135:
{
    const uint64_t a = (uint64_t)(ML_M1(rdi, 0x28)) & 0xFFULL, b = (uint64_t)(0x1ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L224;
    rcx = ML_M8(rbx, 0x0);
{
    const uint64_t a = (uint64_t)(rdi) & ~0ULL, b = (uint64_t)(rcx) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L162;
    rcx = ML_M8(rbx, 0x10);
{
    const uint64_t a = (uint64_t)(ML_M1(rcx, 0x28)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L149;
    ML_M1(rcx, 0x28) = 0x1ULL;
    ML_M1(rbx, 0x28) = 0x0ULL;
    rdx = rbx;
    rcx = rbp;
    rax = ML_CALL(141724870);
    rcx = ML_M8(rbx, 0x10);
L149:
{
    const uint64_t a = (uint64_t)(ML_M1(rcx, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L153;
    rdi = rbx;
    goto L182;
L153:
    rax = ML_M8(rcx, 0x0);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x28)) & 0xFFULL, b = (uint64_t)(0x1ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L187;
    rax = ML_M8(rcx, 0x10);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x28)) & 0xFFULL, b = (uint64_t)(0x1ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L187;
    ML_M1(rcx, 0x28) = 0x0ULL;
    rdi = rbx;
    goto L182;
L162:
{
    const uint64_t a = (uint64_t)(ML_M1(rcx, 0x28)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L170;
    ML_M1(rcx, 0x28) = 0x1ULL;
    ML_M1(rbx, 0x28) = 0x0ULL;
    rdx = rbx;
    rcx = rbp;
    rax = ML_CALL(1417224f0);
    rcx = ML_M8(rbx, 0x0);
L170:
{
    const uint64_t a = (uint64_t)(ML_M1(rcx, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L174;
    rdi = rbx;
    goto L182;
L174:
    rax = ML_M8(rcx, 0x10);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x28)) & 0xFFULL, b = (uint64_t)(0x1ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L206;
    rax = ML_M8(rcx, 0x0);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x28)) & 0xFFULL, b = (uint64_t)(0x1ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L206;
    ML_M1(rcx, 0x28) = 0x0ULL;
    rdi = rbx;
L182:
    rbx = ML_M8(rbx, 0x8);
    rax = ML_M8(rbp, 0x30);
{
    const uint64_t a = (uint64_t)(rdi) & ~0ULL, b = (uint64_t)(ML_M8(rax, 0x8)) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (f_zf) goto L224;
    goto L135;
L187:
    rax = ML_M8(rcx, 0x10);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x28)) & 0xFFULL, b = (uint64_t)(0x1ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L197;
    rax = ML_M8(rcx, 0x0);
    ML_M1(rax, 0x28) = 0x1ULL;
    ML_M1(rcx, 0x28) = 0x0ULL;
    rdx = rcx;
    rcx = rbp;
    rax = ML_CALL(1417224f0);
    rcx = ML_M8(rbx, 0x10);
L197:
    rax = ML_M1(rbx, 0x28);
    ML_M1(rcx, 0x28) = (uint8_t)rax;
    ML_M1(rbx, 0x28) = 0x1ULL;
    rax = ML_M8(rcx, 0x10);
    ML_M1(rax, 0x28) = 0x1ULL;
    rdx = rbx;
    rcx = rbp;
    rax = ML_CALL(141724870);
    goto L224;
L206:
    rax = ML_M8(rcx, 0x0);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x28)) & 0xFFULL, b = (uint64_t)(0x1ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L216;
    rax = ML_M8(rcx, 0x10);
    ML_M1(rax, 0x28) = 0x1ULL;
    ML_M1(rcx, 0x28) = 0x0ULL;
    rdx = rcx;
    rcx = rbp;
    rax = ML_CALL(141724870);
    rcx = ML_M8(rbx, 0x0);
L216:
    rax = ML_M1(rbx, 0x28);
    ML_M1(rcx, 0x28) = (uint8_t)rax;
    ML_M1(rbx, 0x28) = 0x1ULL;
    rax = ML_M8(rcx, 0x0);
    ML_M1(rax, 0x28) = 0x1ULL;
    rdx = rbx;
    rcx = rbp;
    rax = ML_CALL(1417224f0);
L224:
    ML_M1(rdi, 0x28) = 0x1ULL;
L225:
    rcx = rsi;
    rax = ML_CALL(1417f2fdc);
    rax = ML_M8(rbp, 0x38);
{
    const uint64_t r = ((uint64_t)(rax) & ~0ULL) & ((uint64_t)(rax) & ~0ULL);
    f_zf = (r == 0); f_cf = false; f_sf = ((r & 0x8000000000000000ULL) != 0);
    f_of = false;
}
    if (f_zf) goto L232;
    rax = rax - 1;
    ML_M8(rbp, 0x38) = rax;
L232:
    rcx = rsp + 0x20;
    rax = ML_M8(r12, 0x0);
    ML_M8(rcx, 0x0) = rax;
    rax = ML_M8(r12, 0x8);
    ML_M8(rcx, 0x8) = rax;
    rax = ML_M8(rsp, 0x28);
    ML_M8(rsp, 0x28) = rax;
    rax = ML_M8(rbp, 0x0);
    ML_M8(rsp, 0x20) = rax;
    rcx = rsp + 0x20;
    rax = ML_M8(rcx, 0x0);
    ML_M8(r13, 0x0) = rax;
    rax = ML_M8(rcx, 0x8);
    ML_M8(r13, 0x8) = rax;
    rax = r13;
    r11 = rsp + 0xa0;
    rbx = ML_M8(r11, 0x20);
    rbp = ML_M8(r11, 0x28);
    rsi = ML_M8(r11, 0x30);
    rsp = r11;
    { const uint64_t v = ML_M8(rsp, 0); rsp += 8; r13 = v; }
    { const uint64_t v = ML_M8(rsp, 0); rsp += 8; r12 = v; }
    { const uint64_t v = ML_M8(rsp, 0); rsp += 8; rdi = v; }
    return rax;
#undef ML_CALL
    return rax;
}

__attribute__((weak)) uint64_t (*g_fnLIFT_141722680)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t) = nullptr;
__attribute__((weak)) uint64_t (*g_fnLIFT_141723090)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t) = nullptr;
__attribute__((weak)) uint64_t (*g_fnLIFT_141724950)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t) = nullptr;
uint64_t SynLift_14172b870(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A) {
    uint64_t rax = 0, rbx = 0, rbp = 0, rsi = 0, rdi = 0, r10 = 0, r11 = 0, r12 = 0, r13 = 0, r14 = 0, r15 = 0;
    uint64_t rcx = rcxA, rdx = rdxA, r8 = r8A, r9 = r9A;
    bool f_zf = false, f_cf = false, f_sf = false, f_of = false;
    uint8_t xmm0[16] = {0}, xmm1[16] = {0}, xmm2[16] = {0}, xmm3[16] = {0}, xmm4[16] = {0}, xmm5[16] = {0};
    alignas(16) uint8_t stkFrame[0x400] = {0};
    uint64_t rsp = (uint64_t)(uintptr_t)(stkFrame + 0x200);
#define ML_CALL(t) g_fnLIFT_##t(rcx, rdx, r8, r9, ML_M8(rsp, 0x20), ML_M8(rsp, 0x28))
    rax = rsp;
    rsp -= 8; ML_M8(rsp, 0) = rdi;
    rsp -= 8; ML_M8(rsp, 0) = r12;
    rsp -= 8; ML_M8(rsp, 0) = r13;
    rsp = rsp - (0xa0ULL);
    ML_M8(rsp, 0x30) = 0xfffffffffffffffeULL;
    ML_M8(rax, 0x8) = rbx;
    ML_M8(rax, 0x10) = rbp;
    ML_M8(rax, 0x18) = rsi;
    r12 = r8;
    r13 = rdx;
    rbp = rcx;
    rsi = ML_M8(r8, 0x8);
{
    const uint64_t a = (uint64_t)(ML_M1(rsi, 0x49)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L30;
    rdx = (uintptr_t)0x141825ca8;
    rcx = rax - 0x40;
    rax = ML_CALL(141823270);
    rcx = rsp + 0x38;
    rax = ML_CALL(1418233f8);
    rax = (uintptr_t)0x141824a60;
    ML_M8(rsp, 0x38) = rax;
    rdx = rsp + 0x78;
    rcx = rsp + 0x50;
    rax = ML_CALL(141823288);
    rax = (uintptr_t)0x141824ba0;
    ML_M8(rsp, 0x38) = rax;
    rdx = (uintptr_t)0x141881e50;
    rcx = rsp + 0x38;
    rax = ML_CALL(1417f3154);
L30:
    rcx = r8;
    rax = ML_CALL(141723090);
    r11 = ML_M8(rsi, 0x0);
{
    const uint64_t a = (uint64_t)(ML_M1(r11, 0x49)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L37;
    rdi = ML_M8(rsi, 0x10);
    goto L46;
L37:
    rax = ML_M8(rsi, 0x10);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x49)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L42;
    rdi = r11;
    goto L46;
L42:
    rcx = ML_M8(r12, 0x8);
    rdi = ML_M8(rcx, 0x10);
{
    const uint64_t a = (uint64_t)(rcx) & ~0ULL, b = (uint64_t)(rsi) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L93;
L46:
    rbx = ML_M8(rsi, 0x8);
{
    const uint64_t a = (uint64_t)(ML_M1(rdi, 0x49)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L50;
    ML_M8(rdi, 0x8) = rbx;
L50:
    rax = ML_M8(rbp, 0x30);
{
    const uint64_t a = (uint64_t)(ML_M8(rax, 0x8)) & ~0ULL, b = (uint64_t)(rsi) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L55;
    ML_M8(rax, 0x8) = rdi;
    goto L60;
L55:
{
    const uint64_t a = (uint64_t)(ML_M8(rbx, 0x0)) & ~0ULL, b = (uint64_t)(rsi) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L59;
    ML_M8(rbx, 0x0) = rdi;
    goto L60;
L59:
    ML_M8(rbx, 0x10) = rdi;
L60:
    rdx = ML_M8(rbp, 0x30);
{
    const uint64_t a = (uint64_t)(ML_M8(rdx, 0x0)) & ~0ULL, b = (uint64_t)(rsi) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L76;
{
    const uint64_t a = (uint64_t)(ML_M1(rdi, 0x49)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L67;
    rcx = rbx;
    goto L75;
L67:
    rcx = rdi;
    rax = ML_M8(rdi, 0x0);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x49)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L75;
L71:
    rcx = rax;
    rax = ML_M8(rax, 0x0);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x49)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L71;
L75:
    ML_M8(rdx, 0x0) = rcx;
L76:
    rdx = ML_M8(rbp, 0x30);
{
    const uint64_t a = (uint64_t)(ML_M8(rdx, 0x10)) & ~0ULL, b = (uint64_t)(rsi) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L130;
{
    const uint64_t a = (uint64_t)(ML_M1(rdi, 0x49)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L83;
    rcx = rbx;
    goto L91;
L83:
    rcx = rdi;
    rax = ML_M8(rdi, 0x10);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x49)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L91;
L87:
    rcx = rax;
    rax = ML_M8(rax, 0x10);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x49)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L87;
L91:
    ML_M8(rdx, 0x10) = rcx;
    goto L130;
L93:
    ML_M8(r11, 0x8) = rcx;
    rax = ML_M8(rsi, 0x0);
    ML_M8(rcx, 0x0) = rax;
{
    const uint64_t a = (uint64_t)(rcx) & ~0ULL, b = (uint64_t)(ML_M8(rsi, 0x10)) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L100;
    rbx = rcx;
    goto L109;
L100:
    rbx = ML_M8(rcx, 0x8);
{
    const uint64_t a = (uint64_t)(ML_M1(rdi, 0x49)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L104;
    ML_M8(rdi, 0x8) = rbx;
L104:
    ML_M8(rbx, 0x0) = rdi;
    rax = ML_M8(rsi, 0x10);
    ML_M8(rcx, 0x10) = rax;
    rax = ML_M8(rsi, 0x10);
    ML_M8(rax, 0x8) = rcx;
L109:
    rax = ML_M8(rbp, 0x30);
{
    const uint64_t a = (uint64_t)(ML_M8(rax, 0x8)) & ~0ULL, b = (uint64_t)(rsi) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L114;
    ML_M8(rax, 0x8) = rcx;
    goto L120;
L114:
    rax = ML_M8(rsi, 0x8);
{
    const uint64_t a = (uint64_t)(ML_M8(rax, 0x0)) & ~0ULL, b = (uint64_t)(rsi) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L119;
    ML_M8(rax, 0x0) = rcx;
    goto L120;
L119:
    ML_M8(rax, 0x10) = rcx;
L120:
    rax = ML_M8(rsi, 0x8);
    ML_M8(rcx, 0x8) = rax;
    rdx = rsi + 0x48;
    r8 = rcx + 0x48;
{
    const uint64_t a = (uint64_t)(r8) & ~0ULL, b = (uint64_t)(rdx) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (f_zf) goto L130;
    rcx = ML_M1(r8, 0x0);
    rax = ML_M1(rdx, 0x0);
    ML_M1(r8, 0x0) = (uint8_t)rax;
    ML_M1(rdx, 0x0) = (uint8_t)rcx;
L130:
{
    const uint64_t a = (uint64_t)(ML_M1(rsi, 0x48)) & 0xFFULL, b = (uint64_t)(0x1ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L225;
    rax = ML_M8(rbp, 0x30);
{
    const uint64_t a = (uint64_t)(rdi) & ~0ULL, b = (uint64_t)(ML_M8(rax, 0x8)) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (f_zf) goto L224;
L135:
{
    const uint64_t a = (uint64_t)(ML_M1(rdi, 0x48)) & 0xFFULL, b = (uint64_t)(0x1ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L224;
    rcx = ML_M8(rbx, 0x0);
{
    const uint64_t a = (uint64_t)(rdi) & ~0ULL, b = (uint64_t)(rcx) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L162;
    rcx = ML_M8(rbx, 0x10);
{
    const uint64_t a = (uint64_t)(ML_M1(rcx, 0x48)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L149;
    ML_M1(rcx, 0x48) = 0x1ULL;
    ML_M1(rbx, 0x48) = 0x0ULL;
    rdx = rbx;
    rcx = rbp;
    rax = ML_CALL(141724950);
    rcx = ML_M8(rbx, 0x10);
L149:
{
    const uint64_t a = (uint64_t)(ML_M1(rcx, 0x49)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L153;
    rdi = rbx;
    goto L182;
L153:
    rax = ML_M8(rcx, 0x0);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x48)) & 0xFFULL, b = (uint64_t)(0x1ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L187;
    rax = ML_M8(rcx, 0x10);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x48)) & 0xFFULL, b = (uint64_t)(0x1ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L187;
    ML_M1(rcx, 0x48) = 0x0ULL;
    rdi = rbx;
    goto L182;
L162:
{
    const uint64_t a = (uint64_t)(ML_M1(rcx, 0x48)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L170;
    ML_M1(rcx, 0x48) = 0x1ULL;
    ML_M1(rbx, 0x48) = 0x0ULL;
    rdx = rbx;
    rcx = rbp;
    rax = ML_CALL(141722680);
    rcx = ML_M8(rbx, 0x0);
L170:
{
    const uint64_t a = (uint64_t)(ML_M1(rcx, 0x49)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L174;
    rdi = rbx;
    goto L182;
L174:
    rax = ML_M8(rcx, 0x10);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x48)) & 0xFFULL, b = (uint64_t)(0x1ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L206;
    rax = ML_M8(rcx, 0x0);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x48)) & 0xFFULL, b = (uint64_t)(0x1ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L206;
    ML_M1(rcx, 0x48) = 0x0ULL;
    rdi = rbx;
L182:
    rbx = ML_M8(rbx, 0x8);
    rax = ML_M8(rbp, 0x30);
{
    const uint64_t a = (uint64_t)(rdi) & ~0ULL, b = (uint64_t)(ML_M8(rax, 0x8)) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (f_zf) goto L224;
    goto L135;
L187:
    rax = ML_M8(rcx, 0x10);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x48)) & 0xFFULL, b = (uint64_t)(0x1ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L197;
    rax = ML_M8(rcx, 0x0);
    ML_M1(rax, 0x48) = 0x1ULL;
    ML_M1(rcx, 0x48) = 0x0ULL;
    rdx = rcx;
    rcx = rbp;
    rax = ML_CALL(141722680);
    rcx = ML_M8(rbx, 0x10);
L197:
    rax = ML_M1(rbx, 0x48);
    ML_M1(rcx, 0x48) = (uint8_t)rax;
    ML_M1(rbx, 0x48) = 0x1ULL;
    rax = ML_M8(rcx, 0x10);
    ML_M1(rax, 0x48) = 0x1ULL;
    rdx = rbx;
    rcx = rbp;
    rax = ML_CALL(141724950);
    goto L224;
L206:
    rax = ML_M8(rcx, 0x0);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x48)) & 0xFFULL, b = (uint64_t)(0x1ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L216;
    rax = ML_M8(rcx, 0x10);
    ML_M1(rax, 0x48) = 0x1ULL;
    ML_M1(rcx, 0x48) = 0x0ULL;
    rdx = rcx;
    rcx = rbp;
    rax = ML_CALL(141724950);
    rcx = ML_M8(rbx, 0x0);
L216:
    rax = ML_M1(rbx, 0x48);
    ML_M1(rcx, 0x48) = (uint8_t)rax;
    ML_M1(rbx, 0x48) = 0x1ULL;
    rax = ML_M8(rcx, 0x0);
    ML_M1(rax, 0x48) = 0x1ULL;
    rdx = rbx;
    rcx = rbp;
    rax = ML_CALL(141722680);
L224:
    ML_M1(rdi, 0x48) = 0x1ULL;
L225:
    rcx = rsi;
    rax = ML_CALL(1417f2fdc);
    rax = ML_M8(rbp, 0x38);
{
    const uint64_t r = ((uint64_t)(rax) & ~0ULL) & ((uint64_t)(rax) & ~0ULL);
    f_zf = (r == 0); f_cf = false; f_sf = ((r & 0x8000000000000000ULL) != 0);
    f_of = false;
}
    if (f_zf) goto L232;
    rax = rax - 1;
    ML_M8(rbp, 0x38) = rax;
L232:
    rcx = rsp + 0x20;
    rax = ML_M8(r12, 0x0);
    ML_M8(rcx, 0x0) = rax;
    rax = ML_M8(r12, 0x8);
    ML_M8(rcx, 0x8) = rax;
    rax = ML_M8(rsp, 0x28);
    ML_M8(rsp, 0x28) = rax;
    rax = ML_M8(rbp, 0x0);
    ML_M8(rsp, 0x20) = rax;
    rcx = rsp + 0x20;
    rax = ML_M8(rcx, 0x0);
    ML_M8(r13, 0x0) = rax;
    rax = ML_M8(rcx, 0x8);
    ML_M8(r13, 0x8) = rax;
    rax = r13;
    r11 = rsp + 0xa0;
    rbx = ML_M8(r11, 0x20);
    rbp = ML_M8(r11, 0x28);
    rsi = ML_M8(r11, 0x30);
    rsp = r11;
    { const uint64_t v = ML_M8(rsp, 0); rsp += 8; r13 = v; }
    { const uint64_t v = ML_M8(rsp, 0); rsp += 8; r12 = v; }
    { const uint64_t v = ML_M8(rsp, 0); rsp += 8; rdi = v; }
    return rax;
#undef ML_CALL
    return rax;
}

__attribute__((weak)) uint64_t (*g_fnLIFT_1417227e0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t) = nullptr;
__attribute__((weak)) uint64_t (*g_fnLIFT_141722fc0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t) = nullptr;
__attribute__((weak)) uint64_t (*g_fnLIFT_1417249e0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t) = nullptr;
uint64_t SynLift_14172bd00(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A) {
    uint64_t rax = 0, rbx = 0, rbp = 0, rsi = 0, rdi = 0, r10 = 0, r11 = 0, r12 = 0, r13 = 0, r14 = 0, r15 = 0;
    uint64_t rcx = rcxA, rdx = rdxA, r8 = r8A, r9 = r9A;
    bool f_zf = false, f_cf = false, f_sf = false, f_of = false;
    uint8_t xmm0[16] = {0}, xmm1[16] = {0}, xmm2[16] = {0}, xmm3[16] = {0}, xmm4[16] = {0}, xmm5[16] = {0};
    alignas(16) uint8_t stkFrame[0x400] = {0};
    uint64_t rsp = (uint64_t)(uintptr_t)(stkFrame + 0x200);
#define ML_CALL(t) g_fnLIFT_##t(rcx, rdx, r8, r9, ML_M8(rsp, 0x20), ML_M8(rsp, 0x28))
    rax = rsp;
    rsp -= 8; ML_M8(rsp, 0) = rdi;
    rsp -= 8; ML_M8(rsp, 0) = r12;
    rsp -= 8; ML_M8(rsp, 0) = r13;
    rsp = rsp - (0xa0ULL);
    ML_M8(rsp, 0x30) = 0xfffffffffffffffeULL;
    ML_M8(rax, 0x8) = rbx;
    ML_M8(rax, 0x10) = rbp;
    ML_M8(rax, 0x18) = rsi;
    r12 = r8;
    r13 = rdx;
    rbp = rcx;
    rsi = ML_M8(r8, 0x8);
{
    const uint64_t a = (uint64_t)(ML_M1(rsi, 0x1d)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L30;
    rdx = (uintptr_t)0x141825ca8;
    rcx = rax - 0x40;
    rax = ML_CALL(141823270);
    rcx = rsp + 0x38;
    rax = ML_CALL(1418233f8);
    rax = (uintptr_t)0x141824a60;
    ML_M8(rsp, 0x38) = rax;
    rdx = rsp + 0x78;
    rcx = rsp + 0x50;
    rax = ML_CALL(141823288);
    rax = (uintptr_t)0x141824ba0;
    ML_M8(rsp, 0x38) = rax;
    rdx = (uintptr_t)0x141881e50;
    rcx = rsp + 0x38;
    rax = ML_CALL(1417f3154);
L30:
    rcx = r8;
    rax = ML_CALL(141722fc0);
    r11 = ML_M8(rsi, 0x0);
{
    const uint64_t a = (uint64_t)(ML_M1(r11, 0x1d)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L37;
    rdi = ML_M8(rsi, 0x10);
    goto L46;
L37:
    rax = ML_M8(rsi, 0x10);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x1d)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L42;
    rdi = r11;
    goto L46;
L42:
    rcx = ML_M8(r12, 0x8);
    rdi = ML_M8(rcx, 0x10);
{
    const uint64_t a = (uint64_t)(rcx) & ~0ULL, b = (uint64_t)(rsi) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L93;
L46:
    rbx = ML_M8(rsi, 0x8);
{
    const uint64_t a = (uint64_t)(ML_M1(rdi, 0x1d)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L50;
    ML_M8(rdi, 0x8) = rbx;
L50:
    rax = ML_M8(rbp, 0x30);
{
    const uint64_t a = (uint64_t)(ML_M8(rax, 0x8)) & ~0ULL, b = (uint64_t)(rsi) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L55;
    ML_M8(rax, 0x8) = rdi;
    goto L60;
L55:
{
    const uint64_t a = (uint64_t)(ML_M8(rbx, 0x0)) & ~0ULL, b = (uint64_t)(rsi) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L59;
    ML_M8(rbx, 0x0) = rdi;
    goto L60;
L59:
    ML_M8(rbx, 0x10) = rdi;
L60:
    rdx = ML_M8(rbp, 0x30);
{
    const uint64_t a = (uint64_t)(ML_M8(rdx, 0x0)) & ~0ULL, b = (uint64_t)(rsi) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L76;
{
    const uint64_t a = (uint64_t)(ML_M1(rdi, 0x1d)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L67;
    rcx = rbx;
    goto L75;
L67:
    rcx = rdi;
    rax = ML_M8(rdi, 0x0);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x1d)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L75;
L71:
    rcx = rax;
    rax = ML_M8(rax, 0x0);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x1d)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L71;
L75:
    ML_M8(rdx, 0x0) = rcx;
L76:
    rdx = ML_M8(rbp, 0x30);
{
    const uint64_t a = (uint64_t)(ML_M8(rdx, 0x10)) & ~0ULL, b = (uint64_t)(rsi) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L130;
{
    const uint64_t a = (uint64_t)(ML_M1(rdi, 0x1d)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L83;
    rcx = rbx;
    goto L91;
L83:
    rcx = rdi;
    rax = ML_M8(rdi, 0x10);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x1d)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L91;
L87:
    rcx = rax;
    rax = ML_M8(rax, 0x10);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x1d)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L87;
L91:
    ML_M8(rdx, 0x10) = rcx;
    goto L130;
L93:
    ML_M8(r11, 0x8) = rcx;
    rax = ML_M8(rsi, 0x0);
    ML_M8(rcx, 0x0) = rax;
{
    const uint64_t a = (uint64_t)(rcx) & ~0ULL, b = (uint64_t)(ML_M8(rsi, 0x10)) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L100;
    rbx = rcx;
    goto L109;
L100:
    rbx = ML_M8(rcx, 0x8);
{
    const uint64_t a = (uint64_t)(ML_M1(rdi, 0x1d)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L104;
    ML_M8(rdi, 0x8) = rbx;
L104:
    ML_M8(rbx, 0x0) = rdi;
    rax = ML_M8(rsi, 0x10);
    ML_M8(rcx, 0x10) = rax;
    rax = ML_M8(rsi, 0x10);
    ML_M8(rax, 0x8) = rcx;
L109:
    rax = ML_M8(rbp, 0x30);
{
    const uint64_t a = (uint64_t)(ML_M8(rax, 0x8)) & ~0ULL, b = (uint64_t)(rsi) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L114;
    ML_M8(rax, 0x8) = rcx;
    goto L120;
L114:
    rax = ML_M8(rsi, 0x8);
{
    const uint64_t a = (uint64_t)(ML_M8(rax, 0x0)) & ~0ULL, b = (uint64_t)(rsi) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L119;
    ML_M8(rax, 0x0) = rcx;
    goto L120;
L119:
    ML_M8(rax, 0x10) = rcx;
L120:
    rax = ML_M8(rsi, 0x8);
    ML_M8(rcx, 0x8) = rax;
    rdx = rsi + 0x1c;
    r8 = rcx + 0x1c;
{
    const uint64_t a = (uint64_t)(r8) & ~0ULL, b = (uint64_t)(rdx) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (f_zf) goto L130;
    rcx = ML_M1(r8, 0x0);
    rax = ML_M1(rdx, 0x0);
    ML_M1(r8, 0x0) = (uint8_t)rax;
    ML_M1(rdx, 0x0) = (uint8_t)rcx;
L130:
{
    const uint64_t a = (uint64_t)(ML_M1(rsi, 0x1c)) & 0xFFULL, b = (uint64_t)(0x1ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L225;
    rax = ML_M8(rbp, 0x30);
{
    const uint64_t a = (uint64_t)(rdi) & ~0ULL, b = (uint64_t)(ML_M8(rax, 0x8)) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (f_zf) goto L224;
L135:
{
    const uint64_t a = (uint64_t)(ML_M1(rdi, 0x1c)) & 0xFFULL, b = (uint64_t)(0x1ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L224;
    rcx = ML_M8(rbx, 0x0);
{
    const uint64_t a = (uint64_t)(rdi) & ~0ULL, b = (uint64_t)(rcx) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L162;
    rcx = ML_M8(rbx, 0x10);
{
    const uint64_t a = (uint64_t)(ML_M1(rcx, 0x1c)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L149;
    ML_M1(rcx, 0x1c) = 0x1ULL;
    ML_M1(rbx, 0x1c) = 0x0ULL;
    rdx = rbx;
    rcx = rbp;
    rax = ML_CALL(1417249e0);
    rcx = ML_M8(rbx, 0x10);
L149:
{
    const uint64_t a = (uint64_t)(ML_M1(rcx, 0x1d)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L153;
    rdi = rbx;
    goto L182;
L153:
    rax = ML_M8(rcx, 0x0);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x1c)) & 0xFFULL, b = (uint64_t)(0x1ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L187;
    rax = ML_M8(rcx, 0x10);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x1c)) & 0xFFULL, b = (uint64_t)(0x1ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L187;
    ML_M1(rcx, 0x1c) = 0x0ULL;
    rdi = rbx;
    goto L182;
L162:
{
    const uint64_t a = (uint64_t)(ML_M1(rcx, 0x1c)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L170;
    ML_M1(rcx, 0x1c) = 0x1ULL;
    ML_M1(rbx, 0x1c) = 0x0ULL;
    rdx = rbx;
    rcx = rbp;
    rax = ML_CALL(1417227e0);
    rcx = ML_M8(rbx, 0x0);
L170:
{
    const uint64_t a = (uint64_t)(ML_M1(rcx, 0x1d)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L174;
    rdi = rbx;
    goto L182;
L174:
    rax = ML_M8(rcx, 0x10);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x1c)) & 0xFFULL, b = (uint64_t)(0x1ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L206;
    rax = ML_M8(rcx, 0x0);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x1c)) & 0xFFULL, b = (uint64_t)(0x1ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L206;
    ML_M1(rcx, 0x1c) = 0x0ULL;
    rdi = rbx;
L182:
    rbx = ML_M8(rbx, 0x8);
    rax = ML_M8(rbp, 0x30);
{
    const uint64_t a = (uint64_t)(rdi) & ~0ULL, b = (uint64_t)(ML_M8(rax, 0x8)) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (f_zf) goto L224;
    goto L135;
L187:
    rax = ML_M8(rcx, 0x10);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x1c)) & 0xFFULL, b = (uint64_t)(0x1ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L197;
    rax = ML_M8(rcx, 0x0);
    ML_M1(rax, 0x1c) = 0x1ULL;
    ML_M1(rcx, 0x1c) = 0x0ULL;
    rdx = rcx;
    rcx = rbp;
    rax = ML_CALL(1417227e0);
    rcx = ML_M8(rbx, 0x10);
L197:
    rax = ML_M1(rbx, 0x1c);
    ML_M1(rcx, 0x1c) = (uint8_t)rax;
    ML_M1(rbx, 0x1c) = 0x1ULL;
    rax = ML_M8(rcx, 0x10);
    ML_M1(rax, 0x1c) = 0x1ULL;
    rdx = rbx;
    rcx = rbp;
    rax = ML_CALL(1417249e0);
    goto L224;
L206:
    rax = ML_M8(rcx, 0x0);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x1c)) & 0xFFULL, b = (uint64_t)(0x1ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L216;
    rax = ML_M8(rcx, 0x10);
    ML_M1(rax, 0x1c) = 0x1ULL;
    ML_M1(rcx, 0x1c) = 0x0ULL;
    rdx = rcx;
    rcx = rbp;
    rax = ML_CALL(1417249e0);
    rcx = ML_M8(rbx, 0x0);
L216:
    rax = ML_M1(rbx, 0x1c);
    ML_M1(rcx, 0x1c) = (uint8_t)rax;
    ML_M1(rbx, 0x1c) = 0x1ULL;
    rax = ML_M8(rcx, 0x0);
    ML_M1(rax, 0x1c) = 0x1ULL;
    rdx = rbx;
    rcx = rbp;
    rax = ML_CALL(1417227e0);
L224:
    ML_M1(rdi, 0x1c) = 0x1ULL;
L225:
    rcx = rsi;
    rax = ML_CALL(1417f2fdc);
    rax = ML_M8(rbp, 0x38);
{
    const uint64_t r = ((uint64_t)(rax) & ~0ULL) & ((uint64_t)(rax) & ~0ULL);
    f_zf = (r == 0); f_cf = false; f_sf = ((r & 0x8000000000000000ULL) != 0);
    f_of = false;
}
    if (f_zf) goto L232;
    rax = rax - 1;
    ML_M8(rbp, 0x38) = rax;
L232:
    rcx = rsp + 0x20;
    rax = ML_M8(r12, 0x0);
    ML_M8(rcx, 0x0) = rax;
    rax = ML_M8(r12, 0x8);
    ML_M8(rcx, 0x8) = rax;
    rax = ML_M8(rsp, 0x28);
    ML_M8(rsp, 0x28) = rax;
    rax = ML_M8(rbp, 0x0);
    ML_M8(rsp, 0x20) = rax;
    rcx = rsp + 0x20;
    rax = ML_M8(rcx, 0x0);
    ML_M8(r13, 0x0) = rax;
    rax = ML_M8(rcx, 0x8);
    ML_M8(r13, 0x8) = rax;
    rax = r13;
    r11 = rsp + 0xa0;
    rbx = ML_M8(r11, 0x20);
    rbp = ML_M8(r11, 0x28);
    rsi = ML_M8(r11, 0x30);
    rsp = r11;
    { const uint64_t v = ML_M8(rsp, 0); rsp += 8; r13 = v; }
    { const uint64_t v = ML_M8(rsp, 0); rsp += 8; r12 = v; }
    { const uint64_t v = ML_M8(rsp, 0); rsp += 8; rdi = v; }
    return rax;
#undef ML_CALL
    return rax;
}

uint64_t SynLift_14173b0e0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A) {
    uint64_t rax = 0, rbx = 0, rbp = 0, rsi = 0, rdi = 0, r10 = 0, r11 = 0, r12 = 0, r13 = 0, r14 = 0, r15 = 0;
    uint64_t rcx = rcxA, rdx = rdxA, r8 = r8A, r9 = r9A;
    bool f_zf = false, f_cf = false, f_sf = false, f_of = false;
    uint8_t xmm0[16] = {0}, xmm1[16] = {0}, xmm2[16] = {0}, xmm3[16] = {0}, xmm4[16] = {0}, xmm5[16] = {0};
    alignas(16) uint8_t stkFrame[0x400] = {0};
    uint64_t rsp = (uint64_t)(uintptr_t)(stkFrame + 0x200);
#define ML_CALL(t) g_fnLIFT_##t(rcx, rdx, r8, r9, ML_M8(rsp, 0x20), ML_M8(rsp, 0x28))
    r8 = ML_M8(rdx, 0x10);
    rax = ML_M8(r8, 0x0);
    ML_M8(rdx, 0x10) = rax;
    rax = ML_M8(r8, 0x0);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x21)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L7;
    ML_M8(rax, 0x8) = rdx;
L7:
    rax = ML_M8(rdx, 0x8);
    ML_M8(r8, 0x8) = rax;
    rax = ML_M8(rcx, 0x30);
{
    const uint64_t a = (uint64_t)(rdx) & ~0ULL, b = (uint64_t)(ML_M8(rax, 0x8)) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L16;
    ML_M8(rax, 0x8) = r8;
    ML_M8(r8, 0x0) = rdx;
    ML_M8(rdx, 0x8) = r8;
    return rax;
L16:
    rax = ML_M8(rdx, 0x8);
{
    const uint64_t a = (uint64_t)(rdx) & ~0ULL, b = (uint64_t)(ML_M8(rax, 0x0)) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L23;
    ML_M8(rax, 0x0) = r8;
    ML_M8(r8, 0x0) = rdx;
    ML_M8(rdx, 0x8) = r8;
    return rax;
L23:
    ML_M8(rax, 0x10) = r8;
    ML_M8(r8, 0x0) = rdx;
    ML_M8(rdx, 0x8) = r8;
    return rax;
#undef ML_CALL
    return rax;
}

uint64_t SynLift_14173b140(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A) {
    uint64_t rax = 0, rbx = 0, rbp = 0, rsi = 0, rdi = 0, r10 = 0, r11 = 0, r12 = 0, r13 = 0, r14 = 0, r15 = 0;
    uint64_t rcx = rcxA, rdx = rdxA, r8 = r8A, r9 = r9A;
    bool f_zf = false, f_cf = false, f_sf = false, f_of = false;
    uint8_t xmm0[16] = {0}, xmm1[16] = {0}, xmm2[16] = {0}, xmm3[16] = {0}, xmm4[16] = {0}, xmm5[16] = {0};
    alignas(16) uint8_t stkFrame[0x400] = {0};
    uint64_t rsp = (uint64_t)(uintptr_t)(stkFrame + 0x200);
#define ML_CALL(t) g_fnLIFT_##t(rcx, rdx, r8, r9, ML_M8(rsp, 0x20), ML_M8(rsp, 0x28))
    r8 = ML_M8(rdx, 0x0);
    rax = ML_M8(r8, 0x10);
    ML_M8(rdx, 0x0) = rax;
    rax = ML_M8(r8, 0x10);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x21)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L7;
    ML_M8(rax, 0x8) = rdx;
L7:
    rax = ML_M8(rdx, 0x8);
    ML_M8(r8, 0x8) = rax;
    rax = ML_M8(rcx, 0x30);
{
    const uint64_t a = (uint64_t)(rdx) & ~0ULL, b = (uint64_t)(ML_M8(rax, 0x8)) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L16;
    ML_M8(rax, 0x8) = r8;
    ML_M8(r8, 0x10) = rdx;
    ML_M8(rdx, 0x8) = r8;
    return rax;
L16:
    rax = ML_M8(rdx, 0x8);
{
    const uint64_t a = (uint64_t)(rdx) & ~0ULL, b = (uint64_t)(ML_M8(rax, 0x10)) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L23;
    ML_M8(rax, 0x10) = r8;
    ML_M8(r8, 0x10) = rdx;
    ML_M8(rdx, 0x8) = r8;
    return rax;
L23:
    ML_M8(rax, 0x0) = r8;
    ML_M8(r8, 0x10) = rdx;
    ML_M8(rdx, 0x8) = r8;
    return rax;
#undef ML_CALL
    return rax;
}

uint64_t SynLift_14173b240(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A) {
    uint64_t rax = 0, rbx = 0, rbp = 0, rsi = 0, rdi = 0, r10 = 0, r11 = 0, r12 = 0, r13 = 0, r14 = 0, r15 = 0;
    uint64_t rcx = rcxA, rdx = rdxA, r8 = r8A, r9 = r9A;
    bool f_zf = false, f_cf = false, f_sf = false, f_of = false;
    uint8_t xmm0[16] = {0}, xmm1[16] = {0}, xmm2[16] = {0}, xmm3[16] = {0}, xmm4[16] = {0}, xmm5[16] = {0};
    alignas(16) uint8_t stkFrame[0x400] = {0};
    uint64_t rsp = (uint64_t)(uintptr_t)(stkFrame + 0x200);
#define ML_CALL(t) g_fnLIFT_##t(rcx, rdx, r8, r9, ML_M8(rsp, 0x20), ML_M8(rsp, 0x28))
    rsp -= 8; ML_M8(rsp, 0) = rbx;
    rsp = rsp - (0x20ULL);
{
    const uint64_t a = (uint64_t)(ML_M8(rcx, 0x0)) & ~0ULL, b = (uint64_t)(0x0ULL) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    rbx = rcx;
    if (!f_zf) goto L6;
    rax = ML_CALL(1418233c0);
L6:
    rcx = ML_M8(rbx, 0x8);
{
    const uint64_t a = (uint64_t)(ML_M1(rcx, 0x21)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L12;
    rsp = rsp + (0x20ULL);
    { const uint64_t v = ML_M8(rsp, 0); rsp += 8; rbx = v; }
    return ML_CALL(1418233c0);   // tail call
L12:
    rax = ML_M8(rcx, 0x10);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x21)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L27;
    rcx = ML_M8(rax, 0x0);
{
    const uint64_t a = (uint64_t)(ML_M1(rcx, 0x21)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L23;
    ;
L19:
    rax = rcx;
    rcx = ML_M8(rcx, 0x0);
{
    const uint64_t a = (uint64_t)(ML_M1(rcx, 0x21)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L19;
L23:
    ML_M8(rbx, 0x8) = rax;
    rsp = rsp + (0x20ULL);
    { const uint64_t v = ML_M8(rsp, 0); rsp += 8; rbx = v; }
    return rax;
L27:
    rcx = ML_M8(rcx, 0x8);
{
    const uint64_t a = (uint64_t)(ML_M1(rcx, 0x21)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L37;
L30:
    rax = ML_M8(rcx, 0x10);
{
    const uint64_t a = (uint64_t)(ML_M8(rbx, 0x8)) & ~0ULL, b = (uint64_t)(rax) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L37;
    ML_M8(rbx, 0x8) = rcx;
    rcx = ML_M8(rcx, 0x8);
{
    const uint64_t a = (uint64_t)(ML_M1(rcx, 0x21)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L30;
L37:
    ML_M8(rbx, 0x8) = rcx;
    rsp = rsp + (0x20ULL);
    { const uint64_t v = ML_M8(rsp, 0); rsp += 8; rbx = v; }
    return rax;
#undef ML_CALL
    return rax;
}

__attribute__((weak)) uint64_t (*g_fnLIFT_14173b0e0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t) = nullptr;
__attribute__((weak)) uint64_t (*g_fnLIFT_14173b140)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t) = nullptr;
__attribute__((weak)) uint64_t (*g_fnLIFT_14173b240)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t) = nullptr;
uint64_t SynLift_14173c0b0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A) {
    uint64_t rax = 0, rbx = 0, rbp = 0, rsi = 0, rdi = 0, r10 = 0, r11 = 0, r12 = 0, r13 = 0, r14 = 0, r15 = 0;
    uint64_t rcx = rcxA, rdx = rdxA, r8 = r8A, r9 = r9A;
    bool f_zf = false, f_cf = false, f_sf = false, f_of = false;
    uint8_t xmm0[16] = {0}, xmm1[16] = {0}, xmm2[16] = {0}, xmm3[16] = {0}, xmm4[16] = {0}, xmm5[16] = {0};
    alignas(16) uint8_t stkFrame[0x400] = {0};
    uint64_t rsp = (uint64_t)(uintptr_t)(stkFrame + 0x200);
#define ML_CALL(t) g_fnLIFT_##t(rcx, rdx, r8, r9, ML_M8(rsp, 0x20), ML_M8(rsp, 0x28))
    rax = rsp;
    rsp -= 8; ML_M8(rsp, 0) = rdi;
    rsp -= 8; ML_M8(rsp, 0) = r12;
    rsp -= 8; ML_M8(rsp, 0) = r13;
    rsp = rsp - (0xa0ULL);
    ML_M8(rsp, 0x30) = 0xfffffffffffffffeULL;
    ML_M8(rax, 0x8) = rbx;
    ML_M8(rax, 0x10) = rbp;
    ML_M8(rax, 0x18) = rsi;
    r12 = r8;
    r13 = rdx;
    rbp = rcx;
    rsi = ML_M8(r8, 0x8);
{
    const uint64_t a = (uint64_t)(ML_M1(rsi, 0x21)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L30;
    rdx = (uintptr_t)0x141825ca8;
    rcx = rax - 0x40;
    rax = ML_CALL(141823270);
    rcx = rsp + 0x38;
    rax = ML_CALL(1418233f8);
    rax = (uintptr_t)0x141824a60;
    ML_M8(rsp, 0x38) = rax;
    rdx = rsp + 0x78;
    rcx = rsp + 0x50;
    rax = ML_CALL(141823288);
    rax = (uintptr_t)0x141824ba0;
    ML_M8(rsp, 0x38) = rax;
    rdx = (uintptr_t)0x141881e50;
    rcx = rsp + 0x38;
    rax = ML_CALL(1417f3154);
L30:
    rcx = r8;
    rax = ML_CALL(14173b240);
    r11 = ML_M8(rsi, 0x0);
{
    const uint64_t a = (uint64_t)(ML_M1(r11, 0x21)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L37;
    rdi = ML_M8(rsi, 0x10);
    goto L46;
L37:
    rax = ML_M8(rsi, 0x10);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x21)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L42;
    rdi = r11;
    goto L46;
L42:
    rcx = ML_M8(r12, 0x8);
    rdi = ML_M8(rcx, 0x10);
{
    const uint64_t a = (uint64_t)(rcx) & ~0ULL, b = (uint64_t)(rsi) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L93;
L46:
    rbx = ML_M8(rsi, 0x8);
{
    const uint64_t a = (uint64_t)(ML_M1(rdi, 0x21)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L50;
    ML_M8(rdi, 0x8) = rbx;
L50:
    rax = ML_M8(rbp, 0x30);
{
    const uint64_t a = (uint64_t)(ML_M8(rax, 0x8)) & ~0ULL, b = (uint64_t)(rsi) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L55;
    ML_M8(rax, 0x8) = rdi;
    goto L60;
L55:
{
    const uint64_t a = (uint64_t)(ML_M8(rbx, 0x0)) & ~0ULL, b = (uint64_t)(rsi) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L59;
    ML_M8(rbx, 0x0) = rdi;
    goto L60;
L59:
    ML_M8(rbx, 0x10) = rdi;
L60:
    rdx = ML_M8(rbp, 0x30);
{
    const uint64_t a = (uint64_t)(ML_M8(rdx, 0x0)) & ~0ULL, b = (uint64_t)(rsi) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L76;
{
    const uint64_t a = (uint64_t)(ML_M1(rdi, 0x21)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L67;
    rcx = rbx;
    goto L75;
L67:
    rcx = rdi;
    rax = ML_M8(rdi, 0x0);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x21)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L75;
L71:
    rcx = rax;
    rax = ML_M8(rax, 0x0);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x21)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L71;
L75:
    ML_M8(rdx, 0x0) = rcx;
L76:
    rdx = ML_M8(rbp, 0x30);
{
    const uint64_t a = (uint64_t)(ML_M8(rdx, 0x10)) & ~0ULL, b = (uint64_t)(rsi) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L130;
{
    const uint64_t a = (uint64_t)(ML_M1(rdi, 0x21)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L83;
    rcx = rbx;
    goto L91;
L83:
    rcx = rdi;
    rax = ML_M8(rdi, 0x10);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x21)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L91;
L87:
    rcx = rax;
    rax = ML_M8(rax, 0x10);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x21)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L87;
L91:
    ML_M8(rdx, 0x10) = rcx;
    goto L130;
L93:
    ML_M8(r11, 0x8) = rcx;
    rax = ML_M8(rsi, 0x0);
    ML_M8(rcx, 0x0) = rax;
{
    const uint64_t a = (uint64_t)(rcx) & ~0ULL, b = (uint64_t)(ML_M8(rsi, 0x10)) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L100;
    rbx = rcx;
    goto L109;
L100:
    rbx = ML_M8(rcx, 0x8);
{
    const uint64_t a = (uint64_t)(ML_M1(rdi, 0x21)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L104;
    ML_M8(rdi, 0x8) = rbx;
L104:
    ML_M8(rbx, 0x0) = rdi;
    rax = ML_M8(rsi, 0x10);
    ML_M8(rcx, 0x10) = rax;
    rax = ML_M8(rsi, 0x10);
    ML_M8(rax, 0x8) = rcx;
L109:
    rax = ML_M8(rbp, 0x30);
{
    const uint64_t a = (uint64_t)(ML_M8(rax, 0x8)) & ~0ULL, b = (uint64_t)(rsi) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L114;
    ML_M8(rax, 0x8) = rcx;
    goto L120;
L114:
    rax = ML_M8(rsi, 0x8);
{
    const uint64_t a = (uint64_t)(ML_M8(rax, 0x0)) & ~0ULL, b = (uint64_t)(rsi) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L119;
    ML_M8(rax, 0x0) = rcx;
    goto L120;
L119:
    ML_M8(rax, 0x10) = rcx;
L120:
    rax = ML_M8(rsi, 0x8);
    ML_M8(rcx, 0x8) = rax;
    rdx = rsi + 0x20;
    r8 = rcx + 0x20;
{
    const uint64_t a = (uint64_t)(r8) & ~0ULL, b = (uint64_t)(rdx) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (f_zf) goto L130;
    rcx = ML_M1(r8, 0x0);
    rax = ML_M1(rdx, 0x0);
    ML_M1(r8, 0x0) = (uint8_t)rax;
    ML_M1(rdx, 0x0) = (uint8_t)rcx;
L130:
{
    const uint64_t a = (uint64_t)(ML_M1(rsi, 0x20)) & 0xFFULL, b = (uint64_t)(0x1ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L225;
    rax = ML_M8(rbp, 0x30);
{
    const uint64_t a = (uint64_t)(rdi) & ~0ULL, b = (uint64_t)(ML_M8(rax, 0x8)) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (f_zf) goto L224;
L135:
{
    const uint64_t a = (uint64_t)(ML_M1(rdi, 0x20)) & 0xFFULL, b = (uint64_t)(0x1ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L224;
    rcx = ML_M8(rbx, 0x0);
{
    const uint64_t a = (uint64_t)(rdi) & ~0ULL, b = (uint64_t)(rcx) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L162;
    rcx = ML_M8(rbx, 0x10);
{
    const uint64_t a = (uint64_t)(ML_M1(rcx, 0x20)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L149;
    ML_M1(rcx, 0x20) = 0x1ULL;
    ML_M1(rbx, 0x20) = 0x0ULL;
    rdx = rbx;
    rcx = rbp;
    rax = ML_CALL(14173b0e0);
    rcx = ML_M8(rbx, 0x10);
L149:
{
    const uint64_t a = (uint64_t)(ML_M1(rcx, 0x21)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L153;
    rdi = rbx;
    goto L182;
L153:
    rax = ML_M8(rcx, 0x0);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x20)) & 0xFFULL, b = (uint64_t)(0x1ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L187;
    rax = ML_M8(rcx, 0x10);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x20)) & 0xFFULL, b = (uint64_t)(0x1ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L187;
    ML_M1(rcx, 0x20) = 0x0ULL;
    rdi = rbx;
    goto L182;
L162:
{
    const uint64_t a = (uint64_t)(ML_M1(rcx, 0x20)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L170;
    ML_M1(rcx, 0x20) = 0x1ULL;
    ML_M1(rbx, 0x20) = 0x0ULL;
    rdx = rbx;
    rcx = rbp;
    rax = ML_CALL(14173b140);
    rcx = ML_M8(rbx, 0x0);
L170:
{
    const uint64_t a = (uint64_t)(ML_M1(rcx, 0x21)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L174;
    rdi = rbx;
    goto L182;
L174:
    rax = ML_M8(rcx, 0x10);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x20)) & 0xFFULL, b = (uint64_t)(0x1ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L206;
    rax = ML_M8(rcx, 0x0);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x20)) & 0xFFULL, b = (uint64_t)(0x1ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L206;
    ML_M1(rcx, 0x20) = 0x0ULL;
    rdi = rbx;
L182:
    rbx = ML_M8(rbx, 0x8);
    rax = ML_M8(rbp, 0x30);
{
    const uint64_t a = (uint64_t)(rdi) & ~0ULL, b = (uint64_t)(ML_M8(rax, 0x8)) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (f_zf) goto L224;
    goto L135;
L187:
    rax = ML_M8(rcx, 0x10);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x20)) & 0xFFULL, b = (uint64_t)(0x1ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L197;
    rax = ML_M8(rcx, 0x0);
    ML_M1(rax, 0x20) = 0x1ULL;
    ML_M1(rcx, 0x20) = 0x0ULL;
    rdx = rcx;
    rcx = rbp;
    rax = ML_CALL(14173b140);
    rcx = ML_M8(rbx, 0x10);
L197:
    rax = ML_M1(rbx, 0x20);
    ML_M1(rcx, 0x20) = (uint8_t)rax;
    ML_M1(rbx, 0x20) = 0x1ULL;
    rax = ML_M8(rcx, 0x10);
    ML_M1(rax, 0x20) = 0x1ULL;
    rdx = rbx;
    rcx = rbp;
    rax = ML_CALL(14173b0e0);
    goto L224;
L206:
    rax = ML_M8(rcx, 0x0);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x20)) & 0xFFULL, b = (uint64_t)(0x1ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L216;
    rax = ML_M8(rcx, 0x10);
    ML_M1(rax, 0x20) = 0x1ULL;
    ML_M1(rcx, 0x20) = 0x0ULL;
    rdx = rcx;
    rcx = rbp;
    rax = ML_CALL(14173b0e0);
    rcx = ML_M8(rbx, 0x0);
L216:
    rax = ML_M1(rbx, 0x20);
    ML_M1(rcx, 0x20) = (uint8_t)rax;
    ML_M1(rbx, 0x20) = 0x1ULL;
    rax = ML_M8(rcx, 0x0);
    ML_M1(rax, 0x20) = 0x1ULL;
    rdx = rbx;
    rcx = rbp;
    rax = ML_CALL(14173b140);
L224:
    ML_M1(rdi, 0x20) = 0x1ULL;
L225:
    rcx = rsi;
    rax = ML_CALL(1417f2fdc);
    rax = ML_M8(rbp, 0x38);
{
    const uint64_t r = ((uint64_t)(rax) & ~0ULL) & ((uint64_t)(rax) & ~0ULL);
    f_zf = (r == 0); f_cf = false; f_sf = ((r & 0x8000000000000000ULL) != 0);
    f_of = false;
}
    if (f_zf) goto L232;
    rax = rax - 1;
    ML_M8(rbp, 0x38) = rax;
L232:
    rcx = rsp + 0x20;
    rax = ML_M8(r12, 0x0);
    ML_M8(rcx, 0x0) = rax;
    rax = ML_M8(r12, 0x8);
    ML_M8(rcx, 0x8) = rax;
    rax = ML_M8(rsp, 0x28);
    ML_M8(rsp, 0x28) = rax;
    rax = ML_M8(rbp, 0x0);
    ML_M8(rsp, 0x20) = rax;
    rcx = rsp + 0x20;
    rax = ML_M8(rcx, 0x0);
    ML_M8(r13, 0x0) = rax;
    rax = ML_M8(rcx, 0x8);
    ML_M8(r13, 0x8) = rax;
    rax = r13;
    r11 = rsp + 0xa0;
    rbx = ML_M8(r11, 0x20);
    rbp = ML_M8(r11, 0x28);
    rsi = ML_M8(r11, 0x30);
    rsp = r11;
    { const uint64_t v = ML_M8(rsp, 0); rsp += 8; r13 = v; }
    { const uint64_t v = ML_M8(rsp, 0); rsp += 8; r12 = v; }
    { const uint64_t v = ML_M8(rsp, 0); rsp += 8; rdi = v; }
    return rax;
#undef ML_CALL
    return rax;
}

uint64_t SynLift_141744560(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A) {
    uint64_t rax = 0, rbx = 0, rbp = 0, rsi = 0, rdi = 0, r10 = 0, r11 = 0, r12 = 0, r13 = 0, r14 = 0, r15 = 0;
    uint64_t rcx = rcxA, rdx = rdxA, r8 = r8A, r9 = r9A;
    bool f_zf = false, f_cf = false, f_sf = false, f_of = false;
    uint8_t xmm0[16] = {0}, xmm1[16] = {0}, xmm2[16] = {0}, xmm3[16] = {0}, xmm4[16] = {0}, xmm5[16] = {0};
    alignas(16) uint8_t stkFrame[0x400] = {0};
    uint64_t rsp = (uint64_t)(uintptr_t)(stkFrame + 0x200);
#define ML_CALL(t) g_fnLIFT_##t(rcx, rdx, r8, r9, ML_M8(rsp, 0x20), ML_M8(rsp, 0x28))
    r8 = ML_M8(rdx, 0x0);
    rax = ML_M8(r8, 0x10);
    ML_M8(rdx, 0x0) = rax;
    rax = ML_M8(r8, 0x10);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L7;
    ML_M8(rax, 0x8) = rdx;
L7:
    rax = ML_M8(rdx, 0x8);
    ML_M8(r8, 0x8) = rax;
    rax = ML_M8(rcx, 0x30);
{
    const uint64_t a = (uint64_t)(rdx) & ~0ULL, b = (uint64_t)(ML_M8(rax, 0x8)) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L16;
    ML_M8(rax, 0x8) = r8;
    ML_M8(r8, 0x10) = rdx;
    ML_M8(rdx, 0x8) = r8;
    return rax;
L16:
    rax = ML_M8(rdx, 0x8);
{
    const uint64_t a = (uint64_t)(rdx) & ~0ULL, b = (uint64_t)(ML_M8(rax, 0x10)) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L23;
    ML_M8(rax, 0x10) = r8;
    ML_M8(r8, 0x10) = rdx;
    ML_M8(rdx, 0x8) = r8;
    return rax;
L23:
    ML_M8(rax, 0x0) = r8;
    ML_M8(r8, 0x10) = rdx;
    ML_M8(rdx, 0x8) = r8;
    return rax;
#undef ML_CALL
    return rax;
}

uint64_t SynLift_1417447d0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A) {
    uint64_t rax = 0, rbx = 0, rbp = 0, rsi = 0, rdi = 0, r10 = 0, r11 = 0, r12 = 0, r13 = 0, r14 = 0, r15 = 0;
    uint64_t rcx = rcxA, rdx = rdxA, r8 = r8A, r9 = r9A;
    bool f_zf = false, f_cf = false, f_sf = false, f_of = false;
    uint8_t xmm0[16] = {0}, xmm1[16] = {0}, xmm2[16] = {0}, xmm3[16] = {0}, xmm4[16] = {0}, xmm5[16] = {0};
    alignas(16) uint8_t stkFrame[0x400] = {0};
    uint64_t rsp = (uint64_t)(uintptr_t)(stkFrame + 0x200);
#define ML_CALL(t) g_fnLIFT_##t(rcx, rdx, r8, r9, ML_M8(rsp, 0x20), ML_M8(rsp, 0x28))
    rsp -= 8; ML_M8(rsp, 0) = rbx;
    rsp = rsp - (0x20ULL);
{
    const uint64_t a = (uint64_t)(ML_M8(rcx, 0x0)) & ~0ULL, b = (uint64_t)(0x0ULL) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    rbx = rcx;
    if (!f_zf) goto L6;
    rax = ML_CALL(1418233c0);
L6:
    rcx = ML_M8(rbx, 0x8);
{
    const uint64_t a = (uint64_t)(ML_M1(rcx, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L12;
    rsp = rsp + (0x20ULL);
    { const uint64_t v = ML_M8(rsp, 0); rsp += 8; rbx = v; }
    return ML_CALL(1418233c0);   // tail call
L12:
    rax = ML_M8(rcx, 0x10);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L27;
    rcx = ML_M8(rax, 0x0);
{
    const uint64_t a = (uint64_t)(ML_M1(rcx, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L23;
    ;
L19:
    rax = rcx;
    rcx = ML_M8(rcx, 0x0);
{
    const uint64_t a = (uint64_t)(ML_M1(rcx, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L19;
L23:
    ML_M8(rbx, 0x8) = rax;
    rsp = rsp + (0x20ULL);
    { const uint64_t v = ML_M8(rsp, 0); rsp += 8; rbx = v; }
    return rax;
L27:
    rcx = ML_M8(rcx, 0x8);
{
    const uint64_t a = (uint64_t)(ML_M1(rcx, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L37;
L30:
    rax = ML_M8(rcx, 0x10);
{
    const uint64_t a = (uint64_t)(ML_M8(rbx, 0x8)) & ~0ULL, b = (uint64_t)(rax) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L37;
    ML_M8(rbx, 0x8) = rcx;
    rcx = ML_M8(rcx, 0x8);
{
    const uint64_t a = (uint64_t)(ML_M1(rcx, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L30;
L37:
    ML_M8(rbx, 0x8) = rcx;
    rsp = rsp + (0x20ULL);
    { const uint64_t v = ML_M8(rsp, 0); rsp += 8; rbx = v; }
    return rax;
#undef ML_CALL
    return rax;
}

uint64_t SynLift_141744cb0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A) {
    uint64_t rax = 0, rbx = 0, rbp = 0, rsi = 0, rdi = 0, r10 = 0, r11 = 0, r12 = 0, r13 = 0, r14 = 0, r15 = 0;
    uint64_t rcx = rcxA, rdx = rdxA, r8 = r8A, r9 = r9A;
    bool f_zf = false, f_cf = false, f_sf = false, f_of = false;
    uint8_t xmm0[16] = {0}, xmm1[16] = {0}, xmm2[16] = {0}, xmm3[16] = {0}, xmm4[16] = {0}, xmm5[16] = {0};
    alignas(16) uint8_t stkFrame[0x400] = {0};
    uint64_t rsp = (uint64_t)(uintptr_t)(stkFrame + 0x200);
#define ML_CALL(t) g_fnLIFT_##t(rcx, rdx, r8, r9, ML_M8(rsp, 0x20), ML_M8(rsp, 0x28))
    rsp -= 8; ML_M8(rsp, 0) = rbx;
    rsp = rsp - (0x20ULL);
{
    const uint64_t a = (uint64_t)(ML_M8(rcx, 0x0)) & ~0ULL, b = (uint64_t)(0x0ULL) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    rbx = rcx;
    if (!f_zf) goto L6;
    rax = ML_CALL(1418233c0);
L6:
    rcx = ML_M8(rbx, 0x8);
{
    const uint64_t a = (uint64_t)(ML_M1(rcx, 0x3d)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L12;
    rsp = rsp + (0x20ULL);
    { const uint64_t v = ML_M8(rsp, 0); rsp += 8; rbx = v; }
    return ML_CALL(1418233c0);   // tail call
L12:
    rax = ML_M8(rcx, 0x10);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x3d)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L27;
    rcx = ML_M8(rax, 0x0);
{
    const uint64_t a = (uint64_t)(ML_M1(rcx, 0x3d)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L23;
    ;
L19:
    rax = rcx;
    rcx = ML_M8(rcx, 0x0);
{
    const uint64_t a = (uint64_t)(ML_M1(rcx, 0x3d)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L19;
L23:
    ML_M8(rbx, 0x8) = rax;
    rsp = rsp + (0x20ULL);
    { const uint64_t v = ML_M8(rsp, 0); rsp += 8; rbx = v; }
    return rax;
L27:
    rcx = ML_M8(rcx, 0x8);
{
    const uint64_t a = (uint64_t)(ML_M1(rcx, 0x3d)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L37;
L30:
    rax = ML_M8(rcx, 0x10);
{
    const uint64_t a = (uint64_t)(ML_M8(rbx, 0x8)) & ~0ULL, b = (uint64_t)(rax) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L37;
    ML_M8(rbx, 0x8) = rcx;
    rcx = ML_M8(rcx, 0x8);
{
    const uint64_t a = (uint64_t)(ML_M1(rcx, 0x3d)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L30;
L37:
    ML_M8(rbx, 0x8) = rcx;
    rsp = rsp + (0x20ULL);
    { const uint64_t v = ML_M8(rsp, 0); rsp += 8; rbx = v; }
    return rax;
#undef ML_CALL
    return rax;
}

uint64_t SynLift_141745ad0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A) {
    uint64_t rax = 0, rbx = 0, rbp = 0, rsi = 0, rdi = 0, r10 = 0, r11 = 0, r12 = 0, r13 = 0, r14 = 0, r15 = 0;
    uint64_t rcx = rcxA, rdx = rdxA, r8 = r8A, r9 = r9A;
    bool f_zf = false, f_cf = false, f_sf = false, f_of = false;
    uint8_t xmm0[16] = {0}, xmm1[16] = {0}, xmm2[16] = {0}, xmm3[16] = {0}, xmm4[16] = {0}, xmm5[16] = {0};
    alignas(16) uint8_t stkFrame[0x400] = {0};
    uint64_t rsp = (uint64_t)(uintptr_t)(stkFrame + 0x200);
#define ML_CALL(t) g_fnLIFT_##t(rcx, rdx, r8, r9, ML_M8(rsp, 0x20), ML_M8(rsp, 0x28))
    r8 = ML_M8(rdx, 0x10);
    rax = ML_M8(r8, 0x0);
    ML_M8(rdx, 0x10) = rax;
    rax = ML_M8(r8, 0x0);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L7;
    ML_M8(rax, 0x8) = rdx;
L7:
    rax = ML_M8(rdx, 0x8);
    ML_M8(r8, 0x8) = rax;
    rax = ML_M8(rcx, 0x30);
{
    const uint64_t a = (uint64_t)(rdx) & ~0ULL, b = (uint64_t)(ML_M8(rax, 0x8)) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L16;
    ML_M8(rax, 0x8) = r8;
    ML_M8(r8, 0x0) = rdx;
    ML_M8(rdx, 0x8) = r8;
    return rax;
L16:
    rax = ML_M8(rdx, 0x8);
{
    const uint64_t a = (uint64_t)(rdx) & ~0ULL, b = (uint64_t)(ML_M8(rax, 0x0)) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L23;
    ML_M8(rax, 0x0) = r8;
    ML_M8(r8, 0x0) = rdx;
    ML_M8(rdx, 0x8) = r8;
    return rax;
L23:
    ML_M8(rax, 0x10) = r8;
    ML_M8(r8, 0x0) = rdx;
    ML_M8(rdx, 0x8) = r8;
    return rax;
#undef ML_CALL
    return rax;
}

uint64_t SynLift_141745c30(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A) {
    uint64_t rax = 0, rbx = 0, rbp = 0, rsi = 0, rdi = 0, r10 = 0, r11 = 0, r12 = 0, r13 = 0, r14 = 0, r15 = 0;
    uint64_t rcx = rcxA, rdx = rdxA, r8 = r8A, r9 = r9A;
    bool f_zf = false, f_cf = false, f_sf = false, f_of = false;
    uint8_t xmm0[16] = {0}, xmm1[16] = {0}, xmm2[16] = {0}, xmm3[16] = {0}, xmm4[16] = {0}, xmm5[16] = {0};
    alignas(16) uint8_t stkFrame[0x400] = {0};
    uint64_t rsp = (uint64_t)(uintptr_t)(stkFrame + 0x200);
#define ML_CALL(t) g_fnLIFT_##t(rcx, rdx, r8, r9, ML_M8(rsp, 0x20), ML_M8(rsp, 0x28))
    r8 = ML_M8(rdx, 0x10);
    rax = ML_M8(r8, 0x0);
    ML_M8(rdx, 0x10) = rax;
    rax = ML_M8(r8, 0x0);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x3d)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L7;
    ML_M8(rax, 0x8) = rdx;
L7:
    rax = ML_M8(rdx, 0x8);
    ML_M8(r8, 0x8) = rax;
    rax = ML_M8(rcx, 0x30);
{
    const uint64_t a = (uint64_t)(rdx) & ~0ULL, b = (uint64_t)(ML_M8(rax, 0x8)) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L16;
    ML_M8(rax, 0x8) = r8;
    ML_M8(r8, 0x0) = rdx;
    ML_M8(rdx, 0x8) = r8;
    return rax;
L16:
    rax = ML_M8(rdx, 0x8);
{
    const uint64_t a = (uint64_t)(rdx) & ~0ULL, b = (uint64_t)(ML_M8(rax, 0x0)) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L23;
    ML_M8(rax, 0x0) = r8;
    ML_M8(r8, 0x0) = rdx;
    ML_M8(rdx, 0x8) = r8;
    return rax;
L23:
    ML_M8(rax, 0x10) = r8;
    ML_M8(r8, 0x0) = rdx;
    ML_M8(rdx, 0x8) = r8;
    return rax;
#undef ML_CALL
    return rax;
}

uint64_t SynLift_141745c90(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A) {
    uint64_t rax = 0, rbx = 0, rbp = 0, rsi = 0, rdi = 0, r10 = 0, r11 = 0, r12 = 0, r13 = 0, r14 = 0, r15 = 0;
    uint64_t rcx = rcxA, rdx = rdxA, r8 = r8A, r9 = r9A;
    bool f_zf = false, f_cf = false, f_sf = false, f_of = false;
    uint8_t xmm0[16] = {0}, xmm1[16] = {0}, xmm2[16] = {0}, xmm3[16] = {0}, xmm4[16] = {0}, xmm5[16] = {0};
    alignas(16) uint8_t stkFrame[0x400] = {0};
    uint64_t rsp = (uint64_t)(uintptr_t)(stkFrame + 0x200);
#define ML_CALL(t) g_fnLIFT_##t(rcx, rdx, r8, r9, ML_M8(rsp, 0x20), ML_M8(rsp, 0x28))
    r8 = ML_M8(rdx, 0x0);
    rax = ML_M8(r8, 0x10);
    ML_M8(rdx, 0x0) = rax;
    rax = ML_M8(r8, 0x10);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x3d)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L7;
    ML_M8(rax, 0x8) = rdx;
L7:
    rax = ML_M8(rdx, 0x8);
    ML_M8(r8, 0x8) = rax;
    rax = ML_M8(rcx, 0x30);
{
    const uint64_t a = (uint64_t)(rdx) & ~0ULL, b = (uint64_t)(ML_M8(rax, 0x8)) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L16;
    ML_M8(rax, 0x8) = r8;
    ML_M8(r8, 0x10) = rdx;
    ML_M8(rdx, 0x8) = r8;
    return rax;
L16:
    rax = ML_M8(rdx, 0x8);
{
    const uint64_t a = (uint64_t)(rdx) & ~0ULL, b = (uint64_t)(ML_M8(rax, 0x10)) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L23;
    ML_M8(rax, 0x10) = r8;
    ML_M8(r8, 0x10) = rdx;
    ML_M8(rdx, 0x8) = r8;
    return rax;
L23:
    ML_M8(rax, 0x0) = r8;
    ML_M8(r8, 0x10) = rdx;
    ML_M8(rdx, 0x8) = r8;
    return rax;
#undef ML_CALL
    return rax;
}

__attribute__((weak)) uint64_t (*g_fnLIFT_141744cb0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t) = nullptr;
__attribute__((weak)) uint64_t (*g_fnLIFT_141745c30)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t) = nullptr;
__attribute__((weak)) uint64_t (*g_fnLIFT_141745c90)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t) = nullptr;
uint64_t SynLift_141747400(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A) {
    uint64_t rax = 0, rbx = 0, rbp = 0, rsi = 0, rdi = 0, r10 = 0, r11 = 0, r12 = 0, r13 = 0, r14 = 0, r15 = 0;
    uint64_t rcx = rcxA, rdx = rdxA, r8 = r8A, r9 = r9A;
    bool f_zf = false, f_cf = false, f_sf = false, f_of = false;
    uint8_t xmm0[16] = {0}, xmm1[16] = {0}, xmm2[16] = {0}, xmm3[16] = {0}, xmm4[16] = {0}, xmm5[16] = {0};
    alignas(16) uint8_t stkFrame[0x400] = {0};
    uint64_t rsp = (uint64_t)(uintptr_t)(stkFrame + 0x200);
#define ML_CALL(t) g_fnLIFT_##t(rcx, rdx, r8, r9, ML_M8(rsp, 0x20), ML_M8(rsp, 0x28))
    rax = rsp;
    rsp -= 8; ML_M8(rsp, 0) = rdi;
    rsp -= 8; ML_M8(rsp, 0) = r12;
    rsp -= 8; ML_M8(rsp, 0) = r13;
    rsp = rsp - (0xa0ULL);
    ML_M8(rsp, 0x30) = 0xfffffffffffffffeULL;
    ML_M8(rax, 0x8) = rbx;
    ML_M8(rax, 0x10) = rbp;
    ML_M8(rax, 0x18) = rsi;
    r12 = r8;
    r13 = rdx;
    rbp = rcx;
    rsi = ML_M8(r8, 0x8);
{
    const uint64_t a = (uint64_t)(ML_M1(rsi, 0x3d)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L30;
    rdx = (uintptr_t)0x141825ca8;
    rcx = rax - 0x40;
    rax = ML_CALL(141823270);
    rcx = rsp + 0x38;
    rax = ML_CALL(1418233f8);
    rax = (uintptr_t)0x141824a60;
    ML_M8(rsp, 0x38) = rax;
    rdx = rsp + 0x78;
    rcx = rsp + 0x50;
    rax = ML_CALL(141823288);
    rax = (uintptr_t)0x141824ba0;
    ML_M8(rsp, 0x38) = rax;
    rdx = (uintptr_t)0x141881e50;
    rcx = rsp + 0x38;
    rax = ML_CALL(1417f3154);
L30:
    rcx = r8;
    rax = ML_CALL(141744cb0);
    r11 = ML_M8(rsi, 0x0);
{
    const uint64_t a = (uint64_t)(ML_M1(r11, 0x3d)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L37;
    rdi = ML_M8(rsi, 0x10);
    goto L46;
L37:
    rax = ML_M8(rsi, 0x10);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x3d)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L42;
    rdi = r11;
    goto L46;
L42:
    rcx = ML_M8(r12, 0x8);
    rdi = ML_M8(rcx, 0x10);
{
    const uint64_t a = (uint64_t)(rcx) & ~0ULL, b = (uint64_t)(rsi) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L93;
L46:
    rbx = ML_M8(rsi, 0x8);
{
    const uint64_t a = (uint64_t)(ML_M1(rdi, 0x3d)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L50;
    ML_M8(rdi, 0x8) = rbx;
L50:
    rax = ML_M8(rbp, 0x30);
{
    const uint64_t a = (uint64_t)(ML_M8(rax, 0x8)) & ~0ULL, b = (uint64_t)(rsi) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L55;
    ML_M8(rax, 0x8) = rdi;
    goto L60;
L55:
{
    const uint64_t a = (uint64_t)(ML_M8(rbx, 0x0)) & ~0ULL, b = (uint64_t)(rsi) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L59;
    ML_M8(rbx, 0x0) = rdi;
    goto L60;
L59:
    ML_M8(rbx, 0x10) = rdi;
L60:
    rdx = ML_M8(rbp, 0x30);
{
    const uint64_t a = (uint64_t)(ML_M8(rdx, 0x0)) & ~0ULL, b = (uint64_t)(rsi) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L76;
{
    const uint64_t a = (uint64_t)(ML_M1(rdi, 0x3d)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L67;
    rcx = rbx;
    goto L75;
L67:
    rcx = rdi;
    rax = ML_M8(rdi, 0x0);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x3d)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L75;
L71:
    rcx = rax;
    rax = ML_M8(rax, 0x0);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x3d)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L71;
L75:
    ML_M8(rdx, 0x0) = rcx;
L76:
    rdx = ML_M8(rbp, 0x30);
{
    const uint64_t a = (uint64_t)(ML_M8(rdx, 0x10)) & ~0ULL, b = (uint64_t)(rsi) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L130;
{
    const uint64_t a = (uint64_t)(ML_M1(rdi, 0x3d)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L83;
    rcx = rbx;
    goto L91;
L83:
    rcx = rdi;
    rax = ML_M8(rdi, 0x10);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x3d)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L91;
L87:
    rcx = rax;
    rax = ML_M8(rax, 0x10);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x3d)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L87;
L91:
    ML_M8(rdx, 0x10) = rcx;
    goto L130;
L93:
    ML_M8(r11, 0x8) = rcx;
    rax = ML_M8(rsi, 0x0);
    ML_M8(rcx, 0x0) = rax;
{
    const uint64_t a = (uint64_t)(rcx) & ~0ULL, b = (uint64_t)(ML_M8(rsi, 0x10)) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L100;
    rbx = rcx;
    goto L109;
L100:
    rbx = ML_M8(rcx, 0x8);
{
    const uint64_t a = (uint64_t)(ML_M1(rdi, 0x3d)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L104;
    ML_M8(rdi, 0x8) = rbx;
L104:
    ML_M8(rbx, 0x0) = rdi;
    rax = ML_M8(rsi, 0x10);
    ML_M8(rcx, 0x10) = rax;
    rax = ML_M8(rsi, 0x10);
    ML_M8(rax, 0x8) = rcx;
L109:
    rax = ML_M8(rbp, 0x30);
{
    const uint64_t a = (uint64_t)(ML_M8(rax, 0x8)) & ~0ULL, b = (uint64_t)(rsi) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L114;
    ML_M8(rax, 0x8) = rcx;
    goto L120;
L114:
    rax = ML_M8(rsi, 0x8);
{
    const uint64_t a = (uint64_t)(ML_M8(rax, 0x0)) & ~0ULL, b = (uint64_t)(rsi) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L119;
    ML_M8(rax, 0x0) = rcx;
    goto L120;
L119:
    ML_M8(rax, 0x10) = rcx;
L120:
    rax = ML_M8(rsi, 0x8);
    ML_M8(rcx, 0x8) = rax;
    rdx = rsi + 0x3c;
    r8 = rcx + 0x3c;
{
    const uint64_t a = (uint64_t)(r8) & ~0ULL, b = (uint64_t)(rdx) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (f_zf) goto L130;
    rcx = ML_M1(r8, 0x0);
    rax = ML_M1(rdx, 0x0);
    ML_M1(r8, 0x0) = (uint8_t)rax;
    ML_M1(rdx, 0x0) = (uint8_t)rcx;
L130:
{
    const uint64_t a = (uint64_t)(ML_M1(rsi, 0x3c)) & 0xFFULL, b = (uint64_t)(0x1ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L225;
    rax = ML_M8(rbp, 0x30);
{
    const uint64_t a = (uint64_t)(rdi) & ~0ULL, b = (uint64_t)(ML_M8(rax, 0x8)) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (f_zf) goto L224;
L135:
{
    const uint64_t a = (uint64_t)(ML_M1(rdi, 0x3c)) & 0xFFULL, b = (uint64_t)(0x1ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L224;
    rcx = ML_M8(rbx, 0x0);
{
    const uint64_t a = (uint64_t)(rdi) & ~0ULL, b = (uint64_t)(rcx) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L162;
    rcx = ML_M8(rbx, 0x10);
{
    const uint64_t a = (uint64_t)(ML_M1(rcx, 0x3c)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L149;
    ML_M1(rcx, 0x3c) = 0x1ULL;
    ML_M1(rbx, 0x3c) = 0x0ULL;
    rdx = rbx;
    rcx = rbp;
    rax = ML_CALL(141745c30);
    rcx = ML_M8(rbx, 0x10);
L149:
{
    const uint64_t a = (uint64_t)(ML_M1(rcx, 0x3d)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L153;
    rdi = rbx;
    goto L182;
L153:
    rax = ML_M8(rcx, 0x0);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x3c)) & 0xFFULL, b = (uint64_t)(0x1ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L187;
    rax = ML_M8(rcx, 0x10);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x3c)) & 0xFFULL, b = (uint64_t)(0x1ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L187;
    ML_M1(rcx, 0x3c) = 0x0ULL;
    rdi = rbx;
    goto L182;
L162:
{
    const uint64_t a = (uint64_t)(ML_M1(rcx, 0x3c)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L170;
    ML_M1(rcx, 0x3c) = 0x1ULL;
    ML_M1(rbx, 0x3c) = 0x0ULL;
    rdx = rbx;
    rcx = rbp;
    rax = ML_CALL(141745c90);
    rcx = ML_M8(rbx, 0x0);
L170:
{
    const uint64_t a = (uint64_t)(ML_M1(rcx, 0x3d)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L174;
    rdi = rbx;
    goto L182;
L174:
    rax = ML_M8(rcx, 0x10);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x3c)) & 0xFFULL, b = (uint64_t)(0x1ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L206;
    rax = ML_M8(rcx, 0x0);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x3c)) & 0xFFULL, b = (uint64_t)(0x1ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L206;
    ML_M1(rcx, 0x3c) = 0x0ULL;
    rdi = rbx;
L182:
    rbx = ML_M8(rbx, 0x8);
    rax = ML_M8(rbp, 0x30);
{
    const uint64_t a = (uint64_t)(rdi) & ~0ULL, b = (uint64_t)(ML_M8(rax, 0x8)) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (f_zf) goto L224;
    goto L135;
L187:
    rax = ML_M8(rcx, 0x10);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x3c)) & 0xFFULL, b = (uint64_t)(0x1ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L197;
    rax = ML_M8(rcx, 0x0);
    ML_M1(rax, 0x3c) = 0x1ULL;
    ML_M1(rcx, 0x3c) = 0x0ULL;
    rdx = rcx;
    rcx = rbp;
    rax = ML_CALL(141745c90);
    rcx = ML_M8(rbx, 0x10);
L197:
    rax = ML_M1(rbx, 0x3c);
    ML_M1(rcx, 0x3c) = (uint8_t)rax;
    ML_M1(rbx, 0x3c) = 0x1ULL;
    rax = ML_M8(rcx, 0x10);
    ML_M1(rax, 0x3c) = 0x1ULL;
    rdx = rbx;
    rcx = rbp;
    rax = ML_CALL(141745c30);
    goto L224;
L206:
    rax = ML_M8(rcx, 0x0);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x3c)) & 0xFFULL, b = (uint64_t)(0x1ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L216;
    rax = ML_M8(rcx, 0x10);
    ML_M1(rax, 0x3c) = 0x1ULL;
    ML_M1(rcx, 0x3c) = 0x0ULL;
    rdx = rcx;
    rcx = rbp;
    rax = ML_CALL(141745c30);
    rcx = ML_M8(rbx, 0x0);
L216:
    rax = ML_M1(rbx, 0x3c);
    ML_M1(rcx, 0x3c) = (uint8_t)rax;
    ML_M1(rbx, 0x3c) = 0x1ULL;
    rax = ML_M8(rcx, 0x0);
    ML_M1(rax, 0x3c) = 0x1ULL;
    rdx = rbx;
    rcx = rbp;
    rax = ML_CALL(141745c90);
L224:
    ML_M1(rdi, 0x3c) = 0x1ULL;
L225:
    rcx = rsi;
    rax = ML_CALL(1417f2fdc);
    rax = ML_M8(rbp, 0x38);
{
    const uint64_t r = ((uint64_t)(rax) & ~0ULL) & ((uint64_t)(rax) & ~0ULL);
    f_zf = (r == 0); f_cf = false; f_sf = ((r & 0x8000000000000000ULL) != 0);
    f_of = false;
}
    if (f_zf) goto L232;
    rax = rax - 1;
    ML_M8(rbp, 0x38) = rax;
L232:
    rcx = rsp + 0x20;
    rax = ML_M8(r12, 0x0);
    ML_M8(rcx, 0x0) = rax;
    rax = ML_M8(r12, 0x8);
    ML_M8(rcx, 0x8) = rax;
    rax = ML_M8(rsp, 0x28);
    ML_M8(rsp, 0x28) = rax;
    rax = ML_M8(rbp, 0x0);
    ML_M8(rsp, 0x20) = rax;
    rcx = rsp + 0x20;
    rax = ML_M8(rcx, 0x0);
    ML_M8(r13, 0x0) = rax;
    rax = ML_M8(rcx, 0x8);
    ML_M8(r13, 0x8) = rax;
    rax = r13;
    r11 = rsp + 0xa0;
    rbx = ML_M8(r11, 0x20);
    rbp = ML_M8(r11, 0x28);
    rsi = ML_M8(r11, 0x30);
    rsp = r11;
    { const uint64_t v = ML_M8(rsp, 0); rsp += 8; r13 = v; }
    { const uint64_t v = ML_M8(rsp, 0); rsp += 8; r12 = v; }
    { const uint64_t v = ML_M8(rsp, 0); rsp += 8; rdi = v; }
    return rax;
#undef ML_CALL
    return rax;
}

__attribute__((weak)) uint64_t (*g_fnLIFT_141744560)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t) = nullptr;
__attribute__((weak)) uint64_t (*g_fnLIFT_1417447d0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t) = nullptr;
__attribute__((weak)) uint64_t (*g_fnLIFT_141745ad0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t) = nullptr;
uint64_t SynLift_141749c00(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A) {
    uint64_t rax = 0, rbx = 0, rbp = 0, rsi = 0, rdi = 0, r10 = 0, r11 = 0, r12 = 0, r13 = 0, r14 = 0, r15 = 0;
    uint64_t rcx = rcxA, rdx = rdxA, r8 = r8A, r9 = r9A;
    bool f_zf = false, f_cf = false, f_sf = false, f_of = false;
    uint8_t xmm0[16] = {0}, xmm1[16] = {0}, xmm2[16] = {0}, xmm3[16] = {0}, xmm4[16] = {0}, xmm5[16] = {0};
    alignas(16) uint8_t stkFrame[0x400] = {0};
    uint64_t rsp = (uint64_t)(uintptr_t)(stkFrame + 0x200);
#define ML_CALL(t) g_fnLIFT_##t(rcx, rdx, r8, r9, ML_M8(rsp, 0x20), ML_M8(rsp, 0x28))
    rax = rsp;
    rsp -= 8; ML_M8(rsp, 0) = rdi;
    rsp -= 8; ML_M8(rsp, 0) = r12;
    rsp -= 8; ML_M8(rsp, 0) = r13;
    rsp = rsp - (0xa0ULL);
    ML_M8(rsp, 0x30) = 0xfffffffffffffffeULL;
    ML_M8(rax, 0x8) = rbx;
    ML_M8(rax, 0x10) = rbp;
    ML_M8(rax, 0x18) = rsi;
    r12 = r8;
    r13 = rdx;
    rbp = rcx;
    rsi = ML_M8(r8, 0x8);
{
    const uint64_t a = (uint64_t)(ML_M1(rsi, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L30;
    rdx = (uintptr_t)0x141825ca8;
    rcx = rax - 0x40;
    rax = ML_CALL(141823270);
    rcx = rsp + 0x38;
    rax = ML_CALL(1418233f8);
    rax = (uintptr_t)0x141824a60;
    ML_M8(rsp, 0x38) = rax;
    rdx = rsp + 0x78;
    rcx = rsp + 0x50;
    rax = ML_CALL(141823288);
    rax = (uintptr_t)0x141824ba0;
    ML_M8(rsp, 0x38) = rax;
    rdx = (uintptr_t)0x141881e50;
    rcx = rsp + 0x38;
    rax = ML_CALL(1417f3154);
L30:
    rcx = r8;
    rax = ML_CALL(1417447d0);
    r11 = ML_M8(rsi, 0x0);
{
    const uint64_t a = (uint64_t)(ML_M1(r11, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L37;
    rdi = ML_M8(rsi, 0x10);
    goto L46;
L37:
    rax = ML_M8(rsi, 0x10);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L42;
    rdi = r11;
    goto L46;
L42:
    rcx = ML_M8(r12, 0x8);
    rdi = ML_M8(rcx, 0x10);
{
    const uint64_t a = (uint64_t)(rcx) & ~0ULL, b = (uint64_t)(rsi) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L93;
L46:
    rbx = ML_M8(rsi, 0x8);
{
    const uint64_t a = (uint64_t)(ML_M1(rdi, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L50;
    ML_M8(rdi, 0x8) = rbx;
L50:
    rax = ML_M8(rbp, 0x30);
{
    const uint64_t a = (uint64_t)(ML_M8(rax, 0x8)) & ~0ULL, b = (uint64_t)(rsi) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L55;
    ML_M8(rax, 0x8) = rdi;
    goto L60;
L55:
{
    const uint64_t a = (uint64_t)(ML_M8(rbx, 0x0)) & ~0ULL, b = (uint64_t)(rsi) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L59;
    ML_M8(rbx, 0x0) = rdi;
    goto L60;
L59:
    ML_M8(rbx, 0x10) = rdi;
L60:
    rdx = ML_M8(rbp, 0x30);
{
    const uint64_t a = (uint64_t)(ML_M8(rdx, 0x0)) & ~0ULL, b = (uint64_t)(rsi) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L76;
{
    const uint64_t a = (uint64_t)(ML_M1(rdi, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L67;
    rcx = rbx;
    goto L75;
L67:
    rcx = rdi;
    rax = ML_M8(rdi, 0x0);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L75;
L71:
    rcx = rax;
    rax = ML_M8(rax, 0x0);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L71;
L75:
    ML_M8(rdx, 0x0) = rcx;
L76:
    rdx = ML_M8(rbp, 0x30);
{
    const uint64_t a = (uint64_t)(ML_M8(rdx, 0x10)) & ~0ULL, b = (uint64_t)(rsi) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L130;
{
    const uint64_t a = (uint64_t)(ML_M1(rdi, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L83;
    rcx = rbx;
    goto L91;
L83:
    rcx = rdi;
    rax = ML_M8(rdi, 0x10);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L91;
L87:
    rcx = rax;
    rax = ML_M8(rax, 0x10);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L87;
L91:
    ML_M8(rdx, 0x10) = rcx;
    goto L130;
L93:
    ML_M8(r11, 0x8) = rcx;
    rax = ML_M8(rsi, 0x0);
    ML_M8(rcx, 0x0) = rax;
{
    const uint64_t a = (uint64_t)(rcx) & ~0ULL, b = (uint64_t)(ML_M8(rsi, 0x10)) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L100;
    rbx = rcx;
    goto L109;
L100:
    rbx = ML_M8(rcx, 0x8);
{
    const uint64_t a = (uint64_t)(ML_M1(rdi, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L104;
    ML_M8(rdi, 0x8) = rbx;
L104:
    ML_M8(rbx, 0x0) = rdi;
    rax = ML_M8(rsi, 0x10);
    ML_M8(rcx, 0x10) = rax;
    rax = ML_M8(rsi, 0x10);
    ML_M8(rax, 0x8) = rcx;
L109:
    rax = ML_M8(rbp, 0x30);
{
    const uint64_t a = (uint64_t)(ML_M8(rax, 0x8)) & ~0ULL, b = (uint64_t)(rsi) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L114;
    ML_M8(rax, 0x8) = rcx;
    goto L120;
L114:
    rax = ML_M8(rsi, 0x8);
{
    const uint64_t a = (uint64_t)(ML_M8(rax, 0x0)) & ~0ULL, b = (uint64_t)(rsi) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L119;
    ML_M8(rax, 0x0) = rcx;
    goto L120;
L119:
    ML_M8(rax, 0x10) = rcx;
L120:
    rax = ML_M8(rsi, 0x8);
    ML_M8(rcx, 0x8) = rax;
    rdx = rsi + 0x28;
    r8 = rcx + 0x28;
{
    const uint64_t a = (uint64_t)(r8) & ~0ULL, b = (uint64_t)(rdx) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (f_zf) goto L130;
    rcx = ML_M1(r8, 0x0);
    rax = ML_M1(rdx, 0x0);
    ML_M1(r8, 0x0) = (uint8_t)rax;
    ML_M1(rdx, 0x0) = (uint8_t)rcx;
L130:
{
    const uint64_t a = (uint64_t)(ML_M1(rsi, 0x28)) & 0xFFULL, b = (uint64_t)(0x1ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L225;
    rax = ML_M8(rbp, 0x30);
{
    const uint64_t a = (uint64_t)(rdi) & ~0ULL, b = (uint64_t)(ML_M8(rax, 0x8)) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (f_zf) goto L224;
L135:
{
    const uint64_t a = (uint64_t)(ML_M1(rdi, 0x28)) & 0xFFULL, b = (uint64_t)(0x1ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L224;
    rcx = ML_M8(rbx, 0x0);
{
    const uint64_t a = (uint64_t)(rdi) & ~0ULL, b = (uint64_t)(rcx) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L162;
    rcx = ML_M8(rbx, 0x10);
{
    const uint64_t a = (uint64_t)(ML_M1(rcx, 0x28)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L149;
    ML_M1(rcx, 0x28) = 0x1ULL;
    ML_M1(rbx, 0x28) = 0x0ULL;
    rdx = rbx;
    rcx = rbp;
    rax = ML_CALL(141745ad0);
    rcx = ML_M8(rbx, 0x10);
L149:
{
    const uint64_t a = (uint64_t)(ML_M1(rcx, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L153;
    rdi = rbx;
    goto L182;
L153:
    rax = ML_M8(rcx, 0x0);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x28)) & 0xFFULL, b = (uint64_t)(0x1ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L187;
    rax = ML_M8(rcx, 0x10);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x28)) & 0xFFULL, b = (uint64_t)(0x1ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L187;
    ML_M1(rcx, 0x28) = 0x0ULL;
    rdi = rbx;
    goto L182;
L162:
{
    const uint64_t a = (uint64_t)(ML_M1(rcx, 0x28)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L170;
    ML_M1(rcx, 0x28) = 0x1ULL;
    ML_M1(rbx, 0x28) = 0x0ULL;
    rdx = rbx;
    rcx = rbp;
    rax = ML_CALL(141744560);
    rcx = ML_M8(rbx, 0x0);
L170:
{
    const uint64_t a = (uint64_t)(ML_M1(rcx, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L174;
    rdi = rbx;
    goto L182;
L174:
    rax = ML_M8(rcx, 0x10);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x28)) & 0xFFULL, b = (uint64_t)(0x1ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L206;
    rax = ML_M8(rcx, 0x0);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x28)) & 0xFFULL, b = (uint64_t)(0x1ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L206;
    ML_M1(rcx, 0x28) = 0x0ULL;
    rdi = rbx;
L182:
    rbx = ML_M8(rbx, 0x8);
    rax = ML_M8(rbp, 0x30);
{
    const uint64_t a = (uint64_t)(rdi) & ~0ULL, b = (uint64_t)(ML_M8(rax, 0x8)) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (f_zf) goto L224;
    goto L135;
L187:
    rax = ML_M8(rcx, 0x10);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x28)) & 0xFFULL, b = (uint64_t)(0x1ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L197;
    rax = ML_M8(rcx, 0x0);
    ML_M1(rax, 0x28) = 0x1ULL;
    ML_M1(rcx, 0x28) = 0x0ULL;
    rdx = rcx;
    rcx = rbp;
    rax = ML_CALL(141744560);
    rcx = ML_M8(rbx, 0x10);
L197:
    rax = ML_M1(rbx, 0x28);
    ML_M1(rcx, 0x28) = (uint8_t)rax;
    ML_M1(rbx, 0x28) = 0x1ULL;
    rax = ML_M8(rcx, 0x10);
    ML_M1(rax, 0x28) = 0x1ULL;
    rdx = rbx;
    rcx = rbp;
    rax = ML_CALL(141745ad0);
    goto L224;
L206:
    rax = ML_M8(rcx, 0x0);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x28)) & 0xFFULL, b = (uint64_t)(0x1ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L216;
    rax = ML_M8(rcx, 0x10);
    ML_M1(rax, 0x28) = 0x1ULL;
    ML_M1(rcx, 0x28) = 0x0ULL;
    rdx = rcx;
    rcx = rbp;
    rax = ML_CALL(141745ad0);
    rcx = ML_M8(rbx, 0x0);
L216:
    rax = ML_M1(rbx, 0x28);
    ML_M1(rcx, 0x28) = (uint8_t)rax;
    ML_M1(rbx, 0x28) = 0x1ULL;
    rax = ML_M8(rcx, 0x0);
    ML_M1(rax, 0x28) = 0x1ULL;
    rdx = rbx;
    rcx = rbp;
    rax = ML_CALL(141744560);
L224:
    ML_M1(rdi, 0x28) = 0x1ULL;
L225:
    rcx = rsi;
    rax = ML_CALL(1417f2fdc);
    rax = ML_M8(rbp, 0x38);
{
    const uint64_t r = ((uint64_t)(rax) & ~0ULL) & ((uint64_t)(rax) & ~0ULL);
    f_zf = (r == 0); f_cf = false; f_sf = ((r & 0x8000000000000000ULL) != 0);
    f_of = false;
}
    if (f_zf) goto L232;
    rax = rax - 1;
    ML_M8(rbp, 0x38) = rax;
L232:
    rcx = rsp + 0x20;
    rax = ML_M8(r12, 0x0);
    ML_M8(rcx, 0x0) = rax;
    rax = ML_M8(r12, 0x8);
    ML_M8(rcx, 0x8) = rax;
    rax = ML_M8(rsp, 0x28);
    ML_M8(rsp, 0x28) = rax;
    rax = ML_M8(rbp, 0x0);
    ML_M8(rsp, 0x20) = rax;
    rcx = rsp + 0x20;
    rax = ML_M8(rcx, 0x0);
    ML_M8(r13, 0x0) = rax;
    rax = ML_M8(rcx, 0x8);
    ML_M8(r13, 0x8) = rax;
    rax = r13;
    r11 = rsp + 0xa0;
    rbx = ML_M8(r11, 0x20);
    rbp = ML_M8(r11, 0x28);
    rsi = ML_M8(r11, 0x30);
    rsp = r11;
    { const uint64_t v = ML_M8(rsp, 0); rsp += 8; r13 = v; }
    { const uint64_t v = ML_M8(rsp, 0); rsp += 8; r12 = v; }
    { const uint64_t v = ML_M8(rsp, 0); rsp += 8; rdi = v; }
    return rax;
#undef ML_CALL
    return rax;
}

uint64_t SynLift_14174fe10(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A) {
    uint64_t rax = 0, rbx = 0, rbp = 0, rsi = 0, rdi = 0, r10 = 0, r11 = 0, r12 = 0, r13 = 0, r14 = 0, r15 = 0;
    uint64_t rcx = rcxA, rdx = rdxA, r8 = r8A, r9 = r9A;
    bool f_zf = false, f_cf = false, f_sf = false, f_of = false;
    uint8_t xmm0[16] = {0}, xmm1[16] = {0}, xmm2[16] = {0}, xmm3[16] = {0}, xmm4[16] = {0}, xmm5[16] = {0};
    alignas(16) uint8_t stkFrame[0x400] = {0};
    uint64_t rsp = (uint64_t)(uintptr_t)(stkFrame + 0x200);
#define ML_CALL(t) g_fnLIFT_##t(rcx, rdx, r8, r9, ML_M8(rsp, 0x20), ML_M8(rsp, 0x28))
    r8 = ML_M8(rdx, 0x0);
    rax = ML_M8(r8, 0x10);
    ML_M8(rdx, 0x0) = rax;
    rax = ML_M8(r8, 0x10);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x2d)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L7;
    ML_M8(rax, 0x8) = rdx;
L7:
    rax = ML_M8(rdx, 0x8);
    ML_M8(r8, 0x8) = rax;
    rax = ML_M8(rcx, 0x30);
{
    const uint64_t a = (uint64_t)(rdx) & ~0ULL, b = (uint64_t)(ML_M8(rax, 0x8)) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L16;
    ML_M8(rax, 0x8) = r8;
    ML_M8(r8, 0x10) = rdx;
    ML_M8(rdx, 0x8) = r8;
    return rax;
L16:
    rax = ML_M8(rdx, 0x8);
{
    const uint64_t a = (uint64_t)(rdx) & ~0ULL, b = (uint64_t)(ML_M8(rax, 0x10)) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L23;
    ML_M8(rax, 0x10) = r8;
    ML_M8(r8, 0x10) = rdx;
    ML_M8(rdx, 0x8) = r8;
    return rax;
L23:
    ML_M8(rax, 0x0) = r8;
    ML_M8(r8, 0x10) = rdx;
    ML_M8(rdx, 0x8) = r8;
    return rax;
#undef ML_CALL
    return rax;
}

uint64_t SynLift_141750760(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A) {
    uint64_t rax = 0, rbx = 0, rbp = 0, rsi = 0, rdi = 0, r10 = 0, r11 = 0, r12 = 0, r13 = 0, r14 = 0, r15 = 0;
    uint64_t rcx = rcxA, rdx = rdxA, r8 = r8A, r9 = r9A;
    bool f_zf = false, f_cf = false, f_sf = false, f_of = false;
    uint8_t xmm0[16] = {0}, xmm1[16] = {0}, xmm2[16] = {0}, xmm3[16] = {0}, xmm4[16] = {0}, xmm5[16] = {0};
    alignas(16) uint8_t stkFrame[0x400] = {0};
    uint64_t rsp = (uint64_t)(uintptr_t)(stkFrame + 0x200);
#define ML_CALL(t) g_fnLIFT_##t(rcx, rdx, r8, r9, ML_M8(rsp, 0x20), ML_M8(rsp, 0x28))
    rsp -= 8; ML_M8(rsp, 0) = rbx;
    rsp = rsp - (0x20ULL);
{
    const uint64_t a = (uint64_t)(ML_M8(rcx, 0x0)) & ~0ULL, b = (uint64_t)(0x0ULL) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    rbx = rcx;
    if (!f_zf) goto L6;
    rax = ML_CALL(1418233c0);
L6:
    rcx = ML_M8(rbx, 0x8);
{
    const uint64_t a = (uint64_t)(ML_M1(rcx, 0x2d)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L12;
    rsp = rsp + (0x20ULL);
    { const uint64_t v = ML_M8(rsp, 0); rsp += 8; rbx = v; }
    return ML_CALL(1418233c0);   // tail call
L12:
    rax = ML_M8(rcx, 0x10);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x2d)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L27;
    rcx = ML_M8(rax, 0x0);
{
    const uint64_t a = (uint64_t)(ML_M1(rcx, 0x2d)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L23;
    ;
L19:
    rax = rcx;
    rcx = ML_M8(rcx, 0x0);
{
    const uint64_t a = (uint64_t)(ML_M1(rcx, 0x2d)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L19;
L23:
    ML_M8(rbx, 0x8) = rax;
    rsp = rsp + (0x20ULL);
    { const uint64_t v = ML_M8(rsp, 0); rsp += 8; rbx = v; }
    return rax;
L27:
    rcx = ML_M8(rcx, 0x8);
{
    const uint64_t a = (uint64_t)(ML_M1(rcx, 0x2d)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L37;
L30:
    rax = ML_M8(rcx, 0x10);
{
    const uint64_t a = (uint64_t)(ML_M8(rbx, 0x8)) & ~0ULL, b = (uint64_t)(rax) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L37;
    ML_M8(rbx, 0x8) = rcx;
    rcx = ML_M8(rcx, 0x8);
{
    const uint64_t a = (uint64_t)(ML_M1(rcx, 0x2d)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L30;
L37:
    ML_M8(rbx, 0x8) = rcx;
    rsp = rsp + (0x20ULL);
    { const uint64_t v = ML_M8(rsp, 0); rsp += 8; rbx = v; }
    return rax;
#undef ML_CALL
    return rax;
}

uint64_t SynLift_141750a30(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A) {
    uint64_t rax = 0, rbx = 0, rbp = 0, rsi = 0, rdi = 0, r10 = 0, r11 = 0, r12 = 0, r13 = 0, r14 = 0, r15 = 0;
    uint64_t rcx = rcxA, rdx = rdxA, r8 = r8A, r9 = r9A;
    bool f_zf = false, f_cf = false, f_sf = false, f_of = false;
    uint8_t xmm0[16] = {0}, xmm1[16] = {0}, xmm2[16] = {0}, xmm3[16] = {0}, xmm4[16] = {0}, xmm5[16] = {0};
    alignas(16) uint8_t stkFrame[0x400] = {0};
    uint64_t rsp = (uint64_t)(uintptr_t)(stkFrame + 0x200);
#define ML_CALL(t) g_fnLIFT_##t(rcx, rdx, r8, r9, ML_M8(rsp, 0x20), ML_M8(rsp, 0x28))
    r8 = ML_M8(rdx, 0x0);
    rax = ML_M8(r8, 0x10);
    ML_M8(rdx, 0x0) = rax;
    rax = ML_M8(r8, 0x10);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L7;
    ML_M8(rax, 0x8) = rdx;
L7:
    rax = ML_M8(rdx, 0x8);
    ML_M8(r8, 0x8) = rax;
    rax = ML_M8(rcx, 0x30);
{
    const uint64_t a = (uint64_t)(rdx) & ~0ULL, b = (uint64_t)(ML_M8(rax, 0x8)) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L16;
    ML_M8(rax, 0x8) = r8;
    ML_M8(r8, 0x10) = rdx;
    ML_M8(rdx, 0x8) = r8;
    return rax;
L16:
    rax = ML_M8(rdx, 0x8);
{
    const uint64_t a = (uint64_t)(rdx) & ~0ULL, b = (uint64_t)(ML_M8(rax, 0x10)) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L23;
    ML_M8(rax, 0x10) = r8;
    ML_M8(r8, 0x10) = rdx;
    ML_M8(rdx, 0x8) = r8;
    return rax;
L23:
    ML_M8(rax, 0x0) = r8;
    ML_M8(r8, 0x10) = rdx;
    ML_M8(rdx, 0x8) = r8;
    return rax;
#undef ML_CALL
    return rax;
}

uint64_t SynLift_1417512f0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A) {
    uint64_t rax = 0, rbx = 0, rbp = 0, rsi = 0, rdi = 0, r10 = 0, r11 = 0, r12 = 0, r13 = 0, r14 = 0, r15 = 0;
    uint64_t rcx = rcxA, rdx = rdxA, r8 = r8A, r9 = r9A;
    bool f_zf = false, f_cf = false, f_sf = false, f_of = false;
    uint8_t xmm0[16] = {0}, xmm1[16] = {0}, xmm2[16] = {0}, xmm3[16] = {0}, xmm4[16] = {0}, xmm5[16] = {0};
    alignas(16) uint8_t stkFrame[0x400] = {0};
    uint64_t rsp = (uint64_t)(uintptr_t)(stkFrame + 0x200);
#define ML_CALL(t) g_fnLIFT_##t(rcx, rdx, r8, r9, ML_M8(rsp, 0x20), ML_M8(rsp, 0x28))
    rsp -= 8; ML_M8(rsp, 0) = rbx;
    rsp = rsp - (0x20ULL);
{
    const uint64_t a = (uint64_t)(ML_M8(rcx, 0x0)) & ~0ULL, b = (uint64_t)(0x0ULL) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    rbx = rcx;
    if (!f_zf) goto L6;
    rax = ML_CALL(1418233c0);
L6:
    rcx = ML_M8(rbx, 0x8);
{
    const uint64_t a = (uint64_t)(ML_M1(rcx, 0x59)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L12;
    rsp = rsp + (0x20ULL);
    { const uint64_t v = ML_M8(rsp, 0); rsp += 8; rbx = v; }
    return ML_CALL(1418233c0);   // tail call
L12:
    rax = ML_M8(rcx, 0x10);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x59)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L27;
    rcx = ML_M8(rax, 0x0);
{
    const uint64_t a = (uint64_t)(ML_M1(rcx, 0x59)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L23;
    ;
L19:
    rax = rcx;
    rcx = ML_M8(rcx, 0x0);
{
    const uint64_t a = (uint64_t)(ML_M1(rcx, 0x59)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L19;
L23:
    ML_M8(rbx, 0x8) = rax;
    rsp = rsp + (0x20ULL);
    { const uint64_t v = ML_M8(rsp, 0); rsp += 8; rbx = v; }
    return rax;
L27:
    rcx = ML_M8(rcx, 0x8);
{
    const uint64_t a = (uint64_t)(ML_M1(rcx, 0x59)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L37;
L30:
    rax = ML_M8(rcx, 0x10);
{
    const uint64_t a = (uint64_t)(ML_M8(rbx, 0x8)) & ~0ULL, b = (uint64_t)(rax) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L37;
    ML_M8(rbx, 0x8) = rcx;
    rcx = ML_M8(rcx, 0x8);
{
    const uint64_t a = (uint64_t)(ML_M1(rcx, 0x59)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L30;
L37:
    ML_M8(rbx, 0x8) = rcx;
    rsp = rsp + (0x20ULL);
    { const uint64_t v = ML_M8(rsp, 0); rsp += 8; rbx = v; }
    return rax;
#undef ML_CALL
    return rax;
}

uint64_t SynLift_141751380(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A) {
    uint64_t rax = 0, rbx = 0, rbp = 0, rsi = 0, rdi = 0, r10 = 0, r11 = 0, r12 = 0, r13 = 0, r14 = 0, r15 = 0;
    uint64_t rcx = rcxA, rdx = rdxA, r8 = r8A, r9 = r9A;
    bool f_zf = false, f_cf = false, f_sf = false, f_of = false;
    uint8_t xmm0[16] = {0}, xmm1[16] = {0}, xmm2[16] = {0}, xmm3[16] = {0}, xmm4[16] = {0}, xmm5[16] = {0};
    alignas(16) uint8_t stkFrame[0x400] = {0};
    uint64_t rsp = (uint64_t)(uintptr_t)(stkFrame + 0x200);
#define ML_CALL(t) g_fnLIFT_##t(rcx, rdx, r8, r9, ML_M8(rsp, 0x20), ML_M8(rsp, 0x28))
    rsp -= 8; ML_M8(rsp, 0) = rbx;
    rsp = rsp - (0x20ULL);
{
    const uint64_t a = (uint64_t)(ML_M8(rcx, 0x0)) & ~0ULL, b = (uint64_t)(0x0ULL) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    rbx = rcx;
    if (!f_zf) goto L6;
    rax = ML_CALL(1418233c0);
L6:
    rcx = ML_M8(rbx, 0x8);
{
    const uint64_t a = (uint64_t)(ML_M1(rcx, 0x69)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L12;
    rsp = rsp + (0x20ULL);
    { const uint64_t v = ML_M8(rsp, 0); rsp += 8; rbx = v; }
    return ML_CALL(1418233c0);   // tail call
L12:
    rax = ML_M8(rcx, 0x10);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x69)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L27;
    rcx = ML_M8(rax, 0x0);
{
    const uint64_t a = (uint64_t)(ML_M1(rcx, 0x69)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L23;
    ;
L19:
    rax = rcx;
    rcx = ML_M8(rcx, 0x0);
{
    const uint64_t a = (uint64_t)(ML_M1(rcx, 0x69)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L19;
L23:
    ML_M8(rbx, 0x8) = rax;
    rsp = rsp + (0x20ULL);
    { const uint64_t v = ML_M8(rsp, 0); rsp += 8; rbx = v; }
    return rax;
L27:
    rcx = ML_M8(rcx, 0x8);
{
    const uint64_t a = (uint64_t)(ML_M1(rcx, 0x69)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L37;
L30:
    rax = ML_M8(rcx, 0x10);
{
    const uint64_t a = (uint64_t)(ML_M8(rbx, 0x8)) & ~0ULL, b = (uint64_t)(rax) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L37;
    ML_M8(rbx, 0x8) = rcx;
    rcx = ML_M8(rcx, 0x8);
{
    const uint64_t a = (uint64_t)(ML_M1(rcx, 0x69)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L30;
L37:
    ML_M8(rbx, 0x8) = rcx;
    rsp = rsp + (0x20ULL);
    { const uint64_t v = ML_M8(rsp, 0); rsp += 8; rbx = v; }
    return rax;
#undef ML_CALL
    return rax;
}

uint64_t SynLift_141752ac0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A) {
    uint64_t rax = 0, rbx = 0, rbp = 0, rsi = 0, rdi = 0, r10 = 0, r11 = 0, r12 = 0, r13 = 0, r14 = 0, r15 = 0;
    uint64_t rcx = rcxA, rdx = rdxA, r8 = r8A, r9 = r9A;
    bool f_zf = false, f_cf = false, f_sf = false, f_of = false;
    uint8_t xmm0[16] = {0}, xmm1[16] = {0}, xmm2[16] = {0}, xmm3[16] = {0}, xmm4[16] = {0}, xmm5[16] = {0};
    alignas(16) uint8_t stkFrame[0x400] = {0};
    uint64_t rsp = (uint64_t)(uintptr_t)(stkFrame + 0x200);
#define ML_CALL(t) g_fnLIFT_##t(rcx, rdx, r8, r9, ML_M8(rsp, 0x20), ML_M8(rsp, 0x28))
    r8 = ML_M8(rdx, 0x10);
    rax = ML_M8(r8, 0x0);
    ML_M8(rdx, 0x10) = rax;
    rax = ML_M8(r8, 0x0);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x2d)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L7;
    ML_M8(rax, 0x8) = rdx;
L7:
    rax = ML_M8(rdx, 0x8);
    ML_M8(r8, 0x8) = rax;
    rax = ML_M8(rcx, 0x30);
{
    const uint64_t a = (uint64_t)(rdx) & ~0ULL, b = (uint64_t)(ML_M8(rax, 0x8)) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L16;
    ML_M8(rax, 0x8) = r8;
    ML_M8(r8, 0x0) = rdx;
    ML_M8(rdx, 0x8) = r8;
    return rax;
L16:
    rax = ML_M8(rdx, 0x8);
{
    const uint64_t a = (uint64_t)(rdx) & ~0ULL, b = (uint64_t)(ML_M8(rax, 0x0)) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L23;
    ML_M8(rax, 0x0) = r8;
    ML_M8(r8, 0x0) = rdx;
    ML_M8(rdx, 0x8) = r8;
    return rax;
L23:
    ML_M8(rax, 0x10) = r8;
    ML_M8(r8, 0x0) = rdx;
    ML_M8(rdx, 0x8) = r8;
    return rax;
#undef ML_CALL
    return rax;
}

uint64_t SynLift_141752cd0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A) {
    uint64_t rax = 0, rbx = 0, rbp = 0, rsi = 0, rdi = 0, r10 = 0, r11 = 0, r12 = 0, r13 = 0, r14 = 0, r15 = 0;
    uint64_t rcx = rcxA, rdx = rdxA, r8 = r8A, r9 = r9A;
    bool f_zf = false, f_cf = false, f_sf = false, f_of = false;
    uint8_t xmm0[16] = {0}, xmm1[16] = {0}, xmm2[16] = {0}, xmm3[16] = {0}, xmm4[16] = {0}, xmm5[16] = {0};
    alignas(16) uint8_t stkFrame[0x400] = {0};
    uint64_t rsp = (uint64_t)(uintptr_t)(stkFrame + 0x200);
#define ML_CALL(t) g_fnLIFT_##t(rcx, rdx, r8, r9, ML_M8(rsp, 0x20), ML_M8(rsp, 0x28))
    r8 = ML_M8(rdx, 0x10);
    rax = ML_M8(r8, 0x0);
    ML_M8(rdx, 0x10) = rax;
    rax = ML_M8(r8, 0x0);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L7;
    ML_M8(rax, 0x8) = rdx;
L7:
    rax = ML_M8(rdx, 0x8);
    ML_M8(r8, 0x8) = rax;
    rax = ML_M8(rcx, 0x30);
{
    const uint64_t a = (uint64_t)(rdx) & ~0ULL, b = (uint64_t)(ML_M8(rax, 0x8)) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L16;
    ML_M8(rax, 0x8) = r8;
    ML_M8(r8, 0x0) = rdx;
    ML_M8(rdx, 0x8) = r8;
    return rax;
L16:
    rax = ML_M8(rdx, 0x8);
{
    const uint64_t a = (uint64_t)(rdx) & ~0ULL, b = (uint64_t)(ML_M8(rax, 0x0)) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L23;
    ML_M8(rax, 0x0) = r8;
    ML_M8(r8, 0x0) = rdx;
    ML_M8(rdx, 0x8) = r8;
    return rax;
L23:
    ML_M8(rax, 0x10) = r8;
    ML_M8(r8, 0x0) = rdx;
    ML_M8(rdx, 0x8) = r8;
    return rax;
#undef ML_CALL
    return rax;
}

uint64_t SynLift_141752d30(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A) {
    uint64_t rax = 0, rbx = 0, rbp = 0, rsi = 0, rdi = 0, r10 = 0, r11 = 0, r12 = 0, r13 = 0, r14 = 0, r15 = 0;
    uint64_t rcx = rcxA, rdx = rdxA, r8 = r8A, r9 = r9A;
    bool f_zf = false, f_cf = false, f_sf = false, f_of = false;
    uint8_t xmm0[16] = {0}, xmm1[16] = {0}, xmm2[16] = {0}, xmm3[16] = {0}, xmm4[16] = {0}, xmm5[16] = {0};
    alignas(16) uint8_t stkFrame[0x400] = {0};
    uint64_t rsp = (uint64_t)(uintptr_t)(stkFrame + 0x200);
#define ML_CALL(t) g_fnLIFT_##t(rcx, rdx, r8, r9, ML_M8(rsp, 0x20), ML_M8(rsp, 0x28))
    r8 = ML_M8(rdx, 0x0);
    rax = ML_M8(r8, 0x10);
    ML_M8(rdx, 0x0) = rax;
    rax = ML_M8(r8, 0x10);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L7;
    ML_M8(rax, 0x8) = rdx;
L7:
    rax = ML_M8(rdx, 0x8);
    ML_M8(r8, 0x8) = rax;
    rax = ML_M8(rcx, 0x30);
{
    const uint64_t a = (uint64_t)(rdx) & ~0ULL, b = (uint64_t)(ML_M8(rax, 0x8)) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L16;
    ML_M8(rax, 0x8) = r8;
    ML_M8(r8, 0x10) = rdx;
    ML_M8(rdx, 0x8) = r8;
    return rax;
L16:
    rax = ML_M8(rdx, 0x8);
{
    const uint64_t a = (uint64_t)(rdx) & ~0ULL, b = (uint64_t)(ML_M8(rax, 0x10)) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L23;
    ML_M8(rax, 0x10) = r8;
    ML_M8(r8, 0x10) = rdx;
    ML_M8(rdx, 0x8) = r8;
    return rax;
L23:
    ML_M8(rax, 0x0) = r8;
    ML_M8(r8, 0x10) = rdx;
    ML_M8(rdx, 0x8) = r8;
    return rax;
#undef ML_CALL
    return rax;
}

uint64_t SynLift_141752ef0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A) {
    uint64_t rax = 0, rbx = 0, rbp = 0, rsi = 0, rdi = 0, r10 = 0, r11 = 0, r12 = 0, r13 = 0, r14 = 0, r15 = 0;
    uint64_t rcx = rcxA, rdx = rdxA, r8 = r8A, r9 = r9A;
    bool f_zf = false, f_cf = false, f_sf = false, f_of = false;
    uint8_t xmm0[16] = {0}, xmm1[16] = {0}, xmm2[16] = {0}, xmm3[16] = {0}, xmm4[16] = {0}, xmm5[16] = {0};
    alignas(16) uint8_t stkFrame[0x400] = {0};
    uint64_t rsp = (uint64_t)(uintptr_t)(stkFrame + 0x200);
#define ML_CALL(t) g_fnLIFT_##t(rcx, rdx, r8, r9, ML_M8(rsp, 0x20), ML_M8(rsp, 0x28))
    r8 = ML_M8(rdx, 0x10);
    rax = ML_M8(r8, 0x0);
    ML_M8(rdx, 0x10) = rax;
    rax = ML_M8(r8, 0x0);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x59)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L7;
    ML_M8(rax, 0x8) = rdx;
L7:
    rax = ML_M8(rdx, 0x8);
    ML_M8(r8, 0x8) = rax;
    rax = ML_M8(rcx, 0x30);
{
    const uint64_t a = (uint64_t)(rdx) & ~0ULL, b = (uint64_t)(ML_M8(rax, 0x8)) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L16;
    ML_M8(rax, 0x8) = r8;
    ML_M8(r8, 0x0) = rdx;
    ML_M8(rdx, 0x8) = r8;
    return rax;
L16:
    rax = ML_M8(rdx, 0x8);
{
    const uint64_t a = (uint64_t)(rdx) & ~0ULL, b = (uint64_t)(ML_M8(rax, 0x0)) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L23;
    ML_M8(rax, 0x0) = r8;
    ML_M8(r8, 0x0) = rdx;
    ML_M8(rdx, 0x8) = r8;
    return rax;
L23:
    ML_M8(rax, 0x10) = r8;
    ML_M8(r8, 0x0) = rdx;
    ML_M8(rdx, 0x8) = r8;
    return rax;
#undef ML_CALL
    return rax;
}

uint64_t SynLift_141752f50(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A) {
    uint64_t rax = 0, rbx = 0, rbp = 0, rsi = 0, rdi = 0, r10 = 0, r11 = 0, r12 = 0, r13 = 0, r14 = 0, r15 = 0;
    uint64_t rcx = rcxA, rdx = rdxA, r8 = r8A, r9 = r9A;
    bool f_zf = false, f_cf = false, f_sf = false, f_of = false;
    uint8_t xmm0[16] = {0}, xmm1[16] = {0}, xmm2[16] = {0}, xmm3[16] = {0}, xmm4[16] = {0}, xmm5[16] = {0};
    alignas(16) uint8_t stkFrame[0x400] = {0};
    uint64_t rsp = (uint64_t)(uintptr_t)(stkFrame + 0x200);
#define ML_CALL(t) g_fnLIFT_##t(rcx, rdx, r8, r9, ML_M8(rsp, 0x20), ML_M8(rsp, 0x28))
    r8 = ML_M8(rdx, 0x0);
    rax = ML_M8(r8, 0x10);
    ML_M8(rdx, 0x0) = rax;
    rax = ML_M8(r8, 0x10);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x59)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L7;
    ML_M8(rax, 0x8) = rdx;
L7:
    rax = ML_M8(rdx, 0x8);
    ML_M8(r8, 0x8) = rax;
    rax = ML_M8(rcx, 0x30);
{
    const uint64_t a = (uint64_t)(rdx) & ~0ULL, b = (uint64_t)(ML_M8(rax, 0x8)) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L16;
    ML_M8(rax, 0x8) = r8;
    ML_M8(r8, 0x10) = rdx;
    ML_M8(rdx, 0x8) = r8;
    return rax;
L16:
    rax = ML_M8(rdx, 0x8);
{
    const uint64_t a = (uint64_t)(rdx) & ~0ULL, b = (uint64_t)(ML_M8(rax, 0x10)) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L23;
    ML_M8(rax, 0x10) = r8;
    ML_M8(r8, 0x10) = rdx;
    ML_M8(rdx, 0x8) = r8;
    return rax;
L23:
    ML_M8(rax, 0x0) = r8;
    ML_M8(r8, 0x10) = rdx;
    ML_M8(rdx, 0x8) = r8;
    return rax;
#undef ML_CALL
    return rax;
}

uint64_t SynLift_1417530a0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A) {
    uint64_t rax = 0, rbx = 0, rbp = 0, rsi = 0, rdi = 0, r10 = 0, r11 = 0, r12 = 0, r13 = 0, r14 = 0, r15 = 0;
    uint64_t rcx = rcxA, rdx = rdxA, r8 = r8A, r9 = r9A;
    bool f_zf = false, f_cf = false, f_sf = false, f_of = false;
    uint8_t xmm0[16] = {0}, xmm1[16] = {0}, xmm2[16] = {0}, xmm3[16] = {0}, xmm4[16] = {0}, xmm5[16] = {0};
    alignas(16) uint8_t stkFrame[0x400] = {0};
    uint64_t rsp = (uint64_t)(uintptr_t)(stkFrame + 0x200);
#define ML_CALL(t) g_fnLIFT_##t(rcx, rdx, r8, r9, ML_M8(rsp, 0x20), ML_M8(rsp, 0x28))
    r8 = ML_M8(rdx, 0x10);
    rax = ML_M8(r8, 0x0);
    ML_M8(rdx, 0x10) = rax;
    rax = ML_M8(r8, 0x0);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L7;
    ML_M8(rax, 0x8) = rdx;
L7:
    rax = ML_M8(rdx, 0x8);
    ML_M8(r8, 0x8) = rax;
    rax = ML_M8(rcx, 0x30);
{
    const uint64_t a = (uint64_t)(rdx) & ~0ULL, b = (uint64_t)(ML_M8(rax, 0x8)) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L16;
    ML_M8(rax, 0x8) = r8;
    ML_M8(r8, 0x0) = rdx;
    ML_M8(rdx, 0x8) = r8;
    return rax;
L16:
    rax = ML_M8(rdx, 0x8);
{
    const uint64_t a = (uint64_t)(rdx) & ~0ULL, b = (uint64_t)(ML_M8(rax, 0x0)) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L23;
    ML_M8(rax, 0x0) = r8;
    ML_M8(r8, 0x0) = rdx;
    ML_M8(rdx, 0x8) = r8;
    return rax;
L23:
    ML_M8(rax, 0x10) = r8;
    ML_M8(r8, 0x0) = rdx;
    ML_M8(rdx, 0x8) = r8;
    return rax;
#undef ML_CALL
    return rax;
}

uint64_t SynLift_141753100(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A) {
    uint64_t rax = 0, rbx = 0, rbp = 0, rsi = 0, rdi = 0, r10 = 0, r11 = 0, r12 = 0, r13 = 0, r14 = 0, r15 = 0;
    uint64_t rcx = rcxA, rdx = rdxA, r8 = r8A, r9 = r9A;
    bool f_zf = false, f_cf = false, f_sf = false, f_of = false;
    uint8_t xmm0[16] = {0}, xmm1[16] = {0}, xmm2[16] = {0}, xmm3[16] = {0}, xmm4[16] = {0}, xmm5[16] = {0};
    alignas(16) uint8_t stkFrame[0x400] = {0};
    uint64_t rsp = (uint64_t)(uintptr_t)(stkFrame + 0x200);
#define ML_CALL(t) g_fnLIFT_##t(rcx, rdx, r8, r9, ML_M8(rsp, 0x20), ML_M8(rsp, 0x28))
    r8 = ML_M8(rdx, 0x0);
    rax = ML_M8(r8, 0x10);
    ML_M8(rdx, 0x0) = rax;
    rax = ML_M8(r8, 0x10);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L7;
    ML_M8(rax, 0x8) = rdx;
L7:
    rax = ML_M8(rdx, 0x8);
    ML_M8(r8, 0x8) = rax;
    rax = ML_M8(rcx, 0x30);
{
    const uint64_t a = (uint64_t)(rdx) & ~0ULL, b = (uint64_t)(ML_M8(rax, 0x8)) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L16;
    ML_M8(rax, 0x8) = r8;
    ML_M8(r8, 0x10) = rdx;
    ML_M8(rdx, 0x8) = r8;
    return rax;
L16:
    rax = ML_M8(rdx, 0x8);
{
    const uint64_t a = (uint64_t)(rdx) & ~0ULL, b = (uint64_t)(ML_M8(rax, 0x10)) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L23;
    ML_M8(rax, 0x10) = r8;
    ML_M8(r8, 0x10) = rdx;
    ML_M8(rdx, 0x8) = r8;
    return rax;
L23:
    ML_M8(rax, 0x0) = r8;
    ML_M8(r8, 0x10) = rdx;
    ML_M8(rdx, 0x8) = r8;
    return rax;
#undef ML_CALL
    return rax;
}

uint64_t SynLift_141753320(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A) {
    uint64_t rax = 0, rbx = 0, rbp = 0, rsi = 0, rdi = 0, r10 = 0, r11 = 0, r12 = 0, r13 = 0, r14 = 0, r15 = 0;
    uint64_t rcx = rcxA, rdx = rdxA, r8 = r8A, r9 = r9A;
    bool f_zf = false, f_cf = false, f_sf = false, f_of = false;
    uint8_t xmm0[16] = {0}, xmm1[16] = {0}, xmm2[16] = {0}, xmm3[16] = {0}, xmm4[16] = {0}, xmm5[16] = {0};
    alignas(16) uint8_t stkFrame[0x400] = {0};
    uint64_t rsp = (uint64_t)(uintptr_t)(stkFrame + 0x200);
#define ML_CALL(t) g_fnLIFT_##t(rcx, rdx, r8, r9, ML_M8(rsp, 0x20), ML_M8(rsp, 0x28))
    r8 = ML_M8(rdx, 0x10);
    rax = ML_M8(r8, 0x0);
    ML_M8(rdx, 0x10) = rax;
    rax = ML_M8(r8, 0x0);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x69)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L7;
    ML_M8(rax, 0x8) = rdx;
L7:
    rax = ML_M8(rdx, 0x8);
    ML_M8(r8, 0x8) = rax;
    rax = ML_M8(rcx, 0x30);
{
    const uint64_t a = (uint64_t)(rdx) & ~0ULL, b = (uint64_t)(ML_M8(rax, 0x8)) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L16;
    ML_M8(rax, 0x8) = r8;
    ML_M8(r8, 0x0) = rdx;
    ML_M8(rdx, 0x8) = r8;
    return rax;
L16:
    rax = ML_M8(rdx, 0x8);
{
    const uint64_t a = (uint64_t)(rdx) & ~0ULL, b = (uint64_t)(ML_M8(rax, 0x0)) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L23;
    ML_M8(rax, 0x0) = r8;
    ML_M8(r8, 0x0) = rdx;
    ML_M8(rdx, 0x8) = r8;
    return rax;
L23:
    ML_M8(rax, 0x10) = r8;
    ML_M8(r8, 0x0) = rdx;
    ML_M8(rdx, 0x8) = r8;
    return rax;
#undef ML_CALL
    return rax;
}

uint64_t SynLift_141753380(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A) {
    uint64_t rax = 0, rbx = 0, rbp = 0, rsi = 0, rdi = 0, r10 = 0, r11 = 0, r12 = 0, r13 = 0, r14 = 0, r15 = 0;
    uint64_t rcx = rcxA, rdx = rdxA, r8 = r8A, r9 = r9A;
    bool f_zf = false, f_cf = false, f_sf = false, f_of = false;
    uint8_t xmm0[16] = {0}, xmm1[16] = {0}, xmm2[16] = {0}, xmm3[16] = {0}, xmm4[16] = {0}, xmm5[16] = {0};
    alignas(16) uint8_t stkFrame[0x400] = {0};
    uint64_t rsp = (uint64_t)(uintptr_t)(stkFrame + 0x200);
#define ML_CALL(t) g_fnLIFT_##t(rcx, rdx, r8, r9, ML_M8(rsp, 0x20), ML_M8(rsp, 0x28))
    r8 = ML_M8(rdx, 0x0);
    rax = ML_M8(r8, 0x10);
    ML_M8(rdx, 0x0) = rax;
    rax = ML_M8(r8, 0x10);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x69)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L7;
    ML_M8(rax, 0x8) = rdx;
L7:
    rax = ML_M8(rdx, 0x8);
    ML_M8(r8, 0x8) = rax;
    rax = ML_M8(rcx, 0x30);
{
    const uint64_t a = (uint64_t)(rdx) & ~0ULL, b = (uint64_t)(ML_M8(rax, 0x8)) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L16;
    ML_M8(rax, 0x8) = r8;
    ML_M8(r8, 0x10) = rdx;
    ML_M8(rdx, 0x8) = r8;
    return rax;
L16:
    rax = ML_M8(rdx, 0x8);
{
    const uint64_t a = (uint64_t)(rdx) & ~0ULL, b = (uint64_t)(ML_M8(rax, 0x10)) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L23;
    ML_M8(rax, 0x10) = r8;
    ML_M8(r8, 0x10) = rdx;
    ML_M8(rdx, 0x8) = r8;
    return rax;
L23:
    ML_M8(rax, 0x0) = r8;
    ML_M8(r8, 0x10) = rdx;
    ML_M8(rdx, 0x8) = r8;
    return rax;
#undef ML_CALL
    return rax;
}

uint64_t SynLift_141753470(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A) {
    uint64_t rax = 0, rbx = 0, rbp = 0, rsi = 0, rdi = 0, r10 = 0, r11 = 0, r12 = 0, r13 = 0, r14 = 0, r15 = 0;
    uint64_t rcx = rcxA, rdx = rdxA, r8 = r8A, r9 = r9A;
    bool f_zf = false, f_cf = false, f_sf = false, f_of = false;
    uint8_t xmm0[16] = {0}, xmm1[16] = {0}, xmm2[16] = {0}, xmm3[16] = {0}, xmm4[16] = {0}, xmm5[16] = {0};
    alignas(16) uint8_t stkFrame[0x400] = {0};
    uint64_t rsp = (uint64_t)(uintptr_t)(stkFrame + 0x200);
#define ML_CALL(t) g_fnLIFT_##t(rcx, rdx, r8, r9, ML_M8(rsp, 0x20), ML_M8(rsp, 0x28))
    rsp -= 8; ML_M8(rsp, 0) = rbx;
    rsp = rsp - (0x20ULL);
{
    const uint64_t a = (uint64_t)(ML_M8(rcx, 0x0)) & ~0ULL, b = (uint64_t)(0x0ULL) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    rbx = rcx;
    if (!f_zf) goto L6;
    rax = ML_CALL(1418233c0);
L6:
    rcx = ML_M8(rbx, 0x8);
{
    const uint64_t a = (uint64_t)(ML_M1(rcx, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L12;
    rsp = rsp + (0x20ULL);
    { const uint64_t v = ML_M8(rsp, 0); rsp += 8; rbx = v; }
    return ML_CALL(1418233c0);   // tail call
L12:
    rax = ML_M8(rcx, 0x10);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L27;
    rcx = ML_M8(rax, 0x0);
{
    const uint64_t a = (uint64_t)(ML_M1(rcx, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L23;
    ;
L19:
    rax = rcx;
    rcx = ML_M8(rcx, 0x0);
{
    const uint64_t a = (uint64_t)(ML_M1(rcx, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L19;
L23:
    ML_M8(rbx, 0x8) = rax;
    rsp = rsp + (0x20ULL);
    { const uint64_t v = ML_M8(rsp, 0); rsp += 8; rbx = v; }
    return rax;
L27:
    rcx = ML_M8(rcx, 0x8);
{
    const uint64_t a = (uint64_t)(ML_M1(rcx, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L37;
L30:
    rax = ML_M8(rcx, 0x10);
{
    const uint64_t a = (uint64_t)(ML_M8(rbx, 0x8)) & ~0ULL, b = (uint64_t)(rax) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L37;
    ML_M8(rbx, 0x8) = rcx;
    rcx = ML_M8(rcx, 0x8);
{
    const uint64_t a = (uint64_t)(ML_M1(rcx, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L30;
L37:
    ML_M8(rbx, 0x8) = rcx;
    rsp = rsp + (0x20ULL);
    { const uint64_t v = ML_M8(rsp, 0); rsp += 8; rbx = v; }
    return rax;
#undef ML_CALL
    return rax;
}

uint64_t SynLift_141753620(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A) {
    uint64_t rax = 0, rbx = 0, rbp = 0, rsi = 0, rdi = 0, r10 = 0, r11 = 0, r12 = 0, r13 = 0, r14 = 0, r15 = 0;
    uint64_t rcx = rcxA, rdx = rdxA, r8 = r8A, r9 = r9A;
    bool f_zf = false, f_cf = false, f_sf = false, f_of = false;
    uint8_t xmm0[16] = {0}, xmm1[16] = {0}, xmm2[16] = {0}, xmm3[16] = {0}, xmm4[16] = {0}, xmm5[16] = {0};
    alignas(16) uint8_t stkFrame[0x400] = {0};
    uint64_t rsp = (uint64_t)(uintptr_t)(stkFrame + 0x200);
#define ML_CALL(t) g_fnLIFT_##t(rcx, rdx, r8, r9, ML_M8(rsp, 0x20), ML_M8(rsp, 0x28))
    rsp -= 8; ML_M8(rsp, 0) = rbx;
    rsp = rsp - (0x20ULL);
{
    const uint64_t a = (uint64_t)(ML_M8(rcx, 0x0)) & ~0ULL, b = (uint64_t)(0x0ULL) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    rbx = rcx;
    if (!f_zf) goto L6;
    rax = ML_CALL(1418233c0);
L6:
    rcx = ML_M8(rbx, 0x8);
{
    const uint64_t a = (uint64_t)(ML_M1(rcx, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L12;
    rsp = rsp + (0x20ULL);
    { const uint64_t v = ML_M8(rsp, 0); rsp += 8; rbx = v; }
    return ML_CALL(1418233c0);   // tail call
L12:
    rax = ML_M8(rcx, 0x10);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L27;
    rcx = ML_M8(rax, 0x0);
{
    const uint64_t a = (uint64_t)(ML_M1(rcx, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L23;
    ;
L19:
    rax = rcx;
    rcx = ML_M8(rcx, 0x0);
{
    const uint64_t a = (uint64_t)(ML_M1(rcx, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L19;
L23:
    ML_M8(rbx, 0x8) = rax;
    rsp = rsp + (0x20ULL);
    { const uint64_t v = ML_M8(rsp, 0); rsp += 8; rbx = v; }
    return rax;
L27:
    rcx = ML_M8(rcx, 0x8);
{
    const uint64_t a = (uint64_t)(ML_M1(rcx, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L37;
L30:
    rax = ML_M8(rcx, 0x10);
{
    const uint64_t a = (uint64_t)(ML_M8(rbx, 0x8)) & ~0ULL, b = (uint64_t)(rax) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L37;
    ML_M8(rbx, 0x8) = rcx;
    rcx = ML_M8(rcx, 0x8);
{
    const uint64_t a = (uint64_t)(ML_M1(rcx, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L30;
L37:
    ML_M8(rbx, 0x8) = rcx;
    rsp = rsp + (0x20ULL);
    { const uint64_t v = ML_M8(rsp, 0); rsp += 8; rbx = v; }
    return rax;
#undef ML_CALL
    return rax;
}

uint64_t SynLift_1417536b0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A) {
    uint64_t rax = 0, rbx = 0, rbp = 0, rsi = 0, rdi = 0, r10 = 0, r11 = 0, r12 = 0, r13 = 0, r14 = 0, r15 = 0;
    uint64_t rcx = rcxA, rdx = rdxA, r8 = r8A, r9 = r9A;
    bool f_zf = false, f_cf = false, f_sf = false, f_of = false;
    uint8_t xmm0[16] = {0}, xmm1[16] = {0}, xmm2[16] = {0}, xmm3[16] = {0}, xmm4[16] = {0}, xmm5[16] = {0};
    alignas(16) uint8_t stkFrame[0x400] = {0};
    uint64_t rsp = (uint64_t)(uintptr_t)(stkFrame + 0x200);
#define ML_CALL(t) g_fnLIFT_##t(rcx, rdx, r8, r9, ML_M8(rsp, 0x20), ML_M8(rsp, 0x28))
    rsp -= 8; ML_M8(rsp, 0) = rbx;
    rsp = rsp - (0x20ULL);
{
    const uint64_t a = (uint64_t)(ML_M8(rcx, 0x0)) & ~0ULL, b = (uint64_t)(0x0ULL) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    rbx = rcx;
    if (!f_zf) goto L6;
    rax = ML_CALL(1418233c0);
L6:
    rcx = ML_M8(rbx, 0x8);
{
    const uint64_t a = (uint64_t)(ML_M1(rcx, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L12;
    rsp = rsp + (0x20ULL);
    { const uint64_t v = ML_M8(rsp, 0); rsp += 8; rbx = v; }
    return ML_CALL(1418233c0);   // tail call
L12:
    rax = ML_M8(rcx, 0x10);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L27;
    rcx = ML_M8(rax, 0x0);
{
    const uint64_t a = (uint64_t)(ML_M1(rcx, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L23;
    ;
L19:
    rax = rcx;
    rcx = ML_M8(rcx, 0x0);
{
    const uint64_t a = (uint64_t)(ML_M1(rcx, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L19;
L23:
    ML_M8(rbx, 0x8) = rax;
    rsp = rsp + (0x20ULL);
    { const uint64_t v = ML_M8(rsp, 0); rsp += 8; rbx = v; }
    return rax;
L27:
    rcx = ML_M8(rcx, 0x8);
{
    const uint64_t a = (uint64_t)(ML_M1(rcx, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L37;
L30:
    rax = ML_M8(rcx, 0x10);
{
    const uint64_t a = (uint64_t)(ML_M8(rbx, 0x8)) & ~0ULL, b = (uint64_t)(rax) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L37;
    ML_M8(rbx, 0x8) = rcx;
    rcx = ML_M8(rcx, 0x8);
{
    const uint64_t a = (uint64_t)(ML_M1(rcx, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L30;
L37:
    ML_M8(rbx, 0x8) = rcx;
    rsp = rsp + (0x20ULL);
    { const uint64_t v = ML_M8(rsp, 0); rsp += 8; rbx = v; }
    return rax;
#undef ML_CALL
    return rax;
}

uint64_t SynLift_1417538f0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A) {
    uint64_t rax = 0, rbx = 0, rbp = 0, rsi = 0, rdi = 0, r10 = 0, r11 = 0, r12 = 0, r13 = 0, r14 = 0, r15 = 0;
    uint64_t rcx = rcxA, rdx = rdxA, r8 = r8A, r9 = r9A;
    bool f_zf = false, f_cf = false, f_sf = false, f_of = false;
    uint8_t xmm0[16] = {0}, xmm1[16] = {0}, xmm2[16] = {0}, xmm3[16] = {0}, xmm4[16] = {0}, xmm5[16] = {0};
    alignas(16) uint8_t stkFrame[0x400] = {0};
    uint64_t rsp = (uint64_t)(uintptr_t)(stkFrame + 0x200);
#define ML_CALL(t) g_fnLIFT_##t(rcx, rdx, r8, r9, ML_M8(rsp, 0x20), ML_M8(rsp, 0x28))
    r8 = ML_M8(rdx, 0x10);
    rax = ML_M8(r8, 0x0);
    ML_M8(rdx, 0x10) = rax;
    rax = ML_M8(r8, 0x0);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L7;
    ML_M8(rax, 0x8) = rdx;
L7:
    rax = ML_M8(rdx, 0x8);
    ML_M8(r8, 0x8) = rax;
    rax = ML_M8(rcx, 0x30);
{
    const uint64_t a = (uint64_t)(rdx) & ~0ULL, b = (uint64_t)(ML_M8(rax, 0x8)) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L16;
    ML_M8(rax, 0x8) = r8;
    ML_M8(r8, 0x0) = rdx;
    ML_M8(rdx, 0x8) = r8;
    return rax;
L16:
    rax = ML_M8(rdx, 0x8);
{
    const uint64_t a = (uint64_t)(rdx) & ~0ULL, b = (uint64_t)(ML_M8(rax, 0x0)) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L23;
    ML_M8(rax, 0x0) = r8;
    ML_M8(r8, 0x0) = rdx;
    ML_M8(rdx, 0x8) = r8;
    return rax;
L23:
    ML_M8(rax, 0x10) = r8;
    ML_M8(r8, 0x0) = rdx;
    ML_M8(rdx, 0x8) = r8;
    return rax;
#undef ML_CALL
    return rax;
}

uint64_t SynLift_141753ab0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A) {
    uint64_t rax = 0, rbx = 0, rbp = 0, rsi = 0, rdi = 0, r10 = 0, r11 = 0, r12 = 0, r13 = 0, r14 = 0, r15 = 0;
    uint64_t rcx = rcxA, rdx = rdxA, r8 = r8A, r9 = r9A;
    bool f_zf = false, f_cf = false, f_sf = false, f_of = false;
    uint8_t xmm0[16] = {0}, xmm1[16] = {0}, xmm2[16] = {0}, xmm3[16] = {0}, xmm4[16] = {0}, xmm5[16] = {0};
    alignas(16) uint8_t stkFrame[0x400] = {0};
    uint64_t rsp = (uint64_t)(uintptr_t)(stkFrame + 0x200);
#define ML_CALL(t) g_fnLIFT_##t(rcx, rdx, r8, r9, ML_M8(rsp, 0x20), ML_M8(rsp, 0x28))
    r8 = ML_M8(rdx, 0x10);
    rax = ML_M8(r8, 0x0);
    ML_M8(rdx, 0x10) = rax;
    rax = ML_M8(r8, 0x0);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L7;
    ML_M8(rax, 0x8) = rdx;
L7:
    rax = ML_M8(rdx, 0x8);
    ML_M8(r8, 0x8) = rax;
    rax = ML_M8(rcx, 0x30);
{
    const uint64_t a = (uint64_t)(rdx) & ~0ULL, b = (uint64_t)(ML_M8(rax, 0x8)) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L16;
    ML_M8(rax, 0x8) = r8;
    ML_M8(r8, 0x0) = rdx;
    ML_M8(rdx, 0x8) = r8;
    return rax;
L16:
    rax = ML_M8(rdx, 0x8);
{
    const uint64_t a = (uint64_t)(rdx) & ~0ULL, b = (uint64_t)(ML_M8(rax, 0x0)) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L23;
    ML_M8(rax, 0x0) = r8;
    ML_M8(r8, 0x0) = rdx;
    ML_M8(rdx, 0x8) = r8;
    return rax;
L23:
    ML_M8(rax, 0x10) = r8;
    ML_M8(r8, 0x0) = rdx;
    ML_M8(rdx, 0x8) = r8;
    return rax;
#undef ML_CALL
    return rax;
}

uint64_t SynLift_141753b10(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A) {
    uint64_t rax = 0, rbx = 0, rbp = 0, rsi = 0, rdi = 0, r10 = 0, r11 = 0, r12 = 0, r13 = 0, r14 = 0, r15 = 0;
    uint64_t rcx = rcxA, rdx = rdxA, r8 = r8A, r9 = r9A;
    bool f_zf = false, f_cf = false, f_sf = false, f_of = false;
    uint8_t xmm0[16] = {0}, xmm1[16] = {0}, xmm2[16] = {0}, xmm3[16] = {0}, xmm4[16] = {0}, xmm5[16] = {0};
    alignas(16) uint8_t stkFrame[0x400] = {0};
    uint64_t rsp = (uint64_t)(uintptr_t)(stkFrame + 0x200);
#define ML_CALL(t) g_fnLIFT_##t(rcx, rdx, r8, r9, ML_M8(rsp, 0x20), ML_M8(rsp, 0x28))
    r8 = ML_M8(rdx, 0x0);
    rax = ML_M8(r8, 0x10);
    ML_M8(rdx, 0x0) = rax;
    rax = ML_M8(r8, 0x10);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L7;
    ML_M8(rax, 0x8) = rdx;
L7:
    rax = ML_M8(rdx, 0x8);
    ML_M8(r8, 0x8) = rax;
    rax = ML_M8(rcx, 0x30);
{
    const uint64_t a = (uint64_t)(rdx) & ~0ULL, b = (uint64_t)(ML_M8(rax, 0x8)) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L16;
    ML_M8(rax, 0x8) = r8;
    ML_M8(r8, 0x10) = rdx;
    ML_M8(rdx, 0x8) = r8;
    return rax;
L16:
    rax = ML_M8(rdx, 0x8);
{
    const uint64_t a = (uint64_t)(rdx) & ~0ULL, b = (uint64_t)(ML_M8(rax, 0x10)) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L23;
    ML_M8(rax, 0x10) = r8;
    ML_M8(r8, 0x10) = rdx;
    ML_M8(rdx, 0x8) = r8;
    return rax;
L23:
    ML_M8(rax, 0x0) = r8;
    ML_M8(r8, 0x10) = rdx;
    ML_M8(rdx, 0x8) = r8;
    return rax;
#undef ML_CALL
    return rax;
}

uint64_t SynLift_141753bf0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A) {
    uint64_t rax = 0, rbx = 0, rbp = 0, rsi = 0, rdi = 0, r10 = 0, r11 = 0, r12 = 0, r13 = 0, r14 = 0, r15 = 0;
    uint64_t rcx = rcxA, rdx = rdxA, r8 = r8A, r9 = r9A;
    bool f_zf = false, f_cf = false, f_sf = false, f_of = false;
    uint8_t xmm0[16] = {0}, xmm1[16] = {0}, xmm2[16] = {0}, xmm3[16] = {0}, xmm4[16] = {0}, xmm5[16] = {0};
    alignas(16) uint8_t stkFrame[0x400] = {0};
    uint64_t rsp = (uint64_t)(uintptr_t)(stkFrame + 0x200);
#define ML_CALL(t) g_fnLIFT_##t(rcx, rdx, r8, r9, ML_M8(rsp, 0x20), ML_M8(rsp, 0x28))
    r8 = ML_M8(rdx, 0x10);
    rax = ML_M8(r8, 0x0);
    ML_M8(rdx, 0x10) = rax;
    rax = ML_M8(r8, 0x0);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L7;
    ML_M8(rax, 0x8) = rdx;
L7:
    rax = ML_M8(rdx, 0x8);
    ML_M8(r8, 0x8) = rax;
    rax = ML_M8(rcx, 0x30);
{
    const uint64_t a = (uint64_t)(rdx) & ~0ULL, b = (uint64_t)(ML_M8(rax, 0x8)) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L16;
    ML_M8(rax, 0x8) = r8;
    ML_M8(r8, 0x0) = rdx;
    ML_M8(rdx, 0x8) = r8;
    return rax;
L16:
    rax = ML_M8(rdx, 0x8);
{
    const uint64_t a = (uint64_t)(rdx) & ~0ULL, b = (uint64_t)(ML_M8(rax, 0x0)) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L23;
    ML_M8(rax, 0x0) = r8;
    ML_M8(r8, 0x0) = rdx;
    ML_M8(rdx, 0x8) = r8;
    return rax;
L23:
    ML_M8(rax, 0x10) = r8;
    ML_M8(r8, 0x0) = rdx;
    ML_M8(rdx, 0x8) = r8;
    return rax;
#undef ML_CALL
    return rax;
}

uint64_t SynLift_141753c50(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A) {
    uint64_t rax = 0, rbx = 0, rbp = 0, rsi = 0, rdi = 0, r10 = 0, r11 = 0, r12 = 0, r13 = 0, r14 = 0, r15 = 0;
    uint64_t rcx = rcxA, rdx = rdxA, r8 = r8A, r9 = r9A;
    bool f_zf = false, f_cf = false, f_sf = false, f_of = false;
    uint8_t xmm0[16] = {0}, xmm1[16] = {0}, xmm2[16] = {0}, xmm3[16] = {0}, xmm4[16] = {0}, xmm5[16] = {0};
    alignas(16) uint8_t stkFrame[0x400] = {0};
    uint64_t rsp = (uint64_t)(uintptr_t)(stkFrame + 0x200);
#define ML_CALL(t) g_fnLIFT_##t(rcx, rdx, r8, r9, ML_M8(rsp, 0x20), ML_M8(rsp, 0x28))
    r8 = ML_M8(rdx, 0x0);
    rax = ML_M8(r8, 0x10);
    ML_M8(rdx, 0x0) = rax;
    rax = ML_M8(r8, 0x10);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L7;
    ML_M8(rax, 0x8) = rdx;
L7:
    rax = ML_M8(rdx, 0x8);
    ML_M8(r8, 0x8) = rax;
    rax = ML_M8(rcx, 0x30);
{
    const uint64_t a = (uint64_t)(rdx) & ~0ULL, b = (uint64_t)(ML_M8(rax, 0x8)) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L16;
    ML_M8(rax, 0x8) = r8;
    ML_M8(r8, 0x10) = rdx;
    ML_M8(rdx, 0x8) = r8;
    return rax;
L16:
    rax = ML_M8(rdx, 0x8);
{
    const uint64_t a = (uint64_t)(rdx) & ~0ULL, b = (uint64_t)(ML_M8(rax, 0x10)) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L23;
    ML_M8(rax, 0x10) = r8;
    ML_M8(r8, 0x10) = rdx;
    ML_M8(rdx, 0x8) = r8;
    return rax;
L23:
    ML_M8(rax, 0x0) = r8;
    ML_M8(r8, 0x10) = rdx;
    ML_M8(rdx, 0x8) = r8;
    return rax;
#undef ML_CALL
    return rax;
}

uint64_t SynLift_141753d70(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A) {
    uint64_t rax = 0, rbx = 0, rbp = 0, rsi = 0, rdi = 0, r10 = 0, r11 = 0, r12 = 0, r13 = 0, r14 = 0, r15 = 0;
    uint64_t rcx = rcxA, rdx = rdxA, r8 = r8A, r9 = r9A;
    bool f_zf = false, f_cf = false, f_sf = false, f_of = false;
    uint8_t xmm0[16] = {0}, xmm1[16] = {0}, xmm2[16] = {0}, xmm3[16] = {0}, xmm4[16] = {0}, xmm5[16] = {0};
    alignas(16) uint8_t stkFrame[0x400] = {0};
    uint64_t rsp = (uint64_t)(uintptr_t)(stkFrame + 0x200);
#define ML_CALL(t) g_fnLIFT_##t(rcx, rdx, r8, r9, ML_M8(rsp, 0x20), ML_M8(rsp, 0x28))
    rsp -= 8; ML_M8(rsp, 0) = rbx;
    rsp = rsp - (0x20ULL);
{
    const uint64_t a = (uint64_t)(ML_M8(rcx, 0x0)) & ~0ULL, b = (uint64_t)(0x0ULL) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    rbx = rcx;
    if (!f_zf) goto L6;
    rax = ML_CALL(1418233c0);
L6:
    rcx = ML_M8(rbx, 0x8);
{
    const uint64_t a = (uint64_t)(ML_M1(rcx, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L12;
    rsp = rsp + (0x20ULL);
    { const uint64_t v = ML_M8(rsp, 0); rsp += 8; rbx = v; }
    return ML_CALL(1418233c0);   // tail call
L12:
    rax = ML_M8(rcx, 0x10);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L27;
    rcx = ML_M8(rax, 0x0);
{
    const uint64_t a = (uint64_t)(ML_M1(rcx, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L23;
    ;
L19:
    rax = rcx;
    rcx = ML_M8(rcx, 0x0);
{
    const uint64_t a = (uint64_t)(ML_M1(rcx, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L19;
L23:
    ML_M8(rbx, 0x8) = rax;
    rsp = rsp + (0x20ULL);
    { const uint64_t v = ML_M8(rsp, 0); rsp += 8; rbx = v; }
    return rax;
L27:
    rcx = ML_M8(rcx, 0x8);
{
    const uint64_t a = (uint64_t)(ML_M1(rcx, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L37;
L30:
    rax = ML_M8(rcx, 0x10);
{
    const uint64_t a = (uint64_t)(ML_M8(rbx, 0x8)) & ~0ULL, b = (uint64_t)(rax) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L37;
    ML_M8(rbx, 0x8) = rcx;
    rcx = ML_M8(rcx, 0x8);
{
    const uint64_t a = (uint64_t)(ML_M1(rcx, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L30;
L37:
    ML_M8(rbx, 0x8) = rcx;
    rsp = rsp + (0x20ULL);
    { const uint64_t v = ML_M8(rsp, 0); rsp += 8; rbx = v; }
    return rax;
#undef ML_CALL
    return rax;
}

uint64_t SynLift_141754000(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A) {
    uint64_t rax = 0, rbx = 0, rbp = 0, rsi = 0, rdi = 0, r10 = 0, r11 = 0, r12 = 0, r13 = 0, r14 = 0, r15 = 0;
    uint64_t rcx = rcxA, rdx = rdxA, r8 = r8A, r9 = r9A;
    bool f_zf = false, f_cf = false, f_sf = false, f_of = false;
    uint8_t xmm0[16] = {0}, xmm1[16] = {0}, xmm2[16] = {0}, xmm3[16] = {0}, xmm4[16] = {0}, xmm5[16] = {0};
    alignas(16) uint8_t stkFrame[0x400] = {0};
    uint64_t rsp = (uint64_t)(uintptr_t)(stkFrame + 0x200);
#define ML_CALL(t) g_fnLIFT_##t(rcx, rdx, r8, r9, ML_M8(rsp, 0x20), ML_M8(rsp, 0x28))
    rsp -= 8; ML_M8(rsp, 0) = rbx;
    rsp = rsp - (0x20ULL);
{
    const uint64_t a = (uint64_t)(ML_M8(rcx, 0x0)) & ~0ULL, b = (uint64_t)(0x0ULL) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    rbx = rcx;
    if (!f_zf) goto L6;
    rax = ML_CALL(1418233c0);
L6:
    rcx = ML_M8(rbx, 0x8);
{
    const uint64_t a = (uint64_t)(ML_M1(rcx, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L12;
    rsp = rsp + (0x20ULL);
    { const uint64_t v = ML_M8(rsp, 0); rsp += 8; rbx = v; }
    return ML_CALL(1418233c0);   // tail call
L12:
    rax = ML_M8(rcx, 0x10);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L27;
    rcx = ML_M8(rax, 0x0);
{
    const uint64_t a = (uint64_t)(ML_M1(rcx, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L23;
    ;
L19:
    rax = rcx;
    rcx = ML_M8(rcx, 0x0);
{
    const uint64_t a = (uint64_t)(ML_M1(rcx, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L19;
L23:
    ML_M8(rbx, 0x8) = rax;
    rsp = rsp + (0x20ULL);
    { const uint64_t v = ML_M8(rsp, 0); rsp += 8; rbx = v; }
    return rax;
L27:
    rcx = ML_M8(rcx, 0x8);
{
    const uint64_t a = (uint64_t)(ML_M1(rcx, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L37;
L30:
    rax = ML_M8(rcx, 0x10);
{
    const uint64_t a = (uint64_t)(ML_M8(rbx, 0x8)) & ~0ULL, b = (uint64_t)(rax) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L37;
    ML_M8(rbx, 0x8) = rcx;
    rcx = ML_M8(rcx, 0x8);
{
    const uint64_t a = (uint64_t)(ML_M1(rcx, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L30;
L37:
    ML_M8(rbx, 0x8) = rcx;
    rsp = rsp + (0x20ULL);
    { const uint64_t v = ML_M8(rsp, 0); rsp += 8; rbx = v; }
    return rax;
#undef ML_CALL
    return rax;
}

__attribute__((weak)) uint64_t (*g_fnLIFT_141752cd0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t) = nullptr;
__attribute__((weak)) uint64_t (*g_fnLIFT_141752d30)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t) = nullptr;
__attribute__((weak)) uint64_t (*g_fnLIFT_141753470)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t) = nullptr;
uint64_t SynLift_141758050(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A) {
    uint64_t rax = 0, rbx = 0, rbp = 0, rsi = 0, rdi = 0, r10 = 0, r11 = 0, r12 = 0, r13 = 0, r14 = 0, r15 = 0;
    uint64_t rcx = rcxA, rdx = rdxA, r8 = r8A, r9 = r9A;
    bool f_zf = false, f_cf = false, f_sf = false, f_of = false;
    uint8_t xmm0[16] = {0}, xmm1[16] = {0}, xmm2[16] = {0}, xmm3[16] = {0}, xmm4[16] = {0}, xmm5[16] = {0};
    alignas(16) uint8_t stkFrame[0x400] = {0};
    uint64_t rsp = (uint64_t)(uintptr_t)(stkFrame + 0x200);
#define ML_CALL(t) g_fnLIFT_##t(rcx, rdx, r8, r9, ML_M8(rsp, 0x20), ML_M8(rsp, 0x28))
    rax = rsp;
    rsp -= 8; ML_M8(rsp, 0) = rdi;
    rsp -= 8; ML_M8(rsp, 0) = r12;
    rsp -= 8; ML_M8(rsp, 0) = r13;
    rsp = rsp - (0xa0ULL);
    ML_M8(rsp, 0x30) = 0xfffffffffffffffeULL;
    ML_M8(rax, 0x8) = rbx;
    ML_M8(rax, 0x10) = rbp;
    ML_M8(rax, 0x18) = rsi;
    r12 = r8;
    r13 = rdx;
    rbp = rcx;
    rsi = ML_M8(r8, 0x8);
{
    const uint64_t a = (uint64_t)(ML_M1(rsi, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L30;
    rdx = (uintptr_t)0x141825ca8;
    rcx = rax - 0x40;
    rax = ML_CALL(141823270);
    rcx = rsp + 0x38;
    rax = ML_CALL(1418233f8);
    rax = (uintptr_t)0x141824a60;
    ML_M8(rsp, 0x38) = rax;
    rdx = rsp + 0x78;
    rcx = rsp + 0x50;
    rax = ML_CALL(141823288);
    rax = (uintptr_t)0x141824ba0;
    ML_M8(rsp, 0x38) = rax;
    rdx = (uintptr_t)0x141881e50;
    rcx = rsp + 0x38;
    rax = ML_CALL(1417f3154);
L30:
    rcx = r8;
    rax = ML_CALL(141753470);
    r11 = ML_M8(rsi, 0x0);
{
    const uint64_t a = (uint64_t)(ML_M1(r11, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L37;
    rdi = ML_M8(rsi, 0x10);
    goto L46;
L37:
    rax = ML_M8(rsi, 0x10);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L42;
    rdi = r11;
    goto L46;
L42:
    rcx = ML_M8(r12, 0x8);
    rdi = ML_M8(rcx, 0x10);
{
    const uint64_t a = (uint64_t)(rcx) & ~0ULL, b = (uint64_t)(rsi) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L93;
L46:
    rbx = ML_M8(rsi, 0x8);
{
    const uint64_t a = (uint64_t)(ML_M1(rdi, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L50;
    ML_M8(rdi, 0x8) = rbx;
L50:
    rax = ML_M8(rbp, 0x30);
{
    const uint64_t a = (uint64_t)(ML_M8(rax, 0x8)) & ~0ULL, b = (uint64_t)(rsi) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L55;
    ML_M8(rax, 0x8) = rdi;
    goto L60;
L55:
{
    const uint64_t a = (uint64_t)(ML_M8(rbx, 0x0)) & ~0ULL, b = (uint64_t)(rsi) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L59;
    ML_M8(rbx, 0x0) = rdi;
    goto L60;
L59:
    ML_M8(rbx, 0x10) = rdi;
L60:
    rdx = ML_M8(rbp, 0x30);
{
    const uint64_t a = (uint64_t)(ML_M8(rdx, 0x0)) & ~0ULL, b = (uint64_t)(rsi) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L76;
{
    const uint64_t a = (uint64_t)(ML_M1(rdi, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L67;
    rcx = rbx;
    goto L75;
L67:
    rcx = rdi;
    rax = ML_M8(rdi, 0x0);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L75;
L71:
    rcx = rax;
    rax = ML_M8(rax, 0x0);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L71;
L75:
    ML_M8(rdx, 0x0) = rcx;
L76:
    rdx = ML_M8(rbp, 0x30);
{
    const uint64_t a = (uint64_t)(ML_M8(rdx, 0x10)) & ~0ULL, b = (uint64_t)(rsi) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L130;
{
    const uint64_t a = (uint64_t)(ML_M1(rdi, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L83;
    rcx = rbx;
    goto L91;
L83:
    rcx = rdi;
    rax = ML_M8(rdi, 0x10);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L91;
L87:
    rcx = rax;
    rax = ML_M8(rax, 0x10);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L87;
L91:
    ML_M8(rdx, 0x10) = rcx;
    goto L130;
L93:
    ML_M8(r11, 0x8) = rcx;
    rax = ML_M8(rsi, 0x0);
    ML_M8(rcx, 0x0) = rax;
{
    const uint64_t a = (uint64_t)(rcx) & ~0ULL, b = (uint64_t)(ML_M8(rsi, 0x10)) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L100;
    rbx = rcx;
    goto L109;
L100:
    rbx = ML_M8(rcx, 0x8);
{
    const uint64_t a = (uint64_t)(ML_M1(rdi, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L104;
    ML_M8(rdi, 0x8) = rbx;
L104:
    ML_M8(rbx, 0x0) = rdi;
    rax = ML_M8(rsi, 0x10);
    ML_M8(rcx, 0x10) = rax;
    rax = ML_M8(rsi, 0x10);
    ML_M8(rax, 0x8) = rcx;
L109:
    rax = ML_M8(rbp, 0x30);
{
    const uint64_t a = (uint64_t)(ML_M8(rax, 0x8)) & ~0ULL, b = (uint64_t)(rsi) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L114;
    ML_M8(rax, 0x8) = rcx;
    goto L120;
L114:
    rax = ML_M8(rsi, 0x8);
{
    const uint64_t a = (uint64_t)(ML_M8(rax, 0x0)) & ~0ULL, b = (uint64_t)(rsi) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L119;
    ML_M8(rax, 0x0) = rcx;
    goto L120;
L119:
    ML_M8(rax, 0x10) = rcx;
L120:
    rax = ML_M8(rsi, 0x8);
    ML_M8(rcx, 0x8) = rax;
    rdx = rsi + 0x28;
    r8 = rcx + 0x28;
{
    const uint64_t a = (uint64_t)(r8) & ~0ULL, b = (uint64_t)(rdx) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (f_zf) goto L130;
    rcx = ML_M1(r8, 0x0);
    rax = ML_M1(rdx, 0x0);
    ML_M1(r8, 0x0) = (uint8_t)rax;
    ML_M1(rdx, 0x0) = (uint8_t)rcx;
L130:
{
    const uint64_t a = (uint64_t)(ML_M1(rsi, 0x28)) & 0xFFULL, b = (uint64_t)(0x1ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L225;
    rax = ML_M8(rbp, 0x30);
{
    const uint64_t a = (uint64_t)(rdi) & ~0ULL, b = (uint64_t)(ML_M8(rax, 0x8)) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (f_zf) goto L224;
L135:
{
    const uint64_t a = (uint64_t)(ML_M1(rdi, 0x28)) & 0xFFULL, b = (uint64_t)(0x1ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L224;
    rcx = ML_M8(rbx, 0x0);
{
    const uint64_t a = (uint64_t)(rdi) & ~0ULL, b = (uint64_t)(rcx) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L162;
    rcx = ML_M8(rbx, 0x10);
{
    const uint64_t a = (uint64_t)(ML_M1(rcx, 0x28)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L149;
    ML_M1(rcx, 0x28) = 0x1ULL;
    ML_M1(rbx, 0x28) = 0x0ULL;
    rdx = rbx;
    rcx = rbp;
    rax = ML_CALL(141752cd0);
    rcx = ML_M8(rbx, 0x10);
L149:
{
    const uint64_t a = (uint64_t)(ML_M1(rcx, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L153;
    rdi = rbx;
    goto L182;
L153:
    rax = ML_M8(rcx, 0x0);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x28)) & 0xFFULL, b = (uint64_t)(0x1ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L187;
    rax = ML_M8(rcx, 0x10);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x28)) & 0xFFULL, b = (uint64_t)(0x1ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L187;
    ML_M1(rcx, 0x28) = 0x0ULL;
    rdi = rbx;
    goto L182;
L162:
{
    const uint64_t a = (uint64_t)(ML_M1(rcx, 0x28)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L170;
    ML_M1(rcx, 0x28) = 0x1ULL;
    ML_M1(rbx, 0x28) = 0x0ULL;
    rdx = rbx;
    rcx = rbp;
    rax = ML_CALL(141752d30);
    rcx = ML_M8(rbx, 0x0);
L170:
{
    const uint64_t a = (uint64_t)(ML_M1(rcx, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L174;
    rdi = rbx;
    goto L182;
L174:
    rax = ML_M8(rcx, 0x10);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x28)) & 0xFFULL, b = (uint64_t)(0x1ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L206;
    rax = ML_M8(rcx, 0x0);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x28)) & 0xFFULL, b = (uint64_t)(0x1ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L206;
    ML_M1(rcx, 0x28) = 0x0ULL;
    rdi = rbx;
L182:
    rbx = ML_M8(rbx, 0x8);
    rax = ML_M8(rbp, 0x30);
{
    const uint64_t a = (uint64_t)(rdi) & ~0ULL, b = (uint64_t)(ML_M8(rax, 0x8)) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (f_zf) goto L224;
    goto L135;
L187:
    rax = ML_M8(rcx, 0x10);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x28)) & 0xFFULL, b = (uint64_t)(0x1ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L197;
    rax = ML_M8(rcx, 0x0);
    ML_M1(rax, 0x28) = 0x1ULL;
    ML_M1(rcx, 0x28) = 0x0ULL;
    rdx = rcx;
    rcx = rbp;
    rax = ML_CALL(141752d30);
    rcx = ML_M8(rbx, 0x10);
L197:
    rax = ML_M1(rbx, 0x28);
    ML_M1(rcx, 0x28) = (uint8_t)rax;
    ML_M1(rbx, 0x28) = 0x1ULL;
    rax = ML_M8(rcx, 0x10);
    ML_M1(rax, 0x28) = 0x1ULL;
    rdx = rbx;
    rcx = rbp;
    rax = ML_CALL(141752cd0);
    goto L224;
L206:
    rax = ML_M8(rcx, 0x0);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x28)) & 0xFFULL, b = (uint64_t)(0x1ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L216;
    rax = ML_M8(rcx, 0x10);
    ML_M1(rax, 0x28) = 0x1ULL;
    ML_M1(rcx, 0x28) = 0x0ULL;
    rdx = rcx;
    rcx = rbp;
    rax = ML_CALL(141752cd0);
    rcx = ML_M8(rbx, 0x0);
L216:
    rax = ML_M1(rbx, 0x28);
    ML_M1(rcx, 0x28) = (uint8_t)rax;
    ML_M1(rbx, 0x28) = 0x1ULL;
    rax = ML_M8(rcx, 0x0);
    ML_M1(rax, 0x28) = 0x1ULL;
    rdx = rbx;
    rcx = rbp;
    rax = ML_CALL(141752d30);
L224:
    ML_M1(rdi, 0x28) = 0x1ULL;
L225:
    rcx = rsi;
    rax = ML_CALL(1417f2fdc);
    rax = ML_M8(rbp, 0x38);
{
    const uint64_t r = ((uint64_t)(rax) & ~0ULL) & ((uint64_t)(rax) & ~0ULL);
    f_zf = (r == 0); f_cf = false; f_sf = ((r & 0x8000000000000000ULL) != 0);
    f_of = false;
}
    if (f_zf) goto L232;
    rax = rax - 1;
    ML_M8(rbp, 0x38) = rax;
L232:
    rcx = rsp + 0x20;
    rax = ML_M8(r12, 0x0);
    ML_M8(rcx, 0x0) = rax;
    rax = ML_M8(r12, 0x8);
    ML_M8(rcx, 0x8) = rax;
    rax = ML_M8(rsp, 0x28);
    ML_M8(rsp, 0x28) = rax;
    rax = ML_M8(rbp, 0x0);
    ML_M8(rsp, 0x20) = rax;
    rcx = rsp + 0x20;
    rax = ML_M8(rcx, 0x0);
    ML_M8(r13, 0x0) = rax;
    rax = ML_M8(rcx, 0x8);
    ML_M8(r13, 0x8) = rax;
    rax = r13;
    r11 = rsp + 0xa0;
    rbx = ML_M8(r11, 0x20);
    rbp = ML_M8(r11, 0x28);
    rsi = ML_M8(r11, 0x30);
    rsp = r11;
    { const uint64_t v = ML_M8(rsp, 0); rsp += 8; r13 = v; }
    { const uint64_t v = ML_M8(rsp, 0); rsp += 8; r12 = v; }
    { const uint64_t v = ML_M8(rsp, 0); rsp += 8; rdi = v; }
    return rax;
#undef ML_CALL
    return rax;
}

__attribute__((weak)) uint64_t (*g_fnLIFT_1417512f0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t) = nullptr;
__attribute__((weak)) uint64_t (*g_fnLIFT_141752ef0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t) = nullptr;
__attribute__((weak)) uint64_t (*g_fnLIFT_141752f50)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t) = nullptr;
uint64_t SynLift_1417591f0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A) {
    uint64_t rax = 0, rbx = 0, rbp = 0, rsi = 0, rdi = 0, r10 = 0, r11 = 0, r12 = 0, r13 = 0, r14 = 0, r15 = 0;
    uint64_t rcx = rcxA, rdx = rdxA, r8 = r8A, r9 = r9A;
    bool f_zf = false, f_cf = false, f_sf = false, f_of = false;
    uint8_t xmm0[16] = {0}, xmm1[16] = {0}, xmm2[16] = {0}, xmm3[16] = {0}, xmm4[16] = {0}, xmm5[16] = {0};
    alignas(16) uint8_t stkFrame[0x400] = {0};
    uint64_t rsp = (uint64_t)(uintptr_t)(stkFrame + 0x200);
#define ML_CALL(t) g_fnLIFT_##t(rcx, rdx, r8, r9, ML_M8(rsp, 0x20), ML_M8(rsp, 0x28))
    rax = rsp;
    rsp -= 8; ML_M8(rsp, 0) = rdi;
    rsp -= 8; ML_M8(rsp, 0) = r12;
    rsp -= 8; ML_M8(rsp, 0) = r13;
    rsp = rsp - (0xa0ULL);
    ML_M8(rsp, 0x30) = 0xfffffffffffffffeULL;
    ML_M8(rax, 0x8) = rbx;
    ML_M8(rax, 0x10) = rbp;
    ML_M8(rax, 0x18) = rsi;
    r12 = r8;
    r13 = rdx;
    rbp = rcx;
    rsi = ML_M8(r8, 0x8);
{
    const uint64_t a = (uint64_t)(ML_M1(rsi, 0x59)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L30;
    rdx = (uintptr_t)0x141825ca8;
    rcx = rax - 0x40;
    rax = ML_CALL(141823270);
    rcx = rsp + 0x38;
    rax = ML_CALL(1418233f8);
    rax = (uintptr_t)0x141824a60;
    ML_M8(rsp, 0x38) = rax;
    rdx = rsp + 0x78;
    rcx = rsp + 0x50;
    rax = ML_CALL(141823288);
    rax = (uintptr_t)0x141824ba0;
    ML_M8(rsp, 0x38) = rax;
    rdx = (uintptr_t)0x141881e50;
    rcx = rsp + 0x38;
    rax = ML_CALL(1417f3154);
L30:
    rcx = r8;
    rax = ML_CALL(1417512f0);
    r11 = ML_M8(rsi, 0x0);
{
    const uint64_t a = (uint64_t)(ML_M1(r11, 0x59)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L37;
    rdi = ML_M8(rsi, 0x10);
    goto L46;
L37:
    rax = ML_M8(rsi, 0x10);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x59)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L42;
    rdi = r11;
    goto L46;
L42:
    rcx = ML_M8(r12, 0x8);
    rdi = ML_M8(rcx, 0x10);
{
    const uint64_t a = (uint64_t)(rcx) & ~0ULL, b = (uint64_t)(rsi) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L93;
L46:
    rbx = ML_M8(rsi, 0x8);
{
    const uint64_t a = (uint64_t)(ML_M1(rdi, 0x59)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L50;
    ML_M8(rdi, 0x8) = rbx;
L50:
    rax = ML_M8(rbp, 0x30);
{
    const uint64_t a = (uint64_t)(ML_M8(rax, 0x8)) & ~0ULL, b = (uint64_t)(rsi) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L55;
    ML_M8(rax, 0x8) = rdi;
    goto L60;
L55:
{
    const uint64_t a = (uint64_t)(ML_M8(rbx, 0x0)) & ~0ULL, b = (uint64_t)(rsi) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L59;
    ML_M8(rbx, 0x0) = rdi;
    goto L60;
L59:
    ML_M8(rbx, 0x10) = rdi;
L60:
    rdx = ML_M8(rbp, 0x30);
{
    const uint64_t a = (uint64_t)(ML_M8(rdx, 0x0)) & ~0ULL, b = (uint64_t)(rsi) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L76;
{
    const uint64_t a = (uint64_t)(ML_M1(rdi, 0x59)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L67;
    rcx = rbx;
    goto L75;
L67:
    rcx = rdi;
    rax = ML_M8(rdi, 0x0);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x59)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L75;
L71:
    rcx = rax;
    rax = ML_M8(rax, 0x0);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x59)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L71;
L75:
    ML_M8(rdx, 0x0) = rcx;
L76:
    rdx = ML_M8(rbp, 0x30);
{
    const uint64_t a = (uint64_t)(ML_M8(rdx, 0x10)) & ~0ULL, b = (uint64_t)(rsi) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L130;
{
    const uint64_t a = (uint64_t)(ML_M1(rdi, 0x59)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L83;
    rcx = rbx;
    goto L91;
L83:
    rcx = rdi;
    rax = ML_M8(rdi, 0x10);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x59)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L91;
L87:
    rcx = rax;
    rax = ML_M8(rax, 0x10);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x59)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L87;
L91:
    ML_M8(rdx, 0x10) = rcx;
    goto L130;
L93:
    ML_M8(r11, 0x8) = rcx;
    rax = ML_M8(rsi, 0x0);
    ML_M8(rcx, 0x0) = rax;
{
    const uint64_t a = (uint64_t)(rcx) & ~0ULL, b = (uint64_t)(ML_M8(rsi, 0x10)) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L100;
    rbx = rcx;
    goto L109;
L100:
    rbx = ML_M8(rcx, 0x8);
{
    const uint64_t a = (uint64_t)(ML_M1(rdi, 0x59)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L104;
    ML_M8(rdi, 0x8) = rbx;
L104:
    ML_M8(rbx, 0x0) = rdi;
    rax = ML_M8(rsi, 0x10);
    ML_M8(rcx, 0x10) = rax;
    rax = ML_M8(rsi, 0x10);
    ML_M8(rax, 0x8) = rcx;
L109:
    rax = ML_M8(rbp, 0x30);
{
    const uint64_t a = (uint64_t)(ML_M8(rax, 0x8)) & ~0ULL, b = (uint64_t)(rsi) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L114;
    ML_M8(rax, 0x8) = rcx;
    goto L120;
L114:
    rax = ML_M8(rsi, 0x8);
{
    const uint64_t a = (uint64_t)(ML_M8(rax, 0x0)) & ~0ULL, b = (uint64_t)(rsi) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L119;
    ML_M8(rax, 0x0) = rcx;
    goto L120;
L119:
    ML_M8(rax, 0x10) = rcx;
L120:
    rax = ML_M8(rsi, 0x8);
    ML_M8(rcx, 0x8) = rax;
    rdx = rsi + 0x58;
    r8 = rcx + 0x58;
{
    const uint64_t a = (uint64_t)(r8) & ~0ULL, b = (uint64_t)(rdx) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (f_zf) goto L130;
    rcx = ML_M1(r8, 0x0);
    rax = ML_M1(rdx, 0x0);
    ML_M1(r8, 0x0) = (uint8_t)rax;
    ML_M1(rdx, 0x0) = (uint8_t)rcx;
L130:
{
    const uint64_t a = (uint64_t)(ML_M1(rsi, 0x58)) & 0xFFULL, b = (uint64_t)(0x1ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L225;
    rax = ML_M8(rbp, 0x30);
{
    const uint64_t a = (uint64_t)(rdi) & ~0ULL, b = (uint64_t)(ML_M8(rax, 0x8)) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (f_zf) goto L224;
L135:
{
    const uint64_t a = (uint64_t)(ML_M1(rdi, 0x58)) & 0xFFULL, b = (uint64_t)(0x1ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L224;
    rcx = ML_M8(rbx, 0x0);
{
    const uint64_t a = (uint64_t)(rdi) & ~0ULL, b = (uint64_t)(rcx) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L162;
    rcx = ML_M8(rbx, 0x10);
{
    const uint64_t a = (uint64_t)(ML_M1(rcx, 0x58)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L149;
    ML_M1(rcx, 0x58) = 0x1ULL;
    ML_M1(rbx, 0x58) = 0x0ULL;
    rdx = rbx;
    rcx = rbp;
    rax = ML_CALL(141752ef0);
    rcx = ML_M8(rbx, 0x10);
L149:
{
    const uint64_t a = (uint64_t)(ML_M1(rcx, 0x59)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L153;
    rdi = rbx;
    goto L182;
L153:
    rax = ML_M8(rcx, 0x0);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x58)) & 0xFFULL, b = (uint64_t)(0x1ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L187;
    rax = ML_M8(rcx, 0x10);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x58)) & 0xFFULL, b = (uint64_t)(0x1ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L187;
    ML_M1(rcx, 0x58) = 0x0ULL;
    rdi = rbx;
    goto L182;
L162:
{
    const uint64_t a = (uint64_t)(ML_M1(rcx, 0x58)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L170;
    ML_M1(rcx, 0x58) = 0x1ULL;
    ML_M1(rbx, 0x58) = 0x0ULL;
    rdx = rbx;
    rcx = rbp;
    rax = ML_CALL(141752f50);
    rcx = ML_M8(rbx, 0x0);
L170:
{
    const uint64_t a = (uint64_t)(ML_M1(rcx, 0x59)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L174;
    rdi = rbx;
    goto L182;
L174:
    rax = ML_M8(rcx, 0x10);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x58)) & 0xFFULL, b = (uint64_t)(0x1ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L206;
    rax = ML_M8(rcx, 0x0);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x58)) & 0xFFULL, b = (uint64_t)(0x1ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L206;
    ML_M1(rcx, 0x58) = 0x0ULL;
    rdi = rbx;
L182:
    rbx = ML_M8(rbx, 0x8);
    rax = ML_M8(rbp, 0x30);
{
    const uint64_t a = (uint64_t)(rdi) & ~0ULL, b = (uint64_t)(ML_M8(rax, 0x8)) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (f_zf) goto L224;
    goto L135;
L187:
    rax = ML_M8(rcx, 0x10);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x58)) & 0xFFULL, b = (uint64_t)(0x1ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L197;
    rax = ML_M8(rcx, 0x0);
    ML_M1(rax, 0x58) = 0x1ULL;
    ML_M1(rcx, 0x58) = 0x0ULL;
    rdx = rcx;
    rcx = rbp;
    rax = ML_CALL(141752f50);
    rcx = ML_M8(rbx, 0x10);
L197:
    rax = ML_M1(rbx, 0x58);
    ML_M1(rcx, 0x58) = (uint8_t)rax;
    ML_M1(rbx, 0x58) = 0x1ULL;
    rax = ML_M8(rcx, 0x10);
    ML_M1(rax, 0x58) = 0x1ULL;
    rdx = rbx;
    rcx = rbp;
    rax = ML_CALL(141752ef0);
    goto L224;
L206:
    rax = ML_M8(rcx, 0x0);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x58)) & 0xFFULL, b = (uint64_t)(0x1ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L216;
    rax = ML_M8(rcx, 0x10);
    ML_M1(rax, 0x58) = 0x1ULL;
    ML_M1(rcx, 0x58) = 0x0ULL;
    rdx = rcx;
    rcx = rbp;
    rax = ML_CALL(141752ef0);
    rcx = ML_M8(rbx, 0x0);
L216:
    rax = ML_M1(rbx, 0x58);
    ML_M1(rcx, 0x58) = (uint8_t)rax;
    ML_M1(rbx, 0x58) = 0x1ULL;
    rax = ML_M8(rcx, 0x0);
    ML_M1(rax, 0x58) = 0x1ULL;
    rdx = rbx;
    rcx = rbp;
    rax = ML_CALL(141752f50);
L224:
    ML_M1(rdi, 0x58) = 0x1ULL;
L225:
    rcx = rsi;
    rax = ML_CALL(1417f2fdc);
    rax = ML_M8(rbp, 0x38);
{
    const uint64_t r = ((uint64_t)(rax) & ~0ULL) & ((uint64_t)(rax) & ~0ULL);
    f_zf = (r == 0); f_cf = false; f_sf = ((r & 0x8000000000000000ULL) != 0);
    f_of = false;
}
    if (f_zf) goto L232;
    rax = rax - 1;
    ML_M8(rbp, 0x38) = rax;
L232:
    rcx = rsp + 0x20;
    rax = ML_M8(r12, 0x0);
    ML_M8(rcx, 0x0) = rax;
    rax = ML_M8(r12, 0x8);
    ML_M8(rcx, 0x8) = rax;
    rax = ML_M8(rsp, 0x28);
    ML_M8(rsp, 0x28) = rax;
    rax = ML_M8(rbp, 0x0);
    ML_M8(rsp, 0x20) = rax;
    rcx = rsp + 0x20;
    rax = ML_M8(rcx, 0x0);
    ML_M8(r13, 0x0) = rax;
    rax = ML_M8(rcx, 0x8);
    ML_M8(r13, 0x8) = rax;
    rax = r13;
    r11 = rsp + 0xa0;
    rbx = ML_M8(r11, 0x20);
    rbp = ML_M8(r11, 0x28);
    rsi = ML_M8(r11, 0x30);
    rsp = r11;
    { const uint64_t v = ML_M8(rsp, 0); rsp += 8; r13 = v; }
    { const uint64_t v = ML_M8(rsp, 0); rsp += 8; r12 = v; }
    { const uint64_t v = ML_M8(rsp, 0); rsp += 8; rdi = v; }
    return rax;
#undef ML_CALL
    return rax;
}

__attribute__((weak)) uint64_t (*g_fnLIFT_141750a30)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t) = nullptr;
__attribute__((weak)) uint64_t (*g_fnLIFT_1417538f0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t) = nullptr;
__attribute__((weak)) uint64_t (*g_fnLIFT_141754000)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t) = nullptr;
uint64_t SynLift_141759600(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A) {
    uint64_t rax = 0, rbx = 0, rbp = 0, rsi = 0, rdi = 0, r10 = 0, r11 = 0, r12 = 0, r13 = 0, r14 = 0, r15 = 0;
    uint64_t rcx = rcxA, rdx = rdxA, r8 = r8A, r9 = r9A;
    bool f_zf = false, f_cf = false, f_sf = false, f_of = false;
    uint8_t xmm0[16] = {0}, xmm1[16] = {0}, xmm2[16] = {0}, xmm3[16] = {0}, xmm4[16] = {0}, xmm5[16] = {0};
    alignas(16) uint8_t stkFrame[0x400] = {0};
    uint64_t rsp = (uint64_t)(uintptr_t)(stkFrame + 0x200);
#define ML_CALL(t) g_fnLIFT_##t(rcx, rdx, r8, r9, ML_M8(rsp, 0x20), ML_M8(rsp, 0x28))
    rax = rsp;
    rsp -= 8; ML_M8(rsp, 0) = rdi;
    rsp -= 8; ML_M8(rsp, 0) = r12;
    rsp -= 8; ML_M8(rsp, 0) = r13;
    rsp = rsp - (0xa0ULL);
    ML_M8(rsp, 0x30) = 0xfffffffffffffffeULL;
    ML_M8(rax, 0x8) = rbx;
    ML_M8(rax, 0x10) = rbp;
    ML_M8(rax, 0x18) = rsi;
    r12 = r8;
    r13 = rdx;
    rbp = rcx;
    rsi = ML_M8(r8, 0x8);
{
    const uint64_t a = (uint64_t)(ML_M1(rsi, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L30;
    rdx = (uintptr_t)0x141825ca8;
    rcx = rax - 0x40;
    rax = ML_CALL(141823270);
    rcx = rsp + 0x38;
    rax = ML_CALL(1418233f8);
    rax = (uintptr_t)0x141824a60;
    ML_M8(rsp, 0x38) = rax;
    rdx = rsp + 0x78;
    rcx = rsp + 0x50;
    rax = ML_CALL(141823288);
    rax = (uintptr_t)0x141824ba0;
    ML_M8(rsp, 0x38) = rax;
    rdx = (uintptr_t)0x141881e50;
    rcx = rsp + 0x38;
    rax = ML_CALL(1417f3154);
L30:
    rcx = r8;
    rax = ML_CALL(141754000);
    r11 = ML_M8(rsi, 0x0);
{
    const uint64_t a = (uint64_t)(ML_M1(r11, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L37;
    rdi = ML_M8(rsi, 0x10);
    goto L46;
L37:
    rax = ML_M8(rsi, 0x10);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L42;
    rdi = r11;
    goto L46;
L42:
    rcx = ML_M8(r12, 0x8);
    rdi = ML_M8(rcx, 0x10);
{
    const uint64_t a = (uint64_t)(rcx) & ~0ULL, b = (uint64_t)(rsi) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L93;
L46:
    rbx = ML_M8(rsi, 0x8);
{
    const uint64_t a = (uint64_t)(ML_M1(rdi, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L50;
    ML_M8(rdi, 0x8) = rbx;
L50:
    rax = ML_M8(rbp, 0x30);
{
    const uint64_t a = (uint64_t)(ML_M8(rax, 0x8)) & ~0ULL, b = (uint64_t)(rsi) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L55;
    ML_M8(rax, 0x8) = rdi;
    goto L60;
L55:
{
    const uint64_t a = (uint64_t)(ML_M8(rbx, 0x0)) & ~0ULL, b = (uint64_t)(rsi) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L59;
    ML_M8(rbx, 0x0) = rdi;
    goto L60;
L59:
    ML_M8(rbx, 0x10) = rdi;
L60:
    rdx = ML_M8(rbp, 0x30);
{
    const uint64_t a = (uint64_t)(ML_M8(rdx, 0x0)) & ~0ULL, b = (uint64_t)(rsi) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L76;
{
    const uint64_t a = (uint64_t)(ML_M1(rdi, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L67;
    rcx = rbx;
    goto L75;
L67:
    rcx = rdi;
    rax = ML_M8(rdi, 0x0);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L75;
L71:
    rcx = rax;
    rax = ML_M8(rax, 0x0);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L71;
L75:
    ML_M8(rdx, 0x0) = rcx;
L76:
    rdx = ML_M8(rbp, 0x30);
{
    const uint64_t a = (uint64_t)(ML_M8(rdx, 0x10)) & ~0ULL, b = (uint64_t)(rsi) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L130;
{
    const uint64_t a = (uint64_t)(ML_M1(rdi, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L83;
    rcx = rbx;
    goto L91;
L83:
    rcx = rdi;
    rax = ML_M8(rdi, 0x10);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L91;
L87:
    rcx = rax;
    rax = ML_M8(rax, 0x10);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L87;
L91:
    ML_M8(rdx, 0x10) = rcx;
    goto L130;
L93:
    ML_M8(r11, 0x8) = rcx;
    rax = ML_M8(rsi, 0x0);
    ML_M8(rcx, 0x0) = rax;
{
    const uint64_t a = (uint64_t)(rcx) & ~0ULL, b = (uint64_t)(ML_M8(rsi, 0x10)) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L100;
    rbx = rcx;
    goto L109;
L100:
    rbx = ML_M8(rcx, 0x8);
{
    const uint64_t a = (uint64_t)(ML_M1(rdi, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L104;
    ML_M8(rdi, 0x8) = rbx;
L104:
    ML_M8(rbx, 0x0) = rdi;
    rax = ML_M8(rsi, 0x10);
    ML_M8(rcx, 0x10) = rax;
    rax = ML_M8(rsi, 0x10);
    ML_M8(rax, 0x8) = rcx;
L109:
    rax = ML_M8(rbp, 0x30);
{
    const uint64_t a = (uint64_t)(ML_M8(rax, 0x8)) & ~0ULL, b = (uint64_t)(rsi) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L114;
    ML_M8(rax, 0x8) = rcx;
    goto L120;
L114:
    rax = ML_M8(rsi, 0x8);
{
    const uint64_t a = (uint64_t)(ML_M8(rax, 0x0)) & ~0ULL, b = (uint64_t)(rsi) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L119;
    ML_M8(rax, 0x0) = rcx;
    goto L120;
L119:
    ML_M8(rax, 0x10) = rcx;
L120:
    rax = ML_M8(rsi, 0x8);
    ML_M8(rcx, 0x8) = rax;
    rdx = rsi + 0x28;
    r8 = rcx + 0x28;
{
    const uint64_t a = (uint64_t)(r8) & ~0ULL, b = (uint64_t)(rdx) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (f_zf) goto L130;
    rcx = ML_M1(r8, 0x0);
    rax = ML_M1(rdx, 0x0);
    ML_M1(r8, 0x0) = (uint8_t)rax;
    ML_M1(rdx, 0x0) = (uint8_t)rcx;
L130:
{
    const uint64_t a = (uint64_t)(ML_M1(rsi, 0x28)) & 0xFFULL, b = (uint64_t)(0x1ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L225;
    rax = ML_M8(rbp, 0x30);
{
    const uint64_t a = (uint64_t)(rdi) & ~0ULL, b = (uint64_t)(ML_M8(rax, 0x8)) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (f_zf) goto L224;
L135:
{
    const uint64_t a = (uint64_t)(ML_M1(rdi, 0x28)) & 0xFFULL, b = (uint64_t)(0x1ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L224;
    rcx = ML_M8(rbx, 0x0);
{
    const uint64_t a = (uint64_t)(rdi) & ~0ULL, b = (uint64_t)(rcx) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L162;
    rcx = ML_M8(rbx, 0x10);
{
    const uint64_t a = (uint64_t)(ML_M1(rcx, 0x28)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L149;
    ML_M1(rcx, 0x28) = 0x1ULL;
    ML_M1(rbx, 0x28) = 0x0ULL;
    rdx = rbx;
    rcx = rbp;
    rax = ML_CALL(1417538f0);
    rcx = ML_M8(rbx, 0x10);
L149:
{
    const uint64_t a = (uint64_t)(ML_M1(rcx, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L153;
    rdi = rbx;
    goto L182;
L153:
    rax = ML_M8(rcx, 0x0);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x28)) & 0xFFULL, b = (uint64_t)(0x1ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L187;
    rax = ML_M8(rcx, 0x10);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x28)) & 0xFFULL, b = (uint64_t)(0x1ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L187;
    ML_M1(rcx, 0x28) = 0x0ULL;
    rdi = rbx;
    goto L182;
L162:
{
    const uint64_t a = (uint64_t)(ML_M1(rcx, 0x28)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L170;
    ML_M1(rcx, 0x28) = 0x1ULL;
    ML_M1(rbx, 0x28) = 0x0ULL;
    rdx = rbx;
    rcx = rbp;
    rax = ML_CALL(141750a30);
    rcx = ML_M8(rbx, 0x0);
L170:
{
    const uint64_t a = (uint64_t)(ML_M1(rcx, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L174;
    rdi = rbx;
    goto L182;
L174:
    rax = ML_M8(rcx, 0x10);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x28)) & 0xFFULL, b = (uint64_t)(0x1ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L206;
    rax = ML_M8(rcx, 0x0);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x28)) & 0xFFULL, b = (uint64_t)(0x1ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L206;
    ML_M1(rcx, 0x28) = 0x0ULL;
    rdi = rbx;
L182:
    rbx = ML_M8(rbx, 0x8);
    rax = ML_M8(rbp, 0x30);
{
    const uint64_t a = (uint64_t)(rdi) & ~0ULL, b = (uint64_t)(ML_M8(rax, 0x8)) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (f_zf) goto L224;
    goto L135;
L187:
    rax = ML_M8(rcx, 0x10);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x28)) & 0xFFULL, b = (uint64_t)(0x1ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L197;
    rax = ML_M8(rcx, 0x0);
    ML_M1(rax, 0x28) = 0x1ULL;
    ML_M1(rcx, 0x28) = 0x0ULL;
    rdx = rcx;
    rcx = rbp;
    rax = ML_CALL(141750a30);
    rcx = ML_M8(rbx, 0x10);
L197:
    rax = ML_M1(rbx, 0x28);
    ML_M1(rcx, 0x28) = (uint8_t)rax;
    ML_M1(rbx, 0x28) = 0x1ULL;
    rax = ML_M8(rcx, 0x10);
    ML_M1(rax, 0x28) = 0x1ULL;
    rdx = rbx;
    rcx = rbp;
    rax = ML_CALL(1417538f0);
    goto L224;
L206:
    rax = ML_M8(rcx, 0x0);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x28)) & 0xFFULL, b = (uint64_t)(0x1ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L216;
    rax = ML_M8(rcx, 0x10);
    ML_M1(rax, 0x28) = 0x1ULL;
    ML_M1(rcx, 0x28) = 0x0ULL;
    rdx = rcx;
    rcx = rbp;
    rax = ML_CALL(1417538f0);
    rcx = ML_M8(rbx, 0x0);
L216:
    rax = ML_M1(rbx, 0x28);
    ML_M1(rcx, 0x28) = (uint8_t)rax;
    ML_M1(rbx, 0x28) = 0x1ULL;
    rax = ML_M8(rcx, 0x0);
    ML_M1(rax, 0x28) = 0x1ULL;
    rdx = rbx;
    rcx = rbp;
    rax = ML_CALL(141750a30);
L224:
    ML_M1(rdi, 0x28) = 0x1ULL;
L225:
    rcx = rsi;
    rax = ML_CALL(1417f2fdc);
    rax = ML_M8(rbp, 0x38);
{
    const uint64_t r = ((uint64_t)(rax) & ~0ULL) & ((uint64_t)(rax) & ~0ULL);
    f_zf = (r == 0); f_cf = false; f_sf = ((r & 0x8000000000000000ULL) != 0);
    f_of = false;
}
    if (f_zf) goto L232;
    rax = rax - 1;
    ML_M8(rbp, 0x38) = rax;
L232:
    rcx = rsp + 0x20;
    rax = ML_M8(r12, 0x0);
    ML_M8(rcx, 0x0) = rax;
    rax = ML_M8(r12, 0x8);
    ML_M8(rcx, 0x8) = rax;
    rax = ML_M8(rsp, 0x28);
    ML_M8(rsp, 0x28) = rax;
    rax = ML_M8(rbp, 0x0);
    ML_M8(rsp, 0x20) = rax;
    rcx = rsp + 0x20;
    rax = ML_M8(rcx, 0x0);
    ML_M8(r13, 0x0) = rax;
    rax = ML_M8(rcx, 0x8);
    ML_M8(r13, 0x8) = rax;
    rax = r13;
    r11 = rsp + 0xa0;
    rbx = ML_M8(r11, 0x20);
    rbp = ML_M8(r11, 0x28);
    rsi = ML_M8(r11, 0x30);
    rsp = r11;
    { const uint64_t v = ML_M8(rsp, 0); rsp += 8; r13 = v; }
    { const uint64_t v = ML_M8(rsp, 0); rsp += 8; r12 = v; }
    { const uint64_t v = ML_M8(rsp, 0); rsp += 8; rdi = v; }
    return rax;
#undef ML_CALL
    return rax;
}

__attribute__((weak)) uint64_t (*g_fnLIFT_1417530a0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t) = nullptr;
__attribute__((weak)) uint64_t (*g_fnLIFT_141753100)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t) = nullptr;
__attribute__((weak)) uint64_t (*g_fnLIFT_141753620)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t) = nullptr;
uint64_t SynLift_141759a90(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A) {
    uint64_t rax = 0, rbx = 0, rbp = 0, rsi = 0, rdi = 0, r10 = 0, r11 = 0, r12 = 0, r13 = 0, r14 = 0, r15 = 0;
    uint64_t rcx = rcxA, rdx = rdxA, r8 = r8A, r9 = r9A;
    bool f_zf = false, f_cf = false, f_sf = false, f_of = false;
    uint8_t xmm0[16] = {0}, xmm1[16] = {0}, xmm2[16] = {0}, xmm3[16] = {0}, xmm4[16] = {0}, xmm5[16] = {0};
    alignas(16) uint8_t stkFrame[0x400] = {0};
    uint64_t rsp = (uint64_t)(uintptr_t)(stkFrame + 0x200);
#define ML_CALL(t) g_fnLIFT_##t(rcx, rdx, r8, r9, ML_M8(rsp, 0x20), ML_M8(rsp, 0x28))
    rax = rsp;
    rsp -= 8; ML_M8(rsp, 0) = rdi;
    rsp -= 8; ML_M8(rsp, 0) = r12;
    rsp -= 8; ML_M8(rsp, 0) = r13;
    rsp = rsp - (0xa0ULL);
    ML_M8(rsp, 0x30) = 0xfffffffffffffffeULL;
    ML_M8(rax, 0x8) = rbx;
    ML_M8(rax, 0x10) = rbp;
    ML_M8(rax, 0x18) = rsi;
    r12 = r8;
    r13 = rdx;
    rbp = rcx;
    rsi = ML_M8(r8, 0x8);
{
    const uint64_t a = (uint64_t)(ML_M1(rsi, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L30;
    rdx = (uintptr_t)0x141825ca8;
    rcx = rax - 0x40;
    rax = ML_CALL(141823270);
    rcx = rsp + 0x38;
    rax = ML_CALL(1418233f8);
    rax = (uintptr_t)0x141824a60;
    ML_M8(rsp, 0x38) = rax;
    rdx = rsp + 0x78;
    rcx = rsp + 0x50;
    rax = ML_CALL(141823288);
    rax = (uintptr_t)0x141824ba0;
    ML_M8(rsp, 0x38) = rax;
    rdx = (uintptr_t)0x141881e50;
    rcx = rsp + 0x38;
    rax = ML_CALL(1417f3154);
L30:
    rcx = r8;
    rax = ML_CALL(141753620);
    r11 = ML_M8(rsi, 0x0);
{
    const uint64_t a = (uint64_t)(ML_M1(r11, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L37;
    rdi = ML_M8(rsi, 0x10);
    goto L46;
L37:
    rax = ML_M8(rsi, 0x10);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L42;
    rdi = r11;
    goto L46;
L42:
    rcx = ML_M8(r12, 0x8);
    rdi = ML_M8(rcx, 0x10);
{
    const uint64_t a = (uint64_t)(rcx) & ~0ULL, b = (uint64_t)(rsi) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L93;
L46:
    rbx = ML_M8(rsi, 0x8);
{
    const uint64_t a = (uint64_t)(ML_M1(rdi, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L50;
    ML_M8(rdi, 0x8) = rbx;
L50:
    rax = ML_M8(rbp, 0x30);
{
    const uint64_t a = (uint64_t)(ML_M8(rax, 0x8)) & ~0ULL, b = (uint64_t)(rsi) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L55;
    ML_M8(rax, 0x8) = rdi;
    goto L60;
L55:
{
    const uint64_t a = (uint64_t)(ML_M8(rbx, 0x0)) & ~0ULL, b = (uint64_t)(rsi) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L59;
    ML_M8(rbx, 0x0) = rdi;
    goto L60;
L59:
    ML_M8(rbx, 0x10) = rdi;
L60:
    rdx = ML_M8(rbp, 0x30);
{
    const uint64_t a = (uint64_t)(ML_M8(rdx, 0x0)) & ~0ULL, b = (uint64_t)(rsi) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L76;
{
    const uint64_t a = (uint64_t)(ML_M1(rdi, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L67;
    rcx = rbx;
    goto L75;
L67:
    rcx = rdi;
    rax = ML_M8(rdi, 0x0);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L75;
L71:
    rcx = rax;
    rax = ML_M8(rax, 0x0);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L71;
L75:
    ML_M8(rdx, 0x0) = rcx;
L76:
    rdx = ML_M8(rbp, 0x30);
{
    const uint64_t a = (uint64_t)(ML_M8(rdx, 0x10)) & ~0ULL, b = (uint64_t)(rsi) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L130;
{
    const uint64_t a = (uint64_t)(ML_M1(rdi, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L83;
    rcx = rbx;
    goto L91;
L83:
    rcx = rdi;
    rax = ML_M8(rdi, 0x10);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L91;
L87:
    rcx = rax;
    rax = ML_M8(rax, 0x10);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L87;
L91:
    ML_M8(rdx, 0x10) = rcx;
    goto L130;
L93:
    ML_M8(r11, 0x8) = rcx;
    rax = ML_M8(rsi, 0x0);
    ML_M8(rcx, 0x0) = rax;
{
    const uint64_t a = (uint64_t)(rcx) & ~0ULL, b = (uint64_t)(ML_M8(rsi, 0x10)) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L100;
    rbx = rcx;
    goto L109;
L100:
    rbx = ML_M8(rcx, 0x8);
{
    const uint64_t a = (uint64_t)(ML_M1(rdi, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L104;
    ML_M8(rdi, 0x8) = rbx;
L104:
    ML_M8(rbx, 0x0) = rdi;
    rax = ML_M8(rsi, 0x10);
    ML_M8(rcx, 0x10) = rax;
    rax = ML_M8(rsi, 0x10);
    ML_M8(rax, 0x8) = rcx;
L109:
    rax = ML_M8(rbp, 0x30);
{
    const uint64_t a = (uint64_t)(ML_M8(rax, 0x8)) & ~0ULL, b = (uint64_t)(rsi) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L114;
    ML_M8(rax, 0x8) = rcx;
    goto L120;
L114:
    rax = ML_M8(rsi, 0x8);
{
    const uint64_t a = (uint64_t)(ML_M8(rax, 0x0)) & ~0ULL, b = (uint64_t)(rsi) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L119;
    ML_M8(rax, 0x0) = rcx;
    goto L120;
L119:
    ML_M8(rax, 0x10) = rcx;
L120:
    rax = ML_M8(rsi, 0x8);
    ML_M8(rcx, 0x8) = rax;
    rdx = rsi + 0x28;
    r8 = rcx + 0x28;
{
    const uint64_t a = (uint64_t)(r8) & ~0ULL, b = (uint64_t)(rdx) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (f_zf) goto L130;
    rcx = ML_M1(r8, 0x0);
    rax = ML_M1(rdx, 0x0);
    ML_M1(r8, 0x0) = (uint8_t)rax;
    ML_M1(rdx, 0x0) = (uint8_t)rcx;
L130:
{
    const uint64_t a = (uint64_t)(ML_M1(rsi, 0x28)) & 0xFFULL, b = (uint64_t)(0x1ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L225;
    rax = ML_M8(rbp, 0x30);
{
    const uint64_t a = (uint64_t)(rdi) & ~0ULL, b = (uint64_t)(ML_M8(rax, 0x8)) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (f_zf) goto L224;
L135:
{
    const uint64_t a = (uint64_t)(ML_M1(rdi, 0x28)) & 0xFFULL, b = (uint64_t)(0x1ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L224;
    rcx = ML_M8(rbx, 0x0);
{
    const uint64_t a = (uint64_t)(rdi) & ~0ULL, b = (uint64_t)(rcx) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L162;
    rcx = ML_M8(rbx, 0x10);
{
    const uint64_t a = (uint64_t)(ML_M1(rcx, 0x28)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L149;
    ML_M1(rcx, 0x28) = 0x1ULL;
    ML_M1(rbx, 0x28) = 0x0ULL;
    rdx = rbx;
    rcx = rbp;
    rax = ML_CALL(1417530a0);
    rcx = ML_M8(rbx, 0x10);
L149:
{
    const uint64_t a = (uint64_t)(ML_M1(rcx, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L153;
    rdi = rbx;
    goto L182;
L153:
    rax = ML_M8(rcx, 0x0);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x28)) & 0xFFULL, b = (uint64_t)(0x1ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L187;
    rax = ML_M8(rcx, 0x10);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x28)) & 0xFFULL, b = (uint64_t)(0x1ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L187;
    ML_M1(rcx, 0x28) = 0x0ULL;
    rdi = rbx;
    goto L182;
L162:
{
    const uint64_t a = (uint64_t)(ML_M1(rcx, 0x28)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L170;
    ML_M1(rcx, 0x28) = 0x1ULL;
    ML_M1(rbx, 0x28) = 0x0ULL;
    rdx = rbx;
    rcx = rbp;
    rax = ML_CALL(141753100);
    rcx = ML_M8(rbx, 0x0);
L170:
{
    const uint64_t a = (uint64_t)(ML_M1(rcx, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L174;
    rdi = rbx;
    goto L182;
L174:
    rax = ML_M8(rcx, 0x10);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x28)) & 0xFFULL, b = (uint64_t)(0x1ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L206;
    rax = ML_M8(rcx, 0x0);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x28)) & 0xFFULL, b = (uint64_t)(0x1ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L206;
    ML_M1(rcx, 0x28) = 0x0ULL;
    rdi = rbx;
L182:
    rbx = ML_M8(rbx, 0x8);
    rax = ML_M8(rbp, 0x30);
{
    const uint64_t a = (uint64_t)(rdi) & ~0ULL, b = (uint64_t)(ML_M8(rax, 0x8)) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (f_zf) goto L224;
    goto L135;
L187:
    rax = ML_M8(rcx, 0x10);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x28)) & 0xFFULL, b = (uint64_t)(0x1ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L197;
    rax = ML_M8(rcx, 0x0);
    ML_M1(rax, 0x28) = 0x1ULL;
    ML_M1(rcx, 0x28) = 0x0ULL;
    rdx = rcx;
    rcx = rbp;
    rax = ML_CALL(141753100);
    rcx = ML_M8(rbx, 0x10);
L197:
    rax = ML_M1(rbx, 0x28);
    ML_M1(rcx, 0x28) = (uint8_t)rax;
    ML_M1(rbx, 0x28) = 0x1ULL;
    rax = ML_M8(rcx, 0x10);
    ML_M1(rax, 0x28) = 0x1ULL;
    rdx = rbx;
    rcx = rbp;
    rax = ML_CALL(1417530a0);
    goto L224;
L206:
    rax = ML_M8(rcx, 0x0);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x28)) & 0xFFULL, b = (uint64_t)(0x1ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L216;
    rax = ML_M8(rcx, 0x10);
    ML_M1(rax, 0x28) = 0x1ULL;
    ML_M1(rcx, 0x28) = 0x0ULL;
    rdx = rcx;
    rcx = rbp;
    rax = ML_CALL(1417530a0);
    rcx = ML_M8(rbx, 0x0);
L216:
    rax = ML_M1(rbx, 0x28);
    ML_M1(rcx, 0x28) = (uint8_t)rax;
    ML_M1(rbx, 0x28) = 0x1ULL;
    rax = ML_M8(rcx, 0x0);
    ML_M1(rax, 0x28) = 0x1ULL;
    rdx = rbx;
    rcx = rbp;
    rax = ML_CALL(141753100);
L224:
    ML_M1(rdi, 0x28) = 0x1ULL;
L225:
    rcx = rsi;
    rax = ML_CALL(1417f2fdc);
    rax = ML_M8(rbp, 0x38);
{
    const uint64_t r = ((uint64_t)(rax) & ~0ULL) & ((uint64_t)(rax) & ~0ULL);
    f_zf = (r == 0); f_cf = false; f_sf = ((r & 0x8000000000000000ULL) != 0);
    f_of = false;
}
    if (f_zf) goto L232;
    rax = rax - 1;
    ML_M8(rbp, 0x38) = rax;
L232:
    rcx = rsp + 0x20;
    rax = ML_M8(r12, 0x0);
    ML_M8(rcx, 0x0) = rax;
    rax = ML_M8(r12, 0x8);
    ML_M8(rcx, 0x8) = rax;
    rax = ML_M8(rsp, 0x28);
    ML_M8(rsp, 0x28) = rax;
    rax = ML_M8(rbp, 0x0);
    ML_M8(rsp, 0x20) = rax;
    rcx = rsp + 0x20;
    rax = ML_M8(rcx, 0x0);
    ML_M8(r13, 0x0) = rax;
    rax = ML_M8(rcx, 0x8);
    ML_M8(r13, 0x8) = rax;
    rax = r13;
    r11 = rsp + 0xa0;
    rbx = ML_M8(r11, 0x20);
    rbp = ML_M8(r11, 0x28);
    rsi = ML_M8(r11, 0x30);
    rsp = r11;
    { const uint64_t v = ML_M8(rsp, 0); rsp += 8; r13 = v; }
    { const uint64_t v = ML_M8(rsp, 0); rsp += 8; r12 = v; }
    { const uint64_t v = ML_M8(rsp, 0); rsp += 8; rdi = v; }
    return rax;
#undef ML_CALL
    return rax;
}

__attribute__((weak)) uint64_t (*g_fnLIFT_141753ab0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t) = nullptr;
__attribute__((weak)) uint64_t (*g_fnLIFT_141753b10)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t) = nullptr;
__attribute__((weak)) uint64_t (*g_fnLIFT_141753d70)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t) = nullptr;
uint64_t SynLift_141759ef0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A) {
    uint64_t rax = 0, rbx = 0, rbp = 0, rsi = 0, rdi = 0, r10 = 0, r11 = 0, r12 = 0, r13 = 0, r14 = 0, r15 = 0;
    uint64_t rcx = rcxA, rdx = rdxA, r8 = r8A, r9 = r9A;
    bool f_zf = false, f_cf = false, f_sf = false, f_of = false;
    uint8_t xmm0[16] = {0}, xmm1[16] = {0}, xmm2[16] = {0}, xmm3[16] = {0}, xmm4[16] = {0}, xmm5[16] = {0};
    alignas(16) uint8_t stkFrame[0x400] = {0};
    uint64_t rsp = (uint64_t)(uintptr_t)(stkFrame + 0x200);
#define ML_CALL(t) g_fnLIFT_##t(rcx, rdx, r8, r9, ML_M8(rsp, 0x20), ML_M8(rsp, 0x28))
    rax = rsp;
    rsp -= 8; ML_M8(rsp, 0) = rdi;
    rsp -= 8; ML_M8(rsp, 0) = r12;
    rsp -= 8; ML_M8(rsp, 0) = r13;
    rsp = rsp - (0xa0ULL);
    ML_M8(rsp, 0x30) = 0xfffffffffffffffeULL;
    ML_M8(rax, 0x8) = rbx;
    ML_M8(rax, 0x10) = rbp;
    ML_M8(rax, 0x18) = rsi;
    r12 = r8;
    r13 = rdx;
    rbp = rcx;
    rsi = ML_M8(r8, 0x8);
{
    const uint64_t a = (uint64_t)(ML_M1(rsi, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L30;
    rdx = (uintptr_t)0x141825ca8;
    rcx = rax - 0x40;
    rax = ML_CALL(141823270);
    rcx = rsp + 0x38;
    rax = ML_CALL(1418233f8);
    rax = (uintptr_t)0x141824a60;
    ML_M8(rsp, 0x38) = rax;
    rdx = rsp + 0x78;
    rcx = rsp + 0x50;
    rax = ML_CALL(141823288);
    rax = (uintptr_t)0x141824ba0;
    ML_M8(rsp, 0x38) = rax;
    rdx = (uintptr_t)0x141881e50;
    rcx = rsp + 0x38;
    rax = ML_CALL(1417f3154);
L30:
    rcx = r8;
    rax = ML_CALL(141753d70);
    r11 = ML_M8(rsi, 0x0);
{
    const uint64_t a = (uint64_t)(ML_M1(r11, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L37;
    rdi = ML_M8(rsi, 0x10);
    goto L46;
L37:
    rax = ML_M8(rsi, 0x10);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L42;
    rdi = r11;
    goto L46;
L42:
    rcx = ML_M8(r12, 0x8);
    rdi = ML_M8(rcx, 0x10);
{
    const uint64_t a = (uint64_t)(rcx) & ~0ULL, b = (uint64_t)(rsi) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L93;
L46:
    rbx = ML_M8(rsi, 0x8);
{
    const uint64_t a = (uint64_t)(ML_M1(rdi, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L50;
    ML_M8(rdi, 0x8) = rbx;
L50:
    rax = ML_M8(rbp, 0x30);
{
    const uint64_t a = (uint64_t)(ML_M8(rax, 0x8)) & ~0ULL, b = (uint64_t)(rsi) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L55;
    ML_M8(rax, 0x8) = rdi;
    goto L60;
L55:
{
    const uint64_t a = (uint64_t)(ML_M8(rbx, 0x0)) & ~0ULL, b = (uint64_t)(rsi) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L59;
    ML_M8(rbx, 0x0) = rdi;
    goto L60;
L59:
    ML_M8(rbx, 0x10) = rdi;
L60:
    rdx = ML_M8(rbp, 0x30);
{
    const uint64_t a = (uint64_t)(ML_M8(rdx, 0x0)) & ~0ULL, b = (uint64_t)(rsi) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L76;
{
    const uint64_t a = (uint64_t)(ML_M1(rdi, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L67;
    rcx = rbx;
    goto L75;
L67:
    rcx = rdi;
    rax = ML_M8(rdi, 0x0);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L75;
L71:
    rcx = rax;
    rax = ML_M8(rax, 0x0);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L71;
L75:
    ML_M8(rdx, 0x0) = rcx;
L76:
    rdx = ML_M8(rbp, 0x30);
{
    const uint64_t a = (uint64_t)(ML_M8(rdx, 0x10)) & ~0ULL, b = (uint64_t)(rsi) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L130;
{
    const uint64_t a = (uint64_t)(ML_M1(rdi, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L83;
    rcx = rbx;
    goto L91;
L83:
    rcx = rdi;
    rax = ML_M8(rdi, 0x10);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L91;
L87:
    rcx = rax;
    rax = ML_M8(rax, 0x10);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L87;
L91:
    ML_M8(rdx, 0x10) = rcx;
    goto L130;
L93:
    ML_M8(r11, 0x8) = rcx;
    rax = ML_M8(rsi, 0x0);
    ML_M8(rcx, 0x0) = rax;
{
    const uint64_t a = (uint64_t)(rcx) & ~0ULL, b = (uint64_t)(ML_M8(rsi, 0x10)) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L100;
    rbx = rcx;
    goto L109;
L100:
    rbx = ML_M8(rcx, 0x8);
{
    const uint64_t a = (uint64_t)(ML_M1(rdi, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L104;
    ML_M8(rdi, 0x8) = rbx;
L104:
    ML_M8(rbx, 0x0) = rdi;
    rax = ML_M8(rsi, 0x10);
    ML_M8(rcx, 0x10) = rax;
    rax = ML_M8(rsi, 0x10);
    ML_M8(rax, 0x8) = rcx;
L109:
    rax = ML_M8(rbp, 0x30);
{
    const uint64_t a = (uint64_t)(ML_M8(rax, 0x8)) & ~0ULL, b = (uint64_t)(rsi) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L114;
    ML_M8(rax, 0x8) = rcx;
    goto L120;
L114:
    rax = ML_M8(rsi, 0x8);
{
    const uint64_t a = (uint64_t)(ML_M8(rax, 0x0)) & ~0ULL, b = (uint64_t)(rsi) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L119;
    ML_M8(rax, 0x0) = rcx;
    goto L120;
L119:
    ML_M8(rax, 0x10) = rcx;
L120:
    rax = ML_M8(rsi, 0x8);
    ML_M8(rcx, 0x8) = rax;
    rdx = rsi + 0x28;
    r8 = rcx + 0x28;
{
    const uint64_t a = (uint64_t)(r8) & ~0ULL, b = (uint64_t)(rdx) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (f_zf) goto L130;
    rcx = ML_M1(r8, 0x0);
    rax = ML_M1(rdx, 0x0);
    ML_M1(r8, 0x0) = (uint8_t)rax;
    ML_M1(rdx, 0x0) = (uint8_t)rcx;
L130:
{
    const uint64_t a = (uint64_t)(ML_M1(rsi, 0x28)) & 0xFFULL, b = (uint64_t)(0x1ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L225;
    rax = ML_M8(rbp, 0x30);
{
    const uint64_t a = (uint64_t)(rdi) & ~0ULL, b = (uint64_t)(ML_M8(rax, 0x8)) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (f_zf) goto L224;
L135:
{
    const uint64_t a = (uint64_t)(ML_M1(rdi, 0x28)) & 0xFFULL, b = (uint64_t)(0x1ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L224;
    rcx = ML_M8(rbx, 0x0);
{
    const uint64_t a = (uint64_t)(rdi) & ~0ULL, b = (uint64_t)(rcx) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L162;
    rcx = ML_M8(rbx, 0x10);
{
    const uint64_t a = (uint64_t)(ML_M1(rcx, 0x28)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L149;
    ML_M1(rcx, 0x28) = 0x1ULL;
    ML_M1(rbx, 0x28) = 0x0ULL;
    rdx = rbx;
    rcx = rbp;
    rax = ML_CALL(141753ab0);
    rcx = ML_M8(rbx, 0x10);
L149:
{
    const uint64_t a = (uint64_t)(ML_M1(rcx, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L153;
    rdi = rbx;
    goto L182;
L153:
    rax = ML_M8(rcx, 0x0);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x28)) & 0xFFULL, b = (uint64_t)(0x1ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L187;
    rax = ML_M8(rcx, 0x10);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x28)) & 0xFFULL, b = (uint64_t)(0x1ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L187;
    ML_M1(rcx, 0x28) = 0x0ULL;
    rdi = rbx;
    goto L182;
L162:
{
    const uint64_t a = (uint64_t)(ML_M1(rcx, 0x28)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L170;
    ML_M1(rcx, 0x28) = 0x1ULL;
    ML_M1(rbx, 0x28) = 0x0ULL;
    rdx = rbx;
    rcx = rbp;
    rax = ML_CALL(141753b10);
    rcx = ML_M8(rbx, 0x0);
L170:
{
    const uint64_t a = (uint64_t)(ML_M1(rcx, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L174;
    rdi = rbx;
    goto L182;
L174:
    rax = ML_M8(rcx, 0x10);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x28)) & 0xFFULL, b = (uint64_t)(0x1ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L206;
    rax = ML_M8(rcx, 0x0);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x28)) & 0xFFULL, b = (uint64_t)(0x1ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L206;
    ML_M1(rcx, 0x28) = 0x0ULL;
    rdi = rbx;
L182:
    rbx = ML_M8(rbx, 0x8);
    rax = ML_M8(rbp, 0x30);
{
    const uint64_t a = (uint64_t)(rdi) & ~0ULL, b = (uint64_t)(ML_M8(rax, 0x8)) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (f_zf) goto L224;
    goto L135;
L187:
    rax = ML_M8(rcx, 0x10);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x28)) & 0xFFULL, b = (uint64_t)(0x1ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L197;
    rax = ML_M8(rcx, 0x0);
    ML_M1(rax, 0x28) = 0x1ULL;
    ML_M1(rcx, 0x28) = 0x0ULL;
    rdx = rcx;
    rcx = rbp;
    rax = ML_CALL(141753b10);
    rcx = ML_M8(rbx, 0x10);
L197:
    rax = ML_M1(rbx, 0x28);
    ML_M1(rcx, 0x28) = (uint8_t)rax;
    ML_M1(rbx, 0x28) = 0x1ULL;
    rax = ML_M8(rcx, 0x10);
    ML_M1(rax, 0x28) = 0x1ULL;
    rdx = rbx;
    rcx = rbp;
    rax = ML_CALL(141753ab0);
    goto L224;
L206:
    rax = ML_M8(rcx, 0x0);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x28)) & 0xFFULL, b = (uint64_t)(0x1ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L216;
    rax = ML_M8(rcx, 0x10);
    ML_M1(rax, 0x28) = 0x1ULL;
    ML_M1(rcx, 0x28) = 0x0ULL;
    rdx = rcx;
    rcx = rbp;
    rax = ML_CALL(141753ab0);
    rcx = ML_M8(rbx, 0x0);
L216:
    rax = ML_M1(rbx, 0x28);
    ML_M1(rcx, 0x28) = (uint8_t)rax;
    ML_M1(rbx, 0x28) = 0x1ULL;
    rax = ML_M8(rcx, 0x0);
    ML_M1(rax, 0x28) = 0x1ULL;
    rdx = rbx;
    rcx = rbp;
    rax = ML_CALL(141753b10);
L224:
    ML_M1(rdi, 0x28) = 0x1ULL;
L225:
    rcx = rsi;
    rax = ML_CALL(1417f2fdc);
    rax = ML_M8(rbp, 0x38);
{
    const uint64_t r = ((uint64_t)(rax) & ~0ULL) & ((uint64_t)(rax) & ~0ULL);
    f_zf = (r == 0); f_cf = false; f_sf = ((r & 0x8000000000000000ULL) != 0);
    f_of = false;
}
    if (f_zf) goto L232;
    rax = rax - 1;
    ML_M8(rbp, 0x38) = rax;
L232:
    rcx = rsp + 0x20;
    rax = ML_M8(r12, 0x0);
    ML_M8(rcx, 0x0) = rax;
    rax = ML_M8(r12, 0x8);
    ML_M8(rcx, 0x8) = rax;
    rax = ML_M8(rsp, 0x28);
    ML_M8(rsp, 0x28) = rax;
    rax = ML_M8(rbp, 0x0);
    ML_M8(rsp, 0x20) = rax;
    rcx = rsp + 0x20;
    rax = ML_M8(rcx, 0x0);
    ML_M8(r13, 0x0) = rax;
    rax = ML_M8(rcx, 0x8);
    ML_M8(r13, 0x8) = rax;
    rax = r13;
    r11 = rsp + 0xa0;
    rbx = ML_M8(r11, 0x20);
    rbp = ML_M8(r11, 0x28);
    rsi = ML_M8(r11, 0x30);
    rsp = r11;
    { const uint64_t v = ML_M8(rsp, 0); rsp += 8; r13 = v; }
    { const uint64_t v = ML_M8(rsp, 0); rsp += 8; r12 = v; }
    { const uint64_t v = ML_M8(rsp, 0); rsp += 8; rdi = v; }
    return rax;
#undef ML_CALL
    return rax;
}

__attribute__((weak)) uint64_t (*g_fnLIFT_141751380)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t) = nullptr;
__attribute__((weak)) uint64_t (*g_fnLIFT_141753320)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t) = nullptr;
__attribute__((weak)) uint64_t (*g_fnLIFT_141753380)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t) = nullptr;
uint64_t SynLift_14175a300(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A) {
    uint64_t rax = 0, rbx = 0, rbp = 0, rsi = 0, rdi = 0, r10 = 0, r11 = 0, r12 = 0, r13 = 0, r14 = 0, r15 = 0;
    uint64_t rcx = rcxA, rdx = rdxA, r8 = r8A, r9 = r9A;
    bool f_zf = false, f_cf = false, f_sf = false, f_of = false;
    uint8_t xmm0[16] = {0}, xmm1[16] = {0}, xmm2[16] = {0}, xmm3[16] = {0}, xmm4[16] = {0}, xmm5[16] = {0};
    alignas(16) uint8_t stkFrame[0x400] = {0};
    uint64_t rsp = (uint64_t)(uintptr_t)(stkFrame + 0x200);
#define ML_CALL(t) g_fnLIFT_##t(rcx, rdx, r8, r9, ML_M8(rsp, 0x20), ML_M8(rsp, 0x28))
    rax = rsp;
    rsp -= 8; ML_M8(rsp, 0) = rdi;
    rsp -= 8; ML_M8(rsp, 0) = r12;
    rsp -= 8; ML_M8(rsp, 0) = r13;
    rsp = rsp - (0xa0ULL);
    ML_M8(rsp, 0x30) = 0xfffffffffffffffeULL;
    ML_M8(rax, 0x8) = rbx;
    ML_M8(rax, 0x10) = rbp;
    ML_M8(rax, 0x18) = rsi;
    r12 = r8;
    r13 = rdx;
    rbp = rcx;
    rsi = ML_M8(r8, 0x8);
{
    const uint64_t a = (uint64_t)(ML_M1(rsi, 0x69)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L30;
    rdx = (uintptr_t)0x141825ca8;
    rcx = rax - 0x40;
    rax = ML_CALL(141823270);
    rcx = rsp + 0x38;
    rax = ML_CALL(1418233f8);
    rax = (uintptr_t)0x141824a60;
    ML_M8(rsp, 0x38) = rax;
    rdx = rsp + 0x78;
    rcx = rsp + 0x50;
    rax = ML_CALL(141823288);
    rax = (uintptr_t)0x141824ba0;
    ML_M8(rsp, 0x38) = rax;
    rdx = (uintptr_t)0x141881e50;
    rcx = rsp + 0x38;
    rax = ML_CALL(1417f3154);
L30:
    rcx = r8;
    rax = ML_CALL(141751380);
    r11 = ML_M8(rsi, 0x0);
{
    const uint64_t a = (uint64_t)(ML_M1(r11, 0x69)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L37;
    rdi = ML_M8(rsi, 0x10);
    goto L46;
L37:
    rax = ML_M8(rsi, 0x10);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x69)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L42;
    rdi = r11;
    goto L46;
L42:
    rcx = ML_M8(r12, 0x8);
    rdi = ML_M8(rcx, 0x10);
{
    const uint64_t a = (uint64_t)(rcx) & ~0ULL, b = (uint64_t)(rsi) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L93;
L46:
    rbx = ML_M8(rsi, 0x8);
{
    const uint64_t a = (uint64_t)(ML_M1(rdi, 0x69)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L50;
    ML_M8(rdi, 0x8) = rbx;
L50:
    rax = ML_M8(rbp, 0x30);
{
    const uint64_t a = (uint64_t)(ML_M8(rax, 0x8)) & ~0ULL, b = (uint64_t)(rsi) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L55;
    ML_M8(rax, 0x8) = rdi;
    goto L60;
L55:
{
    const uint64_t a = (uint64_t)(ML_M8(rbx, 0x0)) & ~0ULL, b = (uint64_t)(rsi) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L59;
    ML_M8(rbx, 0x0) = rdi;
    goto L60;
L59:
    ML_M8(rbx, 0x10) = rdi;
L60:
    rdx = ML_M8(rbp, 0x30);
{
    const uint64_t a = (uint64_t)(ML_M8(rdx, 0x0)) & ~0ULL, b = (uint64_t)(rsi) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L76;
{
    const uint64_t a = (uint64_t)(ML_M1(rdi, 0x69)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L67;
    rcx = rbx;
    goto L75;
L67:
    rcx = rdi;
    rax = ML_M8(rdi, 0x0);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x69)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L75;
L71:
    rcx = rax;
    rax = ML_M8(rax, 0x0);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x69)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L71;
L75:
    ML_M8(rdx, 0x0) = rcx;
L76:
    rdx = ML_M8(rbp, 0x30);
{
    const uint64_t a = (uint64_t)(ML_M8(rdx, 0x10)) & ~0ULL, b = (uint64_t)(rsi) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L130;
{
    const uint64_t a = (uint64_t)(ML_M1(rdi, 0x69)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L83;
    rcx = rbx;
    goto L91;
L83:
    rcx = rdi;
    rax = ML_M8(rdi, 0x10);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x69)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L91;
L87:
    rcx = rax;
    rax = ML_M8(rax, 0x10);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x69)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L87;
L91:
    ML_M8(rdx, 0x10) = rcx;
    goto L130;
L93:
    ML_M8(r11, 0x8) = rcx;
    rax = ML_M8(rsi, 0x0);
    ML_M8(rcx, 0x0) = rax;
{
    const uint64_t a = (uint64_t)(rcx) & ~0ULL, b = (uint64_t)(ML_M8(rsi, 0x10)) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L100;
    rbx = rcx;
    goto L109;
L100:
    rbx = ML_M8(rcx, 0x8);
{
    const uint64_t a = (uint64_t)(ML_M1(rdi, 0x69)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L104;
    ML_M8(rdi, 0x8) = rbx;
L104:
    ML_M8(rbx, 0x0) = rdi;
    rax = ML_M8(rsi, 0x10);
    ML_M8(rcx, 0x10) = rax;
    rax = ML_M8(rsi, 0x10);
    ML_M8(rax, 0x8) = rcx;
L109:
    rax = ML_M8(rbp, 0x30);
{
    const uint64_t a = (uint64_t)(ML_M8(rax, 0x8)) & ~0ULL, b = (uint64_t)(rsi) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L114;
    ML_M8(rax, 0x8) = rcx;
    goto L120;
L114:
    rax = ML_M8(rsi, 0x8);
{
    const uint64_t a = (uint64_t)(ML_M8(rax, 0x0)) & ~0ULL, b = (uint64_t)(rsi) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L119;
    ML_M8(rax, 0x0) = rcx;
    goto L120;
L119:
    ML_M8(rax, 0x10) = rcx;
L120:
    rax = ML_M8(rsi, 0x8);
    ML_M8(rcx, 0x8) = rax;
    rdx = rsi + 0x68;
    r8 = rcx + 0x68;
{
    const uint64_t a = (uint64_t)(r8) & ~0ULL, b = (uint64_t)(rdx) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (f_zf) goto L130;
    rcx = ML_M1(r8, 0x0);
    rax = ML_M1(rdx, 0x0);
    ML_M1(r8, 0x0) = (uint8_t)rax;
    ML_M1(rdx, 0x0) = (uint8_t)rcx;
L130:
{
    const uint64_t a = (uint64_t)(ML_M1(rsi, 0x68)) & 0xFFULL, b = (uint64_t)(0x1ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L225;
    rax = ML_M8(rbp, 0x30);
{
    const uint64_t a = (uint64_t)(rdi) & ~0ULL, b = (uint64_t)(ML_M8(rax, 0x8)) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (f_zf) goto L224;
L135:
{
    const uint64_t a = (uint64_t)(ML_M1(rdi, 0x68)) & 0xFFULL, b = (uint64_t)(0x1ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L224;
    rcx = ML_M8(rbx, 0x0);
{
    const uint64_t a = (uint64_t)(rdi) & ~0ULL, b = (uint64_t)(rcx) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L162;
    rcx = ML_M8(rbx, 0x10);
{
    const uint64_t a = (uint64_t)(ML_M1(rcx, 0x68)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L149;
    ML_M1(rcx, 0x68) = 0x1ULL;
    ML_M1(rbx, 0x68) = 0x0ULL;
    rdx = rbx;
    rcx = rbp;
    rax = ML_CALL(141753320);
    rcx = ML_M8(rbx, 0x10);
L149:
{
    const uint64_t a = (uint64_t)(ML_M1(rcx, 0x69)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L153;
    rdi = rbx;
    goto L182;
L153:
    rax = ML_M8(rcx, 0x0);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x68)) & 0xFFULL, b = (uint64_t)(0x1ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L187;
    rax = ML_M8(rcx, 0x10);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x68)) & 0xFFULL, b = (uint64_t)(0x1ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L187;
    ML_M1(rcx, 0x68) = 0x0ULL;
    rdi = rbx;
    goto L182;
L162:
{
    const uint64_t a = (uint64_t)(ML_M1(rcx, 0x68)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L170;
    ML_M1(rcx, 0x68) = 0x1ULL;
    ML_M1(rbx, 0x68) = 0x0ULL;
    rdx = rbx;
    rcx = rbp;
    rax = ML_CALL(141753380);
    rcx = ML_M8(rbx, 0x0);
L170:
{
    const uint64_t a = (uint64_t)(ML_M1(rcx, 0x69)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L174;
    rdi = rbx;
    goto L182;
L174:
    rax = ML_M8(rcx, 0x10);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x68)) & 0xFFULL, b = (uint64_t)(0x1ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L206;
    rax = ML_M8(rcx, 0x0);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x68)) & 0xFFULL, b = (uint64_t)(0x1ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L206;
    ML_M1(rcx, 0x68) = 0x0ULL;
    rdi = rbx;
L182:
    rbx = ML_M8(rbx, 0x8);
    rax = ML_M8(rbp, 0x30);
{
    const uint64_t a = (uint64_t)(rdi) & ~0ULL, b = (uint64_t)(ML_M8(rax, 0x8)) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (f_zf) goto L224;
    goto L135;
L187:
    rax = ML_M8(rcx, 0x10);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x68)) & 0xFFULL, b = (uint64_t)(0x1ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L197;
    rax = ML_M8(rcx, 0x0);
    ML_M1(rax, 0x68) = 0x1ULL;
    ML_M1(rcx, 0x68) = 0x0ULL;
    rdx = rcx;
    rcx = rbp;
    rax = ML_CALL(141753380);
    rcx = ML_M8(rbx, 0x10);
L197:
    rax = ML_M1(rbx, 0x68);
    ML_M1(rcx, 0x68) = (uint8_t)rax;
    ML_M1(rbx, 0x68) = 0x1ULL;
    rax = ML_M8(rcx, 0x10);
    ML_M1(rax, 0x68) = 0x1ULL;
    rdx = rbx;
    rcx = rbp;
    rax = ML_CALL(141753320);
    goto L224;
L206:
    rax = ML_M8(rcx, 0x0);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x68)) & 0xFFULL, b = (uint64_t)(0x1ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L216;
    rax = ML_M8(rcx, 0x10);
    ML_M1(rax, 0x68) = 0x1ULL;
    ML_M1(rcx, 0x68) = 0x0ULL;
    rdx = rcx;
    rcx = rbp;
    rax = ML_CALL(141753320);
    rcx = ML_M8(rbx, 0x0);
L216:
    rax = ML_M1(rbx, 0x68);
    ML_M1(rcx, 0x68) = (uint8_t)rax;
    ML_M1(rbx, 0x68) = 0x1ULL;
    rax = ML_M8(rcx, 0x0);
    ML_M1(rax, 0x68) = 0x1ULL;
    rdx = rbx;
    rcx = rbp;
    rax = ML_CALL(141753380);
L224:
    ML_M1(rdi, 0x68) = 0x1ULL;
L225:
    rcx = rsi;
    rax = ML_CALL(1417f2fdc);
    rax = ML_M8(rbp, 0x38);
{
    const uint64_t r = ((uint64_t)(rax) & ~0ULL) & ((uint64_t)(rax) & ~0ULL);
    f_zf = (r == 0); f_cf = false; f_sf = ((r & 0x8000000000000000ULL) != 0);
    f_of = false;
}
    if (f_zf) goto L232;
    rax = rax - 1;
    ML_M8(rbp, 0x38) = rax;
L232:
    rcx = rsp + 0x20;
    rax = ML_M8(r12, 0x0);
    ML_M8(rcx, 0x0) = rax;
    rax = ML_M8(r12, 0x8);
    ML_M8(rcx, 0x8) = rax;
    rax = ML_M8(rsp, 0x28);
    ML_M8(rsp, 0x28) = rax;
    rax = ML_M8(rbp, 0x0);
    ML_M8(rsp, 0x20) = rax;
    rcx = rsp + 0x20;
    rax = ML_M8(rcx, 0x0);
    ML_M8(r13, 0x0) = rax;
    rax = ML_M8(rcx, 0x8);
    ML_M8(r13, 0x8) = rax;
    rax = r13;
    r11 = rsp + 0xa0;
    rbx = ML_M8(r11, 0x20);
    rbp = ML_M8(r11, 0x28);
    rsi = ML_M8(r11, 0x30);
    rsp = r11;
    { const uint64_t v = ML_M8(rsp, 0); rsp += 8; r13 = v; }
    { const uint64_t v = ML_M8(rsp, 0); rsp += 8; r12 = v; }
    { const uint64_t v = ML_M8(rsp, 0); rsp += 8; rdi = v; }
    return rax;
#undef ML_CALL
    return rax;
}

__attribute__((weak)) uint64_t (*g_fnLIFT_1417536b0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t) = nullptr;
__attribute__((weak)) uint64_t (*g_fnLIFT_141753bf0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t) = nullptr;
__attribute__((weak)) uint64_t (*g_fnLIFT_141753c50)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t) = nullptr;
uint64_t SynLift_14175a710(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A) {
    uint64_t rax = 0, rbx = 0, rbp = 0, rsi = 0, rdi = 0, r10 = 0, r11 = 0, r12 = 0, r13 = 0, r14 = 0, r15 = 0;
    uint64_t rcx = rcxA, rdx = rdxA, r8 = r8A, r9 = r9A;
    bool f_zf = false, f_cf = false, f_sf = false, f_of = false;
    uint8_t xmm0[16] = {0}, xmm1[16] = {0}, xmm2[16] = {0}, xmm3[16] = {0}, xmm4[16] = {0}, xmm5[16] = {0};
    alignas(16) uint8_t stkFrame[0x400] = {0};
    uint64_t rsp = (uint64_t)(uintptr_t)(stkFrame + 0x200);
#define ML_CALL(t) g_fnLIFT_##t(rcx, rdx, r8, r9, ML_M8(rsp, 0x20), ML_M8(rsp, 0x28))
    rax = rsp;
    rsp -= 8; ML_M8(rsp, 0) = rdi;
    rsp -= 8; ML_M8(rsp, 0) = r12;
    rsp -= 8; ML_M8(rsp, 0) = r13;
    rsp = rsp - (0xa0ULL);
    ML_M8(rsp, 0x30) = 0xfffffffffffffffeULL;
    ML_M8(rax, 0x8) = rbx;
    ML_M8(rax, 0x10) = rbp;
    ML_M8(rax, 0x18) = rsi;
    r12 = r8;
    r13 = rdx;
    rbp = rcx;
    rsi = ML_M8(r8, 0x8);
{
    const uint64_t a = (uint64_t)(ML_M1(rsi, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L30;
    rdx = (uintptr_t)0x141825ca8;
    rcx = rax - 0x40;
    rax = ML_CALL(141823270);
    rcx = rsp + 0x38;
    rax = ML_CALL(1418233f8);
    rax = (uintptr_t)0x141824a60;
    ML_M8(rsp, 0x38) = rax;
    rdx = rsp + 0x78;
    rcx = rsp + 0x50;
    rax = ML_CALL(141823288);
    rax = (uintptr_t)0x141824ba0;
    ML_M8(rsp, 0x38) = rax;
    rdx = (uintptr_t)0x141881e50;
    rcx = rsp + 0x38;
    rax = ML_CALL(1417f3154);
L30:
    rcx = r8;
    rax = ML_CALL(1417536b0);
    r11 = ML_M8(rsi, 0x0);
{
    const uint64_t a = (uint64_t)(ML_M1(r11, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L37;
    rdi = ML_M8(rsi, 0x10);
    goto L46;
L37:
    rax = ML_M8(rsi, 0x10);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L42;
    rdi = r11;
    goto L46;
L42:
    rcx = ML_M8(r12, 0x8);
    rdi = ML_M8(rcx, 0x10);
{
    const uint64_t a = (uint64_t)(rcx) & ~0ULL, b = (uint64_t)(rsi) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L93;
L46:
    rbx = ML_M8(rsi, 0x8);
{
    const uint64_t a = (uint64_t)(ML_M1(rdi, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L50;
    ML_M8(rdi, 0x8) = rbx;
L50:
    rax = ML_M8(rbp, 0x30);
{
    const uint64_t a = (uint64_t)(ML_M8(rax, 0x8)) & ~0ULL, b = (uint64_t)(rsi) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L55;
    ML_M8(rax, 0x8) = rdi;
    goto L60;
L55:
{
    const uint64_t a = (uint64_t)(ML_M8(rbx, 0x0)) & ~0ULL, b = (uint64_t)(rsi) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L59;
    ML_M8(rbx, 0x0) = rdi;
    goto L60;
L59:
    ML_M8(rbx, 0x10) = rdi;
L60:
    rdx = ML_M8(rbp, 0x30);
{
    const uint64_t a = (uint64_t)(ML_M8(rdx, 0x0)) & ~0ULL, b = (uint64_t)(rsi) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L76;
{
    const uint64_t a = (uint64_t)(ML_M1(rdi, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L67;
    rcx = rbx;
    goto L75;
L67:
    rcx = rdi;
    rax = ML_M8(rdi, 0x0);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L75;
L71:
    rcx = rax;
    rax = ML_M8(rax, 0x0);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L71;
L75:
    ML_M8(rdx, 0x0) = rcx;
L76:
    rdx = ML_M8(rbp, 0x30);
{
    const uint64_t a = (uint64_t)(ML_M8(rdx, 0x10)) & ~0ULL, b = (uint64_t)(rsi) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L130;
{
    const uint64_t a = (uint64_t)(ML_M1(rdi, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L83;
    rcx = rbx;
    goto L91;
L83:
    rcx = rdi;
    rax = ML_M8(rdi, 0x10);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L91;
L87:
    rcx = rax;
    rax = ML_M8(rax, 0x10);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L87;
L91:
    ML_M8(rdx, 0x10) = rcx;
    goto L130;
L93:
    ML_M8(r11, 0x8) = rcx;
    rax = ML_M8(rsi, 0x0);
    ML_M8(rcx, 0x0) = rax;
{
    const uint64_t a = (uint64_t)(rcx) & ~0ULL, b = (uint64_t)(ML_M8(rsi, 0x10)) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L100;
    rbx = rcx;
    goto L109;
L100:
    rbx = ML_M8(rcx, 0x8);
{
    const uint64_t a = (uint64_t)(ML_M1(rdi, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L104;
    ML_M8(rdi, 0x8) = rbx;
L104:
    ML_M8(rbx, 0x0) = rdi;
    rax = ML_M8(rsi, 0x10);
    ML_M8(rcx, 0x10) = rax;
    rax = ML_M8(rsi, 0x10);
    ML_M8(rax, 0x8) = rcx;
L109:
    rax = ML_M8(rbp, 0x30);
{
    const uint64_t a = (uint64_t)(ML_M8(rax, 0x8)) & ~0ULL, b = (uint64_t)(rsi) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L114;
    ML_M8(rax, 0x8) = rcx;
    goto L120;
L114:
    rax = ML_M8(rsi, 0x8);
{
    const uint64_t a = (uint64_t)(ML_M8(rax, 0x0)) & ~0ULL, b = (uint64_t)(rsi) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L119;
    ML_M8(rax, 0x0) = rcx;
    goto L120;
L119:
    ML_M8(rax, 0x10) = rcx;
L120:
    rax = ML_M8(rsi, 0x8);
    ML_M8(rcx, 0x8) = rax;
    rdx = rsi + 0x28;
    r8 = rcx + 0x28;
{
    const uint64_t a = (uint64_t)(r8) & ~0ULL, b = (uint64_t)(rdx) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (f_zf) goto L130;
    rcx = ML_M1(r8, 0x0);
    rax = ML_M1(rdx, 0x0);
    ML_M1(r8, 0x0) = (uint8_t)rax;
    ML_M1(rdx, 0x0) = (uint8_t)rcx;
L130:
{
    const uint64_t a = (uint64_t)(ML_M1(rsi, 0x28)) & 0xFFULL, b = (uint64_t)(0x1ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L225;
    rax = ML_M8(rbp, 0x30);
{
    const uint64_t a = (uint64_t)(rdi) & ~0ULL, b = (uint64_t)(ML_M8(rax, 0x8)) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (f_zf) goto L224;
L135:
{
    const uint64_t a = (uint64_t)(ML_M1(rdi, 0x28)) & 0xFFULL, b = (uint64_t)(0x1ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L224;
    rcx = ML_M8(rbx, 0x0);
{
    const uint64_t a = (uint64_t)(rdi) & ~0ULL, b = (uint64_t)(rcx) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L162;
    rcx = ML_M8(rbx, 0x10);
{
    const uint64_t a = (uint64_t)(ML_M1(rcx, 0x28)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L149;
    ML_M1(rcx, 0x28) = 0x1ULL;
    ML_M1(rbx, 0x28) = 0x0ULL;
    rdx = rbx;
    rcx = rbp;
    rax = ML_CALL(141753bf0);
    rcx = ML_M8(rbx, 0x10);
L149:
{
    const uint64_t a = (uint64_t)(ML_M1(rcx, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L153;
    rdi = rbx;
    goto L182;
L153:
    rax = ML_M8(rcx, 0x0);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x28)) & 0xFFULL, b = (uint64_t)(0x1ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L187;
    rax = ML_M8(rcx, 0x10);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x28)) & 0xFFULL, b = (uint64_t)(0x1ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L187;
    ML_M1(rcx, 0x28) = 0x0ULL;
    rdi = rbx;
    goto L182;
L162:
{
    const uint64_t a = (uint64_t)(ML_M1(rcx, 0x28)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L170;
    ML_M1(rcx, 0x28) = 0x1ULL;
    ML_M1(rbx, 0x28) = 0x0ULL;
    rdx = rbx;
    rcx = rbp;
    rax = ML_CALL(141753c50);
    rcx = ML_M8(rbx, 0x0);
L170:
{
    const uint64_t a = (uint64_t)(ML_M1(rcx, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L174;
    rdi = rbx;
    goto L182;
L174:
    rax = ML_M8(rcx, 0x10);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x28)) & 0xFFULL, b = (uint64_t)(0x1ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L206;
    rax = ML_M8(rcx, 0x0);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x28)) & 0xFFULL, b = (uint64_t)(0x1ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L206;
    ML_M1(rcx, 0x28) = 0x0ULL;
    rdi = rbx;
L182:
    rbx = ML_M8(rbx, 0x8);
    rax = ML_M8(rbp, 0x30);
{
    const uint64_t a = (uint64_t)(rdi) & ~0ULL, b = (uint64_t)(ML_M8(rax, 0x8)) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (f_zf) goto L224;
    goto L135;
L187:
    rax = ML_M8(rcx, 0x10);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x28)) & 0xFFULL, b = (uint64_t)(0x1ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L197;
    rax = ML_M8(rcx, 0x0);
    ML_M1(rax, 0x28) = 0x1ULL;
    ML_M1(rcx, 0x28) = 0x0ULL;
    rdx = rcx;
    rcx = rbp;
    rax = ML_CALL(141753c50);
    rcx = ML_M8(rbx, 0x10);
L197:
    rax = ML_M1(rbx, 0x28);
    ML_M1(rcx, 0x28) = (uint8_t)rax;
    ML_M1(rbx, 0x28) = 0x1ULL;
    rax = ML_M8(rcx, 0x10);
    ML_M1(rax, 0x28) = 0x1ULL;
    rdx = rbx;
    rcx = rbp;
    rax = ML_CALL(141753bf0);
    goto L224;
L206:
    rax = ML_M8(rcx, 0x0);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x28)) & 0xFFULL, b = (uint64_t)(0x1ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L216;
    rax = ML_M8(rcx, 0x10);
    ML_M1(rax, 0x28) = 0x1ULL;
    ML_M1(rcx, 0x28) = 0x0ULL;
    rdx = rcx;
    rcx = rbp;
    rax = ML_CALL(141753bf0);
    rcx = ML_M8(rbx, 0x0);
L216:
    rax = ML_M1(rbx, 0x28);
    ML_M1(rcx, 0x28) = (uint8_t)rax;
    ML_M1(rbx, 0x28) = 0x1ULL;
    rax = ML_M8(rcx, 0x0);
    ML_M1(rax, 0x28) = 0x1ULL;
    rdx = rbx;
    rcx = rbp;
    rax = ML_CALL(141753c50);
L224:
    ML_M1(rdi, 0x28) = 0x1ULL;
L225:
    rcx = rsi;
    rax = ML_CALL(1417f2fdc);
    rax = ML_M8(rbp, 0x38);
{
    const uint64_t r = ((uint64_t)(rax) & ~0ULL) & ((uint64_t)(rax) & ~0ULL);
    f_zf = (r == 0); f_cf = false; f_sf = ((r & 0x8000000000000000ULL) != 0);
    f_of = false;
}
    if (f_zf) goto L232;
    rax = rax - 1;
    ML_M8(rbp, 0x38) = rax;
L232:
    rcx = rsp + 0x20;
    rax = ML_M8(r12, 0x0);
    ML_M8(rcx, 0x0) = rax;
    rax = ML_M8(r12, 0x8);
    ML_M8(rcx, 0x8) = rax;
    rax = ML_M8(rsp, 0x28);
    ML_M8(rsp, 0x28) = rax;
    rax = ML_M8(rbp, 0x0);
    ML_M8(rsp, 0x20) = rax;
    rcx = rsp + 0x20;
    rax = ML_M8(rcx, 0x0);
    ML_M8(r13, 0x0) = rax;
    rax = ML_M8(rcx, 0x8);
    ML_M8(r13, 0x8) = rax;
    rax = r13;
    r11 = rsp + 0xa0;
    rbx = ML_M8(r11, 0x20);
    rbp = ML_M8(r11, 0x28);
    rsi = ML_M8(r11, 0x30);
    rsp = r11;
    { const uint64_t v = ML_M8(rsp, 0); rsp += 8; r13 = v; }
    { const uint64_t v = ML_M8(rsp, 0); rsp += 8; r12 = v; }
    { const uint64_t v = ML_M8(rsp, 0); rsp += 8; rdi = v; }
    return rax;
#undef ML_CALL
    return rax;
}

__attribute__((weak)) uint64_t (*g_fnLIFT_14174fe10)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t) = nullptr;
__attribute__((weak)) uint64_t (*g_fnLIFT_141750760)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t) = nullptr;
__attribute__((weak)) uint64_t (*g_fnLIFT_141752ac0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t) = nullptr;
uint64_t SynLift_1417614e0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A) {
    uint64_t rax = 0, rbx = 0, rbp = 0, rsi = 0, rdi = 0, r10 = 0, r11 = 0, r12 = 0, r13 = 0, r14 = 0, r15 = 0;
    uint64_t rcx = rcxA, rdx = rdxA, r8 = r8A, r9 = r9A;
    bool f_zf = false, f_cf = false, f_sf = false, f_of = false;
    uint8_t xmm0[16] = {0}, xmm1[16] = {0}, xmm2[16] = {0}, xmm3[16] = {0}, xmm4[16] = {0}, xmm5[16] = {0};
    alignas(16) uint8_t stkFrame[0x400] = {0};
    uint64_t rsp = (uint64_t)(uintptr_t)(stkFrame + 0x200);
#define ML_CALL(t) g_fnLIFT_##t(rcx, rdx, r8, r9, ML_M8(rsp, 0x20), ML_M8(rsp, 0x28))
    rax = rsp;
    rsp -= 8; ML_M8(rsp, 0) = rdi;
    rsp -= 8; ML_M8(rsp, 0) = r12;
    rsp -= 8; ML_M8(rsp, 0) = r13;
    rsp = rsp - (0xa0ULL);
    ML_M8(rsp, 0x30) = 0xfffffffffffffffeULL;
    ML_M8(rax, 0x8) = rbx;
    ML_M8(rax, 0x10) = rbp;
    ML_M8(rax, 0x18) = rsi;
    r12 = r8;
    r13 = rdx;
    rbp = rcx;
    rsi = ML_M8(r8, 0x8);
{
    const uint64_t a = (uint64_t)(ML_M1(rsi, 0x2d)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L30;
    rdx = (uintptr_t)0x141825ca8;
    rcx = rax - 0x40;
    rax = ML_CALL(141823270);
    rcx = rsp + 0x38;
    rax = ML_CALL(1418233f8);
    rax = (uintptr_t)0x141824a60;
    ML_M8(rsp, 0x38) = rax;
    rdx = rsp + 0x78;
    rcx = rsp + 0x50;
    rax = ML_CALL(141823288);
    rax = (uintptr_t)0x141824ba0;
    ML_M8(rsp, 0x38) = rax;
    rdx = (uintptr_t)0x141881e50;
    rcx = rsp + 0x38;
    rax = ML_CALL(1417f3154);
L30:
    rcx = r8;
    rax = ML_CALL(141750760);
    r11 = ML_M8(rsi, 0x0);
{
    const uint64_t a = (uint64_t)(ML_M1(r11, 0x2d)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L37;
    rdi = ML_M8(rsi, 0x10);
    goto L46;
L37:
    rax = ML_M8(rsi, 0x10);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x2d)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L42;
    rdi = r11;
    goto L46;
L42:
    rcx = ML_M8(r12, 0x8);
    rdi = ML_M8(rcx, 0x10);
{
    const uint64_t a = (uint64_t)(rcx) & ~0ULL, b = (uint64_t)(rsi) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L93;
L46:
    rbx = ML_M8(rsi, 0x8);
{
    const uint64_t a = (uint64_t)(ML_M1(rdi, 0x2d)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L50;
    ML_M8(rdi, 0x8) = rbx;
L50:
    rax = ML_M8(rbp, 0x30);
{
    const uint64_t a = (uint64_t)(ML_M8(rax, 0x8)) & ~0ULL, b = (uint64_t)(rsi) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L55;
    ML_M8(rax, 0x8) = rdi;
    goto L60;
L55:
{
    const uint64_t a = (uint64_t)(ML_M8(rbx, 0x0)) & ~0ULL, b = (uint64_t)(rsi) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L59;
    ML_M8(rbx, 0x0) = rdi;
    goto L60;
L59:
    ML_M8(rbx, 0x10) = rdi;
L60:
    rdx = ML_M8(rbp, 0x30);
{
    const uint64_t a = (uint64_t)(ML_M8(rdx, 0x0)) & ~0ULL, b = (uint64_t)(rsi) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L76;
{
    const uint64_t a = (uint64_t)(ML_M1(rdi, 0x2d)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L67;
    rcx = rbx;
    goto L75;
L67:
    rcx = rdi;
    rax = ML_M8(rdi, 0x0);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x2d)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L75;
L71:
    rcx = rax;
    rax = ML_M8(rax, 0x0);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x2d)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L71;
L75:
    ML_M8(rdx, 0x0) = rcx;
L76:
    rdx = ML_M8(rbp, 0x30);
{
    const uint64_t a = (uint64_t)(ML_M8(rdx, 0x10)) & ~0ULL, b = (uint64_t)(rsi) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L130;
{
    const uint64_t a = (uint64_t)(ML_M1(rdi, 0x2d)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L83;
    rcx = rbx;
    goto L91;
L83:
    rcx = rdi;
    rax = ML_M8(rdi, 0x10);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x2d)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L91;
L87:
    rcx = rax;
    rax = ML_M8(rax, 0x10);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x2d)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L87;
L91:
    ML_M8(rdx, 0x10) = rcx;
    goto L130;
L93:
    ML_M8(r11, 0x8) = rcx;
    rax = ML_M8(rsi, 0x0);
    ML_M8(rcx, 0x0) = rax;
{
    const uint64_t a = (uint64_t)(rcx) & ~0ULL, b = (uint64_t)(ML_M8(rsi, 0x10)) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L100;
    rbx = rcx;
    goto L109;
L100:
    rbx = ML_M8(rcx, 0x8);
{
    const uint64_t a = (uint64_t)(ML_M1(rdi, 0x2d)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L104;
    ML_M8(rdi, 0x8) = rbx;
L104:
    ML_M8(rbx, 0x0) = rdi;
    rax = ML_M8(rsi, 0x10);
    ML_M8(rcx, 0x10) = rax;
    rax = ML_M8(rsi, 0x10);
    ML_M8(rax, 0x8) = rcx;
L109:
    rax = ML_M8(rbp, 0x30);
{
    const uint64_t a = (uint64_t)(ML_M8(rax, 0x8)) & ~0ULL, b = (uint64_t)(rsi) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L114;
    ML_M8(rax, 0x8) = rcx;
    goto L120;
L114:
    rax = ML_M8(rsi, 0x8);
{
    const uint64_t a = (uint64_t)(ML_M8(rax, 0x0)) & ~0ULL, b = (uint64_t)(rsi) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L119;
    ML_M8(rax, 0x0) = rcx;
    goto L120;
L119:
    ML_M8(rax, 0x10) = rcx;
L120:
    rax = ML_M8(rsi, 0x8);
    ML_M8(rcx, 0x8) = rax;
    rdx = rsi + 0x2c;
    r8 = rcx + 0x2c;
{
    const uint64_t a = (uint64_t)(r8) & ~0ULL, b = (uint64_t)(rdx) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (f_zf) goto L130;
    rcx = ML_M1(r8, 0x0);
    rax = ML_M1(rdx, 0x0);
    ML_M1(r8, 0x0) = (uint8_t)rax;
    ML_M1(rdx, 0x0) = (uint8_t)rcx;
L130:
{
    const uint64_t a = (uint64_t)(ML_M1(rsi, 0x2c)) & 0xFFULL, b = (uint64_t)(0x1ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L225;
    rax = ML_M8(rbp, 0x30);
{
    const uint64_t a = (uint64_t)(rdi) & ~0ULL, b = (uint64_t)(ML_M8(rax, 0x8)) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (f_zf) goto L224;
L135:
{
    const uint64_t a = (uint64_t)(ML_M1(rdi, 0x2c)) & 0xFFULL, b = (uint64_t)(0x1ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L224;
    rcx = ML_M8(rbx, 0x0);
{
    const uint64_t a = (uint64_t)(rdi) & ~0ULL, b = (uint64_t)(rcx) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L162;
    rcx = ML_M8(rbx, 0x10);
{
    const uint64_t a = (uint64_t)(ML_M1(rcx, 0x2c)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L149;
    ML_M1(rcx, 0x2c) = 0x1ULL;
    ML_M1(rbx, 0x2c) = 0x0ULL;
    rdx = rbx;
    rcx = rbp;
    rax = ML_CALL(141752ac0);
    rcx = ML_M8(rbx, 0x10);
L149:
{
    const uint64_t a = (uint64_t)(ML_M1(rcx, 0x2d)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L153;
    rdi = rbx;
    goto L182;
L153:
    rax = ML_M8(rcx, 0x0);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x2c)) & 0xFFULL, b = (uint64_t)(0x1ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L187;
    rax = ML_M8(rcx, 0x10);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x2c)) & 0xFFULL, b = (uint64_t)(0x1ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L187;
    ML_M1(rcx, 0x2c) = 0x0ULL;
    rdi = rbx;
    goto L182;
L162:
{
    const uint64_t a = (uint64_t)(ML_M1(rcx, 0x2c)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L170;
    ML_M1(rcx, 0x2c) = 0x1ULL;
    ML_M1(rbx, 0x2c) = 0x0ULL;
    rdx = rbx;
    rcx = rbp;
    rax = ML_CALL(14174fe10);
    rcx = ML_M8(rbx, 0x0);
L170:
{
    const uint64_t a = (uint64_t)(ML_M1(rcx, 0x2d)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L174;
    rdi = rbx;
    goto L182;
L174:
    rax = ML_M8(rcx, 0x10);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x2c)) & 0xFFULL, b = (uint64_t)(0x1ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L206;
    rax = ML_M8(rcx, 0x0);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x2c)) & 0xFFULL, b = (uint64_t)(0x1ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L206;
    ML_M1(rcx, 0x2c) = 0x0ULL;
    rdi = rbx;
L182:
    rbx = ML_M8(rbx, 0x8);
    rax = ML_M8(rbp, 0x30);
{
    const uint64_t a = (uint64_t)(rdi) & ~0ULL, b = (uint64_t)(ML_M8(rax, 0x8)) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (f_zf) goto L224;
    goto L135;
L187:
    rax = ML_M8(rcx, 0x10);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x2c)) & 0xFFULL, b = (uint64_t)(0x1ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L197;
    rax = ML_M8(rcx, 0x0);
    ML_M1(rax, 0x2c) = 0x1ULL;
    ML_M1(rcx, 0x2c) = 0x0ULL;
    rdx = rcx;
    rcx = rbp;
    rax = ML_CALL(14174fe10);
    rcx = ML_M8(rbx, 0x10);
L197:
    rax = ML_M1(rbx, 0x2c);
    ML_M1(rcx, 0x2c) = (uint8_t)rax;
    ML_M1(rbx, 0x2c) = 0x1ULL;
    rax = ML_M8(rcx, 0x10);
    ML_M1(rax, 0x2c) = 0x1ULL;
    rdx = rbx;
    rcx = rbp;
    rax = ML_CALL(141752ac0);
    goto L224;
L206:
    rax = ML_M8(rcx, 0x0);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x2c)) & 0xFFULL, b = (uint64_t)(0x1ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L216;
    rax = ML_M8(rcx, 0x10);
    ML_M1(rax, 0x2c) = 0x1ULL;
    ML_M1(rcx, 0x2c) = 0x0ULL;
    rdx = rcx;
    rcx = rbp;
    rax = ML_CALL(141752ac0);
    rcx = ML_M8(rbx, 0x0);
L216:
    rax = ML_M1(rbx, 0x2c);
    ML_M1(rcx, 0x2c) = (uint8_t)rax;
    ML_M1(rbx, 0x2c) = 0x1ULL;
    rax = ML_M8(rcx, 0x0);
    ML_M1(rax, 0x2c) = 0x1ULL;
    rdx = rbx;
    rcx = rbp;
    rax = ML_CALL(14174fe10);
L224:
    ML_M1(rdi, 0x2c) = 0x1ULL;
L225:
    rcx = rsi;
    rax = ML_CALL(1417f2fdc);
    rax = ML_M8(rbp, 0x38);
{
    const uint64_t r = ((uint64_t)(rax) & ~0ULL) & ((uint64_t)(rax) & ~0ULL);
    f_zf = (r == 0); f_cf = false; f_sf = ((r & 0x8000000000000000ULL) != 0);
    f_of = false;
}
    if (f_zf) goto L232;
    rax = rax - 1;
    ML_M8(rbp, 0x38) = rax;
L232:
    rcx = rsp + 0x20;
    rax = ML_M8(r12, 0x0);
    ML_M8(rcx, 0x0) = rax;
    rax = ML_M8(r12, 0x8);
    ML_M8(rcx, 0x8) = rax;
    rax = ML_M8(rsp, 0x28);
    ML_M8(rsp, 0x28) = rax;
    rax = ML_M8(rbp, 0x0);
    ML_M8(rsp, 0x20) = rax;
    rcx = rsp + 0x20;
    rax = ML_M8(rcx, 0x0);
    ML_M8(r13, 0x0) = rax;
    rax = ML_M8(rcx, 0x8);
    ML_M8(r13, 0x8) = rax;
    rax = r13;
    r11 = rsp + 0xa0;
    rbx = ML_M8(r11, 0x20);
    rbp = ML_M8(r11, 0x28);
    rsi = ML_M8(r11, 0x30);
    rsp = r11;
    { const uint64_t v = ML_M8(rsp, 0); rsp += 8; r13 = v; }
    { const uint64_t v = ML_M8(rsp, 0); rsp += 8; r12 = v; }
    { const uint64_t v = ML_M8(rsp, 0); rsp += 8; rdi = v; }
    return rax;
#undef ML_CALL
    return rax;
}

uint64_t SynLift_141776070(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A) {
    uint64_t rax = 0, rbx = 0, rbp = 0, rsi = 0, rdi = 0, r10 = 0, r11 = 0, r12 = 0, r13 = 0, r14 = 0, r15 = 0;
    uint64_t rcx = rcxA, rdx = rdxA, r8 = r8A, r9 = r9A;
    bool f_zf = false, f_cf = false, f_sf = false, f_of = false;
    uint8_t xmm0[16] = {0}, xmm1[16] = {0}, xmm2[16] = {0}, xmm3[16] = {0}, xmm4[16] = {0}, xmm5[16] = {0};
    alignas(16) uint8_t stkFrame[0x400] = {0};
    uint64_t rsp = (uint64_t)(uintptr_t)(stkFrame + 0x200);
#define ML_CALL(t) g_fnLIFT_##t(rcx, rdx, r8, r9, ML_M8(rsp, 0x20), ML_M8(rsp, 0x28))
    r8 = ML_M8(rdx, 0x0);
    rax = ML_M8(r8, 0x10);
    ML_M8(rdx, 0x0) = rax;
    rax = ML_M8(r8, 0x10);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x39)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L7;
    ML_M8(rax, 0x8) = rdx;
L7:
    rax = ML_M8(rdx, 0x8);
    ML_M8(r8, 0x8) = rax;
    rax = ML_M8(rcx, 0x30);
{
    const uint64_t a = (uint64_t)(rdx) & ~0ULL, b = (uint64_t)(ML_M8(rax, 0x8)) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L16;
    ML_M8(rax, 0x8) = r8;
    ML_M8(r8, 0x10) = rdx;
    ML_M8(rdx, 0x8) = r8;
    return rax;
L16:
    rax = ML_M8(rdx, 0x8);
{
    const uint64_t a = (uint64_t)(rdx) & ~0ULL, b = (uint64_t)(ML_M8(rax, 0x10)) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L23;
    ML_M8(rax, 0x10) = r8;
    ML_M8(r8, 0x10) = rdx;
    ML_M8(rdx, 0x8) = r8;
    return rax;
L23:
    ML_M8(rax, 0x0) = r8;
    ML_M8(r8, 0x10) = rdx;
    ML_M8(rdx, 0x8) = r8;
    return rax;
#undef ML_CALL
    return rax;
}

uint64_t SynLift_141776360(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A) {
    uint64_t rax = 0, rbx = 0, rbp = 0, rsi = 0, rdi = 0, r10 = 0, r11 = 0, r12 = 0, r13 = 0, r14 = 0, r15 = 0;
    uint64_t rcx = rcxA, rdx = rdxA, r8 = r8A, r9 = r9A;
    bool f_zf = false, f_cf = false, f_sf = false, f_of = false;
    uint8_t xmm0[16] = {0}, xmm1[16] = {0}, xmm2[16] = {0}, xmm3[16] = {0}, xmm4[16] = {0}, xmm5[16] = {0};
    alignas(16) uint8_t stkFrame[0x400] = {0};
    uint64_t rsp = (uint64_t)(uintptr_t)(stkFrame + 0x200);
#define ML_CALL(t) g_fnLIFT_##t(rcx, rdx, r8, r9, ML_M8(rsp, 0x20), ML_M8(rsp, 0x28))
    r8 = ML_M8(rdx, 0x10);
    rax = ML_M8(r8, 0x0);
    ML_M8(rdx, 0x10) = rax;
    rax = ML_M8(r8, 0x0);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x39)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L7;
    ML_M8(rax, 0x8) = rdx;
L7:
    rax = ML_M8(rdx, 0x8);
    ML_M8(r8, 0x8) = rax;
    rax = ML_M8(rcx, 0x30);
{
    const uint64_t a = (uint64_t)(rdx) & ~0ULL, b = (uint64_t)(ML_M8(rax, 0x8)) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L16;
    ML_M8(rax, 0x8) = r8;
    ML_M8(r8, 0x0) = rdx;
    ML_M8(rdx, 0x8) = r8;
    return rax;
L16:
    rax = ML_M8(rdx, 0x8);
{
    const uint64_t a = (uint64_t)(rdx) & ~0ULL, b = (uint64_t)(ML_M8(rax, 0x0)) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L23;
    ML_M8(rax, 0x0) = r8;
    ML_M8(r8, 0x0) = rdx;
    ML_M8(rdx, 0x8) = r8;
    return rax;
L23:
    ML_M8(rax, 0x10) = r8;
    ML_M8(r8, 0x0) = rdx;
    ML_M8(rdx, 0x8) = r8;
    return rax;
#undef ML_CALL
    return rax;
}

uint64_t SynLift_141776460(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A) {
    uint64_t rax = 0, rbx = 0, rbp = 0, rsi = 0, rdi = 0, r10 = 0, r11 = 0, r12 = 0, r13 = 0, r14 = 0, r15 = 0;
    uint64_t rcx = rcxA, rdx = rdxA, r8 = r8A, r9 = r9A;
    bool f_zf = false, f_cf = false, f_sf = false, f_of = false;
    uint8_t xmm0[16] = {0}, xmm1[16] = {0}, xmm2[16] = {0}, xmm3[16] = {0}, xmm4[16] = {0}, xmm5[16] = {0};
    alignas(16) uint8_t stkFrame[0x400] = {0};
    uint64_t rsp = (uint64_t)(uintptr_t)(stkFrame + 0x200);
#define ML_CALL(t) g_fnLIFT_##t(rcx, rdx, r8, r9, ML_M8(rsp, 0x20), ML_M8(rsp, 0x28))
    rsp -= 8; ML_M8(rsp, 0) = rbx;
    rsp = rsp - (0x20ULL);
{
    const uint64_t a = (uint64_t)(ML_M8(rcx, 0x0)) & ~0ULL, b = (uint64_t)(0x0ULL) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    rbx = rcx;
    if (!f_zf) goto L6;
    rax = ML_CALL(1418233c0);
L6:
    rcx = ML_M8(rbx, 0x8);
{
    const uint64_t a = (uint64_t)(ML_M1(rcx, 0x39)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L12;
    rsp = rsp + (0x20ULL);
    { const uint64_t v = ML_M8(rsp, 0); rsp += 8; rbx = v; }
    return ML_CALL(1418233c0);   // tail call
L12:
    rax = ML_M8(rcx, 0x10);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x39)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L27;
    rcx = ML_M8(rax, 0x0);
{
    const uint64_t a = (uint64_t)(ML_M1(rcx, 0x39)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L23;
    ;
L19:
    rax = rcx;
    rcx = ML_M8(rcx, 0x0);
{
    const uint64_t a = (uint64_t)(ML_M1(rcx, 0x39)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L19;
L23:
    ML_M8(rbx, 0x8) = rax;
    rsp = rsp + (0x20ULL);
    { const uint64_t v = ML_M8(rsp, 0); rsp += 8; rbx = v; }
    return rax;
L27:
    rcx = ML_M8(rcx, 0x8);
{
    const uint64_t a = (uint64_t)(ML_M1(rcx, 0x39)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L37;
L30:
    rax = ML_M8(rcx, 0x10);
{
    const uint64_t a = (uint64_t)(ML_M8(rbx, 0x8)) & ~0ULL, b = (uint64_t)(rax) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L37;
    ML_M8(rbx, 0x8) = rcx;
    rcx = ML_M8(rcx, 0x8);
{
    const uint64_t a = (uint64_t)(ML_M1(rcx, 0x39)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L30;
L37:
    ML_M8(rbx, 0x8) = rcx;
    rsp = rsp + (0x20ULL);
    { const uint64_t v = ML_M8(rsp, 0); rsp += 8; rbx = v; }
    return rax;
#undef ML_CALL
    return rax;
}

__attribute__((weak)) uint64_t (*g_fnLIFT_141776070)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t) = nullptr;
__attribute__((weak)) uint64_t (*g_fnLIFT_141776360)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t) = nullptr;
__attribute__((weak)) uint64_t (*g_fnLIFT_141776460)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t) = nullptr;
uint64_t SynLift_141776c90(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A) {
    uint64_t rax = 0, rbx = 0, rbp = 0, rsi = 0, rdi = 0, r10 = 0, r11 = 0, r12 = 0, r13 = 0, r14 = 0, r15 = 0;
    uint64_t rcx = rcxA, rdx = rdxA, r8 = r8A, r9 = r9A;
    bool f_zf = false, f_cf = false, f_sf = false, f_of = false;
    uint8_t xmm0[16] = {0}, xmm1[16] = {0}, xmm2[16] = {0}, xmm3[16] = {0}, xmm4[16] = {0}, xmm5[16] = {0};
    alignas(16) uint8_t stkFrame[0x400] = {0};
    uint64_t rsp = (uint64_t)(uintptr_t)(stkFrame + 0x200);
#define ML_CALL(t) g_fnLIFT_##t(rcx, rdx, r8, r9, ML_M8(rsp, 0x20), ML_M8(rsp, 0x28))
    rax = rsp;
    rsp -= 8; ML_M8(rsp, 0) = rdi;
    rsp -= 8; ML_M8(rsp, 0) = r12;
    rsp -= 8; ML_M8(rsp, 0) = r13;
    rsp = rsp - (0xa0ULL);
    ML_M8(rsp, 0x30) = 0xfffffffffffffffeULL;
    ML_M8(rax, 0x8) = rbx;
    ML_M8(rax, 0x10) = rbp;
    ML_M8(rax, 0x18) = rsi;
    r12 = r8;
    r13 = rdx;
    rbp = rcx;
    rsi = ML_M8(r8, 0x8);
{
    const uint64_t a = (uint64_t)(ML_M1(rsi, 0x39)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L30;
    rdx = (uintptr_t)0x141825ca8;
    rcx = rax - 0x40;
    rax = ML_CALL(141823270);
    rcx = rsp + 0x38;
    rax = ML_CALL(1418233f8);
    rax = (uintptr_t)0x141824a60;
    ML_M8(rsp, 0x38) = rax;
    rdx = rsp + 0x78;
    rcx = rsp + 0x50;
    rax = ML_CALL(141823288);
    rax = (uintptr_t)0x141824ba0;
    ML_M8(rsp, 0x38) = rax;
    rdx = (uintptr_t)0x141881e50;
    rcx = rsp + 0x38;
    rax = ML_CALL(1417f3154);
L30:
    rcx = r8;
    rax = ML_CALL(141776460);
    r11 = ML_M8(rsi, 0x0);
{
    const uint64_t a = (uint64_t)(ML_M1(r11, 0x39)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L37;
    rdi = ML_M8(rsi, 0x10);
    goto L46;
L37:
    rax = ML_M8(rsi, 0x10);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x39)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L42;
    rdi = r11;
    goto L46;
L42:
    rcx = ML_M8(r12, 0x8);
    rdi = ML_M8(rcx, 0x10);
{
    const uint64_t a = (uint64_t)(rcx) & ~0ULL, b = (uint64_t)(rsi) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L93;
L46:
    rbx = ML_M8(rsi, 0x8);
{
    const uint64_t a = (uint64_t)(ML_M1(rdi, 0x39)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L50;
    ML_M8(rdi, 0x8) = rbx;
L50:
    rax = ML_M8(rbp, 0x30);
{
    const uint64_t a = (uint64_t)(ML_M8(rax, 0x8)) & ~0ULL, b = (uint64_t)(rsi) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L55;
    ML_M8(rax, 0x8) = rdi;
    goto L60;
L55:
{
    const uint64_t a = (uint64_t)(ML_M8(rbx, 0x0)) & ~0ULL, b = (uint64_t)(rsi) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L59;
    ML_M8(rbx, 0x0) = rdi;
    goto L60;
L59:
    ML_M8(rbx, 0x10) = rdi;
L60:
    rdx = ML_M8(rbp, 0x30);
{
    const uint64_t a = (uint64_t)(ML_M8(rdx, 0x0)) & ~0ULL, b = (uint64_t)(rsi) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L76;
{
    const uint64_t a = (uint64_t)(ML_M1(rdi, 0x39)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L67;
    rcx = rbx;
    goto L75;
L67:
    rcx = rdi;
    rax = ML_M8(rdi, 0x0);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x39)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L75;
L71:
    rcx = rax;
    rax = ML_M8(rax, 0x0);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x39)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L71;
L75:
    ML_M8(rdx, 0x0) = rcx;
L76:
    rdx = ML_M8(rbp, 0x30);
{
    const uint64_t a = (uint64_t)(ML_M8(rdx, 0x10)) & ~0ULL, b = (uint64_t)(rsi) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L130;
{
    const uint64_t a = (uint64_t)(ML_M1(rdi, 0x39)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L83;
    rcx = rbx;
    goto L91;
L83:
    rcx = rdi;
    rax = ML_M8(rdi, 0x10);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x39)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L91;
L87:
    rcx = rax;
    rax = ML_M8(rax, 0x10);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x39)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L87;
L91:
    ML_M8(rdx, 0x10) = rcx;
    goto L130;
L93:
    ML_M8(r11, 0x8) = rcx;
    rax = ML_M8(rsi, 0x0);
    ML_M8(rcx, 0x0) = rax;
{
    const uint64_t a = (uint64_t)(rcx) & ~0ULL, b = (uint64_t)(ML_M8(rsi, 0x10)) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L100;
    rbx = rcx;
    goto L109;
L100:
    rbx = ML_M8(rcx, 0x8);
{
    const uint64_t a = (uint64_t)(ML_M1(rdi, 0x39)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L104;
    ML_M8(rdi, 0x8) = rbx;
L104:
    ML_M8(rbx, 0x0) = rdi;
    rax = ML_M8(rsi, 0x10);
    ML_M8(rcx, 0x10) = rax;
    rax = ML_M8(rsi, 0x10);
    ML_M8(rax, 0x8) = rcx;
L109:
    rax = ML_M8(rbp, 0x30);
{
    const uint64_t a = (uint64_t)(ML_M8(rax, 0x8)) & ~0ULL, b = (uint64_t)(rsi) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L114;
    ML_M8(rax, 0x8) = rcx;
    goto L120;
L114:
    rax = ML_M8(rsi, 0x8);
{
    const uint64_t a = (uint64_t)(ML_M8(rax, 0x0)) & ~0ULL, b = (uint64_t)(rsi) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L119;
    ML_M8(rax, 0x0) = rcx;
    goto L120;
L119:
    ML_M8(rax, 0x10) = rcx;
L120:
    rax = ML_M8(rsi, 0x8);
    ML_M8(rcx, 0x8) = rax;
    rdx = rsi + 0x38;
    r8 = rcx + 0x38;
{
    const uint64_t a = (uint64_t)(r8) & ~0ULL, b = (uint64_t)(rdx) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (f_zf) goto L130;
    rcx = ML_M1(r8, 0x0);
    rax = ML_M1(rdx, 0x0);
    ML_M1(r8, 0x0) = (uint8_t)rax;
    ML_M1(rdx, 0x0) = (uint8_t)rcx;
L130:
{
    const uint64_t a = (uint64_t)(ML_M1(rsi, 0x38)) & 0xFFULL, b = (uint64_t)(0x1ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L225;
    rax = ML_M8(rbp, 0x30);
{
    const uint64_t a = (uint64_t)(rdi) & ~0ULL, b = (uint64_t)(ML_M8(rax, 0x8)) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (f_zf) goto L224;
L135:
{
    const uint64_t a = (uint64_t)(ML_M1(rdi, 0x38)) & 0xFFULL, b = (uint64_t)(0x1ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L224;
    rcx = ML_M8(rbx, 0x0);
{
    const uint64_t a = (uint64_t)(rdi) & ~0ULL, b = (uint64_t)(rcx) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L162;
    rcx = ML_M8(rbx, 0x10);
{
    const uint64_t a = (uint64_t)(ML_M1(rcx, 0x38)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L149;
    ML_M1(rcx, 0x38) = 0x1ULL;
    ML_M1(rbx, 0x38) = 0x0ULL;
    rdx = rbx;
    rcx = rbp;
    rax = ML_CALL(141776360);
    rcx = ML_M8(rbx, 0x10);
L149:
{
    const uint64_t a = (uint64_t)(ML_M1(rcx, 0x39)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L153;
    rdi = rbx;
    goto L182;
L153:
    rax = ML_M8(rcx, 0x0);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x38)) & 0xFFULL, b = (uint64_t)(0x1ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L187;
    rax = ML_M8(rcx, 0x10);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x38)) & 0xFFULL, b = (uint64_t)(0x1ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L187;
    ML_M1(rcx, 0x38) = 0x0ULL;
    rdi = rbx;
    goto L182;
L162:
{
    const uint64_t a = (uint64_t)(ML_M1(rcx, 0x38)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L170;
    ML_M1(rcx, 0x38) = 0x1ULL;
    ML_M1(rbx, 0x38) = 0x0ULL;
    rdx = rbx;
    rcx = rbp;
    rax = ML_CALL(141776070);
    rcx = ML_M8(rbx, 0x0);
L170:
{
    const uint64_t a = (uint64_t)(ML_M1(rcx, 0x39)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L174;
    rdi = rbx;
    goto L182;
L174:
    rax = ML_M8(rcx, 0x10);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x38)) & 0xFFULL, b = (uint64_t)(0x1ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L206;
    rax = ML_M8(rcx, 0x0);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x38)) & 0xFFULL, b = (uint64_t)(0x1ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L206;
    ML_M1(rcx, 0x38) = 0x0ULL;
    rdi = rbx;
L182:
    rbx = ML_M8(rbx, 0x8);
    rax = ML_M8(rbp, 0x30);
{
    const uint64_t a = (uint64_t)(rdi) & ~0ULL, b = (uint64_t)(ML_M8(rax, 0x8)) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (f_zf) goto L224;
    goto L135;
L187:
    rax = ML_M8(rcx, 0x10);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x38)) & 0xFFULL, b = (uint64_t)(0x1ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L197;
    rax = ML_M8(rcx, 0x0);
    ML_M1(rax, 0x38) = 0x1ULL;
    ML_M1(rcx, 0x38) = 0x0ULL;
    rdx = rcx;
    rcx = rbp;
    rax = ML_CALL(141776070);
    rcx = ML_M8(rbx, 0x10);
L197:
    rax = ML_M1(rbx, 0x38);
    ML_M1(rcx, 0x38) = (uint8_t)rax;
    ML_M1(rbx, 0x38) = 0x1ULL;
    rax = ML_M8(rcx, 0x10);
    ML_M1(rax, 0x38) = 0x1ULL;
    rdx = rbx;
    rcx = rbp;
    rax = ML_CALL(141776360);
    goto L224;
L206:
    rax = ML_M8(rcx, 0x0);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x38)) & 0xFFULL, b = (uint64_t)(0x1ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L216;
    rax = ML_M8(rcx, 0x10);
    ML_M1(rax, 0x38) = 0x1ULL;
    ML_M1(rcx, 0x38) = 0x0ULL;
    rdx = rcx;
    rcx = rbp;
    rax = ML_CALL(141776360);
    rcx = ML_M8(rbx, 0x0);
L216:
    rax = ML_M1(rbx, 0x38);
    ML_M1(rcx, 0x38) = (uint8_t)rax;
    ML_M1(rbx, 0x38) = 0x1ULL;
    rax = ML_M8(rcx, 0x0);
    ML_M1(rax, 0x38) = 0x1ULL;
    rdx = rbx;
    rcx = rbp;
    rax = ML_CALL(141776070);
L224:
    ML_M1(rdi, 0x38) = 0x1ULL;
L225:
    rcx = rsi;
    rax = ML_CALL(1417f2fdc);
    rax = ML_M8(rbp, 0x38);
{
    const uint64_t r = ((uint64_t)(rax) & ~0ULL) & ((uint64_t)(rax) & ~0ULL);
    f_zf = (r == 0); f_cf = false; f_sf = ((r & 0x8000000000000000ULL) != 0);
    f_of = false;
}
    if (f_zf) goto L232;
    rax = rax - 1;
    ML_M8(rbp, 0x38) = rax;
L232:
    rcx = rsp + 0x20;
    rax = ML_M8(r12, 0x0);
    ML_M8(rcx, 0x0) = rax;
    rax = ML_M8(r12, 0x8);
    ML_M8(rcx, 0x8) = rax;
    rax = ML_M8(rsp, 0x28);
    ML_M8(rsp, 0x28) = rax;
    rax = ML_M8(rbp, 0x0);
    ML_M8(rsp, 0x20) = rax;
    rcx = rsp + 0x20;
    rax = ML_M8(rcx, 0x0);
    ML_M8(r13, 0x0) = rax;
    rax = ML_M8(rcx, 0x8);
    ML_M8(r13, 0x8) = rax;
    rax = r13;
    r11 = rsp + 0xa0;
    rbx = ML_M8(r11, 0x20);
    rbp = ML_M8(r11, 0x28);
    rsi = ML_M8(r11, 0x30);
    rsp = r11;
    { const uint64_t v = ML_M8(rsp, 0); rsp += 8; r13 = v; }
    { const uint64_t v = ML_M8(rsp, 0); rsp += 8; r12 = v; }
    { const uint64_t v = ML_M8(rsp, 0); rsp += 8; rdi = v; }
    return rax;
#undef ML_CALL
    return rax;
}

uint64_t SynLift_14177a460(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A) {
    uint64_t rax = 0, rbx = 0, rbp = 0, rsi = 0, rdi = 0, r10 = 0, r11 = 0, r12 = 0, r13 = 0, r14 = 0, r15 = 0;
    uint64_t rcx = rcxA, rdx = rdxA, r8 = r8A, r9 = r9A;
    bool f_zf = false, f_cf = false, f_sf = false, f_of = false;
    uint8_t xmm0[16] = {0}, xmm1[16] = {0}, xmm2[16] = {0}, xmm3[16] = {0}, xmm4[16] = {0}, xmm5[16] = {0};
    alignas(16) uint8_t stkFrame[0x400] = {0};
    uint64_t rsp = (uint64_t)(uintptr_t)(stkFrame + 0x200);
#define ML_CALL(t) g_fnLIFT_##t(rcx, rdx, r8, r9, ML_M8(rsp, 0x20), ML_M8(rsp, 0x28))
    r8 = ML_M8(rdx, 0x0);
    rax = ML_M8(r8, 0x10);
    ML_M8(rdx, 0x0) = rax;
    rax = ML_M8(r8, 0x10);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L7;
    ML_M8(rax, 0x8) = rdx;
L7:
    rax = ML_M8(rdx, 0x8);
    ML_M8(r8, 0x8) = rax;
    rax = ML_M8(rcx, 0x30);
{
    const uint64_t a = (uint64_t)(rdx) & ~0ULL, b = (uint64_t)(ML_M8(rax, 0x8)) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L16;
    ML_M8(rax, 0x8) = r8;
    ML_M8(r8, 0x10) = rdx;
    ML_M8(rdx, 0x8) = r8;
    return rax;
L16:
    rax = ML_M8(rdx, 0x8);
{
    const uint64_t a = (uint64_t)(rdx) & ~0ULL, b = (uint64_t)(ML_M8(rax, 0x10)) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L23;
    ML_M8(rax, 0x10) = r8;
    ML_M8(r8, 0x10) = rdx;
    ML_M8(rdx, 0x8) = r8;
    return rax;
L23:
    ML_M8(rax, 0x0) = r8;
    ML_M8(r8, 0x10) = rdx;
    ML_M8(rdx, 0x8) = r8;
    return rax;
#undef ML_CALL
    return rax;
}

uint64_t SynLift_14177a5c0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A) {
    uint64_t rax = 0, rbx = 0, rbp = 0, rsi = 0, rdi = 0, r10 = 0, r11 = 0, r12 = 0, r13 = 0, r14 = 0, r15 = 0;
    uint64_t rcx = rcxA, rdx = rdxA, r8 = r8A, r9 = r9A;
    bool f_zf = false, f_cf = false, f_sf = false, f_of = false;
    uint8_t xmm0[16] = {0}, xmm1[16] = {0}, xmm2[16] = {0}, xmm3[16] = {0}, xmm4[16] = {0}, xmm5[16] = {0};
    alignas(16) uint8_t stkFrame[0x400] = {0};
    uint64_t rsp = (uint64_t)(uintptr_t)(stkFrame + 0x200);
#define ML_CALL(t) g_fnLIFT_##t(rcx, rdx, r8, r9, ML_M8(rsp, 0x20), ML_M8(rsp, 0x28))
    rsp -= 8; ML_M8(rsp, 0) = rbx;
    rsp = rsp - (0x20ULL);
{
    const uint64_t a = (uint64_t)(ML_M8(rcx, 0x0)) & ~0ULL, b = (uint64_t)(0x0ULL) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    rbx = rcx;
    if (!f_zf) goto L6;
    rax = ML_CALL(1418233c0);
L6:
    rcx = ML_M8(rbx, 0x8);
{
    const uint64_t a = (uint64_t)(ML_M1(rcx, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L12;
    rsp = rsp + (0x20ULL);
    { const uint64_t v = ML_M8(rsp, 0); rsp += 8; rbx = v; }
    return ML_CALL(1418233c0);   // tail call
L12:
    rax = ML_M8(rcx, 0x10);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L27;
    rcx = ML_M8(rax, 0x0);
{
    const uint64_t a = (uint64_t)(ML_M1(rcx, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L23;
    ;
L19:
    rax = rcx;
    rcx = ML_M8(rcx, 0x0);
{
    const uint64_t a = (uint64_t)(ML_M1(rcx, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L19;
L23:
    ML_M8(rbx, 0x8) = rax;
    rsp = rsp + (0x20ULL);
    { const uint64_t v = ML_M8(rsp, 0); rsp += 8; rbx = v; }
    return rax;
L27:
    rcx = ML_M8(rcx, 0x8);
{
    const uint64_t a = (uint64_t)(ML_M1(rcx, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L37;
L30:
    rax = ML_M8(rcx, 0x10);
{
    const uint64_t a = (uint64_t)(ML_M8(rbx, 0x8)) & ~0ULL, b = (uint64_t)(rax) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L37;
    ML_M8(rbx, 0x8) = rcx;
    rcx = ML_M8(rcx, 0x8);
{
    const uint64_t a = (uint64_t)(ML_M1(rcx, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L30;
L37:
    ML_M8(rbx, 0x8) = rcx;
    rsp = rsp + (0x20ULL);
    { const uint64_t v = ML_M8(rsp, 0); rsp += 8; rbx = v; }
    return rax;
#undef ML_CALL
    return rax;
}

uint64_t SynLift_14177a860(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A) {
    uint64_t rax = 0, rbx = 0, rbp = 0, rsi = 0, rdi = 0, r10 = 0, r11 = 0, r12 = 0, r13 = 0, r14 = 0, r15 = 0;
    uint64_t rcx = rcxA, rdx = rdxA, r8 = r8A, r9 = r9A;
    bool f_zf = false, f_cf = false, f_sf = false, f_of = false;
    uint8_t xmm0[16] = {0}, xmm1[16] = {0}, xmm2[16] = {0}, xmm3[16] = {0}, xmm4[16] = {0}, xmm5[16] = {0};
    alignas(16) uint8_t stkFrame[0x400] = {0};
    uint64_t rsp = (uint64_t)(uintptr_t)(stkFrame + 0x200);
#define ML_CALL(t) g_fnLIFT_##t(rcx, rdx, r8, r9, ML_M8(rsp, 0x20), ML_M8(rsp, 0x28))
    r8 = ML_M8(rdx, 0x10);
    rax = ML_M8(r8, 0x0);
    ML_M8(rdx, 0x10) = rax;
    rax = ML_M8(r8, 0x0);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L7;
    ML_M8(rax, 0x8) = rdx;
L7:
    rax = ML_M8(rdx, 0x8);
    ML_M8(r8, 0x8) = rax;
    rax = ML_M8(rcx, 0x30);
{
    const uint64_t a = (uint64_t)(rdx) & ~0ULL, b = (uint64_t)(ML_M8(rax, 0x8)) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L16;
    ML_M8(rax, 0x8) = r8;
    ML_M8(r8, 0x0) = rdx;
    ML_M8(rdx, 0x8) = r8;
    return rax;
L16:
    rax = ML_M8(rdx, 0x8);
{
    const uint64_t a = (uint64_t)(rdx) & ~0ULL, b = (uint64_t)(ML_M8(rax, 0x0)) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L23;
    ML_M8(rax, 0x0) = r8;
    ML_M8(r8, 0x0) = rdx;
    ML_M8(rdx, 0x8) = r8;
    return rax;
L23:
    ML_M8(rax, 0x10) = r8;
    ML_M8(r8, 0x0) = rdx;
    ML_M8(rdx, 0x8) = r8;
    return rax;
#undef ML_CALL
    return rax;
}

__attribute__((weak)) uint64_t (*g_fnLIFT_14177a460)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t) = nullptr;
__attribute__((weak)) uint64_t (*g_fnLIFT_14177a5c0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t) = nullptr;
__attribute__((weak)) uint64_t (*g_fnLIFT_14177a860)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t) = nullptr;
uint64_t SynLift_14177b800(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A) {
    uint64_t rax = 0, rbx = 0, rbp = 0, rsi = 0, rdi = 0, r10 = 0, r11 = 0, r12 = 0, r13 = 0, r14 = 0, r15 = 0;
    uint64_t rcx = rcxA, rdx = rdxA, r8 = r8A, r9 = r9A;
    bool f_zf = false, f_cf = false, f_sf = false, f_of = false;
    uint8_t xmm0[16] = {0}, xmm1[16] = {0}, xmm2[16] = {0}, xmm3[16] = {0}, xmm4[16] = {0}, xmm5[16] = {0};
    alignas(16) uint8_t stkFrame[0x400] = {0};
    uint64_t rsp = (uint64_t)(uintptr_t)(stkFrame + 0x200);
#define ML_CALL(t) g_fnLIFT_##t(rcx, rdx, r8, r9, ML_M8(rsp, 0x20), ML_M8(rsp, 0x28))
    rax = rsp;
    rsp -= 8; ML_M8(rsp, 0) = rdi;
    rsp -= 8; ML_M8(rsp, 0) = r12;
    rsp -= 8; ML_M8(rsp, 0) = r13;
    rsp = rsp - (0xa0ULL);
    ML_M8(rsp, 0x30) = 0xfffffffffffffffeULL;
    ML_M8(rax, 0x8) = rbx;
    ML_M8(rax, 0x10) = rbp;
    ML_M8(rax, 0x18) = rsi;
    r12 = r8;
    r13 = rdx;
    rbp = rcx;
    rsi = ML_M8(r8, 0x8);
{
    const uint64_t a = (uint64_t)(ML_M1(rsi, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L30;
    rdx = (uintptr_t)0x141825ca8;
    rcx = rax - 0x40;
    rax = ML_CALL(141823270);
    rcx = rsp + 0x38;
    rax = ML_CALL(1418233f8);
    rax = (uintptr_t)0x141824a60;
    ML_M8(rsp, 0x38) = rax;
    rdx = rsp + 0x78;
    rcx = rsp + 0x50;
    rax = ML_CALL(141823288);
    rax = (uintptr_t)0x141824ba0;
    ML_M8(rsp, 0x38) = rax;
    rdx = (uintptr_t)0x141881e50;
    rcx = rsp + 0x38;
    rax = ML_CALL(1417f3154);
L30:
    rcx = r8;
    rax = ML_CALL(14177a5c0);
    r11 = ML_M8(rsi, 0x0);
{
    const uint64_t a = (uint64_t)(ML_M1(r11, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L37;
    rdi = ML_M8(rsi, 0x10);
    goto L46;
L37:
    rax = ML_M8(rsi, 0x10);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L42;
    rdi = r11;
    goto L46;
L42:
    rcx = ML_M8(r12, 0x8);
    rdi = ML_M8(rcx, 0x10);
{
    const uint64_t a = (uint64_t)(rcx) & ~0ULL, b = (uint64_t)(rsi) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L93;
L46:
    rbx = ML_M8(rsi, 0x8);
{
    const uint64_t a = (uint64_t)(ML_M1(rdi, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L50;
    ML_M8(rdi, 0x8) = rbx;
L50:
    rax = ML_M8(rbp, 0x30);
{
    const uint64_t a = (uint64_t)(ML_M8(rax, 0x8)) & ~0ULL, b = (uint64_t)(rsi) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L55;
    ML_M8(rax, 0x8) = rdi;
    goto L60;
L55:
{
    const uint64_t a = (uint64_t)(ML_M8(rbx, 0x0)) & ~0ULL, b = (uint64_t)(rsi) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L59;
    ML_M8(rbx, 0x0) = rdi;
    goto L60;
L59:
    ML_M8(rbx, 0x10) = rdi;
L60:
    rdx = ML_M8(rbp, 0x30);
{
    const uint64_t a = (uint64_t)(ML_M8(rdx, 0x0)) & ~0ULL, b = (uint64_t)(rsi) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L76;
{
    const uint64_t a = (uint64_t)(ML_M1(rdi, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L67;
    rcx = rbx;
    goto L75;
L67:
    rcx = rdi;
    rax = ML_M8(rdi, 0x0);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L75;
L71:
    rcx = rax;
    rax = ML_M8(rax, 0x0);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L71;
L75:
    ML_M8(rdx, 0x0) = rcx;
L76:
    rdx = ML_M8(rbp, 0x30);
{
    const uint64_t a = (uint64_t)(ML_M8(rdx, 0x10)) & ~0ULL, b = (uint64_t)(rsi) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L130;
{
    const uint64_t a = (uint64_t)(ML_M1(rdi, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L83;
    rcx = rbx;
    goto L91;
L83:
    rcx = rdi;
    rax = ML_M8(rdi, 0x10);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L91;
L87:
    rcx = rax;
    rax = ML_M8(rax, 0x10);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L87;
L91:
    ML_M8(rdx, 0x10) = rcx;
    goto L130;
L93:
    ML_M8(r11, 0x8) = rcx;
    rax = ML_M8(rsi, 0x0);
    ML_M8(rcx, 0x0) = rax;
{
    const uint64_t a = (uint64_t)(rcx) & ~0ULL, b = (uint64_t)(ML_M8(rsi, 0x10)) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L100;
    rbx = rcx;
    goto L109;
L100:
    rbx = ML_M8(rcx, 0x8);
{
    const uint64_t a = (uint64_t)(ML_M1(rdi, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L104;
    ML_M8(rdi, 0x8) = rbx;
L104:
    ML_M8(rbx, 0x0) = rdi;
    rax = ML_M8(rsi, 0x10);
    ML_M8(rcx, 0x10) = rax;
    rax = ML_M8(rsi, 0x10);
    ML_M8(rax, 0x8) = rcx;
L109:
    rax = ML_M8(rbp, 0x30);
{
    const uint64_t a = (uint64_t)(ML_M8(rax, 0x8)) & ~0ULL, b = (uint64_t)(rsi) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L114;
    ML_M8(rax, 0x8) = rcx;
    goto L120;
L114:
    rax = ML_M8(rsi, 0x8);
{
    const uint64_t a = (uint64_t)(ML_M8(rax, 0x0)) & ~0ULL, b = (uint64_t)(rsi) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L119;
    ML_M8(rax, 0x0) = rcx;
    goto L120;
L119:
    ML_M8(rax, 0x10) = rcx;
L120:
    rax = ML_M8(rsi, 0x8);
    ML_M8(rcx, 0x8) = rax;
    rdx = rsi + 0x28;
    r8 = rcx + 0x28;
{
    const uint64_t a = (uint64_t)(r8) & ~0ULL, b = (uint64_t)(rdx) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (f_zf) goto L130;
    rcx = ML_M1(r8, 0x0);
    rax = ML_M1(rdx, 0x0);
    ML_M1(r8, 0x0) = (uint8_t)rax;
    ML_M1(rdx, 0x0) = (uint8_t)rcx;
L130:
{
    const uint64_t a = (uint64_t)(ML_M1(rsi, 0x28)) & 0xFFULL, b = (uint64_t)(0x1ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L225;
    rax = ML_M8(rbp, 0x30);
{
    const uint64_t a = (uint64_t)(rdi) & ~0ULL, b = (uint64_t)(ML_M8(rax, 0x8)) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (f_zf) goto L224;
L135:
{
    const uint64_t a = (uint64_t)(ML_M1(rdi, 0x28)) & 0xFFULL, b = (uint64_t)(0x1ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L224;
    rcx = ML_M8(rbx, 0x0);
{
    const uint64_t a = (uint64_t)(rdi) & ~0ULL, b = (uint64_t)(rcx) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L162;
    rcx = ML_M8(rbx, 0x10);
{
    const uint64_t a = (uint64_t)(ML_M1(rcx, 0x28)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L149;
    ML_M1(rcx, 0x28) = 0x1ULL;
    ML_M1(rbx, 0x28) = 0x0ULL;
    rdx = rbx;
    rcx = rbp;
    rax = ML_CALL(14177a860);
    rcx = ML_M8(rbx, 0x10);
L149:
{
    const uint64_t a = (uint64_t)(ML_M1(rcx, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L153;
    rdi = rbx;
    goto L182;
L153:
    rax = ML_M8(rcx, 0x0);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x28)) & 0xFFULL, b = (uint64_t)(0x1ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L187;
    rax = ML_M8(rcx, 0x10);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x28)) & 0xFFULL, b = (uint64_t)(0x1ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L187;
    ML_M1(rcx, 0x28) = 0x0ULL;
    rdi = rbx;
    goto L182;
L162:
{
    const uint64_t a = (uint64_t)(ML_M1(rcx, 0x28)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L170;
    ML_M1(rcx, 0x28) = 0x1ULL;
    ML_M1(rbx, 0x28) = 0x0ULL;
    rdx = rbx;
    rcx = rbp;
    rax = ML_CALL(14177a460);
    rcx = ML_M8(rbx, 0x0);
L170:
{
    const uint64_t a = (uint64_t)(ML_M1(rcx, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L174;
    rdi = rbx;
    goto L182;
L174:
    rax = ML_M8(rcx, 0x10);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x28)) & 0xFFULL, b = (uint64_t)(0x1ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L206;
    rax = ML_M8(rcx, 0x0);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x28)) & 0xFFULL, b = (uint64_t)(0x1ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L206;
    ML_M1(rcx, 0x28) = 0x0ULL;
    rdi = rbx;
L182:
    rbx = ML_M8(rbx, 0x8);
    rax = ML_M8(rbp, 0x30);
{
    const uint64_t a = (uint64_t)(rdi) & ~0ULL, b = (uint64_t)(ML_M8(rax, 0x8)) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (f_zf) goto L224;
    goto L135;
L187:
    rax = ML_M8(rcx, 0x10);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x28)) & 0xFFULL, b = (uint64_t)(0x1ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L197;
    rax = ML_M8(rcx, 0x0);
    ML_M1(rax, 0x28) = 0x1ULL;
    ML_M1(rcx, 0x28) = 0x0ULL;
    rdx = rcx;
    rcx = rbp;
    rax = ML_CALL(14177a460);
    rcx = ML_M8(rbx, 0x10);
L197:
    rax = ML_M1(rbx, 0x28);
    ML_M1(rcx, 0x28) = (uint8_t)rax;
    ML_M1(rbx, 0x28) = 0x1ULL;
    rax = ML_M8(rcx, 0x10);
    ML_M1(rax, 0x28) = 0x1ULL;
    rdx = rbx;
    rcx = rbp;
    rax = ML_CALL(14177a860);
    goto L224;
L206:
    rax = ML_M8(rcx, 0x0);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x28)) & 0xFFULL, b = (uint64_t)(0x1ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L216;
    rax = ML_M8(rcx, 0x10);
    ML_M1(rax, 0x28) = 0x1ULL;
    ML_M1(rcx, 0x28) = 0x0ULL;
    rdx = rcx;
    rcx = rbp;
    rax = ML_CALL(14177a860);
    rcx = ML_M8(rbx, 0x0);
L216:
    rax = ML_M1(rbx, 0x28);
    ML_M1(rcx, 0x28) = (uint8_t)rax;
    ML_M1(rbx, 0x28) = 0x1ULL;
    rax = ML_M8(rcx, 0x0);
    ML_M1(rax, 0x28) = 0x1ULL;
    rdx = rbx;
    rcx = rbp;
    rax = ML_CALL(14177a460);
L224:
    ML_M1(rdi, 0x28) = 0x1ULL;
L225:
    rcx = rsi;
    rax = ML_CALL(1417f2fdc);
    rax = ML_M8(rbp, 0x38);
{
    const uint64_t r = ((uint64_t)(rax) & ~0ULL) & ((uint64_t)(rax) & ~0ULL);
    f_zf = (r == 0); f_cf = false; f_sf = ((r & 0x8000000000000000ULL) != 0);
    f_of = false;
}
    if (f_zf) goto L232;
    rax = rax - 1;
    ML_M8(rbp, 0x38) = rax;
L232:
    rcx = rsp + 0x20;
    rax = ML_M8(r12, 0x0);
    ML_M8(rcx, 0x0) = rax;
    rax = ML_M8(r12, 0x8);
    ML_M8(rcx, 0x8) = rax;
    rax = ML_M8(rsp, 0x28);
    ML_M8(rsp, 0x28) = rax;
    rax = ML_M8(rbp, 0x0);
    ML_M8(rsp, 0x20) = rax;
    rcx = rsp + 0x20;
    rax = ML_M8(rcx, 0x0);
    ML_M8(r13, 0x0) = rax;
    rax = ML_M8(rcx, 0x8);
    ML_M8(r13, 0x8) = rax;
    rax = r13;
    r11 = rsp + 0xa0;
    rbx = ML_M8(r11, 0x20);
    rbp = ML_M8(r11, 0x28);
    rsi = ML_M8(r11, 0x30);
    rsp = r11;
    { const uint64_t v = ML_M8(rsp, 0); rsp += 8; r13 = v; }
    { const uint64_t v = ML_M8(rsp, 0); rsp += 8; r12 = v; }
    { const uint64_t v = ML_M8(rsp, 0); rsp += 8; rdi = v; }
    return rax;
#undef ML_CALL
    return rax;
}

uint64_t SynLift_141789d70(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A) {
    uint64_t rax = 0, rbx = 0, rbp = 0, rsi = 0, rdi = 0, r10 = 0, r11 = 0, r12 = 0, r13 = 0, r14 = 0, r15 = 0;
    uint64_t rcx = rcxA, rdx = rdxA, r8 = r8A, r9 = r9A;
    bool f_zf = false, f_cf = false, f_sf = false, f_of = false;
    uint8_t xmm0[16] = {0}, xmm1[16] = {0}, xmm2[16] = {0}, xmm3[16] = {0}, xmm4[16] = {0}, xmm5[16] = {0};
    alignas(16) uint8_t stkFrame[0x400] = {0};
    uint64_t rsp = (uint64_t)(uintptr_t)(stkFrame + 0x200);
#define ML_CALL(t) g_fnLIFT_##t(rcx, rdx, r8, r9, ML_M8(rsp, 0x20), ML_M8(rsp, 0x28))
    rsp -= 8; ML_M8(rsp, 0) = rbx;
    rsp = rsp - (0x20ULL);
{
    const uint64_t a = (uint64_t)(ML_M8(rcx, 0x0)) & ~0ULL, b = (uint64_t)(0x0ULL) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    rbx = rcx;
    if (!f_zf) goto L6;
    rax = ML_CALL(1418233c0);
L6:
    rcx = ML_M8(rbx, 0x8);
{
    const uint64_t a = (uint64_t)(ML_M1(rcx, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L12;
    rsp = rsp + (0x20ULL);
    { const uint64_t v = ML_M8(rsp, 0); rsp += 8; rbx = v; }
    return ML_CALL(1418233c0);   // tail call
L12:
    rax = ML_M8(rcx, 0x10);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L27;
    rcx = ML_M8(rax, 0x0);
{
    const uint64_t a = (uint64_t)(ML_M1(rcx, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L23;
    ;
L19:
    rax = rcx;
    rcx = ML_M8(rcx, 0x0);
{
    const uint64_t a = (uint64_t)(ML_M1(rcx, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L19;
L23:
    ML_M8(rbx, 0x8) = rax;
    rsp = rsp + (0x20ULL);
    { const uint64_t v = ML_M8(rsp, 0); rsp += 8; rbx = v; }
    return rax;
L27:
    rcx = ML_M8(rcx, 0x8);
{
    const uint64_t a = (uint64_t)(ML_M1(rcx, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L37;
L30:
    rax = ML_M8(rcx, 0x10);
{
    const uint64_t a = (uint64_t)(ML_M8(rbx, 0x8)) & ~0ULL, b = (uint64_t)(rax) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L37;
    ML_M8(rbx, 0x8) = rcx;
    rcx = ML_M8(rcx, 0x8);
{
    const uint64_t a = (uint64_t)(ML_M1(rcx, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L30;
L37:
    ML_M8(rbx, 0x8) = rcx;
    rsp = rsp + (0x20ULL);
    { const uint64_t v = ML_M8(rsp, 0); rsp += 8; rbx = v; }
    return rax;
#undef ML_CALL
    return rax;
}

uint64_t SynLift_141789ea0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A) {
    uint64_t rax = 0, rbx = 0, rbp = 0, rsi = 0, rdi = 0, r10 = 0, r11 = 0, r12 = 0, r13 = 0, r14 = 0, r15 = 0;
    uint64_t rcx = rcxA, rdx = rdxA, r8 = r8A, r9 = r9A;
    bool f_zf = false, f_cf = false, f_sf = false, f_of = false;
    uint8_t xmm0[16] = {0}, xmm1[16] = {0}, xmm2[16] = {0}, xmm3[16] = {0}, xmm4[16] = {0}, xmm5[16] = {0};
    alignas(16) uint8_t stkFrame[0x400] = {0};
    uint64_t rsp = (uint64_t)(uintptr_t)(stkFrame + 0x200);
#define ML_CALL(t) g_fnLIFT_##t(rcx, rdx, r8, r9, ML_M8(rsp, 0x20), ML_M8(rsp, 0x28))
    r8 = ML_M8(rdx, 0x10);
    rax = ML_M8(r8, 0x0);
    ML_M8(rdx, 0x10) = rax;
    rax = ML_M8(r8, 0x0);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L7;
    ML_M8(rax, 0x8) = rdx;
L7:
    rax = ML_M8(rdx, 0x8);
    ML_M8(r8, 0x8) = rax;
    rax = ML_M8(rcx, 0x30);
{
    const uint64_t a = (uint64_t)(rdx) & ~0ULL, b = (uint64_t)(ML_M8(rax, 0x8)) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L16;
    ML_M8(rax, 0x8) = r8;
    ML_M8(r8, 0x0) = rdx;
    ML_M8(rdx, 0x8) = r8;
    return rax;
L16:
    rax = ML_M8(rdx, 0x8);
{
    const uint64_t a = (uint64_t)(rdx) & ~0ULL, b = (uint64_t)(ML_M8(rax, 0x0)) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L23;
    ML_M8(rax, 0x0) = r8;
    ML_M8(r8, 0x0) = rdx;
    ML_M8(rdx, 0x8) = r8;
    return rax;
L23:
    ML_M8(rax, 0x10) = r8;
    ML_M8(r8, 0x0) = rdx;
    ML_M8(rdx, 0x8) = r8;
    return rax;
#undef ML_CALL
    return rax;
}

uint64_t SynLift_141789f00(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A) {
    uint64_t rax = 0, rbx = 0, rbp = 0, rsi = 0, rdi = 0, r10 = 0, r11 = 0, r12 = 0, r13 = 0, r14 = 0, r15 = 0;
    uint64_t rcx = rcxA, rdx = rdxA, r8 = r8A, r9 = r9A;
    bool f_zf = false, f_cf = false, f_sf = false, f_of = false;
    uint8_t xmm0[16] = {0}, xmm1[16] = {0}, xmm2[16] = {0}, xmm3[16] = {0}, xmm4[16] = {0}, xmm5[16] = {0};
    alignas(16) uint8_t stkFrame[0x400] = {0};
    uint64_t rsp = (uint64_t)(uintptr_t)(stkFrame + 0x200);
#define ML_CALL(t) g_fnLIFT_##t(rcx, rdx, r8, r9, ML_M8(rsp, 0x20), ML_M8(rsp, 0x28))
    r8 = ML_M8(rdx, 0x0);
    rax = ML_M8(r8, 0x10);
    ML_M8(rdx, 0x0) = rax;
    rax = ML_M8(r8, 0x10);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L7;
    ML_M8(rax, 0x8) = rdx;
L7:
    rax = ML_M8(rdx, 0x8);
    ML_M8(r8, 0x8) = rax;
    rax = ML_M8(rcx, 0x30);
{
    const uint64_t a = (uint64_t)(rdx) & ~0ULL, b = (uint64_t)(ML_M8(rax, 0x8)) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L16;
    ML_M8(rax, 0x8) = r8;
    ML_M8(r8, 0x10) = rdx;
    ML_M8(rdx, 0x8) = r8;
    return rax;
L16:
    rax = ML_M8(rdx, 0x8);
{
    const uint64_t a = (uint64_t)(rdx) & ~0ULL, b = (uint64_t)(ML_M8(rax, 0x10)) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L23;
    ML_M8(rax, 0x10) = r8;
    ML_M8(r8, 0x10) = rdx;
    ML_M8(rdx, 0x8) = r8;
    return rax;
L23:
    ML_M8(rax, 0x0) = r8;
    ML_M8(r8, 0x10) = rdx;
    ML_M8(rdx, 0x8) = r8;
    return rax;
#undef ML_CALL
    return rax;
}

__attribute__((weak)) uint64_t (*g_fnLIFT_141789d70)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t) = nullptr;
__attribute__((weak)) uint64_t (*g_fnLIFT_141789ea0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t) = nullptr;
__attribute__((weak)) uint64_t (*g_fnLIFT_141789f00)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t) = nullptr;
uint64_t SynLift_14178ab70(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A) {
    uint64_t rax = 0, rbx = 0, rbp = 0, rsi = 0, rdi = 0, r10 = 0, r11 = 0, r12 = 0, r13 = 0, r14 = 0, r15 = 0;
    uint64_t rcx = rcxA, rdx = rdxA, r8 = r8A, r9 = r9A;
    bool f_zf = false, f_cf = false, f_sf = false, f_of = false;
    uint8_t xmm0[16] = {0}, xmm1[16] = {0}, xmm2[16] = {0}, xmm3[16] = {0}, xmm4[16] = {0}, xmm5[16] = {0};
    alignas(16) uint8_t stkFrame[0x400] = {0};
    uint64_t rsp = (uint64_t)(uintptr_t)(stkFrame + 0x200);
#define ML_CALL(t) g_fnLIFT_##t(rcx, rdx, r8, r9, ML_M8(rsp, 0x20), ML_M8(rsp, 0x28))
    rax = rsp;
    rsp -= 8; ML_M8(rsp, 0) = rdi;
    rsp -= 8; ML_M8(rsp, 0) = r12;
    rsp -= 8; ML_M8(rsp, 0) = r13;
    rsp = rsp - (0xa0ULL);
    ML_M8(rsp, 0x30) = 0xfffffffffffffffeULL;
    ML_M8(rax, 0x8) = rbx;
    ML_M8(rax, 0x10) = rbp;
    ML_M8(rax, 0x18) = rsi;
    r12 = r8;
    r13 = rdx;
    rbp = rcx;
    rsi = ML_M8(r8, 0x8);
{
    const uint64_t a = (uint64_t)(ML_M1(rsi, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L30;
    rdx = (uintptr_t)0x141825ca8;
    rcx = rax - 0x40;
    rax = ML_CALL(141823270);
    rcx = rsp + 0x38;
    rax = ML_CALL(1418233f8);
    rax = (uintptr_t)0x141824a60;
    ML_M8(rsp, 0x38) = rax;
    rdx = rsp + 0x78;
    rcx = rsp + 0x50;
    rax = ML_CALL(141823288);
    rax = (uintptr_t)0x141824ba0;
    ML_M8(rsp, 0x38) = rax;
    rdx = (uintptr_t)0x141881e50;
    rcx = rsp + 0x38;
    rax = ML_CALL(1417f3154);
L30:
    rcx = r8;
    rax = ML_CALL(141789d70);
    r11 = ML_M8(rsi, 0x0);
{
    const uint64_t a = (uint64_t)(ML_M1(r11, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L37;
    rdi = ML_M8(rsi, 0x10);
    goto L46;
L37:
    rax = ML_M8(rsi, 0x10);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L42;
    rdi = r11;
    goto L46;
L42:
    rcx = ML_M8(r12, 0x8);
    rdi = ML_M8(rcx, 0x10);
{
    const uint64_t a = (uint64_t)(rcx) & ~0ULL, b = (uint64_t)(rsi) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L93;
L46:
    rbx = ML_M8(rsi, 0x8);
{
    const uint64_t a = (uint64_t)(ML_M1(rdi, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L50;
    ML_M8(rdi, 0x8) = rbx;
L50:
    rax = ML_M8(rbp, 0x30);
{
    const uint64_t a = (uint64_t)(ML_M8(rax, 0x8)) & ~0ULL, b = (uint64_t)(rsi) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L55;
    ML_M8(rax, 0x8) = rdi;
    goto L60;
L55:
{
    const uint64_t a = (uint64_t)(ML_M8(rbx, 0x0)) & ~0ULL, b = (uint64_t)(rsi) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L59;
    ML_M8(rbx, 0x0) = rdi;
    goto L60;
L59:
    ML_M8(rbx, 0x10) = rdi;
L60:
    rdx = ML_M8(rbp, 0x30);
{
    const uint64_t a = (uint64_t)(ML_M8(rdx, 0x0)) & ~0ULL, b = (uint64_t)(rsi) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L76;
{
    const uint64_t a = (uint64_t)(ML_M1(rdi, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L67;
    rcx = rbx;
    goto L75;
L67:
    rcx = rdi;
    rax = ML_M8(rdi, 0x0);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L75;
L71:
    rcx = rax;
    rax = ML_M8(rax, 0x0);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L71;
L75:
    ML_M8(rdx, 0x0) = rcx;
L76:
    rdx = ML_M8(rbp, 0x30);
{
    const uint64_t a = (uint64_t)(ML_M8(rdx, 0x10)) & ~0ULL, b = (uint64_t)(rsi) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L130;
{
    const uint64_t a = (uint64_t)(ML_M1(rdi, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L83;
    rcx = rbx;
    goto L91;
L83:
    rcx = rdi;
    rax = ML_M8(rdi, 0x10);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L91;
L87:
    rcx = rax;
    rax = ML_M8(rax, 0x10);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L87;
L91:
    ML_M8(rdx, 0x10) = rcx;
    goto L130;
L93:
    ML_M8(r11, 0x8) = rcx;
    rax = ML_M8(rsi, 0x0);
    ML_M8(rcx, 0x0) = rax;
{
    const uint64_t a = (uint64_t)(rcx) & ~0ULL, b = (uint64_t)(ML_M8(rsi, 0x10)) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L100;
    rbx = rcx;
    goto L109;
L100:
    rbx = ML_M8(rcx, 0x8);
{
    const uint64_t a = (uint64_t)(ML_M1(rdi, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L104;
    ML_M8(rdi, 0x8) = rbx;
L104:
    ML_M8(rbx, 0x0) = rdi;
    rax = ML_M8(rsi, 0x10);
    ML_M8(rcx, 0x10) = rax;
    rax = ML_M8(rsi, 0x10);
    ML_M8(rax, 0x8) = rcx;
L109:
    rax = ML_M8(rbp, 0x30);
{
    const uint64_t a = (uint64_t)(ML_M8(rax, 0x8)) & ~0ULL, b = (uint64_t)(rsi) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L114;
    ML_M8(rax, 0x8) = rcx;
    goto L120;
L114:
    rax = ML_M8(rsi, 0x8);
{
    const uint64_t a = (uint64_t)(ML_M8(rax, 0x0)) & ~0ULL, b = (uint64_t)(rsi) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L119;
    ML_M8(rax, 0x0) = rcx;
    goto L120;
L119:
    ML_M8(rax, 0x10) = rcx;
L120:
    rax = ML_M8(rsi, 0x8);
    ML_M8(rcx, 0x8) = rax;
    rdx = rsi + 0x28;
    r8 = rcx + 0x28;
{
    const uint64_t a = (uint64_t)(r8) & ~0ULL, b = (uint64_t)(rdx) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (f_zf) goto L130;
    rcx = ML_M1(r8, 0x0);
    rax = ML_M1(rdx, 0x0);
    ML_M1(r8, 0x0) = (uint8_t)rax;
    ML_M1(rdx, 0x0) = (uint8_t)rcx;
L130:
{
    const uint64_t a = (uint64_t)(ML_M1(rsi, 0x28)) & 0xFFULL, b = (uint64_t)(0x1ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L225;
    rax = ML_M8(rbp, 0x30);
{
    const uint64_t a = (uint64_t)(rdi) & ~0ULL, b = (uint64_t)(ML_M8(rax, 0x8)) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (f_zf) goto L224;
L135:
{
    const uint64_t a = (uint64_t)(ML_M1(rdi, 0x28)) & 0xFFULL, b = (uint64_t)(0x1ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L224;
    rcx = ML_M8(rbx, 0x0);
{
    const uint64_t a = (uint64_t)(rdi) & ~0ULL, b = (uint64_t)(rcx) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L162;
    rcx = ML_M8(rbx, 0x10);
{
    const uint64_t a = (uint64_t)(ML_M1(rcx, 0x28)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L149;
    ML_M1(rcx, 0x28) = 0x1ULL;
    ML_M1(rbx, 0x28) = 0x0ULL;
    rdx = rbx;
    rcx = rbp;
    rax = ML_CALL(141789ea0);
    rcx = ML_M8(rbx, 0x10);
L149:
{
    const uint64_t a = (uint64_t)(ML_M1(rcx, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L153;
    rdi = rbx;
    goto L182;
L153:
    rax = ML_M8(rcx, 0x0);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x28)) & 0xFFULL, b = (uint64_t)(0x1ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L187;
    rax = ML_M8(rcx, 0x10);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x28)) & 0xFFULL, b = (uint64_t)(0x1ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L187;
    ML_M1(rcx, 0x28) = 0x0ULL;
    rdi = rbx;
    goto L182;
L162:
{
    const uint64_t a = (uint64_t)(ML_M1(rcx, 0x28)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L170;
    ML_M1(rcx, 0x28) = 0x1ULL;
    ML_M1(rbx, 0x28) = 0x0ULL;
    rdx = rbx;
    rcx = rbp;
    rax = ML_CALL(141789f00);
    rcx = ML_M8(rbx, 0x0);
L170:
{
    const uint64_t a = (uint64_t)(ML_M1(rcx, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L174;
    rdi = rbx;
    goto L182;
L174:
    rax = ML_M8(rcx, 0x10);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x28)) & 0xFFULL, b = (uint64_t)(0x1ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L206;
    rax = ML_M8(rcx, 0x0);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x28)) & 0xFFULL, b = (uint64_t)(0x1ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L206;
    ML_M1(rcx, 0x28) = 0x0ULL;
    rdi = rbx;
L182:
    rbx = ML_M8(rbx, 0x8);
    rax = ML_M8(rbp, 0x30);
{
    const uint64_t a = (uint64_t)(rdi) & ~0ULL, b = (uint64_t)(ML_M8(rax, 0x8)) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (f_zf) goto L224;
    goto L135;
L187:
    rax = ML_M8(rcx, 0x10);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x28)) & 0xFFULL, b = (uint64_t)(0x1ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L197;
    rax = ML_M8(rcx, 0x0);
    ML_M1(rax, 0x28) = 0x1ULL;
    ML_M1(rcx, 0x28) = 0x0ULL;
    rdx = rcx;
    rcx = rbp;
    rax = ML_CALL(141789f00);
    rcx = ML_M8(rbx, 0x10);
L197:
    rax = ML_M1(rbx, 0x28);
    ML_M1(rcx, 0x28) = (uint8_t)rax;
    ML_M1(rbx, 0x28) = 0x1ULL;
    rax = ML_M8(rcx, 0x10);
    ML_M1(rax, 0x28) = 0x1ULL;
    rdx = rbx;
    rcx = rbp;
    rax = ML_CALL(141789ea0);
    goto L224;
L206:
    rax = ML_M8(rcx, 0x0);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x28)) & 0xFFULL, b = (uint64_t)(0x1ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L216;
    rax = ML_M8(rcx, 0x10);
    ML_M1(rax, 0x28) = 0x1ULL;
    ML_M1(rcx, 0x28) = 0x0ULL;
    rdx = rcx;
    rcx = rbp;
    rax = ML_CALL(141789ea0);
    rcx = ML_M8(rbx, 0x0);
L216:
    rax = ML_M1(rbx, 0x28);
    ML_M1(rcx, 0x28) = (uint8_t)rax;
    ML_M1(rbx, 0x28) = 0x1ULL;
    rax = ML_M8(rcx, 0x0);
    ML_M1(rax, 0x28) = 0x1ULL;
    rdx = rbx;
    rcx = rbp;
    rax = ML_CALL(141789f00);
L224:
    ML_M1(rdi, 0x28) = 0x1ULL;
L225:
    rcx = rsi;
    rax = ML_CALL(1417f2fdc);
    rax = ML_M8(rbp, 0x38);
{
    const uint64_t r = ((uint64_t)(rax) & ~0ULL) & ((uint64_t)(rax) & ~0ULL);
    f_zf = (r == 0); f_cf = false; f_sf = ((r & 0x8000000000000000ULL) != 0);
    f_of = false;
}
    if (f_zf) goto L232;
    rax = rax - 1;
    ML_M8(rbp, 0x38) = rax;
L232:
    rcx = rsp + 0x20;
    rax = ML_M8(r12, 0x0);
    ML_M8(rcx, 0x0) = rax;
    rax = ML_M8(r12, 0x8);
    ML_M8(rcx, 0x8) = rax;
    rax = ML_M8(rsp, 0x28);
    ML_M8(rsp, 0x28) = rax;
    rax = ML_M8(rbp, 0x0);
    ML_M8(rsp, 0x20) = rax;
    rcx = rsp + 0x20;
    rax = ML_M8(rcx, 0x0);
    ML_M8(r13, 0x0) = rax;
    rax = ML_M8(rcx, 0x8);
    ML_M8(r13, 0x8) = rax;
    rax = r13;
    r11 = rsp + 0xa0;
    rbx = ML_M8(r11, 0x20);
    rbp = ML_M8(r11, 0x28);
    rsi = ML_M8(r11, 0x30);
    rsp = r11;
    { const uint64_t v = ML_M8(rsp, 0); rsp += 8; r13 = v; }
    { const uint64_t v = ML_M8(rsp, 0); rsp += 8; r12 = v; }
    { const uint64_t v = ML_M8(rsp, 0); rsp += 8; rdi = v; }
    return rax;
#undef ML_CALL
    return rax;
}

uint64_t SynLift_141790ce0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A) {
    uint64_t rax = 0, rbx = 0, rbp = 0, rsi = 0, rdi = 0, r10 = 0, r11 = 0, r12 = 0, r13 = 0, r14 = 0, r15 = 0;
    uint64_t rcx = rcxA, rdx = rdxA, r8 = r8A, r9 = r9A;
    bool f_zf = false, f_cf = false, f_sf = false, f_of = false;
    uint8_t xmm0[16] = {0}, xmm1[16] = {0}, xmm2[16] = {0}, xmm3[16] = {0}, xmm4[16] = {0}, xmm5[16] = {0};
    alignas(16) uint8_t stkFrame[0x400] = {0};
    uint64_t rsp = (uint64_t)(uintptr_t)(stkFrame + 0x200);
#define ML_CALL(t) g_fnLIFT_##t(rcx, rdx, r8, r9, ML_M8(rsp, 0x20), ML_M8(rsp, 0x28))
    r8 = ML_M8(rdx, 0x0);
    rax = ML_M8(r8, 0x10);
    ML_M8(rdx, 0x0) = rax;
    rax = ML_M8(r8, 0x10);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x21)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L7;
    ML_M8(rax, 0x8) = rdx;
L7:
    rax = ML_M8(rdx, 0x8);
    ML_M8(r8, 0x8) = rax;
    rax = ML_M8(rcx, 0x30);
{
    const uint64_t a = (uint64_t)(rdx) & ~0ULL, b = (uint64_t)(ML_M8(rax, 0x8)) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L16;
    ML_M8(rax, 0x8) = r8;
    ML_M8(r8, 0x10) = rdx;
    ML_M8(rdx, 0x8) = r8;
    return rax;
L16:
    rax = ML_M8(rdx, 0x8);
{
    const uint64_t a = (uint64_t)(rdx) & ~0ULL, b = (uint64_t)(ML_M8(rax, 0x10)) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L23;
    ML_M8(rax, 0x10) = r8;
    ML_M8(r8, 0x10) = rdx;
    ML_M8(rdx, 0x8) = r8;
    return rax;
L23:
    ML_M8(rax, 0x0) = r8;
    ML_M8(r8, 0x10) = rdx;
    ML_M8(rdx, 0x8) = r8;
    return rax;
#undef ML_CALL
    return rax;
}

uint64_t SynLift_141790e10(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A) {
    uint64_t rax = 0, rbx = 0, rbp = 0, rsi = 0, rdi = 0, r10 = 0, r11 = 0, r12 = 0, r13 = 0, r14 = 0, r15 = 0;
    uint64_t rcx = rcxA, rdx = rdxA, r8 = r8A, r9 = r9A;
    bool f_zf = false, f_cf = false, f_sf = false, f_of = false;
    uint8_t xmm0[16] = {0}, xmm1[16] = {0}, xmm2[16] = {0}, xmm3[16] = {0}, xmm4[16] = {0}, xmm5[16] = {0};
    alignas(16) uint8_t stkFrame[0x400] = {0};
    uint64_t rsp = (uint64_t)(uintptr_t)(stkFrame + 0x200);
#define ML_CALL(t) g_fnLIFT_##t(rcx, rdx, r8, r9, ML_M8(rsp, 0x20), ML_M8(rsp, 0x28))
    rsp -= 8; ML_M8(rsp, 0) = rbx;
    rsp = rsp - (0x20ULL);
{
    const uint64_t a = (uint64_t)(ML_M8(rcx, 0x0)) & ~0ULL, b = (uint64_t)(0x0ULL) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    rbx = rcx;
    if (!f_zf) goto L6;
    rax = ML_CALL(1418233c0);
L6:
    rcx = ML_M8(rbx, 0x8);
{
    const uint64_t a = (uint64_t)(ML_M1(rcx, 0x21)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L12;
    rsp = rsp + (0x20ULL);
    { const uint64_t v = ML_M8(rsp, 0); rsp += 8; rbx = v; }
    return ML_CALL(1418233c0);   // tail call
L12:
    rax = ML_M8(rcx, 0x10);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x21)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L27;
    rcx = ML_M8(rax, 0x0);
{
    const uint64_t a = (uint64_t)(ML_M1(rcx, 0x21)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L23;
    ;
L19:
    rax = rcx;
    rcx = ML_M8(rcx, 0x0);
{
    const uint64_t a = (uint64_t)(ML_M1(rcx, 0x21)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L19;
L23:
    ML_M8(rbx, 0x8) = rax;
    rsp = rsp + (0x20ULL);
    { const uint64_t v = ML_M8(rsp, 0); rsp += 8; rbx = v; }
    return rax;
L27:
    rcx = ML_M8(rcx, 0x8);
{
    const uint64_t a = (uint64_t)(ML_M1(rcx, 0x21)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L37;
L30:
    rax = ML_M8(rcx, 0x10);
{
    const uint64_t a = (uint64_t)(ML_M8(rbx, 0x8)) & ~0ULL, b = (uint64_t)(rax) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L37;
    ML_M8(rbx, 0x8) = rcx;
    rcx = ML_M8(rcx, 0x8);
{
    const uint64_t a = (uint64_t)(ML_M1(rcx, 0x21)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L30;
L37:
    ML_M8(rbx, 0x8) = rcx;
    rsp = rsp + (0x20ULL);
    { const uint64_t v = ML_M8(rsp, 0); rsp += 8; rbx = v; }
    return rax;
#undef ML_CALL
    return rax;
}

uint64_t SynLift_141792160(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A) {
    uint64_t rax = 0, rbx = 0, rbp = 0, rsi = 0, rdi = 0, r10 = 0, r11 = 0, r12 = 0, r13 = 0, r14 = 0, r15 = 0;
    uint64_t rcx = rcxA, rdx = rdxA, r8 = r8A, r9 = r9A;
    bool f_zf = false, f_cf = false, f_sf = false, f_of = false;
    uint8_t xmm0[16] = {0}, xmm1[16] = {0}, xmm2[16] = {0}, xmm3[16] = {0}, xmm4[16] = {0}, xmm5[16] = {0};
    alignas(16) uint8_t stkFrame[0x400] = {0};
    uint64_t rsp = (uint64_t)(uintptr_t)(stkFrame + 0x200);
#define ML_CALL(t) g_fnLIFT_##t(rcx, rdx, r8, r9, ML_M8(rsp, 0x20), ML_M8(rsp, 0x28))
    r8 = ML_M8(rdx, 0x10);
    rax = ML_M8(r8, 0x0);
    ML_M8(rdx, 0x10) = rax;
    rax = ML_M8(r8, 0x0);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L7;
    ML_M8(rax, 0x8) = rdx;
L7:
    rax = ML_M8(rdx, 0x8);
    ML_M8(r8, 0x8) = rax;
    rax = ML_M8(rcx, 0x30);
{
    const uint64_t a = (uint64_t)(rdx) & ~0ULL, b = (uint64_t)(ML_M8(rax, 0x8)) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L16;
    ML_M8(rax, 0x8) = r8;
    ML_M8(r8, 0x0) = rdx;
    ML_M8(rdx, 0x8) = r8;
    return rax;
L16:
    rax = ML_M8(rdx, 0x8);
{
    const uint64_t a = (uint64_t)(rdx) & ~0ULL, b = (uint64_t)(ML_M8(rax, 0x0)) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L23;
    ML_M8(rax, 0x0) = r8;
    ML_M8(r8, 0x0) = rdx;
    ML_M8(rdx, 0x8) = r8;
    return rax;
L23:
    ML_M8(rax, 0x10) = r8;
    ML_M8(r8, 0x0) = rdx;
    ML_M8(rdx, 0x8) = r8;
    return rax;
#undef ML_CALL
    return rax;
}

uint64_t SynLift_1417921c0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A) {
    uint64_t rax = 0, rbx = 0, rbp = 0, rsi = 0, rdi = 0, r10 = 0, r11 = 0, r12 = 0, r13 = 0, r14 = 0, r15 = 0;
    uint64_t rcx = rcxA, rdx = rdxA, r8 = r8A, r9 = r9A;
    bool f_zf = false, f_cf = false, f_sf = false, f_of = false;
    uint8_t xmm0[16] = {0}, xmm1[16] = {0}, xmm2[16] = {0}, xmm3[16] = {0}, xmm4[16] = {0}, xmm5[16] = {0};
    alignas(16) uint8_t stkFrame[0x400] = {0};
    uint64_t rsp = (uint64_t)(uintptr_t)(stkFrame + 0x200);
#define ML_CALL(t) g_fnLIFT_##t(rcx, rdx, r8, r9, ML_M8(rsp, 0x20), ML_M8(rsp, 0x28))
    r8 = ML_M8(rdx, 0x0);
    rax = ML_M8(r8, 0x10);
    ML_M8(rdx, 0x0) = rax;
    rax = ML_M8(r8, 0x10);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L7;
    ML_M8(rax, 0x8) = rdx;
L7:
    rax = ML_M8(rdx, 0x8);
    ML_M8(r8, 0x8) = rax;
    rax = ML_M8(rcx, 0x30);
{
    const uint64_t a = (uint64_t)(rdx) & ~0ULL, b = (uint64_t)(ML_M8(rax, 0x8)) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L16;
    ML_M8(rax, 0x8) = r8;
    ML_M8(r8, 0x10) = rdx;
    ML_M8(rdx, 0x8) = r8;
    return rax;
L16:
    rax = ML_M8(rdx, 0x8);
{
    const uint64_t a = (uint64_t)(rdx) & ~0ULL, b = (uint64_t)(ML_M8(rax, 0x10)) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L23;
    ML_M8(rax, 0x10) = r8;
    ML_M8(r8, 0x10) = rdx;
    ML_M8(rdx, 0x8) = r8;
    return rax;
L23:
    ML_M8(rax, 0x0) = r8;
    ML_M8(r8, 0x10) = rdx;
    ML_M8(rdx, 0x8) = r8;
    return rax;
#undef ML_CALL
    return rax;
}

uint64_t SynLift_141792240(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A) {
    uint64_t rax = 0, rbx = 0, rbp = 0, rsi = 0, rdi = 0, r10 = 0, r11 = 0, r12 = 0, r13 = 0, r14 = 0, r15 = 0;
    uint64_t rcx = rcxA, rdx = rdxA, r8 = r8A, r9 = r9A;
    bool f_zf = false, f_cf = false, f_sf = false, f_of = false;
    uint8_t xmm0[16] = {0}, xmm1[16] = {0}, xmm2[16] = {0}, xmm3[16] = {0}, xmm4[16] = {0}, xmm5[16] = {0};
    alignas(16) uint8_t stkFrame[0x400] = {0};
    uint64_t rsp = (uint64_t)(uintptr_t)(stkFrame + 0x200);
#define ML_CALL(t) g_fnLIFT_##t(rcx, rdx, r8, r9, ML_M8(rsp, 0x20), ML_M8(rsp, 0x28))
    rsp -= 8; ML_M8(rsp, 0) = rbx;
    rsp = rsp - (0x20ULL);
{
    const uint64_t a = (uint64_t)(ML_M8(rcx, 0x0)) & ~0ULL, b = (uint64_t)(0x0ULL) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    rbx = rcx;
    if (!f_zf) goto L6;
    rax = ML_CALL(1418233c0);
L6:
    rcx = ML_M8(rbx, 0x8);
{
    const uint64_t a = (uint64_t)(ML_M1(rcx, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L12;
    rsp = rsp + (0x20ULL);
    { const uint64_t v = ML_M8(rsp, 0); rsp += 8; rbx = v; }
    return ML_CALL(1418233c0);   // tail call
L12:
    rax = ML_M8(rcx, 0x10);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L27;
    rcx = ML_M8(rax, 0x0);
{
    const uint64_t a = (uint64_t)(ML_M1(rcx, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L23;
    ;
L19:
    rax = rcx;
    rcx = ML_M8(rcx, 0x0);
{
    const uint64_t a = (uint64_t)(ML_M1(rcx, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L19;
L23:
    ML_M8(rbx, 0x8) = rax;
    rsp = rsp + (0x20ULL);
    { const uint64_t v = ML_M8(rsp, 0); rsp += 8; rbx = v; }
    return rax;
L27:
    rcx = ML_M8(rcx, 0x8);
{
    const uint64_t a = (uint64_t)(ML_M1(rcx, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L37;
L30:
    rax = ML_M8(rcx, 0x10);
{
    const uint64_t a = (uint64_t)(ML_M8(rbx, 0x8)) & ~0ULL, b = (uint64_t)(rax) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L37;
    ML_M8(rbx, 0x8) = rcx;
    rcx = ML_M8(rcx, 0x8);
{
    const uint64_t a = (uint64_t)(ML_M1(rcx, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L30;
L37:
    ML_M8(rbx, 0x8) = rcx;
    rsp = rsp + (0x20ULL);
    { const uint64_t v = ML_M8(rsp, 0); rsp += 8; rbx = v; }
    return rax;
#undef ML_CALL
    return rax;
}

uint64_t SynLift_1417923e0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A) {
    uint64_t rax = 0, rbx = 0, rbp = 0, rsi = 0, rdi = 0, r10 = 0, r11 = 0, r12 = 0, r13 = 0, r14 = 0, r15 = 0;
    uint64_t rcx = rcxA, rdx = rdxA, r8 = r8A, r9 = r9A;
    bool f_zf = false, f_cf = false, f_sf = false, f_of = false;
    uint8_t xmm0[16] = {0}, xmm1[16] = {0}, xmm2[16] = {0}, xmm3[16] = {0}, xmm4[16] = {0}, xmm5[16] = {0};
    alignas(16) uint8_t stkFrame[0x400] = {0};
    uint64_t rsp = (uint64_t)(uintptr_t)(stkFrame + 0x200);
#define ML_CALL(t) g_fnLIFT_##t(rcx, rdx, r8, r9, ML_M8(rsp, 0x20), ML_M8(rsp, 0x28))
    r8 = ML_M8(rdx, 0x10);
    rax = ML_M8(r8, 0x0);
    ML_M8(rdx, 0x10) = rax;
    rax = ML_M8(r8, 0x0);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x21)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L7;
    ML_M8(rax, 0x8) = rdx;
L7:
    rax = ML_M8(rdx, 0x8);
    ML_M8(r8, 0x8) = rax;
    rax = ML_M8(rcx, 0x30);
{
    const uint64_t a = (uint64_t)(rdx) & ~0ULL, b = (uint64_t)(ML_M8(rax, 0x8)) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L16;
    ML_M8(rax, 0x8) = r8;
    ML_M8(r8, 0x0) = rdx;
    ML_M8(rdx, 0x8) = r8;
    return rax;
L16:
    rax = ML_M8(rdx, 0x8);
{
    const uint64_t a = (uint64_t)(rdx) & ~0ULL, b = (uint64_t)(ML_M8(rax, 0x0)) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L23;
    ML_M8(rax, 0x0) = r8;
    ML_M8(r8, 0x0) = rdx;
    ML_M8(rdx, 0x8) = r8;
    return rax;
L23:
    ML_M8(rax, 0x10) = r8;
    ML_M8(r8, 0x0) = rdx;
    ML_M8(rdx, 0x8) = r8;
    return rax;
#undef ML_CALL
    return rax;
}

__attribute__((weak)) uint64_t (*g_fnLIFT_141790ce0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t) = nullptr;
__attribute__((weak)) uint64_t (*g_fnLIFT_141790e10)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t) = nullptr;
__attribute__((weak)) uint64_t (*g_fnLIFT_1417923e0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t) = nullptr;
uint64_t SynLift_1417948b0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A) {
    uint64_t rax = 0, rbx = 0, rbp = 0, rsi = 0, rdi = 0, r10 = 0, r11 = 0, r12 = 0, r13 = 0, r14 = 0, r15 = 0;
    uint64_t rcx = rcxA, rdx = rdxA, r8 = r8A, r9 = r9A;
    bool f_zf = false, f_cf = false, f_sf = false, f_of = false;
    uint8_t xmm0[16] = {0}, xmm1[16] = {0}, xmm2[16] = {0}, xmm3[16] = {0}, xmm4[16] = {0}, xmm5[16] = {0};
    alignas(16) uint8_t stkFrame[0x400] = {0};
    uint64_t rsp = (uint64_t)(uintptr_t)(stkFrame + 0x200);
#define ML_CALL(t) g_fnLIFT_##t(rcx, rdx, r8, r9, ML_M8(rsp, 0x20), ML_M8(rsp, 0x28))
    rax = rsp;
    rsp -= 8; ML_M8(rsp, 0) = rdi;
    rsp -= 8; ML_M8(rsp, 0) = r12;
    rsp -= 8; ML_M8(rsp, 0) = r13;
    rsp = rsp - (0xa0ULL);
    ML_M8(rsp, 0x30) = 0xfffffffffffffffeULL;
    ML_M8(rax, 0x8) = rbx;
    ML_M8(rax, 0x10) = rbp;
    ML_M8(rax, 0x18) = rsi;
    r12 = r8;
    r13 = rdx;
    rbp = rcx;
    rsi = ML_M8(r8, 0x8);
{
    const uint64_t a = (uint64_t)(ML_M1(rsi, 0x21)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L30;
    rdx = (uintptr_t)0x141825ca8;
    rcx = rax - 0x40;
    rax = ML_CALL(141823270);
    rcx = rsp + 0x38;
    rax = ML_CALL(1418233f8);
    rax = (uintptr_t)0x141824a60;
    ML_M8(rsp, 0x38) = rax;
    rdx = rsp + 0x78;
    rcx = rsp + 0x50;
    rax = ML_CALL(141823288);
    rax = (uintptr_t)0x141824ba0;
    ML_M8(rsp, 0x38) = rax;
    rdx = (uintptr_t)0x141881e50;
    rcx = rsp + 0x38;
    rax = ML_CALL(1417f3154);
L30:
    rcx = r8;
    rax = ML_CALL(141790e10);
    r11 = ML_M8(rsi, 0x0);
{
    const uint64_t a = (uint64_t)(ML_M1(r11, 0x21)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L37;
    rdi = ML_M8(rsi, 0x10);
    goto L46;
L37:
    rax = ML_M8(rsi, 0x10);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x21)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L42;
    rdi = r11;
    goto L46;
L42:
    rcx = ML_M8(r12, 0x8);
    rdi = ML_M8(rcx, 0x10);
{
    const uint64_t a = (uint64_t)(rcx) & ~0ULL, b = (uint64_t)(rsi) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L93;
L46:
    rbx = ML_M8(rsi, 0x8);
{
    const uint64_t a = (uint64_t)(ML_M1(rdi, 0x21)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L50;
    ML_M8(rdi, 0x8) = rbx;
L50:
    rax = ML_M8(rbp, 0x30);
{
    const uint64_t a = (uint64_t)(ML_M8(rax, 0x8)) & ~0ULL, b = (uint64_t)(rsi) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L55;
    ML_M8(rax, 0x8) = rdi;
    goto L60;
L55:
{
    const uint64_t a = (uint64_t)(ML_M8(rbx, 0x0)) & ~0ULL, b = (uint64_t)(rsi) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L59;
    ML_M8(rbx, 0x0) = rdi;
    goto L60;
L59:
    ML_M8(rbx, 0x10) = rdi;
L60:
    rdx = ML_M8(rbp, 0x30);
{
    const uint64_t a = (uint64_t)(ML_M8(rdx, 0x0)) & ~0ULL, b = (uint64_t)(rsi) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L76;
{
    const uint64_t a = (uint64_t)(ML_M1(rdi, 0x21)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L67;
    rcx = rbx;
    goto L75;
L67:
    rcx = rdi;
    rax = ML_M8(rdi, 0x0);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x21)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L75;
L71:
    rcx = rax;
    rax = ML_M8(rax, 0x0);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x21)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L71;
L75:
    ML_M8(rdx, 0x0) = rcx;
L76:
    rdx = ML_M8(rbp, 0x30);
{
    const uint64_t a = (uint64_t)(ML_M8(rdx, 0x10)) & ~0ULL, b = (uint64_t)(rsi) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L130;
{
    const uint64_t a = (uint64_t)(ML_M1(rdi, 0x21)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L83;
    rcx = rbx;
    goto L91;
L83:
    rcx = rdi;
    rax = ML_M8(rdi, 0x10);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x21)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L91;
L87:
    rcx = rax;
    rax = ML_M8(rax, 0x10);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x21)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L87;
L91:
    ML_M8(rdx, 0x10) = rcx;
    goto L130;
L93:
    ML_M8(r11, 0x8) = rcx;
    rax = ML_M8(rsi, 0x0);
    ML_M8(rcx, 0x0) = rax;
{
    const uint64_t a = (uint64_t)(rcx) & ~0ULL, b = (uint64_t)(ML_M8(rsi, 0x10)) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L100;
    rbx = rcx;
    goto L109;
L100:
    rbx = ML_M8(rcx, 0x8);
{
    const uint64_t a = (uint64_t)(ML_M1(rdi, 0x21)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L104;
    ML_M8(rdi, 0x8) = rbx;
L104:
    ML_M8(rbx, 0x0) = rdi;
    rax = ML_M8(rsi, 0x10);
    ML_M8(rcx, 0x10) = rax;
    rax = ML_M8(rsi, 0x10);
    ML_M8(rax, 0x8) = rcx;
L109:
    rax = ML_M8(rbp, 0x30);
{
    const uint64_t a = (uint64_t)(ML_M8(rax, 0x8)) & ~0ULL, b = (uint64_t)(rsi) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L114;
    ML_M8(rax, 0x8) = rcx;
    goto L120;
L114:
    rax = ML_M8(rsi, 0x8);
{
    const uint64_t a = (uint64_t)(ML_M8(rax, 0x0)) & ~0ULL, b = (uint64_t)(rsi) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L119;
    ML_M8(rax, 0x0) = rcx;
    goto L120;
L119:
    ML_M8(rax, 0x10) = rcx;
L120:
    rax = ML_M8(rsi, 0x8);
    ML_M8(rcx, 0x8) = rax;
    rdx = rsi + 0x20;
    r8 = rcx + 0x20;
{
    const uint64_t a = (uint64_t)(r8) & ~0ULL, b = (uint64_t)(rdx) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (f_zf) goto L130;
    rcx = ML_M1(r8, 0x0);
    rax = ML_M1(rdx, 0x0);
    ML_M1(r8, 0x0) = (uint8_t)rax;
    ML_M1(rdx, 0x0) = (uint8_t)rcx;
L130:
{
    const uint64_t a = (uint64_t)(ML_M1(rsi, 0x20)) & 0xFFULL, b = (uint64_t)(0x1ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L225;
    rax = ML_M8(rbp, 0x30);
{
    const uint64_t a = (uint64_t)(rdi) & ~0ULL, b = (uint64_t)(ML_M8(rax, 0x8)) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (f_zf) goto L224;
L135:
{
    const uint64_t a = (uint64_t)(ML_M1(rdi, 0x20)) & 0xFFULL, b = (uint64_t)(0x1ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L224;
    rcx = ML_M8(rbx, 0x0);
{
    const uint64_t a = (uint64_t)(rdi) & ~0ULL, b = (uint64_t)(rcx) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L162;
    rcx = ML_M8(rbx, 0x10);
{
    const uint64_t a = (uint64_t)(ML_M1(rcx, 0x20)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L149;
    ML_M1(rcx, 0x20) = 0x1ULL;
    ML_M1(rbx, 0x20) = 0x0ULL;
    rdx = rbx;
    rcx = rbp;
    rax = ML_CALL(1417923e0);
    rcx = ML_M8(rbx, 0x10);
L149:
{
    const uint64_t a = (uint64_t)(ML_M1(rcx, 0x21)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L153;
    rdi = rbx;
    goto L182;
L153:
    rax = ML_M8(rcx, 0x0);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x20)) & 0xFFULL, b = (uint64_t)(0x1ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L187;
    rax = ML_M8(rcx, 0x10);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x20)) & 0xFFULL, b = (uint64_t)(0x1ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L187;
    ML_M1(rcx, 0x20) = 0x0ULL;
    rdi = rbx;
    goto L182;
L162:
{
    const uint64_t a = (uint64_t)(ML_M1(rcx, 0x20)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L170;
    ML_M1(rcx, 0x20) = 0x1ULL;
    ML_M1(rbx, 0x20) = 0x0ULL;
    rdx = rbx;
    rcx = rbp;
    rax = ML_CALL(141790ce0);
    rcx = ML_M8(rbx, 0x0);
L170:
{
    const uint64_t a = (uint64_t)(ML_M1(rcx, 0x21)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L174;
    rdi = rbx;
    goto L182;
L174:
    rax = ML_M8(rcx, 0x10);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x20)) & 0xFFULL, b = (uint64_t)(0x1ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L206;
    rax = ML_M8(rcx, 0x0);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x20)) & 0xFFULL, b = (uint64_t)(0x1ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L206;
    ML_M1(rcx, 0x20) = 0x0ULL;
    rdi = rbx;
L182:
    rbx = ML_M8(rbx, 0x8);
    rax = ML_M8(rbp, 0x30);
{
    const uint64_t a = (uint64_t)(rdi) & ~0ULL, b = (uint64_t)(ML_M8(rax, 0x8)) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (f_zf) goto L224;
    goto L135;
L187:
    rax = ML_M8(rcx, 0x10);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x20)) & 0xFFULL, b = (uint64_t)(0x1ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L197;
    rax = ML_M8(rcx, 0x0);
    ML_M1(rax, 0x20) = 0x1ULL;
    ML_M1(rcx, 0x20) = 0x0ULL;
    rdx = rcx;
    rcx = rbp;
    rax = ML_CALL(141790ce0);
    rcx = ML_M8(rbx, 0x10);
L197:
    rax = ML_M1(rbx, 0x20);
    ML_M1(rcx, 0x20) = (uint8_t)rax;
    ML_M1(rbx, 0x20) = 0x1ULL;
    rax = ML_M8(rcx, 0x10);
    ML_M1(rax, 0x20) = 0x1ULL;
    rdx = rbx;
    rcx = rbp;
    rax = ML_CALL(1417923e0);
    goto L224;
L206:
    rax = ML_M8(rcx, 0x0);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x20)) & 0xFFULL, b = (uint64_t)(0x1ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L216;
    rax = ML_M8(rcx, 0x10);
    ML_M1(rax, 0x20) = 0x1ULL;
    ML_M1(rcx, 0x20) = 0x0ULL;
    rdx = rcx;
    rcx = rbp;
    rax = ML_CALL(1417923e0);
    rcx = ML_M8(rbx, 0x0);
L216:
    rax = ML_M1(rbx, 0x20);
    ML_M1(rcx, 0x20) = (uint8_t)rax;
    ML_M1(rbx, 0x20) = 0x1ULL;
    rax = ML_M8(rcx, 0x0);
    ML_M1(rax, 0x20) = 0x1ULL;
    rdx = rbx;
    rcx = rbp;
    rax = ML_CALL(141790ce0);
L224:
    ML_M1(rdi, 0x20) = 0x1ULL;
L225:
    rcx = rsi;
    rax = ML_CALL(1417f2fdc);
    rax = ML_M8(rbp, 0x38);
{
    const uint64_t r = ((uint64_t)(rax) & ~0ULL) & ((uint64_t)(rax) & ~0ULL);
    f_zf = (r == 0); f_cf = false; f_sf = ((r & 0x8000000000000000ULL) != 0);
    f_of = false;
}
    if (f_zf) goto L232;
    rax = rax - 1;
    ML_M8(rbp, 0x38) = rax;
L232:
    rcx = rsp + 0x20;
    rax = ML_M8(r12, 0x0);
    ML_M8(rcx, 0x0) = rax;
    rax = ML_M8(r12, 0x8);
    ML_M8(rcx, 0x8) = rax;
    rax = ML_M8(rsp, 0x28);
    ML_M8(rsp, 0x28) = rax;
    rax = ML_M8(rbp, 0x0);
    ML_M8(rsp, 0x20) = rax;
    rcx = rsp + 0x20;
    rax = ML_M8(rcx, 0x0);
    ML_M8(r13, 0x0) = rax;
    rax = ML_M8(rcx, 0x8);
    ML_M8(r13, 0x8) = rax;
    rax = r13;
    r11 = rsp + 0xa0;
    rbx = ML_M8(r11, 0x20);
    rbp = ML_M8(r11, 0x28);
    rsi = ML_M8(r11, 0x30);
    rsp = r11;
    { const uint64_t v = ML_M8(rsp, 0); rsp += 8; r13 = v; }
    { const uint64_t v = ML_M8(rsp, 0); rsp += 8; r12 = v; }
    { const uint64_t v = ML_M8(rsp, 0); rsp += 8; rdi = v; }
    return rax;
#undef ML_CALL
    return rax;
}

__attribute__((weak)) uint64_t (*g_fnLIFT_141792160)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t) = nullptr;
__attribute__((weak)) uint64_t (*g_fnLIFT_1417921c0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t) = nullptr;
__attribute__((weak)) uint64_t (*g_fnLIFT_141792240)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t) = nullptr;
uint64_t SynLift_141795230(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A) {
    uint64_t rax = 0, rbx = 0, rbp = 0, rsi = 0, rdi = 0, r10 = 0, r11 = 0, r12 = 0, r13 = 0, r14 = 0, r15 = 0;
    uint64_t rcx = rcxA, rdx = rdxA, r8 = r8A, r9 = r9A;
    bool f_zf = false, f_cf = false, f_sf = false, f_of = false;
    uint8_t xmm0[16] = {0}, xmm1[16] = {0}, xmm2[16] = {0}, xmm3[16] = {0}, xmm4[16] = {0}, xmm5[16] = {0};
    alignas(16) uint8_t stkFrame[0x400] = {0};
    uint64_t rsp = (uint64_t)(uintptr_t)(stkFrame + 0x200);
#define ML_CALL(t) g_fnLIFT_##t(rcx, rdx, r8, r9, ML_M8(rsp, 0x20), ML_M8(rsp, 0x28))
    rax = rsp;
    rsp -= 8; ML_M8(rsp, 0) = rdi;
    rsp -= 8; ML_M8(rsp, 0) = r12;
    rsp -= 8; ML_M8(rsp, 0) = r13;
    rsp = rsp - (0xa0ULL);
    ML_M8(rsp, 0x30) = 0xfffffffffffffffeULL;
    ML_M8(rax, 0x8) = rbx;
    ML_M8(rax, 0x10) = rbp;
    ML_M8(rax, 0x18) = rsi;
    r12 = r8;
    r13 = rdx;
    rbp = rcx;
    rsi = ML_M8(r8, 0x8);
{
    const uint64_t a = (uint64_t)(ML_M1(rsi, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L30;
    rdx = (uintptr_t)0x141825ca8;
    rcx = rax - 0x40;
    rax = ML_CALL(141823270);
    rcx = rsp + 0x38;
    rax = ML_CALL(1418233f8);
    rax = (uintptr_t)0x141824a60;
    ML_M8(rsp, 0x38) = rax;
    rdx = rsp + 0x78;
    rcx = rsp + 0x50;
    rax = ML_CALL(141823288);
    rax = (uintptr_t)0x141824ba0;
    ML_M8(rsp, 0x38) = rax;
    rdx = (uintptr_t)0x141881e50;
    rcx = rsp + 0x38;
    rax = ML_CALL(1417f3154);
L30:
    rcx = r8;
    rax = ML_CALL(141792240);
    r11 = ML_M8(rsi, 0x0);
{
    const uint64_t a = (uint64_t)(ML_M1(r11, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L37;
    rdi = ML_M8(rsi, 0x10);
    goto L46;
L37:
    rax = ML_M8(rsi, 0x10);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L42;
    rdi = r11;
    goto L46;
L42:
    rcx = ML_M8(r12, 0x8);
    rdi = ML_M8(rcx, 0x10);
{
    const uint64_t a = (uint64_t)(rcx) & ~0ULL, b = (uint64_t)(rsi) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L93;
L46:
    rbx = ML_M8(rsi, 0x8);
{
    const uint64_t a = (uint64_t)(ML_M1(rdi, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L50;
    ML_M8(rdi, 0x8) = rbx;
L50:
    rax = ML_M8(rbp, 0x30);
{
    const uint64_t a = (uint64_t)(ML_M8(rax, 0x8)) & ~0ULL, b = (uint64_t)(rsi) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L55;
    ML_M8(rax, 0x8) = rdi;
    goto L60;
L55:
{
    const uint64_t a = (uint64_t)(ML_M8(rbx, 0x0)) & ~0ULL, b = (uint64_t)(rsi) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L59;
    ML_M8(rbx, 0x0) = rdi;
    goto L60;
L59:
    ML_M8(rbx, 0x10) = rdi;
L60:
    rdx = ML_M8(rbp, 0x30);
{
    const uint64_t a = (uint64_t)(ML_M8(rdx, 0x0)) & ~0ULL, b = (uint64_t)(rsi) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L76;
{
    const uint64_t a = (uint64_t)(ML_M1(rdi, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L67;
    rcx = rbx;
    goto L75;
L67:
    rcx = rdi;
    rax = ML_M8(rdi, 0x0);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L75;
L71:
    rcx = rax;
    rax = ML_M8(rax, 0x0);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L71;
L75:
    ML_M8(rdx, 0x0) = rcx;
L76:
    rdx = ML_M8(rbp, 0x30);
{
    const uint64_t a = (uint64_t)(ML_M8(rdx, 0x10)) & ~0ULL, b = (uint64_t)(rsi) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L130;
{
    const uint64_t a = (uint64_t)(ML_M1(rdi, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L83;
    rcx = rbx;
    goto L91;
L83:
    rcx = rdi;
    rax = ML_M8(rdi, 0x10);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L91;
L87:
    rcx = rax;
    rax = ML_M8(rax, 0x10);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L87;
L91:
    ML_M8(rdx, 0x10) = rcx;
    goto L130;
L93:
    ML_M8(r11, 0x8) = rcx;
    rax = ML_M8(rsi, 0x0);
    ML_M8(rcx, 0x0) = rax;
{
    const uint64_t a = (uint64_t)(rcx) & ~0ULL, b = (uint64_t)(ML_M8(rsi, 0x10)) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L100;
    rbx = rcx;
    goto L109;
L100:
    rbx = ML_M8(rcx, 0x8);
{
    const uint64_t a = (uint64_t)(ML_M1(rdi, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L104;
    ML_M8(rdi, 0x8) = rbx;
L104:
    ML_M8(rbx, 0x0) = rdi;
    rax = ML_M8(rsi, 0x10);
    ML_M8(rcx, 0x10) = rax;
    rax = ML_M8(rsi, 0x10);
    ML_M8(rax, 0x8) = rcx;
L109:
    rax = ML_M8(rbp, 0x30);
{
    const uint64_t a = (uint64_t)(ML_M8(rax, 0x8)) & ~0ULL, b = (uint64_t)(rsi) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L114;
    ML_M8(rax, 0x8) = rcx;
    goto L120;
L114:
    rax = ML_M8(rsi, 0x8);
{
    const uint64_t a = (uint64_t)(ML_M8(rax, 0x0)) & ~0ULL, b = (uint64_t)(rsi) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L119;
    ML_M8(rax, 0x0) = rcx;
    goto L120;
L119:
    ML_M8(rax, 0x10) = rcx;
L120:
    rax = ML_M8(rsi, 0x8);
    ML_M8(rcx, 0x8) = rax;
    rdx = rsi + 0x28;
    r8 = rcx + 0x28;
{
    const uint64_t a = (uint64_t)(r8) & ~0ULL, b = (uint64_t)(rdx) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (f_zf) goto L130;
    rcx = ML_M1(r8, 0x0);
    rax = ML_M1(rdx, 0x0);
    ML_M1(r8, 0x0) = (uint8_t)rax;
    ML_M1(rdx, 0x0) = (uint8_t)rcx;
L130:
{
    const uint64_t a = (uint64_t)(ML_M1(rsi, 0x28)) & 0xFFULL, b = (uint64_t)(0x1ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L225;
    rax = ML_M8(rbp, 0x30);
{
    const uint64_t a = (uint64_t)(rdi) & ~0ULL, b = (uint64_t)(ML_M8(rax, 0x8)) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (f_zf) goto L224;
L135:
{
    const uint64_t a = (uint64_t)(ML_M1(rdi, 0x28)) & 0xFFULL, b = (uint64_t)(0x1ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L224;
    rcx = ML_M8(rbx, 0x0);
{
    const uint64_t a = (uint64_t)(rdi) & ~0ULL, b = (uint64_t)(rcx) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L162;
    rcx = ML_M8(rbx, 0x10);
{
    const uint64_t a = (uint64_t)(ML_M1(rcx, 0x28)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L149;
    ML_M1(rcx, 0x28) = 0x1ULL;
    ML_M1(rbx, 0x28) = 0x0ULL;
    rdx = rbx;
    rcx = rbp;
    rax = ML_CALL(141792160);
    rcx = ML_M8(rbx, 0x10);
L149:
{
    const uint64_t a = (uint64_t)(ML_M1(rcx, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L153;
    rdi = rbx;
    goto L182;
L153:
    rax = ML_M8(rcx, 0x0);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x28)) & 0xFFULL, b = (uint64_t)(0x1ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L187;
    rax = ML_M8(rcx, 0x10);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x28)) & 0xFFULL, b = (uint64_t)(0x1ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L187;
    ML_M1(rcx, 0x28) = 0x0ULL;
    rdi = rbx;
    goto L182;
L162:
{
    const uint64_t a = (uint64_t)(ML_M1(rcx, 0x28)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L170;
    ML_M1(rcx, 0x28) = 0x1ULL;
    ML_M1(rbx, 0x28) = 0x0ULL;
    rdx = rbx;
    rcx = rbp;
    rax = ML_CALL(1417921c0);
    rcx = ML_M8(rbx, 0x0);
L170:
{
    const uint64_t a = (uint64_t)(ML_M1(rcx, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L174;
    rdi = rbx;
    goto L182;
L174:
    rax = ML_M8(rcx, 0x10);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x28)) & 0xFFULL, b = (uint64_t)(0x1ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L206;
    rax = ML_M8(rcx, 0x0);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x28)) & 0xFFULL, b = (uint64_t)(0x1ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L206;
    ML_M1(rcx, 0x28) = 0x0ULL;
    rdi = rbx;
L182:
    rbx = ML_M8(rbx, 0x8);
    rax = ML_M8(rbp, 0x30);
{
    const uint64_t a = (uint64_t)(rdi) & ~0ULL, b = (uint64_t)(ML_M8(rax, 0x8)) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (f_zf) goto L224;
    goto L135;
L187:
    rax = ML_M8(rcx, 0x10);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x28)) & 0xFFULL, b = (uint64_t)(0x1ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L197;
    rax = ML_M8(rcx, 0x0);
    ML_M1(rax, 0x28) = 0x1ULL;
    ML_M1(rcx, 0x28) = 0x0ULL;
    rdx = rcx;
    rcx = rbp;
    rax = ML_CALL(1417921c0);
    rcx = ML_M8(rbx, 0x10);
L197:
    rax = ML_M1(rbx, 0x28);
    ML_M1(rcx, 0x28) = (uint8_t)rax;
    ML_M1(rbx, 0x28) = 0x1ULL;
    rax = ML_M8(rcx, 0x10);
    ML_M1(rax, 0x28) = 0x1ULL;
    rdx = rbx;
    rcx = rbp;
    rax = ML_CALL(141792160);
    goto L224;
L206:
    rax = ML_M8(rcx, 0x0);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x28)) & 0xFFULL, b = (uint64_t)(0x1ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L216;
    rax = ML_M8(rcx, 0x10);
    ML_M1(rax, 0x28) = 0x1ULL;
    ML_M1(rcx, 0x28) = 0x0ULL;
    rdx = rcx;
    rcx = rbp;
    rax = ML_CALL(141792160);
    rcx = ML_M8(rbx, 0x0);
L216:
    rax = ML_M1(rbx, 0x28);
    ML_M1(rcx, 0x28) = (uint8_t)rax;
    ML_M1(rbx, 0x28) = 0x1ULL;
    rax = ML_M8(rcx, 0x0);
    ML_M1(rax, 0x28) = 0x1ULL;
    rdx = rbx;
    rcx = rbp;
    rax = ML_CALL(1417921c0);
L224:
    ML_M1(rdi, 0x28) = 0x1ULL;
L225:
    rcx = rsi;
    rax = ML_CALL(1417f2fdc);
    rax = ML_M8(rbp, 0x38);
{
    const uint64_t r = ((uint64_t)(rax) & ~0ULL) & ((uint64_t)(rax) & ~0ULL);
    f_zf = (r == 0); f_cf = false; f_sf = ((r & 0x8000000000000000ULL) != 0);
    f_of = false;
}
    if (f_zf) goto L232;
    rax = rax - 1;
    ML_M8(rbp, 0x38) = rax;
L232:
    rcx = rsp + 0x20;
    rax = ML_M8(r12, 0x0);
    ML_M8(rcx, 0x0) = rax;
    rax = ML_M8(r12, 0x8);
    ML_M8(rcx, 0x8) = rax;
    rax = ML_M8(rsp, 0x28);
    ML_M8(rsp, 0x28) = rax;
    rax = ML_M8(rbp, 0x0);
    ML_M8(rsp, 0x20) = rax;
    rcx = rsp + 0x20;
    rax = ML_M8(rcx, 0x0);
    ML_M8(r13, 0x0) = rax;
    rax = ML_M8(rcx, 0x8);
    ML_M8(r13, 0x8) = rax;
    rax = r13;
    r11 = rsp + 0xa0;
    rbx = ML_M8(r11, 0x20);
    rbp = ML_M8(r11, 0x28);
    rsi = ML_M8(r11, 0x30);
    rsp = r11;
    { const uint64_t v = ML_M8(rsp, 0); rsp += 8; r13 = v; }
    { const uint64_t v = ML_M8(rsp, 0); rsp += 8; r12 = v; }
    { const uint64_t v = ML_M8(rsp, 0); rsp += 8; rdi = v; }
    return rax;
#undef ML_CALL
    return rax;
}

uint64_t SynLift_1417a6f90(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A) {
    uint64_t rax = 0, rbx = 0, rbp = 0, rsi = 0, rdi = 0, r10 = 0, r11 = 0, r12 = 0, r13 = 0, r14 = 0, r15 = 0;
    uint64_t rcx = rcxA, rdx = rdxA, r8 = r8A, r9 = r9A;
    bool f_zf = false, f_cf = false, f_sf = false, f_of = false;
    uint8_t xmm0[16] = {0}, xmm1[16] = {0}, xmm2[16] = {0}, xmm3[16] = {0}, xmm4[16] = {0}, xmm5[16] = {0};
    alignas(16) uint8_t stkFrame[0x400] = {0};
    uint64_t rsp = (uint64_t)(uintptr_t)(stkFrame + 0x200);
#define ML_CALL(t) g_fnLIFT_##t(rcx, rdx, r8, r9, ML_M8(rsp, 0x20), ML_M8(rsp, 0x28))
    r8 = ML_M8(rdx, 0x0);
    rax = ML_M8(r8, 0x10);
    ML_M8(rdx, 0x0) = rax;
    rax = ML_M8(r8, 0x10);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L7;
    ML_M8(rax, 0x8) = rdx;
L7:
    rax = ML_M8(rdx, 0x8);
    ML_M8(r8, 0x8) = rax;
    rax = ML_M8(rcx, 0x30);
{
    const uint64_t a = (uint64_t)(rdx) & ~0ULL, b = (uint64_t)(ML_M8(rax, 0x8)) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L16;
    ML_M8(rax, 0x8) = r8;
    ML_M8(r8, 0x10) = rdx;
    ML_M8(rdx, 0x8) = r8;
    return rax;
L16:
    rax = ML_M8(rdx, 0x8);
{
    const uint64_t a = (uint64_t)(rdx) & ~0ULL, b = (uint64_t)(ML_M8(rax, 0x10)) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L23;
    ML_M8(rax, 0x10) = r8;
    ML_M8(r8, 0x10) = rdx;
    ML_M8(rdx, 0x8) = r8;
    return rax;
L23:
    ML_M8(rax, 0x0) = r8;
    ML_M8(r8, 0x10) = rdx;
    ML_M8(rdx, 0x8) = r8;
    return rax;
#undef ML_CALL
    return rax;
}

uint64_t SynLift_1417a70b0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A) {
    uint64_t rax = 0, rbx = 0, rbp = 0, rsi = 0, rdi = 0, r10 = 0, r11 = 0, r12 = 0, r13 = 0, r14 = 0, r15 = 0;
    uint64_t rcx = rcxA, rdx = rdxA, r8 = r8A, r9 = r9A;
    bool f_zf = false, f_cf = false, f_sf = false, f_of = false;
    uint8_t xmm0[16] = {0}, xmm1[16] = {0}, xmm2[16] = {0}, xmm3[16] = {0}, xmm4[16] = {0}, xmm5[16] = {0};
    alignas(16) uint8_t stkFrame[0x400] = {0};
    uint64_t rsp = (uint64_t)(uintptr_t)(stkFrame + 0x200);
#define ML_CALL(t) g_fnLIFT_##t(rcx, rdx, r8, r9, ML_M8(rsp, 0x20), ML_M8(rsp, 0x28))
    rsp -= 8; ML_M8(rsp, 0) = rbx;
    rsp = rsp - (0x20ULL);
{
    const uint64_t a = (uint64_t)(ML_M8(rcx, 0x0)) & ~0ULL, b = (uint64_t)(0x0ULL) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    rbx = rcx;
    if (!f_zf) goto L6;
    rax = ML_CALL(1418233c0);
L6:
    rcx = ML_M8(rbx, 0x8);
{
    const uint64_t a = (uint64_t)(ML_M1(rcx, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L12;
    rsp = rsp + (0x20ULL);
    { const uint64_t v = ML_M8(rsp, 0); rsp += 8; rbx = v; }
    return ML_CALL(1418233c0);   // tail call
L12:
    rax = ML_M8(rcx, 0x10);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L27;
    rcx = ML_M8(rax, 0x0);
{
    const uint64_t a = (uint64_t)(ML_M1(rcx, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L23;
    ;
L19:
    rax = rcx;
    rcx = ML_M8(rcx, 0x0);
{
    const uint64_t a = (uint64_t)(ML_M1(rcx, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L19;
L23:
    ML_M8(rbx, 0x8) = rax;
    rsp = rsp + (0x20ULL);
    { const uint64_t v = ML_M8(rsp, 0); rsp += 8; rbx = v; }
    return rax;
L27:
    rcx = ML_M8(rcx, 0x8);
{
    const uint64_t a = (uint64_t)(ML_M1(rcx, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L37;
L30:
    rax = ML_M8(rcx, 0x10);
{
    const uint64_t a = (uint64_t)(ML_M8(rbx, 0x8)) & ~0ULL, b = (uint64_t)(rax) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L37;
    ML_M8(rbx, 0x8) = rcx;
    rcx = ML_M8(rcx, 0x8);
{
    const uint64_t a = (uint64_t)(ML_M1(rcx, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L30;
L37:
    ML_M8(rbx, 0x8) = rcx;
    rsp = rsp + (0x20ULL);
    { const uint64_t v = ML_M8(rsp, 0); rsp += 8; rbx = v; }
    return rax;
#undef ML_CALL
    return rax;
}

uint64_t SynLift_1417a7320(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A) {
    uint64_t rax = 0, rbx = 0, rbp = 0, rsi = 0, rdi = 0, r10 = 0, r11 = 0, r12 = 0, r13 = 0, r14 = 0, r15 = 0;
    uint64_t rcx = rcxA, rdx = rdxA, r8 = r8A, r9 = r9A;
    bool f_zf = false, f_cf = false, f_sf = false, f_of = false;
    uint8_t xmm0[16] = {0}, xmm1[16] = {0}, xmm2[16] = {0}, xmm3[16] = {0}, xmm4[16] = {0}, xmm5[16] = {0};
    alignas(16) uint8_t stkFrame[0x400] = {0};
    uint64_t rsp = (uint64_t)(uintptr_t)(stkFrame + 0x200);
#define ML_CALL(t) g_fnLIFT_##t(rcx, rdx, r8, r9, ML_M8(rsp, 0x20), ML_M8(rsp, 0x28))
    r8 = ML_M8(rdx, 0x10);
    rax = ML_M8(r8, 0x0);
    ML_M8(rdx, 0x10) = rax;
    rax = ML_M8(r8, 0x0);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L7;
    ML_M8(rax, 0x8) = rdx;
L7:
    rax = ML_M8(rdx, 0x8);
    ML_M8(r8, 0x8) = rax;
    rax = ML_M8(rcx, 0x30);
{
    const uint64_t a = (uint64_t)(rdx) & ~0ULL, b = (uint64_t)(ML_M8(rax, 0x8)) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L16;
    ML_M8(rax, 0x8) = r8;
    ML_M8(r8, 0x0) = rdx;
    ML_M8(rdx, 0x8) = r8;
    return rax;
L16:
    rax = ML_M8(rdx, 0x8);
{
    const uint64_t a = (uint64_t)(rdx) & ~0ULL, b = (uint64_t)(ML_M8(rax, 0x0)) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L23;
    ML_M8(rax, 0x0) = r8;
    ML_M8(r8, 0x0) = rdx;
    ML_M8(rdx, 0x8) = r8;
    return rax;
L23:
    ML_M8(rax, 0x10) = r8;
    ML_M8(r8, 0x0) = rdx;
    ML_M8(rdx, 0x8) = r8;
    return rax;
#undef ML_CALL
    return rax;
}

__attribute__((weak)) uint64_t (*g_fnLIFT_1417a6f90)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t) = nullptr;
__attribute__((weak)) uint64_t (*g_fnLIFT_1417a70b0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t) = nullptr;
__attribute__((weak)) uint64_t (*g_fnLIFT_1417a7320)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t) = nullptr;
uint64_t SynLift_1417a8160(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A) {
    uint64_t rax = 0, rbx = 0, rbp = 0, rsi = 0, rdi = 0, r10 = 0, r11 = 0, r12 = 0, r13 = 0, r14 = 0, r15 = 0;
    uint64_t rcx = rcxA, rdx = rdxA, r8 = r8A, r9 = r9A;
    bool f_zf = false, f_cf = false, f_sf = false, f_of = false;
    uint8_t xmm0[16] = {0}, xmm1[16] = {0}, xmm2[16] = {0}, xmm3[16] = {0}, xmm4[16] = {0}, xmm5[16] = {0};
    alignas(16) uint8_t stkFrame[0x400] = {0};
    uint64_t rsp = (uint64_t)(uintptr_t)(stkFrame + 0x200);
#define ML_CALL(t) g_fnLIFT_##t(rcx, rdx, r8, r9, ML_M8(rsp, 0x20), ML_M8(rsp, 0x28))
    rax = rsp;
    rsp -= 8; ML_M8(rsp, 0) = rdi;
    rsp -= 8; ML_M8(rsp, 0) = r12;
    rsp -= 8; ML_M8(rsp, 0) = r13;
    rsp = rsp - (0xa0ULL);
    ML_M8(rsp, 0x30) = 0xfffffffffffffffeULL;
    ML_M8(rax, 0x8) = rbx;
    ML_M8(rax, 0x10) = rbp;
    ML_M8(rax, 0x18) = rsi;
    r12 = r8;
    r13 = rdx;
    rbp = rcx;
    rsi = ML_M8(r8, 0x8);
{
    const uint64_t a = (uint64_t)(ML_M1(rsi, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L30;
    rdx = (uintptr_t)0x141825ca8;
    rcx = rax - 0x40;
    rax = ML_CALL(141823270);
    rcx = rsp + 0x38;
    rax = ML_CALL(1418233f8);
    rax = (uintptr_t)0x141824a60;
    ML_M8(rsp, 0x38) = rax;
    rdx = rsp + 0x78;
    rcx = rsp + 0x50;
    rax = ML_CALL(141823288);
    rax = (uintptr_t)0x141824ba0;
    ML_M8(rsp, 0x38) = rax;
    rdx = (uintptr_t)0x141881e50;
    rcx = rsp + 0x38;
    rax = ML_CALL(1417f3154);
L30:
    rcx = r8;
    rax = ML_CALL(1417a70b0);
    r11 = ML_M8(rsi, 0x0);
{
    const uint64_t a = (uint64_t)(ML_M1(r11, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L37;
    rdi = ML_M8(rsi, 0x10);
    goto L46;
L37:
    rax = ML_M8(rsi, 0x10);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L42;
    rdi = r11;
    goto L46;
L42:
    rcx = ML_M8(r12, 0x8);
    rdi = ML_M8(rcx, 0x10);
{
    const uint64_t a = (uint64_t)(rcx) & ~0ULL, b = (uint64_t)(rsi) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L93;
L46:
    rbx = ML_M8(rsi, 0x8);
{
    const uint64_t a = (uint64_t)(ML_M1(rdi, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L50;
    ML_M8(rdi, 0x8) = rbx;
L50:
    rax = ML_M8(rbp, 0x30);
{
    const uint64_t a = (uint64_t)(ML_M8(rax, 0x8)) & ~0ULL, b = (uint64_t)(rsi) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L55;
    ML_M8(rax, 0x8) = rdi;
    goto L60;
L55:
{
    const uint64_t a = (uint64_t)(ML_M8(rbx, 0x0)) & ~0ULL, b = (uint64_t)(rsi) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L59;
    ML_M8(rbx, 0x0) = rdi;
    goto L60;
L59:
    ML_M8(rbx, 0x10) = rdi;
L60:
    rdx = ML_M8(rbp, 0x30);
{
    const uint64_t a = (uint64_t)(ML_M8(rdx, 0x0)) & ~0ULL, b = (uint64_t)(rsi) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L76;
{
    const uint64_t a = (uint64_t)(ML_M1(rdi, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L67;
    rcx = rbx;
    goto L75;
L67:
    rcx = rdi;
    rax = ML_M8(rdi, 0x0);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L75;
L71:
    rcx = rax;
    rax = ML_M8(rax, 0x0);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L71;
L75:
    ML_M8(rdx, 0x0) = rcx;
L76:
    rdx = ML_M8(rbp, 0x30);
{
    const uint64_t a = (uint64_t)(ML_M8(rdx, 0x10)) & ~0ULL, b = (uint64_t)(rsi) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L130;
{
    const uint64_t a = (uint64_t)(ML_M1(rdi, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L83;
    rcx = rbx;
    goto L91;
L83:
    rcx = rdi;
    rax = ML_M8(rdi, 0x10);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L91;
L87:
    rcx = rax;
    rax = ML_M8(rax, 0x10);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L87;
L91:
    ML_M8(rdx, 0x10) = rcx;
    goto L130;
L93:
    ML_M8(r11, 0x8) = rcx;
    rax = ML_M8(rsi, 0x0);
    ML_M8(rcx, 0x0) = rax;
{
    const uint64_t a = (uint64_t)(rcx) & ~0ULL, b = (uint64_t)(ML_M8(rsi, 0x10)) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L100;
    rbx = rcx;
    goto L109;
L100:
    rbx = ML_M8(rcx, 0x8);
{
    const uint64_t a = (uint64_t)(ML_M1(rdi, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L104;
    ML_M8(rdi, 0x8) = rbx;
L104:
    ML_M8(rbx, 0x0) = rdi;
    rax = ML_M8(rsi, 0x10);
    ML_M8(rcx, 0x10) = rax;
    rax = ML_M8(rsi, 0x10);
    ML_M8(rax, 0x8) = rcx;
L109:
    rax = ML_M8(rbp, 0x30);
{
    const uint64_t a = (uint64_t)(ML_M8(rax, 0x8)) & ~0ULL, b = (uint64_t)(rsi) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L114;
    ML_M8(rax, 0x8) = rcx;
    goto L120;
L114:
    rax = ML_M8(rsi, 0x8);
{
    const uint64_t a = (uint64_t)(ML_M8(rax, 0x0)) & ~0ULL, b = (uint64_t)(rsi) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L119;
    ML_M8(rax, 0x0) = rcx;
    goto L120;
L119:
    ML_M8(rax, 0x10) = rcx;
L120:
    rax = ML_M8(rsi, 0x8);
    ML_M8(rcx, 0x8) = rax;
    rdx = rsi + 0x28;
    r8 = rcx + 0x28;
{
    const uint64_t a = (uint64_t)(r8) & ~0ULL, b = (uint64_t)(rdx) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (f_zf) goto L130;
    rcx = ML_M1(r8, 0x0);
    rax = ML_M1(rdx, 0x0);
    ML_M1(r8, 0x0) = (uint8_t)rax;
    ML_M1(rdx, 0x0) = (uint8_t)rcx;
L130:
{
    const uint64_t a = (uint64_t)(ML_M1(rsi, 0x28)) & 0xFFULL, b = (uint64_t)(0x1ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L225;
    rax = ML_M8(rbp, 0x30);
{
    const uint64_t a = (uint64_t)(rdi) & ~0ULL, b = (uint64_t)(ML_M8(rax, 0x8)) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (f_zf) goto L224;
L135:
{
    const uint64_t a = (uint64_t)(ML_M1(rdi, 0x28)) & 0xFFULL, b = (uint64_t)(0x1ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L224;
    rcx = ML_M8(rbx, 0x0);
{
    const uint64_t a = (uint64_t)(rdi) & ~0ULL, b = (uint64_t)(rcx) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L162;
    rcx = ML_M8(rbx, 0x10);
{
    const uint64_t a = (uint64_t)(ML_M1(rcx, 0x28)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L149;
    ML_M1(rcx, 0x28) = 0x1ULL;
    ML_M1(rbx, 0x28) = 0x0ULL;
    rdx = rbx;
    rcx = rbp;
    rax = ML_CALL(1417a7320);
    rcx = ML_M8(rbx, 0x10);
L149:
{
    const uint64_t a = (uint64_t)(ML_M1(rcx, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L153;
    rdi = rbx;
    goto L182;
L153:
    rax = ML_M8(rcx, 0x0);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x28)) & 0xFFULL, b = (uint64_t)(0x1ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L187;
    rax = ML_M8(rcx, 0x10);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x28)) & 0xFFULL, b = (uint64_t)(0x1ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L187;
    ML_M1(rcx, 0x28) = 0x0ULL;
    rdi = rbx;
    goto L182;
L162:
{
    const uint64_t a = (uint64_t)(ML_M1(rcx, 0x28)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L170;
    ML_M1(rcx, 0x28) = 0x1ULL;
    ML_M1(rbx, 0x28) = 0x0ULL;
    rdx = rbx;
    rcx = rbp;
    rax = ML_CALL(1417a6f90);
    rcx = ML_M8(rbx, 0x0);
L170:
{
    const uint64_t a = (uint64_t)(ML_M1(rcx, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L174;
    rdi = rbx;
    goto L182;
L174:
    rax = ML_M8(rcx, 0x10);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x28)) & 0xFFULL, b = (uint64_t)(0x1ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L206;
    rax = ML_M8(rcx, 0x0);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x28)) & 0xFFULL, b = (uint64_t)(0x1ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L206;
    ML_M1(rcx, 0x28) = 0x0ULL;
    rdi = rbx;
L182:
    rbx = ML_M8(rbx, 0x8);
    rax = ML_M8(rbp, 0x30);
{
    const uint64_t a = (uint64_t)(rdi) & ~0ULL, b = (uint64_t)(ML_M8(rax, 0x8)) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (f_zf) goto L224;
    goto L135;
L187:
    rax = ML_M8(rcx, 0x10);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x28)) & 0xFFULL, b = (uint64_t)(0x1ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L197;
    rax = ML_M8(rcx, 0x0);
    ML_M1(rax, 0x28) = 0x1ULL;
    ML_M1(rcx, 0x28) = 0x0ULL;
    rdx = rcx;
    rcx = rbp;
    rax = ML_CALL(1417a6f90);
    rcx = ML_M8(rbx, 0x10);
L197:
    rax = ML_M1(rbx, 0x28);
    ML_M1(rcx, 0x28) = (uint8_t)rax;
    ML_M1(rbx, 0x28) = 0x1ULL;
    rax = ML_M8(rcx, 0x10);
    ML_M1(rax, 0x28) = 0x1ULL;
    rdx = rbx;
    rcx = rbp;
    rax = ML_CALL(1417a7320);
    goto L224;
L206:
    rax = ML_M8(rcx, 0x0);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x28)) & 0xFFULL, b = (uint64_t)(0x1ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L216;
    rax = ML_M8(rcx, 0x10);
    ML_M1(rax, 0x28) = 0x1ULL;
    ML_M1(rcx, 0x28) = 0x0ULL;
    rdx = rcx;
    rcx = rbp;
    rax = ML_CALL(1417a7320);
    rcx = ML_M8(rbx, 0x0);
L216:
    rax = ML_M1(rbx, 0x28);
    ML_M1(rcx, 0x28) = (uint8_t)rax;
    ML_M1(rbx, 0x28) = 0x1ULL;
    rax = ML_M8(rcx, 0x0);
    ML_M1(rax, 0x28) = 0x1ULL;
    rdx = rbx;
    rcx = rbp;
    rax = ML_CALL(1417a6f90);
L224:
    ML_M1(rdi, 0x28) = 0x1ULL;
L225:
    rcx = rsi;
    rax = ML_CALL(1417f2fdc);
    rax = ML_M8(rbp, 0x38);
{
    const uint64_t r = ((uint64_t)(rax) & ~0ULL) & ((uint64_t)(rax) & ~0ULL);
    f_zf = (r == 0); f_cf = false; f_sf = ((r & 0x8000000000000000ULL) != 0);
    f_of = false;
}
    if (f_zf) goto L232;
    rax = rax - 1;
    ML_M8(rbp, 0x38) = rax;
L232:
    rcx = rsp + 0x20;
    rax = ML_M8(r12, 0x0);
    ML_M8(rcx, 0x0) = rax;
    rax = ML_M8(r12, 0x8);
    ML_M8(rcx, 0x8) = rax;
    rax = ML_M8(rsp, 0x28);
    ML_M8(rsp, 0x28) = rax;
    rax = ML_M8(rbp, 0x0);
    ML_M8(rsp, 0x20) = rax;
    rcx = rsp + 0x20;
    rax = ML_M8(rcx, 0x0);
    ML_M8(r13, 0x0) = rax;
    rax = ML_M8(rcx, 0x8);
    ML_M8(r13, 0x8) = rax;
    rax = r13;
    r11 = rsp + 0xa0;
    rbx = ML_M8(r11, 0x20);
    rbp = ML_M8(r11, 0x28);
    rsi = ML_M8(r11, 0x30);
    rsp = r11;
    { const uint64_t v = ML_M8(rsp, 0); rsp += 8; r13 = v; }
    { const uint64_t v = ML_M8(rsp, 0); rsp += 8; r12 = v; }
    { const uint64_t v = ML_M8(rsp, 0); rsp += 8; rdi = v; }
    return rax;
#undef ML_CALL
    return rax;
}

__attribute__((weak)) uint64_t (*g_fnLIFT_1417293c0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t) = nullptr;
uint64_t SynLift_14172ae00(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A) {
    uint64_t rax = 0, rbx = 0, rbp = 0, rsi = 0, rdi = 0, r10 = 0, r11 = 0, r12 = 0, r13 = 0, r14 = 0, r15 = 0;
    uint64_t rcx = rcxA, rdx = rdxA, r8 = r8A, r9 = r9A;
    bool f_zf = false, f_cf = false, f_sf = false, f_of = false;
    uint8_t xmm0[16] = {0}, xmm1[16] = {0}, xmm2[16] = {0}, xmm3[16] = {0}, xmm4[16] = {0}, xmm5[16] = {0};
    alignas(16) uint8_t stkFrame[0x400] = {0};
    uint64_t rsp = (uint64_t)(uintptr_t)(stkFrame + 0x200);
#define ML_CALL(t) g_fnLIFT_##t(rcx, rdx, r8, r9, ML_M8(rsp, 0x20), ML_M8(rsp, 0x28))
    ML_M8(rsp, 0x10) = rbx;
    ML_M8(rsp, 0x18) = rbp;
    rsp -= 8; ML_M8(rsp, 0) = rsi;
    rsp -= 8; ML_M8(rsp, 0) = rdi;
    rsp -= 8; ML_M8(rsp, 0) = r12;
    rsp -= 8; ML_M8(rsp, 0) = r14;
    rsp -= 8; ML_M8(rsp, 0) = r15;
    rsp = rsp - (0x40ULL);
    rdi = ML_M8(rcx, 0x30);
    r14 = r8;
    r12 = rdx;
    rax = ML_M8(rdi, 0x8);
    r15 = rcx;
    rbp = (rbp & ~(uint64_t)0xFFULL) | (uint64_t)(uint8_t)(0x1ULL);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x1d)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L28;
    r9 = (uint64_t)(uint32_t)(ML_M4(r8, 0x0));
    /* padding */
L18:
{
    const uint64_t a = (uint64_t)((uint32_t)r9) & 0xFFFFFFFFULL, b = (uint64_t)(ML_M4(rax, 0x18)) & 0xFFFFFFFFULL;
    const uint64_t d = (a - b) & 0xFFFFFFFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80000000ULL) != 0);
}
    rdi = rax;
    rbp = (rbp & ~(uint64_t)0xFFULL) | (uint64_t)(uint8_t)((f_cf) ? 1 : 0);
{
    const uint64_t r = ((uint64_t)((uint8_t)rbp) & 0xFFULL) & ((uint64_t)((uint8_t)rbp) & 0xFFULL);
    f_zf = (r == 0); f_cf = false; f_sf = ((r & 0x80ULL) != 0);
    f_of = false;
}
    if (f_zf) goto L25;
    rax = ML_M8(rax, 0x0);
    goto L26;
L25:
    rax = ML_M8(rax, 0x10);
L26:
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x1d)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L18;
L28:
    rsi = ML_M8(rcx, 0x0);
    rbx = rdi;
    ML_M8(rsp, 0x30) = rsi;
    ML_M8(rsp, 0x38) = rbx;
{
    const uint64_t r = ((uint64_t)((uint8_t)rbp) & 0xFFULL) & ((uint64_t)((uint8_t)rbp) & 0xFFULL);
    f_zf = (r == 0); f_cf = false; f_sf = ((r & 0x80ULL) != 0);
    f_of = false;
}
    if (f_zf) goto L98;
    rax = ML_M8(rcx, 0x30);
    ML_M8(rsp, 0x70) = r13;
    r13 = ML_M8(rax, 0x0);
{
    const uint64_t r = ((uint64_t)(rsi) & ~0ULL) & ((uint64_t)(rsi) & ~0ULL);
    f_zf = (r == 0); f_cf = false; f_sf = ((r & 0x8000000000000000ULL) != 0);
    f_of = false;
}
    if (f_zf) goto L41;
{
    const uint64_t a = (uint64_t)(rsi) & ~0ULL, b = (uint64_t)(rsi) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (f_zf) goto L42;
L41:
    rax = ML_CALL(1418233c0);
L42:
{
    const uint64_t a = (uint64_t)(rdi) & ~0ULL, b = (uint64_t)(r13) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    r13 = ML_M8(rsp, 0x70);
    if (!f_zf) goto L56;
    ML_M8(rsp, 0x20) = r14;
    r9 = rdi;
    r8 = (r8 & ~(uint64_t)0xFFULL) | (uint64_t)(uint8_t)(0x1ULL);
L48:
    rdx = rsp + 0x30;
    rcx = r15;
    rax = ML_CALL(1417293c0);
    ML_M1(r12, 0x10) = 0x1ULL;
    rcx = ML_M8(rax, 0x0);
    rax = ML_M8(rax, 0x8);
    ML_M8(r12, 0x0) = rcx;
    goto L110;
L56:
{
    const uint64_t r = ((uint64_t)(rsi) & ~0ULL) & ((uint64_t)(rsi) & ~0ULL);
    f_zf = (r == 0); f_cf = false; f_sf = ((r & 0x8000000000000000ULL) != 0);
    f_of = false;
}
    if (!f_zf) goto L59;
    rax = ML_CALL(1418233c0);
L59:
{
    const uint64_t a = (uint64_t)(ML_M1(rdi, 0x1d)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L67;
    rbx = ML_M8(rdi, 0x10);
    ML_M8(rsp, 0x38) = rbx;
{
    const uint64_t a = (uint64_t)(ML_M1(rbx, 0x1d)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L98;
    rax = ML_CALL(1418233c0);
    goto L98;
L67:
    rax = ML_M8(rdi, 0x0);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x1d)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L81;
    rbx = rax;
    rax = ML_M8(rax, 0x10);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x1d)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L79;
    /* padding */
L75:
    rbx = rax;
    rax = ML_M8(rax, 0x10);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x1d)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L75;
L79:
    ML_M8(rsp, 0x38) = rbx;
    goto L98;
L81:
    rax = ML_M8(rdi, 0x8);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x1d)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L92;
    ;
L85:
{
    const uint64_t a = (uint64_t)(rbx) & ~0ULL, b = (uint64_t)(ML_M8(rax, 0x0)) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L92;
    rbx = rax;
    ML_M8(rsp, 0x38) = rax;
    rax = ML_M8(rax, 0x8);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x1d)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L85;
L92:
{
    const uint64_t a = (uint64_t)(ML_M1(rbx, 0x1d)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L96;
    rax = ML_CALL(1418233c0);
    goto L98;
L96:
    rbx = rax;
    ML_M8(rsp, 0x38) = rax;
L98:
    rax = (uint64_t)(uint32_t)(ML_M4(r14, 0x0));
{
    const uint64_t a = (uint64_t)(ML_M4(rbx, 0x18)) & 0xFFFFFFFFULL, b = (uint64_t)((uint32_t)rax) & 0xFFFFFFFFULL;
    const uint64_t d = (a - b) & 0xFFFFFFFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80000000ULL) != 0);
}
    if (!f_cf) goto L105;
    ML_M8(rsp, 0x20) = r14;
    r9 = rdi;
    r8 = (uint8_t)rbp;
    goto L48;
L105:
    rcx = rsp + 0x30;
    ML_M1(r12, 0x10) = 0x0ULL;
    rax = ML_M8(rcx, 0x0);
    ML_M8(r12, 0x0) = rax;
    rax = ML_M8(rcx, 0x8);
L110:
    rbx = ML_M8(rsp, 0x78);
    rbp = ML_M8(rsp, 0x80);
    ML_M8(r12, 0x8) = rax;
    rax = r12;
    rsp = rsp + (0x40ULL);
    { const uint64_t v = ML_M8(rsp, 0); rsp += 8; r15 = v; }
    { const uint64_t v = ML_M8(rsp, 0); rsp += 8; r14 = v; }
    { const uint64_t v = ML_M8(rsp, 0); rsp += 8; r12 = v; }
    { const uint64_t v = ML_M8(rsp, 0); rsp += 8; rdi = v; }
    { const uint64_t v = ML_M8(rsp, 0); rsp += 8; rsi = v; }
    return rax;
#undef ML_CALL
    return rax;
}

__attribute__((weak)) uint64_t (*g_fnLIFT_141729790)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t) = nullptr;
uint64_t SynLift_14172afb0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A) {
    uint64_t rax = 0, rbx = 0, rbp = 0, rsi = 0, rdi = 0, r10 = 0, r11 = 0, r12 = 0, r13 = 0, r14 = 0, r15 = 0;
    uint64_t rcx = rcxA, rdx = rdxA, r8 = r8A, r9 = r9A;
    bool f_zf = false, f_cf = false, f_sf = false, f_of = false;
    uint8_t xmm0[16] = {0}, xmm1[16] = {0}, xmm2[16] = {0}, xmm3[16] = {0}, xmm4[16] = {0}, xmm5[16] = {0};
    alignas(16) uint8_t stkFrame[0x400] = {0};
    uint64_t rsp = (uint64_t)(uintptr_t)(stkFrame + 0x200);
#define ML_CALL(t) g_fnLIFT_##t(rcx, rdx, r8, r9, ML_M8(rsp, 0x20), ML_M8(rsp, 0x28))
    ML_M8(rsp, 0x10) = rbx;
    ML_M8(rsp, 0x18) = rbp;
    rsp -= 8; ML_M8(rsp, 0) = rsi;
    rsp -= 8; ML_M8(rsp, 0) = rdi;
    rsp -= 8; ML_M8(rsp, 0) = r12;
    rsp -= 8; ML_M8(rsp, 0) = r14;
    rsp -= 8; ML_M8(rsp, 0) = r15;
    rsp = rsp - (0x40ULL);
    rdi = ML_M8(rcx, 0x30);
    r14 = r8;
    r12 = rdx;
    rax = ML_M8(rdi, 0x8);
    r15 = rcx;
    rbp = (rbp & ~(uint64_t)0xFFULL) | (uint64_t)(uint8_t)(0x1ULL);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L28;
    r9 = (uint64_t)(uint32_t)(ML_M4(r8, 0x0));
    /* padding */
L18:
{
    const uint64_t a = (uint64_t)((uint32_t)r9) & 0xFFFFFFFFULL, b = (uint64_t)(ML_M4(rax, 0x18)) & 0xFFFFFFFFULL;
    const uint64_t d = (a - b) & 0xFFFFFFFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80000000ULL) != 0);
}
    rdi = rax;
    rbp = (rbp & ~(uint64_t)0xFFULL) | (uint64_t)(uint8_t)((f_cf) ? 1 : 0);
{
    const uint64_t r = ((uint64_t)((uint8_t)rbp) & 0xFFULL) & ((uint64_t)((uint8_t)rbp) & 0xFFULL);
    f_zf = (r == 0); f_cf = false; f_sf = ((r & 0x80ULL) != 0);
    f_of = false;
}
    if (f_zf) goto L25;
    rax = ML_M8(rax, 0x0);
    goto L26;
L25:
    rax = ML_M8(rax, 0x10);
L26:
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L18;
L28:
    rsi = ML_M8(rcx, 0x0);
    rbx = rdi;
    ML_M8(rsp, 0x30) = rsi;
    ML_M8(rsp, 0x38) = rbx;
{
    const uint64_t r = ((uint64_t)((uint8_t)rbp) & 0xFFULL) & ((uint64_t)((uint8_t)rbp) & 0xFFULL);
    f_zf = (r == 0); f_cf = false; f_sf = ((r & 0x80ULL) != 0);
    f_of = false;
}
    if (f_zf) goto L98;
    rax = ML_M8(rcx, 0x30);
    ML_M8(rsp, 0x70) = r13;
    r13 = ML_M8(rax, 0x0);
{
    const uint64_t r = ((uint64_t)(rsi) & ~0ULL) & ((uint64_t)(rsi) & ~0ULL);
    f_zf = (r == 0); f_cf = false; f_sf = ((r & 0x8000000000000000ULL) != 0);
    f_of = false;
}
    if (f_zf) goto L41;
{
    const uint64_t a = (uint64_t)(rsi) & ~0ULL, b = (uint64_t)(rsi) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (f_zf) goto L42;
L41:
    rax = ML_CALL(1418233c0);
L42:
{
    const uint64_t a = (uint64_t)(rdi) & ~0ULL, b = (uint64_t)(r13) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    r13 = ML_M8(rsp, 0x70);
    if (!f_zf) goto L56;
    ML_M8(rsp, 0x20) = r14;
    r9 = rdi;
    r8 = (r8 & ~(uint64_t)0xFFULL) | (uint64_t)(uint8_t)(0x1ULL);
L48:
    rdx = rsp + 0x30;
    rcx = r15;
    rax = ML_CALL(141729790);
    ML_M1(r12, 0x10) = 0x1ULL;
    rcx = ML_M8(rax, 0x0);
    rax = ML_M8(rax, 0x8);
    ML_M8(r12, 0x0) = rcx;
    goto L110;
L56:
{
    const uint64_t r = ((uint64_t)(rsi) & ~0ULL) & ((uint64_t)(rsi) & ~0ULL);
    f_zf = (r == 0); f_cf = false; f_sf = ((r & 0x8000000000000000ULL) != 0);
    f_of = false;
}
    if (!f_zf) goto L59;
    rax = ML_CALL(1418233c0);
L59:
{
    const uint64_t a = (uint64_t)(ML_M1(rdi, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L67;
    rbx = ML_M8(rdi, 0x10);
    ML_M8(rsp, 0x38) = rbx;
{
    const uint64_t a = (uint64_t)(ML_M1(rbx, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L98;
    rax = ML_CALL(1418233c0);
    goto L98;
L67:
    rax = ML_M8(rdi, 0x0);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L81;
    rbx = rax;
    rax = ML_M8(rax, 0x10);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L79;
    /* padding */
L75:
    rbx = rax;
    rax = ML_M8(rax, 0x10);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L75;
L79:
    ML_M8(rsp, 0x38) = rbx;
    goto L98;
L81:
    rax = ML_M8(rdi, 0x8);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L92;
    ;
L85:
{
    const uint64_t a = (uint64_t)(rbx) & ~0ULL, b = (uint64_t)(ML_M8(rax, 0x0)) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L92;
    rbx = rax;
    ML_M8(rsp, 0x38) = rax;
    rax = ML_M8(rax, 0x8);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L85;
L92:
{
    const uint64_t a = (uint64_t)(ML_M1(rbx, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L96;
    rax = ML_CALL(1418233c0);
    goto L98;
L96:
    rbx = rax;
    ML_M8(rsp, 0x38) = rax;
L98:
    rax = (uint64_t)(uint32_t)(ML_M4(r14, 0x0));
{
    const uint64_t a = (uint64_t)(ML_M4(rbx, 0x18)) & 0xFFFFFFFFULL, b = (uint64_t)((uint32_t)rax) & 0xFFFFFFFFULL;
    const uint64_t d = (a - b) & 0xFFFFFFFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80000000ULL) != 0);
}
    if (!f_cf) goto L105;
    ML_M8(rsp, 0x20) = r14;
    r9 = rdi;
    r8 = (uint8_t)rbp;
    goto L48;
L105:
    rcx = rsp + 0x30;
    ML_M1(r12, 0x10) = 0x0ULL;
    rax = ML_M8(rcx, 0x0);
    ML_M8(r12, 0x0) = rax;
    rax = ML_M8(rcx, 0x8);
L110:
    rbx = ML_M8(rsp, 0x78);
    rbp = ML_M8(rsp, 0x80);
    ML_M8(r12, 0x8) = rax;
    rax = r12;
    rsp = rsp + (0x40ULL);
    { const uint64_t v = ML_M8(rsp, 0); rsp += 8; r15 = v; }
    { const uint64_t v = ML_M8(rsp, 0); rsp += 8; r14 = v; }
    { const uint64_t v = ML_M8(rsp, 0); rsp += 8; r12 = v; }
    { const uint64_t v = ML_M8(rsp, 0); rsp += 8; rdi = v; }
    { const uint64_t v = ML_M8(rsp, 0); rsp += 8; rsi = v; }
    return rax;
#undef ML_CALL
    return rax;
}

__attribute__((weak)) uint64_t (*g_fnLIFT_141729ba0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t) = nullptr;
uint64_t SynLift_14172b6c0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A) {
    uint64_t rax = 0, rbx = 0, rbp = 0, rsi = 0, rdi = 0, r10 = 0, r11 = 0, r12 = 0, r13 = 0, r14 = 0, r15 = 0;
    uint64_t rcx = rcxA, rdx = rdxA, r8 = r8A, r9 = r9A;
    bool f_zf = false, f_cf = false, f_sf = false, f_of = false;
    uint8_t xmm0[16] = {0}, xmm1[16] = {0}, xmm2[16] = {0}, xmm3[16] = {0}, xmm4[16] = {0}, xmm5[16] = {0};
    alignas(16) uint8_t stkFrame[0x400] = {0};
    uint64_t rsp = (uint64_t)(uintptr_t)(stkFrame + 0x200);
#define ML_CALL(t) g_fnLIFT_##t(rcx, rdx, r8, r9, ML_M8(rsp, 0x20), ML_M8(rsp, 0x28))
    ML_M8(rsp, 0x10) = rbx;
    ML_M8(rsp, 0x18) = rbp;
    rsp -= 8; ML_M8(rsp, 0) = rsi;
    rsp -= 8; ML_M8(rsp, 0) = rdi;
    rsp -= 8; ML_M8(rsp, 0) = r12;
    rsp -= 8; ML_M8(rsp, 0) = r14;
    rsp -= 8; ML_M8(rsp, 0) = r15;
    rsp = rsp - (0x40ULL);
    rdi = ML_M8(rcx, 0x30);
    r14 = r8;
    r12 = rdx;
    rax = ML_M8(rdi, 0x8);
    r15 = rcx;
    rbp = (rbp & ~(uint64_t)0xFFULL) | (uint64_t)(uint8_t)(0x1ULL);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x49)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L28;
    r9 = (uint64_t)(uint32_t)(ML_M4(r8, 0x0));
    /* padding */
L18:
{
    const uint64_t a = (uint64_t)((uint32_t)r9) & 0xFFFFFFFFULL, b = (uint64_t)(ML_M4(rax, 0x18)) & 0xFFFFFFFFULL;
    const uint64_t d = (a - b) & 0xFFFFFFFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80000000ULL) != 0);
}
    rdi = rax;
    rbp = (rbp & ~(uint64_t)0xFFULL) | (uint64_t)(uint8_t)((f_cf) ? 1 : 0);
{
    const uint64_t r = ((uint64_t)((uint8_t)rbp) & 0xFFULL) & ((uint64_t)((uint8_t)rbp) & 0xFFULL);
    f_zf = (r == 0); f_cf = false; f_sf = ((r & 0x80ULL) != 0);
    f_of = false;
}
    if (f_zf) goto L25;
    rax = ML_M8(rax, 0x0);
    goto L26;
L25:
    rax = ML_M8(rax, 0x10);
L26:
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x49)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L18;
L28:
    rsi = ML_M8(rcx, 0x0);
    rbx = rdi;
    ML_M8(rsp, 0x30) = rsi;
    ML_M8(rsp, 0x38) = rbx;
{
    const uint64_t r = ((uint64_t)((uint8_t)rbp) & 0xFFULL) & ((uint64_t)((uint8_t)rbp) & 0xFFULL);
    f_zf = (r == 0); f_cf = false; f_sf = ((r & 0x80ULL) != 0);
    f_of = false;
}
    if (f_zf) goto L98;
    rax = ML_M8(rcx, 0x30);
    ML_M8(rsp, 0x70) = r13;
    r13 = ML_M8(rax, 0x0);
{
    const uint64_t r = ((uint64_t)(rsi) & ~0ULL) & ((uint64_t)(rsi) & ~0ULL);
    f_zf = (r == 0); f_cf = false; f_sf = ((r & 0x8000000000000000ULL) != 0);
    f_of = false;
}
    if (f_zf) goto L41;
{
    const uint64_t a = (uint64_t)(rsi) & ~0ULL, b = (uint64_t)(rsi) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (f_zf) goto L42;
L41:
    rax = ML_CALL(1418233c0);
L42:
{
    const uint64_t a = (uint64_t)(rdi) & ~0ULL, b = (uint64_t)(r13) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    r13 = ML_M8(rsp, 0x70);
    if (!f_zf) goto L56;
    ML_M8(rsp, 0x20) = r14;
    r9 = rdi;
    r8 = (r8 & ~(uint64_t)0xFFULL) | (uint64_t)(uint8_t)(0x1ULL);
L48:
    rdx = rsp + 0x30;
    rcx = r15;
    rax = ML_CALL(141729ba0);
    ML_M1(r12, 0x10) = 0x1ULL;
    rcx = ML_M8(rax, 0x0);
    rax = ML_M8(rax, 0x8);
    ML_M8(r12, 0x0) = rcx;
    goto L110;
L56:
{
    const uint64_t r = ((uint64_t)(rsi) & ~0ULL) & ((uint64_t)(rsi) & ~0ULL);
    f_zf = (r == 0); f_cf = false; f_sf = ((r & 0x8000000000000000ULL) != 0);
    f_of = false;
}
    if (!f_zf) goto L59;
    rax = ML_CALL(1418233c0);
L59:
{
    const uint64_t a = (uint64_t)(ML_M1(rdi, 0x49)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L67;
    rbx = ML_M8(rdi, 0x10);
    ML_M8(rsp, 0x38) = rbx;
{
    const uint64_t a = (uint64_t)(ML_M1(rbx, 0x49)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L98;
    rax = ML_CALL(1418233c0);
    goto L98;
L67:
    rax = ML_M8(rdi, 0x0);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x49)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L81;
    rbx = rax;
    rax = ML_M8(rax, 0x10);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x49)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L79;
    /* padding */
L75:
    rbx = rax;
    rax = ML_M8(rax, 0x10);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x49)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L75;
L79:
    ML_M8(rsp, 0x38) = rbx;
    goto L98;
L81:
    rax = ML_M8(rdi, 0x8);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x49)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L92;
    ;
L85:
{
    const uint64_t a = (uint64_t)(rbx) & ~0ULL, b = (uint64_t)(ML_M8(rax, 0x0)) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L92;
    rbx = rax;
    ML_M8(rsp, 0x38) = rax;
    rax = ML_M8(rax, 0x8);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x49)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L85;
L92:
{
    const uint64_t a = (uint64_t)(ML_M1(rbx, 0x49)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L96;
    rax = ML_CALL(1418233c0);
    goto L98;
L96:
    rbx = rax;
    ML_M8(rsp, 0x38) = rax;
L98:
    rax = (uint64_t)(uint32_t)(ML_M4(r14, 0x0));
{
    const uint64_t a = (uint64_t)(ML_M4(rbx, 0x18)) & 0xFFFFFFFFULL, b = (uint64_t)((uint32_t)rax) & 0xFFFFFFFFULL;
    const uint64_t d = (a - b) & 0xFFFFFFFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80000000ULL) != 0);
}
    if (!f_cf) goto L105;
    ML_M8(rsp, 0x20) = r14;
    r9 = rdi;
    r8 = (uint8_t)rbp;
    goto L48;
L105:
    rcx = rsp + 0x30;
    ML_M1(r12, 0x10) = 0x0ULL;
    rax = ML_M8(rcx, 0x0);
    ML_M8(r12, 0x0) = rax;
    rax = ML_M8(rcx, 0x8);
L110:
    rbx = ML_M8(rsp, 0x78);
    rbp = ML_M8(rsp, 0x80);
    ML_M8(r12, 0x8) = rax;
    rax = r12;
    rsp = rsp + (0x40ULL);
    { const uint64_t v = ML_M8(rsp, 0); rsp += 8; r15 = v; }
    { const uint64_t v = ML_M8(rsp, 0); rsp += 8; r14 = v; }
    { const uint64_t v = ML_M8(rsp, 0); rsp += 8; r12 = v; }
    { const uint64_t v = ML_M8(rsp, 0); rsp += 8; rdi = v; }
    { const uint64_t v = ML_M8(rsp, 0); rsp += 8; rsi = v; }
    return rax;
#undef ML_CALL
    return rax;
}

__attribute__((weak)) uint64_t (*g_fnLIFT_14173c5c0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t) = nullptr;
uint64_t SynLift_14173cea0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A) {
    uint64_t rax = 0, rbx = 0, rbp = 0, rsi = 0, rdi = 0, r10 = 0, r11 = 0, r12 = 0, r13 = 0, r14 = 0, r15 = 0;
    uint64_t rcx = rcxA, rdx = rdxA, r8 = r8A, r9 = r9A;
    bool f_zf = false, f_cf = false, f_sf = false, f_of = false;
    uint8_t xmm0[16] = {0}, xmm1[16] = {0}, xmm2[16] = {0}, xmm3[16] = {0}, xmm4[16] = {0}, xmm5[16] = {0};
    alignas(16) uint8_t stkFrame[0x400] = {0};
    uint64_t rsp = (uint64_t)(uintptr_t)(stkFrame + 0x200);
#define ML_CALL(t) g_fnLIFT_##t(rcx, rdx, r8, r9, ML_M8(rsp, 0x20), ML_M8(rsp, 0x28))
    ML_M8(rsp, 0x10) = rbx;
    ML_M8(rsp, 0x18) = rbp;
    rsp -= 8; ML_M8(rsp, 0) = rsi;
    rsp -= 8; ML_M8(rsp, 0) = rdi;
    rsp -= 8; ML_M8(rsp, 0) = r12;
    rsp -= 8; ML_M8(rsp, 0) = r14;
    rsp -= 8; ML_M8(rsp, 0) = r15;
    rsp = rsp - (0x40ULL);
    rdi = ML_M8(rcx, 0x30);
    r14 = r8;
    r12 = rdx;
    rax = ML_M8(rdi, 0x8);
    r15 = rcx;
    rbp = (rbp & ~(uint64_t)0xFFULL) | (uint64_t)(uint8_t)(0x1ULL);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x21)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L28;
    r9 = (uint64_t)(uint32_t)(ML_M4(r8, 0x0));
    /* padding */
L18:
{
    const uint64_t a = (uint64_t)((uint32_t)r9) & 0xFFFFFFFFULL, b = (uint64_t)(ML_M4(rax, 0x18)) & 0xFFFFFFFFULL;
    const uint64_t d = (a - b) & 0xFFFFFFFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80000000ULL) != 0);
}
    rdi = rax;
    rbp = (rbp & ~(uint64_t)0xFFULL) | (uint64_t)(uint8_t)((f_cf) ? 1 : 0);
{
    const uint64_t r = ((uint64_t)((uint8_t)rbp) & 0xFFULL) & ((uint64_t)((uint8_t)rbp) & 0xFFULL);
    f_zf = (r == 0); f_cf = false; f_sf = ((r & 0x80ULL) != 0);
    f_of = false;
}
    if (f_zf) goto L25;
    rax = ML_M8(rax, 0x0);
    goto L26;
L25:
    rax = ML_M8(rax, 0x10);
L26:
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x21)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L18;
L28:
    rsi = ML_M8(rcx, 0x0);
    rbx = rdi;
    ML_M8(rsp, 0x30) = rsi;
    ML_M8(rsp, 0x38) = rbx;
{
    const uint64_t r = ((uint64_t)((uint8_t)rbp) & 0xFFULL) & ((uint64_t)((uint8_t)rbp) & 0xFFULL);
    f_zf = (r == 0); f_cf = false; f_sf = ((r & 0x80ULL) != 0);
    f_of = false;
}
    if (f_zf) goto L98;
    rax = ML_M8(rcx, 0x30);
    ML_M8(rsp, 0x70) = r13;
    r13 = ML_M8(rax, 0x0);
{
    const uint64_t r = ((uint64_t)(rsi) & ~0ULL) & ((uint64_t)(rsi) & ~0ULL);
    f_zf = (r == 0); f_cf = false; f_sf = ((r & 0x8000000000000000ULL) != 0);
    f_of = false;
}
    if (f_zf) goto L41;
{
    const uint64_t a = (uint64_t)(rsi) & ~0ULL, b = (uint64_t)(rsi) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (f_zf) goto L42;
L41:
    rax = ML_CALL(1418233c0);
L42:
{
    const uint64_t a = (uint64_t)(rdi) & ~0ULL, b = (uint64_t)(r13) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    r13 = ML_M8(rsp, 0x70);
    if (!f_zf) goto L56;
    ML_M8(rsp, 0x20) = r14;
    r9 = rdi;
    r8 = (r8 & ~(uint64_t)0xFFULL) | (uint64_t)(uint8_t)(0x1ULL);
L48:
    rdx = rsp + 0x30;
    rcx = r15;
    rax = ML_CALL(14173c5c0);
    ML_M1(r12, 0x10) = 0x1ULL;
    rcx = ML_M8(rax, 0x0);
    rax = ML_M8(rax, 0x8);
    ML_M8(r12, 0x0) = rcx;
    goto L110;
L56:
{
    const uint64_t r = ((uint64_t)(rsi) & ~0ULL) & ((uint64_t)(rsi) & ~0ULL);
    f_zf = (r == 0); f_cf = false; f_sf = ((r & 0x8000000000000000ULL) != 0);
    f_of = false;
}
    if (!f_zf) goto L59;
    rax = ML_CALL(1418233c0);
L59:
{
    const uint64_t a = (uint64_t)(ML_M1(rdi, 0x21)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L67;
    rbx = ML_M8(rdi, 0x10);
    ML_M8(rsp, 0x38) = rbx;
{
    const uint64_t a = (uint64_t)(ML_M1(rbx, 0x21)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L98;
    rax = ML_CALL(1418233c0);
    goto L98;
L67:
    rax = ML_M8(rdi, 0x0);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x21)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L81;
    rbx = rax;
    rax = ML_M8(rax, 0x10);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x21)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L79;
    /* padding */
L75:
    rbx = rax;
    rax = ML_M8(rax, 0x10);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x21)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L75;
L79:
    ML_M8(rsp, 0x38) = rbx;
    goto L98;
L81:
    rax = ML_M8(rdi, 0x8);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x21)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L92;
    ;
L85:
{
    const uint64_t a = (uint64_t)(rbx) & ~0ULL, b = (uint64_t)(ML_M8(rax, 0x0)) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L92;
    rbx = rax;
    ML_M8(rsp, 0x38) = rax;
    rax = ML_M8(rax, 0x8);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x21)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L85;
L92:
{
    const uint64_t a = (uint64_t)(ML_M1(rbx, 0x21)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L96;
    rax = ML_CALL(1418233c0);
    goto L98;
L96:
    rbx = rax;
    ML_M8(rsp, 0x38) = rax;
L98:
    rax = (uint64_t)(uint32_t)(ML_M4(r14, 0x0));
{
    const uint64_t a = (uint64_t)(ML_M4(rbx, 0x18)) & 0xFFFFFFFFULL, b = (uint64_t)((uint32_t)rax) & 0xFFFFFFFFULL;
    const uint64_t d = (a - b) & 0xFFFFFFFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80000000ULL) != 0);
}
    if (!f_cf) goto L105;
    ML_M8(rsp, 0x20) = r14;
    r9 = rdi;
    r8 = (uint8_t)rbp;
    goto L48;
L105:
    rcx = rsp + 0x30;
    ML_M1(r12, 0x10) = 0x0ULL;
    rax = ML_M8(rcx, 0x0);
    ML_M8(r12, 0x0) = rax;
    rax = ML_M8(rcx, 0x8);
L110:
    rbx = ML_M8(rsp, 0x78);
    rbp = ML_M8(rsp, 0x80);
    ML_M8(r12, 0x8) = rax;
    rax = r12;
    rsp = rsp + (0x40ULL);
    { const uint64_t v = ML_M8(rsp, 0); rsp += 8; r15 = v; }
    { const uint64_t v = ML_M8(rsp, 0); rsp += 8; r14 = v; }
    { const uint64_t v = ML_M8(rsp, 0); rsp += 8; r12 = v; }
    { const uint64_t v = ML_M8(rsp, 0); rsp += 8; rdi = v; }
    { const uint64_t v = ML_M8(rsp, 0); rsp += 8; rsi = v; }
    return rax;
#undef ML_CALL
    return rax;
}

__attribute__((weak)) uint64_t (*g_fnLIFT_14173e790)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t) = nullptr;
uint64_t SynLift_14173ed60(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A) {
    uint64_t rax = 0, rbx = 0, rbp = 0, rsi = 0, rdi = 0, r10 = 0, r11 = 0, r12 = 0, r13 = 0, r14 = 0, r15 = 0;
    uint64_t rcx = rcxA, rdx = rdxA, r8 = r8A, r9 = r9A;
    bool f_zf = false, f_cf = false, f_sf = false, f_of = false;
    uint8_t xmm0[16] = {0}, xmm1[16] = {0}, xmm2[16] = {0}, xmm3[16] = {0}, xmm4[16] = {0}, xmm5[16] = {0};
    alignas(16) uint8_t stkFrame[0x400] = {0};
    uint64_t rsp = (uint64_t)(uintptr_t)(stkFrame + 0x200);
#define ML_CALL(t) g_fnLIFT_##t(rcx, rdx, r8, r9, ML_M8(rsp, 0x20), ML_M8(rsp, 0x28))
    ML_M8(rsp, 0x10) = rbx;
    ML_M8(rsp, 0x18) = rbp;
    rsp -= 8; ML_M8(rsp, 0) = rsi;
    rsp -= 8; ML_M8(rsp, 0) = rdi;
    rsp -= 8; ML_M8(rsp, 0) = r12;
    rsp -= 8; ML_M8(rsp, 0) = r14;
    rsp -= 8; ML_M8(rsp, 0) = r15;
    rsp = rsp - (0x40ULL);
    rdi = ML_M8(rcx, 0x30);
    r14 = r8;
    r12 = rdx;
    rax = ML_M8(rdi, 0x8);
    r15 = rcx;
    rbp = (rbp & ~(uint64_t)0xFFULL) | (uint64_t)(uint8_t)(0x1ULL);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x61)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L28;
    r9 = (uint64_t)(uint32_t)(ML_M4(r8, 0x0));
    /* padding */
L18:
{
    const uint64_t a = (uint64_t)((uint32_t)r9) & 0xFFFFFFFFULL, b = (uint64_t)(ML_M4(rax, 0x18)) & 0xFFFFFFFFULL;
    const uint64_t d = (a - b) & 0xFFFFFFFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80000000ULL) != 0);
}
    rdi = rax;
    rbp = (rbp & ~(uint64_t)0xFFULL) | (uint64_t)(uint8_t)((f_cf) ? 1 : 0);
{
    const uint64_t r = ((uint64_t)((uint8_t)rbp) & 0xFFULL) & ((uint64_t)((uint8_t)rbp) & 0xFFULL);
    f_zf = (r == 0); f_cf = false; f_sf = ((r & 0x80ULL) != 0);
    f_of = false;
}
    if (f_zf) goto L25;
    rax = ML_M8(rax, 0x0);
    goto L26;
L25:
    rax = ML_M8(rax, 0x10);
L26:
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x61)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L18;
L28:
    rsi = ML_M8(rcx, 0x0);
    rbx = rdi;
    ML_M8(rsp, 0x30) = rsi;
    ML_M8(rsp, 0x38) = rbx;
{
    const uint64_t r = ((uint64_t)((uint8_t)rbp) & 0xFFULL) & ((uint64_t)((uint8_t)rbp) & 0xFFULL);
    f_zf = (r == 0); f_cf = false; f_sf = ((r & 0x80ULL) != 0);
    f_of = false;
}
    if (f_zf) goto L98;
    rax = ML_M8(rcx, 0x30);
    ML_M8(rsp, 0x70) = r13;
    r13 = ML_M8(rax, 0x0);
{
    const uint64_t r = ((uint64_t)(rsi) & ~0ULL) & ((uint64_t)(rsi) & ~0ULL);
    f_zf = (r == 0); f_cf = false; f_sf = ((r & 0x8000000000000000ULL) != 0);
    f_of = false;
}
    if (f_zf) goto L41;
{
    const uint64_t a = (uint64_t)(rsi) & ~0ULL, b = (uint64_t)(rsi) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (f_zf) goto L42;
L41:
    rax = ML_CALL(1418233c0);
L42:
{
    const uint64_t a = (uint64_t)(rdi) & ~0ULL, b = (uint64_t)(r13) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    r13 = ML_M8(rsp, 0x70);
    if (!f_zf) goto L56;
    ML_M8(rsp, 0x20) = r14;
    r9 = rdi;
    r8 = (r8 & ~(uint64_t)0xFFULL) | (uint64_t)(uint8_t)(0x1ULL);
L48:
    rdx = rsp + 0x30;
    rcx = r15;
    rax = ML_CALL(14173e790);
    ML_M1(r12, 0x10) = 0x1ULL;
    rcx = ML_M8(rax, 0x0);
    rax = ML_M8(rax, 0x8);
    ML_M8(r12, 0x0) = rcx;
    goto L110;
L56:
{
    const uint64_t r = ((uint64_t)(rsi) & ~0ULL) & ((uint64_t)(rsi) & ~0ULL);
    f_zf = (r == 0); f_cf = false; f_sf = ((r & 0x8000000000000000ULL) != 0);
    f_of = false;
}
    if (!f_zf) goto L59;
    rax = ML_CALL(1418233c0);
L59:
{
    const uint64_t a = (uint64_t)(ML_M1(rdi, 0x61)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L67;
    rbx = ML_M8(rdi, 0x10);
    ML_M8(rsp, 0x38) = rbx;
{
    const uint64_t a = (uint64_t)(ML_M1(rbx, 0x61)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L98;
    rax = ML_CALL(1418233c0);
    goto L98;
L67:
    rax = ML_M8(rdi, 0x0);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x61)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L81;
    rbx = rax;
    rax = ML_M8(rax, 0x10);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x61)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L79;
    /* padding */
L75:
    rbx = rax;
    rax = ML_M8(rax, 0x10);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x61)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L75;
L79:
    ML_M8(rsp, 0x38) = rbx;
    goto L98;
L81:
    rax = ML_M8(rdi, 0x8);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x61)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L92;
    ;
L85:
{
    const uint64_t a = (uint64_t)(rbx) & ~0ULL, b = (uint64_t)(ML_M8(rax, 0x0)) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L92;
    rbx = rax;
    ML_M8(rsp, 0x38) = rax;
    rax = ML_M8(rax, 0x8);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x61)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L85;
L92:
{
    const uint64_t a = (uint64_t)(ML_M1(rbx, 0x61)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L96;
    rax = ML_CALL(1418233c0);
    goto L98;
L96:
    rbx = rax;
    ML_M8(rsp, 0x38) = rax;
L98:
    rax = (uint64_t)(uint32_t)(ML_M4(r14, 0x0));
{
    const uint64_t a = (uint64_t)(ML_M4(rbx, 0x18)) & 0xFFFFFFFFULL, b = (uint64_t)((uint32_t)rax) & 0xFFFFFFFFULL;
    const uint64_t d = (a - b) & 0xFFFFFFFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80000000ULL) != 0);
}
    if (!f_cf) goto L105;
    ML_M8(rsp, 0x20) = r14;
    r9 = rdi;
    r8 = (uint8_t)rbp;
    goto L48;
L105:
    rcx = rsp + 0x30;
    ML_M1(r12, 0x10) = 0x0ULL;
    rax = ML_M8(rcx, 0x0);
    ML_M8(r12, 0x0) = rax;
    rax = ML_M8(rcx, 0x8);
L110:
    rbx = ML_M8(rsp, 0x78);
    rbp = ML_M8(rsp, 0x80);
    ML_M8(r12, 0x8) = rax;
    rax = r12;
    rsp = rsp + (0x40ULL);
    { const uint64_t v = ML_M8(rsp, 0); rsp += 8; r15 = v; }
    { const uint64_t v = ML_M8(rsp, 0); rsp += 8; r14 = v; }
    { const uint64_t v = ML_M8(rsp, 0); rsp += 8; r12 = v; }
    { const uint64_t v = ML_M8(rsp, 0); rsp += 8; rdi = v; }
    { const uint64_t v = ML_M8(rsp, 0); rsp += 8; rsi = v; }
    return rax;
#undef ML_CALL
    return rax;
}

__attribute__((weak)) uint64_t (*g_fnLIFT_1417483e0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t) = nullptr;
uint64_t SynLift_141749690(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A) {
    uint64_t rax = 0, rbx = 0, rbp = 0, rsi = 0, rdi = 0, r10 = 0, r11 = 0, r12 = 0, r13 = 0, r14 = 0, r15 = 0;
    uint64_t rcx = rcxA, rdx = rdxA, r8 = r8A, r9 = r9A;
    bool f_zf = false, f_cf = false, f_sf = false, f_of = false;
    uint8_t xmm0[16] = {0}, xmm1[16] = {0}, xmm2[16] = {0}, xmm3[16] = {0}, xmm4[16] = {0}, xmm5[16] = {0};
    alignas(16) uint8_t stkFrame[0x400] = {0};
    uint64_t rsp = (uint64_t)(uintptr_t)(stkFrame + 0x200);
#define ML_CALL(t) g_fnLIFT_##t(rcx, rdx, r8, r9, ML_M8(rsp, 0x20), ML_M8(rsp, 0x28))
    ML_M8(rsp, 0x10) = rbx;
    ML_M8(rsp, 0x18) = rbp;
    rsp -= 8; ML_M8(rsp, 0) = rsi;
    rsp -= 8; ML_M8(rsp, 0) = rdi;
    rsp -= 8; ML_M8(rsp, 0) = r12;
    rsp -= 8; ML_M8(rsp, 0) = r14;
    rsp -= 8; ML_M8(rsp, 0) = r15;
    rsp = rsp - (0x40ULL);
    rdi = ML_M8(rcx, 0x30);
    r14 = r8;
    r12 = rdx;
    rax = ML_M8(rdi, 0x8);
    r15 = rcx;
    rbp = (rbp & ~(uint64_t)0xFFULL) | (uint64_t)(uint8_t)(0x1ULL);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x3d)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L28;
    r9 = (uint64_t)(uint32_t)(ML_M4(r8, 0x0));
    /* padding */
L18:
{
    const uint64_t a = (uint64_t)((uint32_t)r9) & 0xFFFFFFFFULL, b = (uint64_t)(ML_M4(rax, 0x18)) & 0xFFFFFFFFULL;
    const uint64_t d = (a - b) & 0xFFFFFFFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80000000ULL) != 0);
}
    rdi = rax;
    rbp = (rbp & ~(uint64_t)0xFFULL) | (uint64_t)(uint8_t)((f_cf) ? 1 : 0);
{
    const uint64_t r = ((uint64_t)((uint8_t)rbp) & 0xFFULL) & ((uint64_t)((uint8_t)rbp) & 0xFFULL);
    f_zf = (r == 0); f_cf = false; f_sf = ((r & 0x80ULL) != 0);
    f_of = false;
}
    if (f_zf) goto L25;
    rax = ML_M8(rax, 0x0);
    goto L26;
L25:
    rax = ML_M8(rax, 0x10);
L26:
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x3d)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L18;
L28:
    rsi = ML_M8(rcx, 0x0);
    rbx = rdi;
    ML_M8(rsp, 0x30) = rsi;
    ML_M8(rsp, 0x38) = rbx;
{
    const uint64_t r = ((uint64_t)((uint8_t)rbp) & 0xFFULL) & ((uint64_t)((uint8_t)rbp) & 0xFFULL);
    f_zf = (r == 0); f_cf = false; f_sf = ((r & 0x80ULL) != 0);
    f_of = false;
}
    if (f_zf) goto L98;
    rax = ML_M8(rcx, 0x30);
    ML_M8(rsp, 0x70) = r13;
    r13 = ML_M8(rax, 0x0);
{
    const uint64_t r = ((uint64_t)(rsi) & ~0ULL) & ((uint64_t)(rsi) & ~0ULL);
    f_zf = (r == 0); f_cf = false; f_sf = ((r & 0x8000000000000000ULL) != 0);
    f_of = false;
}
    if (f_zf) goto L41;
{
    const uint64_t a = (uint64_t)(rsi) & ~0ULL, b = (uint64_t)(rsi) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (f_zf) goto L42;
L41:
    rax = ML_CALL(1418233c0);
L42:
{
    const uint64_t a = (uint64_t)(rdi) & ~0ULL, b = (uint64_t)(r13) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    r13 = ML_M8(rsp, 0x70);
    if (!f_zf) goto L56;
    ML_M8(rsp, 0x20) = r14;
    r9 = rdi;
    r8 = (r8 & ~(uint64_t)0xFFULL) | (uint64_t)(uint8_t)(0x1ULL);
L48:
    rdx = rsp + 0x30;
    rcx = r15;
    rax = ML_CALL(1417483e0);
    ML_M1(r12, 0x10) = 0x1ULL;
    rcx = ML_M8(rax, 0x0);
    rax = ML_M8(rax, 0x8);
    ML_M8(r12, 0x0) = rcx;
    goto L110;
L56:
{
    const uint64_t r = ((uint64_t)(rsi) & ~0ULL) & ((uint64_t)(rsi) & ~0ULL);
    f_zf = (r == 0); f_cf = false; f_sf = ((r & 0x8000000000000000ULL) != 0);
    f_of = false;
}
    if (!f_zf) goto L59;
    rax = ML_CALL(1418233c0);
L59:
{
    const uint64_t a = (uint64_t)(ML_M1(rdi, 0x3d)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L67;
    rbx = ML_M8(rdi, 0x10);
    ML_M8(rsp, 0x38) = rbx;
{
    const uint64_t a = (uint64_t)(ML_M1(rbx, 0x3d)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L98;
    rax = ML_CALL(1418233c0);
    goto L98;
L67:
    rax = ML_M8(rdi, 0x0);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x3d)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L81;
    rbx = rax;
    rax = ML_M8(rax, 0x10);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x3d)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L79;
    /* padding */
L75:
    rbx = rax;
    rax = ML_M8(rax, 0x10);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x3d)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L75;
L79:
    ML_M8(rsp, 0x38) = rbx;
    goto L98;
L81:
    rax = ML_M8(rdi, 0x8);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x3d)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L92;
    ;
L85:
{
    const uint64_t a = (uint64_t)(rbx) & ~0ULL, b = (uint64_t)(ML_M8(rax, 0x0)) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L92;
    rbx = rax;
    ML_M8(rsp, 0x38) = rax;
    rax = ML_M8(rax, 0x8);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x3d)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L85;
L92:
{
    const uint64_t a = (uint64_t)(ML_M1(rbx, 0x3d)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L96;
    rax = ML_CALL(1418233c0);
    goto L98;
L96:
    rbx = rax;
    ML_M8(rsp, 0x38) = rax;
L98:
    rax = (uint64_t)(uint32_t)(ML_M4(r14, 0x0));
{
    const uint64_t a = (uint64_t)(ML_M4(rbx, 0x18)) & 0xFFFFFFFFULL, b = (uint64_t)((uint32_t)rax) & 0xFFFFFFFFULL;
    const uint64_t d = (a - b) & 0xFFFFFFFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80000000ULL) != 0);
}
    if (!f_cf) goto L105;
    ML_M8(rsp, 0x20) = r14;
    r9 = rdi;
    r8 = (uint8_t)rbp;
    goto L48;
L105:
    rcx = rsp + 0x30;
    ML_M1(r12, 0x10) = 0x0ULL;
    rax = ML_M8(rcx, 0x0);
    ML_M8(r12, 0x0) = rax;
    rax = ML_M8(rcx, 0x8);
L110:
    rbx = ML_M8(rsp, 0x78);
    rbp = ML_M8(rsp, 0x80);
    ML_M8(r12, 0x8) = rax;
    rax = r12;
    rsp = rsp + (0x40ULL);
    { const uint64_t v = ML_M8(rsp, 0); rsp += 8; r15 = v; }
    { const uint64_t v = ML_M8(rsp, 0); rsp += 8; r14 = v; }
    { const uint64_t v = ML_M8(rsp, 0); rsp += 8; r12 = v; }
    { const uint64_t v = ML_M8(rsp, 0); rsp += 8; rdi = v; }
    { const uint64_t v = ML_M8(rsp, 0); rsp += 8; rsi = v; }
    return rax;
#undef ML_CALL
    return rax;
}

__attribute__((weak)) uint64_t (*g_fnLIFT_141748820)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t) = nullptr;
uint64_t SynLift_141749a50(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A) {
    uint64_t rax = 0, rbx = 0, rbp = 0, rsi = 0, rdi = 0, r10 = 0, r11 = 0, r12 = 0, r13 = 0, r14 = 0, r15 = 0;
    uint64_t rcx = rcxA, rdx = rdxA, r8 = r8A, r9 = r9A;
    bool f_zf = false, f_cf = false, f_sf = false, f_of = false;
    uint8_t xmm0[16] = {0}, xmm1[16] = {0}, xmm2[16] = {0}, xmm3[16] = {0}, xmm4[16] = {0}, xmm5[16] = {0};
    alignas(16) uint8_t stkFrame[0x400] = {0};
    uint64_t rsp = (uint64_t)(uintptr_t)(stkFrame + 0x200);
#define ML_CALL(t) g_fnLIFT_##t(rcx, rdx, r8, r9, ML_M8(rsp, 0x20), ML_M8(rsp, 0x28))
    ML_M8(rsp, 0x10) = rbx;
    ML_M8(rsp, 0x18) = rbp;
    rsp -= 8; ML_M8(rsp, 0) = rsi;
    rsp -= 8; ML_M8(rsp, 0) = rdi;
    rsp -= 8; ML_M8(rsp, 0) = r12;
    rsp -= 8; ML_M8(rsp, 0) = r14;
    rsp -= 8; ML_M8(rsp, 0) = r15;
    rsp = rsp - (0x40ULL);
    rdi = ML_M8(rcx, 0x30);
    r14 = r8;
    r12 = rdx;
    rax = ML_M8(rdi, 0x8);
    r15 = rcx;
    rbp = (rbp & ~(uint64_t)0xFFULL) | (uint64_t)(uint8_t)(0x1ULL);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L28;
    r9 = (uint64_t)(uint32_t)(ML_M4(r8, 0x0));
    /* padding */
L18:
{
    const uint64_t a = (uint64_t)((uint32_t)r9) & 0xFFFFFFFFULL, b = (uint64_t)(ML_M4(rax, 0x18)) & 0xFFFFFFFFULL;
    const uint64_t d = (a - b) & 0xFFFFFFFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80000000ULL) != 0);
}
    rdi = rax;
    rbp = (rbp & ~(uint64_t)0xFFULL) | (uint64_t)(uint8_t)((f_cf) ? 1 : 0);
{
    const uint64_t r = ((uint64_t)((uint8_t)rbp) & 0xFFULL) & ((uint64_t)((uint8_t)rbp) & 0xFFULL);
    f_zf = (r == 0); f_cf = false; f_sf = ((r & 0x80ULL) != 0);
    f_of = false;
}
    if (f_zf) goto L25;
    rax = ML_M8(rax, 0x0);
    goto L26;
L25:
    rax = ML_M8(rax, 0x10);
L26:
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L18;
L28:
    rsi = ML_M8(rcx, 0x0);
    rbx = rdi;
    ML_M8(rsp, 0x30) = rsi;
    ML_M8(rsp, 0x38) = rbx;
{
    const uint64_t r = ((uint64_t)((uint8_t)rbp) & 0xFFULL) & ((uint64_t)((uint8_t)rbp) & 0xFFULL);
    f_zf = (r == 0); f_cf = false; f_sf = ((r & 0x80ULL) != 0);
    f_of = false;
}
    if (f_zf) goto L98;
    rax = ML_M8(rcx, 0x30);
    ML_M8(rsp, 0x70) = r13;
    r13 = ML_M8(rax, 0x0);
{
    const uint64_t r = ((uint64_t)(rsi) & ~0ULL) & ((uint64_t)(rsi) & ~0ULL);
    f_zf = (r == 0); f_cf = false; f_sf = ((r & 0x8000000000000000ULL) != 0);
    f_of = false;
}
    if (f_zf) goto L41;
{
    const uint64_t a = (uint64_t)(rsi) & ~0ULL, b = (uint64_t)(rsi) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (f_zf) goto L42;
L41:
    rax = ML_CALL(1418233c0);
L42:
{
    const uint64_t a = (uint64_t)(rdi) & ~0ULL, b = (uint64_t)(r13) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    r13 = ML_M8(rsp, 0x70);
    if (!f_zf) goto L56;
    ML_M8(rsp, 0x20) = r14;
    r9 = rdi;
    r8 = (r8 & ~(uint64_t)0xFFULL) | (uint64_t)(uint8_t)(0x1ULL);
L48:
    rdx = rsp + 0x30;
    rcx = r15;
    rax = ML_CALL(141748820);
    ML_M1(r12, 0x10) = 0x1ULL;
    rcx = ML_M8(rax, 0x0);
    rax = ML_M8(rax, 0x8);
    ML_M8(r12, 0x0) = rcx;
    goto L110;
L56:
{
    const uint64_t r = ((uint64_t)(rsi) & ~0ULL) & ((uint64_t)(rsi) & ~0ULL);
    f_zf = (r == 0); f_cf = false; f_sf = ((r & 0x8000000000000000ULL) != 0);
    f_of = false;
}
    if (!f_zf) goto L59;
    rax = ML_CALL(1418233c0);
L59:
{
    const uint64_t a = (uint64_t)(ML_M1(rdi, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L67;
    rbx = ML_M8(rdi, 0x10);
    ML_M8(rsp, 0x38) = rbx;
{
    const uint64_t a = (uint64_t)(ML_M1(rbx, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L98;
    rax = ML_CALL(1418233c0);
    goto L98;
L67:
    rax = ML_M8(rdi, 0x0);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L81;
    rbx = rax;
    rax = ML_M8(rax, 0x10);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L79;
    /* padding */
L75:
    rbx = rax;
    rax = ML_M8(rax, 0x10);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L75;
L79:
    ML_M8(rsp, 0x38) = rbx;
    goto L98;
L81:
    rax = ML_M8(rdi, 0x8);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L92;
    ;
L85:
{
    const uint64_t a = (uint64_t)(rbx) & ~0ULL, b = (uint64_t)(ML_M8(rax, 0x0)) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L92;
    rbx = rax;
    ML_M8(rsp, 0x38) = rax;
    rax = ML_M8(rax, 0x8);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L85;
L92:
{
    const uint64_t a = (uint64_t)(ML_M1(rbx, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L96;
    rax = ML_CALL(1418233c0);
    goto L98;
L96:
    rbx = rax;
    ML_M8(rsp, 0x38) = rax;
L98:
    rax = (uint64_t)(uint32_t)(ML_M4(r14, 0x0));
{
    const uint64_t a = (uint64_t)(ML_M4(rbx, 0x18)) & 0xFFFFFFFFULL, b = (uint64_t)((uint32_t)rax) & 0xFFFFFFFFULL;
    const uint64_t d = (a - b) & 0xFFFFFFFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80000000ULL) != 0);
}
    if (!f_cf) goto L105;
    ML_M8(rsp, 0x20) = r14;
    r9 = rdi;
    r8 = (uint8_t)rbp;
    goto L48;
L105:
    rcx = rsp + 0x30;
    ML_M1(r12, 0x10) = 0x0ULL;
    rax = ML_M8(rcx, 0x0);
    ML_M8(r12, 0x0) = rax;
    rax = ML_M8(rcx, 0x8);
L110:
    rbx = ML_M8(rsp, 0x78);
    rbp = ML_M8(rsp, 0x80);
    ML_M8(r12, 0x8) = rax;
    rax = r12;
    rsp = rsp + (0x40ULL);
    { const uint64_t v = ML_M8(rsp, 0); rsp += 8; r15 = v; }
    { const uint64_t v = ML_M8(rsp, 0); rsp += 8; r14 = v; }
    { const uint64_t v = ML_M8(rsp, 0); rsp += 8; r12 = v; }
    { const uint64_t v = ML_M8(rsp, 0); rsp += 8; rdi = v; }
    { const uint64_t v = ML_M8(rsp, 0); rsp += 8; rsi = v; }
    return rax;
#undef ML_CALL
    return rax;
}

__attribute__((weak)) uint64_t (*g_fnLIFT_1417585d0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t) = nullptr;
uint64_t SynLift_14175d840(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A) {
    uint64_t rax = 0, rbx = 0, rbp = 0, rsi = 0, rdi = 0, r10 = 0, r11 = 0, r12 = 0, r13 = 0, r14 = 0, r15 = 0;
    uint64_t rcx = rcxA, rdx = rdxA, r8 = r8A, r9 = r9A;
    bool f_zf = false, f_cf = false, f_sf = false, f_of = false;
    uint8_t xmm0[16] = {0}, xmm1[16] = {0}, xmm2[16] = {0}, xmm3[16] = {0}, xmm4[16] = {0}, xmm5[16] = {0};
    alignas(16) uint8_t stkFrame[0x400] = {0};
    uint64_t rsp = (uint64_t)(uintptr_t)(stkFrame + 0x200);
#define ML_CALL(t) g_fnLIFT_##t(rcx, rdx, r8, r9, ML_M8(rsp, 0x20), ML_M8(rsp, 0x28))
    ML_M8(rsp, 0x10) = rbx;
    ML_M8(rsp, 0x18) = rbp;
    rsp -= 8; ML_M8(rsp, 0) = rsi;
    rsp -= 8; ML_M8(rsp, 0) = rdi;
    rsp -= 8; ML_M8(rsp, 0) = r12;
    rsp -= 8; ML_M8(rsp, 0) = r14;
    rsp -= 8; ML_M8(rsp, 0) = r15;
    rsp = rsp - (0x40ULL);
    rdi = ML_M8(rcx, 0x30);
    r14 = r8;
    r12 = rdx;
    rax = ML_M8(rdi, 0x8);
    r15 = rcx;
    rbp = (rbp & ~(uint64_t)0xFFULL) | (uint64_t)(uint8_t)(0x1ULL);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L28;
    r9 = (uint64_t)(uint32_t)(ML_M4(r8, 0x0));
    /* padding */
L18:
{
    const uint64_t a = (uint64_t)((uint32_t)r9) & 0xFFFFFFFFULL, b = (uint64_t)(ML_M4(rax, 0x18)) & 0xFFFFFFFFULL;
    const uint64_t d = (a - b) & 0xFFFFFFFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80000000ULL) != 0);
}
    rdi = rax;
    rbp = (rbp & ~(uint64_t)0xFFULL) | (uint64_t)(uint8_t)((f_cf) ? 1 : 0);
{
    const uint64_t r = ((uint64_t)((uint8_t)rbp) & 0xFFULL) & ((uint64_t)((uint8_t)rbp) & 0xFFULL);
    f_zf = (r == 0); f_cf = false; f_sf = ((r & 0x80ULL) != 0);
    f_of = false;
}
    if (f_zf) goto L25;
    rax = ML_M8(rax, 0x0);
    goto L26;
L25:
    rax = ML_M8(rax, 0x10);
L26:
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L18;
L28:
    rsi = ML_M8(rcx, 0x0);
    rbx = rdi;
    ML_M8(rsp, 0x30) = rsi;
    ML_M8(rsp, 0x38) = rbx;
{
    const uint64_t r = ((uint64_t)((uint8_t)rbp) & 0xFFULL) & ((uint64_t)((uint8_t)rbp) & 0xFFULL);
    f_zf = (r == 0); f_cf = false; f_sf = ((r & 0x80ULL) != 0);
    f_of = false;
}
    if (f_zf) goto L98;
    rax = ML_M8(rcx, 0x30);
    ML_M8(rsp, 0x70) = r13;
    r13 = ML_M8(rax, 0x0);
{
    const uint64_t r = ((uint64_t)(rsi) & ~0ULL) & ((uint64_t)(rsi) & ~0ULL);
    f_zf = (r == 0); f_cf = false; f_sf = ((r & 0x8000000000000000ULL) != 0);
    f_of = false;
}
    if (f_zf) goto L41;
{
    const uint64_t a = (uint64_t)(rsi) & ~0ULL, b = (uint64_t)(rsi) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (f_zf) goto L42;
L41:
    rax = ML_CALL(1418233c0);
L42:
{
    const uint64_t a = (uint64_t)(rdi) & ~0ULL, b = (uint64_t)(r13) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    r13 = ML_M8(rsp, 0x70);
    if (!f_zf) goto L56;
    ML_M8(rsp, 0x20) = r14;
    r9 = rdi;
    r8 = (r8 & ~(uint64_t)0xFFULL) | (uint64_t)(uint8_t)(0x1ULL);
L48:
    rdx = rsp + 0x30;
    rcx = r15;
    rax = ML_CALL(1417585d0);
    ML_M1(r12, 0x10) = 0x1ULL;
    rcx = ML_M8(rax, 0x0);
    rax = ML_M8(rax, 0x8);
    ML_M8(r12, 0x0) = rcx;
    goto L110;
L56:
{
    const uint64_t r = ((uint64_t)(rsi) & ~0ULL) & ((uint64_t)(rsi) & ~0ULL);
    f_zf = (r == 0); f_cf = false; f_sf = ((r & 0x8000000000000000ULL) != 0);
    f_of = false;
}
    if (!f_zf) goto L59;
    rax = ML_CALL(1418233c0);
L59:
{
    const uint64_t a = (uint64_t)(ML_M1(rdi, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L67;
    rbx = ML_M8(rdi, 0x10);
    ML_M8(rsp, 0x38) = rbx;
{
    const uint64_t a = (uint64_t)(ML_M1(rbx, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L98;
    rax = ML_CALL(1418233c0);
    goto L98;
L67:
    rax = ML_M8(rdi, 0x0);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L81;
    rbx = rax;
    rax = ML_M8(rax, 0x10);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L79;
    /* padding */
L75:
    rbx = rax;
    rax = ML_M8(rax, 0x10);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L75;
L79:
    ML_M8(rsp, 0x38) = rbx;
    goto L98;
L81:
    rax = ML_M8(rdi, 0x8);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L92;
    ;
L85:
{
    const uint64_t a = (uint64_t)(rbx) & ~0ULL, b = (uint64_t)(ML_M8(rax, 0x0)) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L92;
    rbx = rax;
    ML_M8(rsp, 0x38) = rax;
    rax = ML_M8(rax, 0x8);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L85;
L92:
{
    const uint64_t a = (uint64_t)(ML_M1(rbx, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L96;
    rax = ML_CALL(1418233c0);
    goto L98;
L96:
    rbx = rax;
    ML_M8(rsp, 0x38) = rax;
L98:
    rax = (uint64_t)(uint32_t)(ML_M4(r14, 0x0));
{
    const uint64_t a = (uint64_t)(ML_M4(rbx, 0x18)) & 0xFFFFFFFFULL, b = (uint64_t)((uint32_t)rax) & 0xFFFFFFFFULL;
    const uint64_t d = (a - b) & 0xFFFFFFFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80000000ULL) != 0);
}
    if (!f_cf) goto L105;
    ML_M8(rsp, 0x20) = r14;
    r9 = rdi;
    r8 = (uint8_t)rbp;
    goto L48;
L105:
    rcx = rsp + 0x30;
    ML_M1(r12, 0x10) = 0x0ULL;
    rax = ML_M8(rcx, 0x0);
    ML_M8(r12, 0x0) = rax;
    rax = ML_M8(rcx, 0x8);
L110:
    rbx = ML_M8(rsp, 0x78);
    rbp = ML_M8(rsp, 0x80);
    ML_M8(r12, 0x8) = rax;
    rax = r12;
    rsp = rsp + (0x40ULL);
    { const uint64_t v = ML_M8(rsp, 0); rsp += 8; r15 = v; }
    { const uint64_t v = ML_M8(rsp, 0); rsp += 8; r14 = v; }
    { const uint64_t v = ML_M8(rsp, 0); rsp += 8; r12 = v; }
    { const uint64_t v = ML_M8(rsp, 0); rsp += 8; rdi = v; }
    { const uint64_t v = ML_M8(rsp, 0); rsp += 8; rsi = v; }
    return rax;
#undef ML_CALL
    return rax;
}

__attribute__((weak)) uint64_t (*g_fnLIFT_141758a10)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t) = nullptr;
uint64_t SynLift_14175dd50(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A) {
    uint64_t rax = 0, rbx = 0, rbp = 0, rsi = 0, rdi = 0, r10 = 0, r11 = 0, r12 = 0, r13 = 0, r14 = 0, r15 = 0;
    uint64_t rcx = rcxA, rdx = rdxA, r8 = r8A, r9 = r9A;
    bool f_zf = false, f_cf = false, f_sf = false, f_of = false;
    uint8_t xmm0[16] = {0}, xmm1[16] = {0}, xmm2[16] = {0}, xmm3[16] = {0}, xmm4[16] = {0}, xmm5[16] = {0};
    alignas(16) uint8_t stkFrame[0x400] = {0};
    uint64_t rsp = (uint64_t)(uintptr_t)(stkFrame + 0x200);
#define ML_CALL(t) g_fnLIFT_##t(rcx, rdx, r8, r9, ML_M8(rsp, 0x20), ML_M8(rsp, 0x28))
    ML_M8(rsp, 0x10) = rbx;
    ML_M8(rsp, 0x18) = rbp;
    rsp -= 8; ML_M8(rsp, 0) = rsi;
    rsp -= 8; ML_M8(rsp, 0) = rdi;
    rsp -= 8; ML_M8(rsp, 0) = r12;
    rsp -= 8; ML_M8(rsp, 0) = r14;
    rsp -= 8; ML_M8(rsp, 0) = r15;
    rsp = rsp - (0x40ULL);
    rdi = ML_M8(rcx, 0x30);
    r14 = r8;
    r12 = rdx;
    rax = ML_M8(rdi, 0x8);
    r15 = rcx;
    rbp = (rbp & ~(uint64_t)0xFFULL) | (uint64_t)(uint8_t)(0x1ULL);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L28;
    r9 = (uint64_t)(uint32_t)(ML_M4(r8, 0x0));
    /* padding */
L18:
{
    const uint64_t a = (uint64_t)((uint32_t)r9) & 0xFFFFFFFFULL, b = (uint64_t)(ML_M4(rax, 0x18)) & 0xFFFFFFFFULL;
    const uint64_t d = (a - b) & 0xFFFFFFFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80000000ULL) != 0);
}
    rdi = rax;
    rbp = (rbp & ~(uint64_t)0xFFULL) | (uint64_t)(uint8_t)((f_cf) ? 1 : 0);
{
    const uint64_t r = ((uint64_t)((uint8_t)rbp) & 0xFFULL) & ((uint64_t)((uint8_t)rbp) & 0xFFULL);
    f_zf = (r == 0); f_cf = false; f_sf = ((r & 0x80ULL) != 0);
    f_of = false;
}
    if (f_zf) goto L25;
    rax = ML_M8(rax, 0x0);
    goto L26;
L25:
    rax = ML_M8(rax, 0x10);
L26:
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L18;
L28:
    rsi = ML_M8(rcx, 0x0);
    rbx = rdi;
    ML_M8(rsp, 0x30) = rsi;
    ML_M8(rsp, 0x38) = rbx;
{
    const uint64_t r = ((uint64_t)((uint8_t)rbp) & 0xFFULL) & ((uint64_t)((uint8_t)rbp) & 0xFFULL);
    f_zf = (r == 0); f_cf = false; f_sf = ((r & 0x80ULL) != 0);
    f_of = false;
}
    if (f_zf) goto L98;
    rax = ML_M8(rcx, 0x30);
    ML_M8(rsp, 0x70) = r13;
    r13 = ML_M8(rax, 0x0);
{
    const uint64_t r = ((uint64_t)(rsi) & ~0ULL) & ((uint64_t)(rsi) & ~0ULL);
    f_zf = (r == 0); f_cf = false; f_sf = ((r & 0x8000000000000000ULL) != 0);
    f_of = false;
}
    if (f_zf) goto L41;
{
    const uint64_t a = (uint64_t)(rsi) & ~0ULL, b = (uint64_t)(rsi) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (f_zf) goto L42;
L41:
    rax = ML_CALL(1418233c0);
L42:
{
    const uint64_t a = (uint64_t)(rdi) & ~0ULL, b = (uint64_t)(r13) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    r13 = ML_M8(rsp, 0x70);
    if (!f_zf) goto L56;
    ML_M8(rsp, 0x20) = r14;
    r9 = rdi;
    r8 = (r8 & ~(uint64_t)0xFFULL) | (uint64_t)(uint8_t)(0x1ULL);
L48:
    rdx = rsp + 0x30;
    rcx = r15;
    rax = ML_CALL(141758a10);
    ML_M1(r12, 0x10) = 0x1ULL;
    rcx = ML_M8(rax, 0x0);
    rax = ML_M8(rax, 0x8);
    ML_M8(r12, 0x0) = rcx;
    goto L110;
L56:
{
    const uint64_t r = ((uint64_t)(rsi) & ~0ULL) & ((uint64_t)(rsi) & ~0ULL);
    f_zf = (r == 0); f_cf = false; f_sf = ((r & 0x8000000000000000ULL) != 0);
    f_of = false;
}
    if (!f_zf) goto L59;
    rax = ML_CALL(1418233c0);
L59:
{
    const uint64_t a = (uint64_t)(ML_M1(rdi, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L67;
    rbx = ML_M8(rdi, 0x10);
    ML_M8(rsp, 0x38) = rbx;
{
    const uint64_t a = (uint64_t)(ML_M1(rbx, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L98;
    rax = ML_CALL(1418233c0);
    goto L98;
L67:
    rax = ML_M8(rdi, 0x0);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L81;
    rbx = rax;
    rax = ML_M8(rax, 0x10);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L79;
    /* padding */
L75:
    rbx = rax;
    rax = ML_M8(rax, 0x10);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L75;
L79:
    ML_M8(rsp, 0x38) = rbx;
    goto L98;
L81:
    rax = ML_M8(rdi, 0x8);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L92;
    ;
L85:
{
    const uint64_t a = (uint64_t)(rbx) & ~0ULL, b = (uint64_t)(ML_M8(rax, 0x0)) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L92;
    rbx = rax;
    ML_M8(rsp, 0x38) = rax;
    rax = ML_M8(rax, 0x8);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L85;
L92:
{
    const uint64_t a = (uint64_t)(ML_M1(rbx, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L96;
    rax = ML_CALL(1418233c0);
    goto L98;
L96:
    rbx = rax;
    ML_M8(rsp, 0x38) = rax;
L98:
    rax = (uint64_t)(uint32_t)(ML_M4(r14, 0x0));
{
    const uint64_t a = (uint64_t)(ML_M4(rbx, 0x18)) & 0xFFFFFFFFULL, b = (uint64_t)((uint32_t)rax) & 0xFFFFFFFFULL;
    const uint64_t d = (a - b) & 0xFFFFFFFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80000000ULL) != 0);
}
    if (!f_cf) goto L105;
    ML_M8(rsp, 0x20) = r14;
    r9 = rdi;
    r8 = (uint8_t)rbp;
    goto L48;
L105:
    rcx = rsp + 0x30;
    ML_M1(r12, 0x10) = 0x0ULL;
    rax = ML_M8(rcx, 0x0);
    ML_M8(r12, 0x0) = rax;
    rax = ML_M8(rcx, 0x8);
L110:
    rbx = ML_M8(rsp, 0x78);
    rbp = ML_M8(rsp, 0x80);
    ML_M8(r12, 0x8) = rax;
    rax = r12;
    rsp = rsp + (0x40ULL);
    { const uint64_t v = ML_M8(rsp, 0); rsp += 8; r15 = v; }
    { const uint64_t v = ML_M8(rsp, 0); rsp += 8; r14 = v; }
    { const uint64_t v = ML_M8(rsp, 0); rsp += 8; r12 = v; }
    { const uint64_t v = ML_M8(rsp, 0); rsp += 8; rdi = v; }
    { const uint64_t v = ML_M8(rsp, 0); rsp += 8; rsi = v; }
    return rax;
#undef ML_CALL
    return rax;
}

__attribute__((weak)) uint64_t (*g_fnLIFT_14175bfb0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t) = nullptr;
uint64_t SynLift_1417601b0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A) {
    uint64_t rax = 0, rbx = 0, rbp = 0, rsi = 0, rdi = 0, r10 = 0, r11 = 0, r12 = 0, r13 = 0, r14 = 0, r15 = 0;
    uint64_t rcx = rcxA, rdx = rdxA, r8 = r8A, r9 = r9A;
    bool f_zf = false, f_cf = false, f_sf = false, f_of = false;
    uint8_t xmm0[16] = {0}, xmm1[16] = {0}, xmm2[16] = {0}, xmm3[16] = {0}, xmm4[16] = {0}, xmm5[16] = {0};
    alignas(16) uint8_t stkFrame[0x400] = {0};
    uint64_t rsp = (uint64_t)(uintptr_t)(stkFrame + 0x200);
#define ML_CALL(t) g_fnLIFT_##t(rcx, rdx, r8, r9, ML_M8(rsp, 0x20), ML_M8(rsp, 0x28))
    ML_M8(rsp, 0x10) = rbx;
    ML_M8(rsp, 0x18) = rbp;
    rsp -= 8; ML_M8(rsp, 0) = rsi;
    rsp -= 8; ML_M8(rsp, 0) = rdi;
    rsp -= 8; ML_M8(rsp, 0) = r12;
    rsp -= 8; ML_M8(rsp, 0) = r14;
    rsp -= 8; ML_M8(rsp, 0) = r15;
    rsp = rsp - (0x40ULL);
    rdi = ML_M8(rcx, 0x30);
    r14 = r8;
    r12 = rdx;
    rax = ML_M8(rdi, 0x8);
    r15 = rcx;
    rbp = (rbp & ~(uint64_t)0xFFULL) | (uint64_t)(uint8_t)(0x1ULL);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L28;
    r9 = (uint64_t)(uint32_t)(ML_M4(r8, 0x0));
    /* padding */
L18:
{
    const uint64_t a = (uint64_t)((uint32_t)r9) & 0xFFFFFFFFULL, b = (uint64_t)(ML_M4(rax, 0x18)) & 0xFFFFFFFFULL;
    const uint64_t d = (a - b) & 0xFFFFFFFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80000000ULL) != 0);
}
    rdi = rax;
    rbp = (rbp & ~(uint64_t)0xFFULL) | (uint64_t)(uint8_t)((f_cf) ? 1 : 0);
{
    const uint64_t r = ((uint64_t)((uint8_t)rbp) & 0xFFULL) & ((uint64_t)((uint8_t)rbp) & 0xFFULL);
    f_zf = (r == 0); f_cf = false; f_sf = ((r & 0x80ULL) != 0);
    f_of = false;
}
    if (f_zf) goto L25;
    rax = ML_M8(rax, 0x0);
    goto L26;
L25:
    rax = ML_M8(rax, 0x10);
L26:
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L18;
L28:
    rsi = ML_M8(rcx, 0x0);
    rbx = rdi;
    ML_M8(rsp, 0x30) = rsi;
    ML_M8(rsp, 0x38) = rbx;
{
    const uint64_t r = ((uint64_t)((uint8_t)rbp) & 0xFFULL) & ((uint64_t)((uint8_t)rbp) & 0xFFULL);
    f_zf = (r == 0); f_cf = false; f_sf = ((r & 0x80ULL) != 0);
    f_of = false;
}
    if (f_zf) goto L98;
    rax = ML_M8(rcx, 0x30);
    ML_M8(rsp, 0x70) = r13;
    r13 = ML_M8(rax, 0x0);
{
    const uint64_t r = ((uint64_t)(rsi) & ~0ULL) & ((uint64_t)(rsi) & ~0ULL);
    f_zf = (r == 0); f_cf = false; f_sf = ((r & 0x8000000000000000ULL) != 0);
    f_of = false;
}
    if (f_zf) goto L41;
{
    const uint64_t a = (uint64_t)(rsi) & ~0ULL, b = (uint64_t)(rsi) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (f_zf) goto L42;
L41:
    rax = ML_CALL(1418233c0);
L42:
{
    const uint64_t a = (uint64_t)(rdi) & ~0ULL, b = (uint64_t)(r13) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    r13 = ML_M8(rsp, 0x70);
    if (!f_zf) goto L56;
    ML_M8(rsp, 0x20) = r14;
    r9 = rdi;
    r8 = (r8 & ~(uint64_t)0xFFULL) | (uint64_t)(uint8_t)(0x1ULL);
L48:
    rdx = rsp + 0x30;
    rcx = r15;
    rax = ML_CALL(14175bfb0);
    ML_M1(r12, 0x10) = 0x1ULL;
    rcx = ML_M8(rax, 0x0);
    rax = ML_M8(rax, 0x8);
    ML_M8(r12, 0x0) = rcx;
    goto L110;
L56:
{
    const uint64_t r = ((uint64_t)(rsi) & ~0ULL) & ((uint64_t)(rsi) & ~0ULL);
    f_zf = (r == 0); f_cf = false; f_sf = ((r & 0x8000000000000000ULL) != 0);
    f_of = false;
}
    if (!f_zf) goto L59;
    rax = ML_CALL(1418233c0);
L59:
{
    const uint64_t a = (uint64_t)(ML_M1(rdi, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L67;
    rbx = ML_M8(rdi, 0x10);
    ML_M8(rsp, 0x38) = rbx;
{
    const uint64_t a = (uint64_t)(ML_M1(rbx, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L98;
    rax = ML_CALL(1418233c0);
    goto L98;
L67:
    rax = ML_M8(rdi, 0x0);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L81;
    rbx = rax;
    rax = ML_M8(rax, 0x10);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L79;
    /* padding */
L75:
    rbx = rax;
    rax = ML_M8(rax, 0x10);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L75;
L79:
    ML_M8(rsp, 0x38) = rbx;
    goto L98;
L81:
    rax = ML_M8(rdi, 0x8);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L92;
    ;
L85:
{
    const uint64_t a = (uint64_t)(rbx) & ~0ULL, b = (uint64_t)(ML_M8(rax, 0x0)) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L92;
    rbx = rax;
    ML_M8(rsp, 0x38) = rax;
    rax = ML_M8(rax, 0x8);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L85;
L92:
{
    const uint64_t a = (uint64_t)(ML_M1(rbx, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L96;
    rax = ML_CALL(1418233c0);
    goto L98;
L96:
    rbx = rax;
    ML_M8(rsp, 0x38) = rax;
L98:
    rax = (uint64_t)(uint32_t)(ML_M4(r14, 0x0));
{
    const uint64_t a = (uint64_t)(ML_M4(rbx, 0x18)) & 0xFFFFFFFFULL, b = (uint64_t)((uint32_t)rax) & 0xFFFFFFFFULL;
    const uint64_t d = (a - b) & 0xFFFFFFFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80000000ULL) != 0);
}
    if (!f_cf) goto L105;
    ML_M8(rsp, 0x20) = r14;
    r9 = rdi;
    r8 = (uint8_t)rbp;
    goto L48;
L105:
    rcx = rsp + 0x30;
    ML_M1(r12, 0x10) = 0x0ULL;
    rax = ML_M8(rcx, 0x0);
    ML_M8(r12, 0x0) = rax;
    rax = ML_M8(rcx, 0x8);
L110:
    rbx = ML_M8(rsp, 0x78);
    rbp = ML_M8(rsp, 0x80);
    ML_M8(r12, 0x8) = rax;
    rax = r12;
    rsp = rsp + (0x40ULL);
    { const uint64_t v = ML_M8(rsp, 0); rsp += 8; r15 = v; }
    { const uint64_t v = ML_M8(rsp, 0); rsp += 8; r14 = v; }
    { const uint64_t v = ML_M8(rsp, 0); rsp += 8; r12 = v; }
    { const uint64_t v = ML_M8(rsp, 0); rsp += 8; rdi = v; }
    { const uint64_t v = ML_M8(rsp, 0); rsp += 8; rsi = v; }
    return rax;
#undef ML_CALL
    return rax;
}

__attribute__((weak)) uint64_t (*g_fnLIFT_14175c600)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t) = nullptr;
uint64_t SynLift_1417607a0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A) {
    uint64_t rax = 0, rbx = 0, rbp = 0, rsi = 0, rdi = 0, r10 = 0, r11 = 0, r12 = 0, r13 = 0, r14 = 0, r15 = 0;
    uint64_t rcx = rcxA, rdx = rdxA, r8 = r8A, r9 = r9A;
    bool f_zf = false, f_cf = false, f_sf = false, f_of = false;
    uint8_t xmm0[16] = {0}, xmm1[16] = {0}, xmm2[16] = {0}, xmm3[16] = {0}, xmm4[16] = {0}, xmm5[16] = {0};
    alignas(16) uint8_t stkFrame[0x400] = {0};
    uint64_t rsp = (uint64_t)(uintptr_t)(stkFrame + 0x200);
#define ML_CALL(t) g_fnLIFT_##t(rcx, rdx, r8, r9, ML_M8(rsp, 0x20), ML_M8(rsp, 0x28))
    ML_M8(rsp, 0x10) = rbx;
    ML_M8(rsp, 0x18) = rbp;
    rsp -= 8; ML_M8(rsp, 0) = rsi;
    rsp -= 8; ML_M8(rsp, 0) = rdi;
    rsp -= 8; ML_M8(rsp, 0) = r12;
    rsp -= 8; ML_M8(rsp, 0) = r14;
    rsp -= 8; ML_M8(rsp, 0) = r15;
    rsp = rsp - (0x40ULL);
    rdi = ML_M8(rcx, 0x30);
    r14 = r8;
    r12 = rdx;
    rax = ML_M8(rdi, 0x8);
    r15 = rcx;
    rbp = (rbp & ~(uint64_t)0xFFULL) | (uint64_t)(uint8_t)(0x1ULL);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x59)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L28;
    r9 = (uint64_t)(uint32_t)(ML_M4(r8, 0x0));
    /* padding */
L18:
{
    const uint64_t a = (uint64_t)((uint32_t)r9) & 0xFFFFFFFFULL, b = (uint64_t)(ML_M4(rax, 0x18)) & 0xFFFFFFFFULL;
    const uint64_t d = (a - b) & 0xFFFFFFFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80000000ULL) != 0);
}
    rdi = rax;
    rbp = (rbp & ~(uint64_t)0xFFULL) | (uint64_t)(uint8_t)((f_cf) ? 1 : 0);
{
    const uint64_t r = ((uint64_t)((uint8_t)rbp) & 0xFFULL) & ((uint64_t)((uint8_t)rbp) & 0xFFULL);
    f_zf = (r == 0); f_cf = false; f_sf = ((r & 0x80ULL) != 0);
    f_of = false;
}
    if (f_zf) goto L25;
    rax = ML_M8(rax, 0x0);
    goto L26;
L25:
    rax = ML_M8(rax, 0x10);
L26:
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x59)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L18;
L28:
    rsi = ML_M8(rcx, 0x0);
    rbx = rdi;
    ML_M8(rsp, 0x30) = rsi;
    ML_M8(rsp, 0x38) = rbx;
{
    const uint64_t r = ((uint64_t)((uint8_t)rbp) & 0xFFULL) & ((uint64_t)((uint8_t)rbp) & 0xFFULL);
    f_zf = (r == 0); f_cf = false; f_sf = ((r & 0x80ULL) != 0);
    f_of = false;
}
    if (f_zf) goto L98;
    rax = ML_M8(rcx, 0x30);
    ML_M8(rsp, 0x70) = r13;
    r13 = ML_M8(rax, 0x0);
{
    const uint64_t r = ((uint64_t)(rsi) & ~0ULL) & ((uint64_t)(rsi) & ~0ULL);
    f_zf = (r == 0); f_cf = false; f_sf = ((r & 0x8000000000000000ULL) != 0);
    f_of = false;
}
    if (f_zf) goto L41;
{
    const uint64_t a = (uint64_t)(rsi) & ~0ULL, b = (uint64_t)(rsi) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (f_zf) goto L42;
L41:
    rax = ML_CALL(1418233c0);
L42:
{
    const uint64_t a = (uint64_t)(rdi) & ~0ULL, b = (uint64_t)(r13) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    r13 = ML_M8(rsp, 0x70);
    if (!f_zf) goto L56;
    ML_M8(rsp, 0x20) = r14;
    r9 = rdi;
    r8 = (r8 & ~(uint64_t)0xFFULL) | (uint64_t)(uint8_t)(0x1ULL);
L48:
    rdx = rsp + 0x30;
    rcx = r15;
    rax = ML_CALL(14175c600);
    ML_M1(r12, 0x10) = 0x1ULL;
    rcx = ML_M8(rax, 0x0);
    rax = ML_M8(rax, 0x8);
    ML_M8(r12, 0x0) = rcx;
    goto L110;
L56:
{
    const uint64_t r = ((uint64_t)(rsi) & ~0ULL) & ((uint64_t)(rsi) & ~0ULL);
    f_zf = (r == 0); f_cf = false; f_sf = ((r & 0x8000000000000000ULL) != 0);
    f_of = false;
}
    if (!f_zf) goto L59;
    rax = ML_CALL(1418233c0);
L59:
{
    const uint64_t a = (uint64_t)(ML_M1(rdi, 0x59)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L67;
    rbx = ML_M8(rdi, 0x10);
    ML_M8(rsp, 0x38) = rbx;
{
    const uint64_t a = (uint64_t)(ML_M1(rbx, 0x59)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L98;
    rax = ML_CALL(1418233c0);
    goto L98;
L67:
    rax = ML_M8(rdi, 0x0);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x59)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L81;
    rbx = rax;
    rax = ML_M8(rax, 0x10);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x59)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L79;
    /* padding */
L75:
    rbx = rax;
    rax = ML_M8(rax, 0x10);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x59)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L75;
L79:
    ML_M8(rsp, 0x38) = rbx;
    goto L98;
L81:
    rax = ML_M8(rdi, 0x8);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x59)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L92;
    ;
L85:
{
    const uint64_t a = (uint64_t)(rbx) & ~0ULL, b = (uint64_t)(ML_M8(rax, 0x0)) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L92;
    rbx = rax;
    ML_M8(rsp, 0x38) = rax;
    rax = ML_M8(rax, 0x8);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x59)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L85;
L92:
{
    const uint64_t a = (uint64_t)(ML_M1(rbx, 0x59)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L96;
    rax = ML_CALL(1418233c0);
    goto L98;
L96:
    rbx = rax;
    ML_M8(rsp, 0x38) = rax;
L98:
    rax = (uint64_t)(uint32_t)(ML_M4(r14, 0x0));
{
    const uint64_t a = (uint64_t)(ML_M4(rbx, 0x18)) & 0xFFFFFFFFULL, b = (uint64_t)((uint32_t)rax) & 0xFFFFFFFFULL;
    const uint64_t d = (a - b) & 0xFFFFFFFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80000000ULL) != 0);
}
    if (!f_cf) goto L105;
    ML_M8(rsp, 0x20) = r14;
    r9 = rdi;
    r8 = (uint8_t)rbp;
    goto L48;
L105:
    rcx = rsp + 0x30;
    ML_M1(r12, 0x10) = 0x0ULL;
    rax = ML_M8(rcx, 0x0);
    ML_M8(r12, 0x0) = rax;
    rax = ML_M8(rcx, 0x8);
L110:
    rbx = ML_M8(rsp, 0x78);
    rbp = ML_M8(rsp, 0x80);
    ML_M8(r12, 0x8) = rax;
    rax = r12;
    rsp = rsp + (0x40ULL);
    { const uint64_t v = ML_M8(rsp, 0); rsp += 8; r15 = v; }
    { const uint64_t v = ML_M8(rsp, 0); rsp += 8; r14 = v; }
    { const uint64_t v = ML_M8(rsp, 0); rsp += 8; r12 = v; }
    { const uint64_t v = ML_M8(rsp, 0); rsp += 8; rdi = v; }
    { const uint64_t v = ML_M8(rsp, 0); rsp += 8; rsi = v; }
    return rax;
#undef ML_CALL
    return rax;
}

__attribute__((weak)) uint64_t (*g_fnLIFT_14175ca70)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t) = nullptr;
uint64_t SynLift_141760bc0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A) {
    uint64_t rax = 0, rbx = 0, rbp = 0, rsi = 0, rdi = 0, r10 = 0, r11 = 0, r12 = 0, r13 = 0, r14 = 0, r15 = 0;
    uint64_t rcx = rcxA, rdx = rdxA, r8 = r8A, r9 = r9A;
    bool f_zf = false, f_cf = false, f_sf = false, f_of = false;
    uint8_t xmm0[16] = {0}, xmm1[16] = {0}, xmm2[16] = {0}, xmm3[16] = {0}, xmm4[16] = {0}, xmm5[16] = {0};
    alignas(16) uint8_t stkFrame[0x400] = {0};
    uint64_t rsp = (uint64_t)(uintptr_t)(stkFrame + 0x200);
#define ML_CALL(t) g_fnLIFT_##t(rcx, rdx, r8, r9, ML_M8(rsp, 0x20), ML_M8(rsp, 0x28))
    ML_M8(rsp, 0x10) = rbx;
    ML_M8(rsp, 0x18) = rbp;
    rsp -= 8; ML_M8(rsp, 0) = rsi;
    rsp -= 8; ML_M8(rsp, 0) = rdi;
    rsp -= 8; ML_M8(rsp, 0) = r12;
    rsp -= 8; ML_M8(rsp, 0) = r14;
    rsp -= 8; ML_M8(rsp, 0) = r15;
    rsp = rsp - (0x40ULL);
    rdi = ML_M8(rcx, 0x30);
    r14 = r8;
    r12 = rdx;
    rax = ML_M8(rdi, 0x8);
    r15 = rcx;
    rbp = (rbp & ~(uint64_t)0xFFULL) | (uint64_t)(uint8_t)(0x1ULL);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L28;
    r9 = (uint64_t)(uint32_t)(ML_M4(r8, 0x0));
    /* padding */
L18:
{
    const uint64_t a = (uint64_t)((uint32_t)r9) & 0xFFFFFFFFULL, b = (uint64_t)(ML_M4(rax, 0x18)) & 0xFFFFFFFFULL;
    const uint64_t d = (a - b) & 0xFFFFFFFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80000000ULL) != 0);
}
    rdi = rax;
    rbp = (rbp & ~(uint64_t)0xFFULL) | (uint64_t)(uint8_t)((f_cf) ? 1 : 0);
{
    const uint64_t r = ((uint64_t)((uint8_t)rbp) & 0xFFULL) & ((uint64_t)((uint8_t)rbp) & 0xFFULL);
    f_zf = (r == 0); f_cf = false; f_sf = ((r & 0x80ULL) != 0);
    f_of = false;
}
    if (f_zf) goto L25;
    rax = ML_M8(rax, 0x0);
    goto L26;
L25:
    rax = ML_M8(rax, 0x10);
L26:
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L18;
L28:
    rsi = ML_M8(rcx, 0x0);
    rbx = rdi;
    ML_M8(rsp, 0x30) = rsi;
    ML_M8(rsp, 0x38) = rbx;
{
    const uint64_t r = ((uint64_t)((uint8_t)rbp) & 0xFFULL) & ((uint64_t)((uint8_t)rbp) & 0xFFULL);
    f_zf = (r == 0); f_cf = false; f_sf = ((r & 0x80ULL) != 0);
    f_of = false;
}
    if (f_zf) goto L98;
    rax = ML_M8(rcx, 0x30);
    ML_M8(rsp, 0x70) = r13;
    r13 = ML_M8(rax, 0x0);
{
    const uint64_t r = ((uint64_t)(rsi) & ~0ULL) & ((uint64_t)(rsi) & ~0ULL);
    f_zf = (r == 0); f_cf = false; f_sf = ((r & 0x8000000000000000ULL) != 0);
    f_of = false;
}
    if (f_zf) goto L41;
{
    const uint64_t a = (uint64_t)(rsi) & ~0ULL, b = (uint64_t)(rsi) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (f_zf) goto L42;
L41:
    rax = ML_CALL(1418233c0);
L42:
{
    const uint64_t a = (uint64_t)(rdi) & ~0ULL, b = (uint64_t)(r13) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    r13 = ML_M8(rsp, 0x70);
    if (!f_zf) goto L56;
    ML_M8(rsp, 0x20) = r14;
    r9 = rdi;
    r8 = (r8 & ~(uint64_t)0xFFULL) | (uint64_t)(uint8_t)(0x1ULL);
L48:
    rdx = rsp + 0x30;
    rcx = r15;
    rax = ML_CALL(14175ca70);
    ML_M1(r12, 0x10) = 0x1ULL;
    rcx = ML_M8(rax, 0x0);
    rax = ML_M8(rax, 0x8);
    ML_M8(r12, 0x0) = rcx;
    goto L110;
L56:
{
    const uint64_t r = ((uint64_t)(rsi) & ~0ULL) & ((uint64_t)(rsi) & ~0ULL);
    f_zf = (r == 0); f_cf = false; f_sf = ((r & 0x8000000000000000ULL) != 0);
    f_of = false;
}
    if (!f_zf) goto L59;
    rax = ML_CALL(1418233c0);
L59:
{
    const uint64_t a = (uint64_t)(ML_M1(rdi, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L67;
    rbx = ML_M8(rdi, 0x10);
    ML_M8(rsp, 0x38) = rbx;
{
    const uint64_t a = (uint64_t)(ML_M1(rbx, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L98;
    rax = ML_CALL(1418233c0);
    goto L98;
L67:
    rax = ML_M8(rdi, 0x0);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L81;
    rbx = rax;
    rax = ML_M8(rax, 0x10);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L79;
    /* padding */
L75:
    rbx = rax;
    rax = ML_M8(rax, 0x10);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L75;
L79:
    ML_M8(rsp, 0x38) = rbx;
    goto L98;
L81:
    rax = ML_M8(rdi, 0x8);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L92;
    ;
L85:
{
    const uint64_t a = (uint64_t)(rbx) & ~0ULL, b = (uint64_t)(ML_M8(rax, 0x0)) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L92;
    rbx = rax;
    ML_M8(rsp, 0x38) = rax;
    rax = ML_M8(rax, 0x8);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L85;
L92:
{
    const uint64_t a = (uint64_t)(ML_M1(rbx, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L96;
    rax = ML_CALL(1418233c0);
    goto L98;
L96:
    rbx = rax;
    ML_M8(rsp, 0x38) = rax;
L98:
    rax = (uint64_t)(uint32_t)(ML_M4(r14, 0x0));
{
    const uint64_t a = (uint64_t)(ML_M4(rbx, 0x18)) & 0xFFFFFFFFULL, b = (uint64_t)((uint32_t)rax) & 0xFFFFFFFFULL;
    const uint64_t d = (a - b) & 0xFFFFFFFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80000000ULL) != 0);
}
    if (!f_cf) goto L105;
    ML_M8(rsp, 0x20) = r14;
    r9 = rdi;
    r8 = (uint8_t)rbp;
    goto L48;
L105:
    rcx = rsp + 0x30;
    ML_M1(r12, 0x10) = 0x0ULL;
    rax = ML_M8(rcx, 0x0);
    ML_M8(r12, 0x0) = rax;
    rax = ML_M8(rcx, 0x8);
L110:
    rbx = ML_M8(rsp, 0x78);
    rbp = ML_M8(rsp, 0x80);
    ML_M8(r12, 0x8) = rax;
    rax = r12;
    rsp = rsp + (0x40ULL);
    { const uint64_t v = ML_M8(rsp, 0); rsp += 8; r15 = v; }
    { const uint64_t v = ML_M8(rsp, 0); rsp += 8; r14 = v; }
    { const uint64_t v = ML_M8(rsp, 0); rsp += 8; r12 = v; }
    { const uint64_t v = ML_M8(rsp, 0); rsp += 8; rdi = v; }
    { const uint64_t v = ML_M8(rsp, 0); rsp += 8; rsi = v; }
    return rax;
#undef ML_CALL
    return rax;
}

__attribute__((weak)) uint64_t (*g_fnLIFT_14175d350)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t) = nullptr;
uint64_t SynLift_141761330(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A) {
    uint64_t rax = 0, rbx = 0, rbp = 0, rsi = 0, rdi = 0, r10 = 0, r11 = 0, r12 = 0, r13 = 0, r14 = 0, r15 = 0;
    uint64_t rcx = rcxA, rdx = rdxA, r8 = r8A, r9 = r9A;
    bool f_zf = false, f_cf = false, f_sf = false, f_of = false;
    uint8_t xmm0[16] = {0}, xmm1[16] = {0}, xmm2[16] = {0}, xmm3[16] = {0}, xmm4[16] = {0}, xmm5[16] = {0};
    alignas(16) uint8_t stkFrame[0x400] = {0};
    uint64_t rsp = (uint64_t)(uintptr_t)(stkFrame + 0x200);
#define ML_CALL(t) g_fnLIFT_##t(rcx, rdx, r8, r9, ML_M8(rsp, 0x20), ML_M8(rsp, 0x28))
    ML_M8(rsp, 0x10) = rbx;
    ML_M8(rsp, 0x18) = rbp;
    rsp -= 8; ML_M8(rsp, 0) = rsi;
    rsp -= 8; ML_M8(rsp, 0) = rdi;
    rsp -= 8; ML_M8(rsp, 0) = r12;
    rsp -= 8; ML_M8(rsp, 0) = r14;
    rsp -= 8; ML_M8(rsp, 0) = r15;
    rsp = rsp - (0x40ULL);
    rdi = ML_M8(rcx, 0x30);
    r14 = r8;
    r12 = rdx;
    rax = ML_M8(rdi, 0x8);
    r15 = rcx;
    rbp = (rbp & ~(uint64_t)0xFFULL) | (uint64_t)(uint8_t)(0x1ULL);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x2d)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L28;
    r9 = (uint64_t)(uint32_t)(ML_M4(r8, 0x0));
    /* padding */
L18:
{
    const uint64_t a = (uint64_t)((uint32_t)r9) & 0xFFFFFFFFULL, b = (uint64_t)(ML_M4(rax, 0x18)) & 0xFFFFFFFFULL;
    const uint64_t d = (a - b) & 0xFFFFFFFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80000000ULL) != 0);
}
    rdi = rax;
    rbp = (rbp & ~(uint64_t)0xFFULL) | (uint64_t)(uint8_t)((f_cf) ? 1 : 0);
{
    const uint64_t r = ((uint64_t)((uint8_t)rbp) & 0xFFULL) & ((uint64_t)((uint8_t)rbp) & 0xFFULL);
    f_zf = (r == 0); f_cf = false; f_sf = ((r & 0x80ULL) != 0);
    f_of = false;
}
    if (f_zf) goto L25;
    rax = ML_M8(rax, 0x0);
    goto L26;
L25:
    rax = ML_M8(rax, 0x10);
L26:
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x2d)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L18;
L28:
    rsi = ML_M8(rcx, 0x0);
    rbx = rdi;
    ML_M8(rsp, 0x30) = rsi;
    ML_M8(rsp, 0x38) = rbx;
{
    const uint64_t r = ((uint64_t)((uint8_t)rbp) & 0xFFULL) & ((uint64_t)((uint8_t)rbp) & 0xFFULL);
    f_zf = (r == 0); f_cf = false; f_sf = ((r & 0x80ULL) != 0);
    f_of = false;
}
    if (f_zf) goto L98;
    rax = ML_M8(rcx, 0x30);
    ML_M8(rsp, 0x70) = r13;
    r13 = ML_M8(rax, 0x0);
{
    const uint64_t r = ((uint64_t)(rsi) & ~0ULL) & ((uint64_t)(rsi) & ~0ULL);
    f_zf = (r == 0); f_cf = false; f_sf = ((r & 0x8000000000000000ULL) != 0);
    f_of = false;
}
    if (f_zf) goto L41;
{
    const uint64_t a = (uint64_t)(rsi) & ~0ULL, b = (uint64_t)(rsi) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (f_zf) goto L42;
L41:
    rax = ML_CALL(1418233c0);
L42:
{
    const uint64_t a = (uint64_t)(rdi) & ~0ULL, b = (uint64_t)(r13) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    r13 = ML_M8(rsp, 0x70);
    if (!f_zf) goto L56;
    ML_M8(rsp, 0x20) = r14;
    r9 = rdi;
    r8 = (r8 & ~(uint64_t)0xFFULL) | (uint64_t)(uint8_t)(0x1ULL);
L48:
    rdx = rsp + 0x30;
    rcx = r15;
    rax = ML_CALL(14175d350);
    ML_M1(r12, 0x10) = 0x1ULL;
    rcx = ML_M8(rax, 0x0);
    rax = ML_M8(rax, 0x8);
    ML_M8(r12, 0x0) = rcx;
    goto L110;
L56:
{
    const uint64_t r = ((uint64_t)(rsi) & ~0ULL) & ((uint64_t)(rsi) & ~0ULL);
    f_zf = (r == 0); f_cf = false; f_sf = ((r & 0x8000000000000000ULL) != 0);
    f_of = false;
}
    if (!f_zf) goto L59;
    rax = ML_CALL(1418233c0);
L59:
{
    const uint64_t a = (uint64_t)(ML_M1(rdi, 0x2d)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L67;
    rbx = ML_M8(rdi, 0x10);
    ML_M8(rsp, 0x38) = rbx;
{
    const uint64_t a = (uint64_t)(ML_M1(rbx, 0x2d)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L98;
    rax = ML_CALL(1418233c0);
    goto L98;
L67:
    rax = ML_M8(rdi, 0x0);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x2d)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L81;
    rbx = rax;
    rax = ML_M8(rax, 0x10);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x2d)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L79;
    /* padding */
L75:
    rbx = rax;
    rax = ML_M8(rax, 0x10);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x2d)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L75;
L79:
    ML_M8(rsp, 0x38) = rbx;
    goto L98;
L81:
    rax = ML_M8(rdi, 0x8);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x2d)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L92;
    ;
L85:
{
    const uint64_t a = (uint64_t)(rbx) & ~0ULL, b = (uint64_t)(ML_M8(rax, 0x0)) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L92;
    rbx = rax;
    ML_M8(rsp, 0x38) = rax;
    rax = ML_M8(rax, 0x8);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x2d)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L85;
L92:
{
    const uint64_t a = (uint64_t)(ML_M1(rbx, 0x2d)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L96;
    rax = ML_CALL(1418233c0);
    goto L98;
L96:
    rbx = rax;
    ML_M8(rsp, 0x38) = rax;
L98:
    rax = (uint64_t)(uint32_t)(ML_M4(r14, 0x0));
{
    const uint64_t a = (uint64_t)(ML_M4(rbx, 0x18)) & 0xFFFFFFFFULL, b = (uint64_t)((uint32_t)rax) & 0xFFFFFFFFULL;
    const uint64_t d = (a - b) & 0xFFFFFFFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80000000ULL) != 0);
}
    if (!f_cf) goto L105;
    ML_M8(rsp, 0x20) = r14;
    r9 = rdi;
    r8 = (uint8_t)rbp;
    goto L48;
L105:
    rcx = rsp + 0x30;
    ML_M1(r12, 0x10) = 0x0ULL;
    rax = ML_M8(rcx, 0x0);
    ML_M8(r12, 0x0) = rax;
    rax = ML_M8(rcx, 0x8);
L110:
    rbx = ML_M8(rsp, 0x78);
    rbp = ML_M8(rsp, 0x80);
    ML_M8(r12, 0x8) = rax;
    rax = r12;
    rsp = rsp + (0x40ULL);
    { const uint64_t v = ML_M8(rsp, 0); rsp += 8; r15 = v; }
    { const uint64_t v = ML_M8(rsp, 0); rsp += 8; r14 = v; }
    { const uint64_t v = ML_M8(rsp, 0); rsp += 8; r12 = v; }
    { const uint64_t v = ML_M8(rsp, 0); rsp += 8; rdi = v; }
    { const uint64_t v = ML_M8(rsp, 0); rsp += 8; rsi = v; }
    return rax;
#undef ML_CALL
    return rax;
}

__attribute__((weak)) uint64_t (*g_fnLIFT_141770600)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t) = nullptr;
uint64_t SynLift_141770ea0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A) {
    uint64_t rax = 0, rbx = 0, rbp = 0, rsi = 0, rdi = 0, r10 = 0, r11 = 0, r12 = 0, r13 = 0, r14 = 0, r15 = 0;
    uint64_t rcx = rcxA, rdx = rdxA, r8 = r8A, r9 = r9A;
    bool f_zf = false, f_cf = false, f_sf = false, f_of = false;
    uint8_t xmm0[16] = {0}, xmm1[16] = {0}, xmm2[16] = {0}, xmm3[16] = {0}, xmm4[16] = {0}, xmm5[16] = {0};
    alignas(16) uint8_t stkFrame[0x400] = {0};
    uint64_t rsp = (uint64_t)(uintptr_t)(stkFrame + 0x200);
#define ML_CALL(t) g_fnLIFT_##t(rcx, rdx, r8, r9, ML_M8(rsp, 0x20), ML_M8(rsp, 0x28))
    ML_M8(rsp, 0x10) = rbx;
    ML_M8(rsp, 0x18) = rbp;
    rsp -= 8; ML_M8(rsp, 0) = rsi;
    rsp -= 8; ML_M8(rsp, 0) = rdi;
    rsp -= 8; ML_M8(rsp, 0) = r12;
    rsp -= 8; ML_M8(rsp, 0) = r14;
    rsp -= 8; ML_M8(rsp, 0) = r15;
    rsp = rsp - (0x40ULL);
    rdi = ML_M8(rcx, 0x30);
    r14 = r8;
    r12 = rdx;
    rax = ML_M8(rdi, 0x8);
    r15 = rcx;
    rbp = (rbp & ~(uint64_t)0xFFULL) | (uint64_t)(uint8_t)(0x1ULL);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x61)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L28;
    r9 = (uint64_t)(uint32_t)(ML_M4(r8, 0x0));
    /* padding */
L18:
{
    const uint64_t a = (uint64_t)((uint32_t)r9) & 0xFFFFFFFFULL, b = (uint64_t)(ML_M4(rax, 0x18)) & 0xFFFFFFFFULL;
    const uint64_t d = (a - b) & 0xFFFFFFFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80000000ULL) != 0);
}
    rdi = rax;
    rbp = (rbp & ~(uint64_t)0xFFULL) | (uint64_t)(uint8_t)((f_cf) ? 1 : 0);
{
    const uint64_t r = ((uint64_t)((uint8_t)rbp) & 0xFFULL) & ((uint64_t)((uint8_t)rbp) & 0xFFULL);
    f_zf = (r == 0); f_cf = false; f_sf = ((r & 0x80ULL) != 0);
    f_of = false;
}
    if (f_zf) goto L25;
    rax = ML_M8(rax, 0x0);
    goto L26;
L25:
    rax = ML_M8(rax, 0x10);
L26:
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x61)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L18;
L28:
    rsi = ML_M8(rcx, 0x0);
    rbx = rdi;
    ML_M8(rsp, 0x30) = rsi;
    ML_M8(rsp, 0x38) = rbx;
{
    const uint64_t r = ((uint64_t)((uint8_t)rbp) & 0xFFULL) & ((uint64_t)((uint8_t)rbp) & 0xFFULL);
    f_zf = (r == 0); f_cf = false; f_sf = ((r & 0x80ULL) != 0);
    f_of = false;
}
    if (f_zf) goto L98;
    rax = ML_M8(rcx, 0x30);
    ML_M8(rsp, 0x70) = r13;
    r13 = ML_M8(rax, 0x0);
{
    const uint64_t r = ((uint64_t)(rsi) & ~0ULL) & ((uint64_t)(rsi) & ~0ULL);
    f_zf = (r == 0); f_cf = false; f_sf = ((r & 0x8000000000000000ULL) != 0);
    f_of = false;
}
    if (f_zf) goto L41;
{
    const uint64_t a = (uint64_t)(rsi) & ~0ULL, b = (uint64_t)(rsi) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (f_zf) goto L42;
L41:
    rax = ML_CALL(1418233c0);
L42:
{
    const uint64_t a = (uint64_t)(rdi) & ~0ULL, b = (uint64_t)(r13) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    r13 = ML_M8(rsp, 0x70);
    if (!f_zf) goto L56;
    ML_M8(rsp, 0x20) = r14;
    r9 = rdi;
    r8 = (r8 & ~(uint64_t)0xFFULL) | (uint64_t)(uint8_t)(0x1ULL);
L48:
    rdx = rsp + 0x30;
    rcx = r15;
    rax = ML_CALL(141770600);
    ML_M1(r12, 0x10) = 0x1ULL;
    rcx = ML_M8(rax, 0x0);
    rax = ML_M8(rax, 0x8);
    ML_M8(r12, 0x0) = rcx;
    goto L110;
L56:
{
    const uint64_t r = ((uint64_t)(rsi) & ~0ULL) & ((uint64_t)(rsi) & ~0ULL);
    f_zf = (r == 0); f_cf = false; f_sf = ((r & 0x8000000000000000ULL) != 0);
    f_of = false;
}
    if (!f_zf) goto L59;
    rax = ML_CALL(1418233c0);
L59:
{
    const uint64_t a = (uint64_t)(ML_M1(rdi, 0x61)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L67;
    rbx = ML_M8(rdi, 0x10);
    ML_M8(rsp, 0x38) = rbx;
{
    const uint64_t a = (uint64_t)(ML_M1(rbx, 0x61)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L98;
    rax = ML_CALL(1418233c0);
    goto L98;
L67:
    rax = ML_M8(rdi, 0x0);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x61)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L81;
    rbx = rax;
    rax = ML_M8(rax, 0x10);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x61)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L79;
    /* padding */
L75:
    rbx = rax;
    rax = ML_M8(rax, 0x10);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x61)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L75;
L79:
    ML_M8(rsp, 0x38) = rbx;
    goto L98;
L81:
    rax = ML_M8(rdi, 0x8);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x61)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L92;
    ;
L85:
{
    const uint64_t a = (uint64_t)(rbx) & ~0ULL, b = (uint64_t)(ML_M8(rax, 0x0)) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L92;
    rbx = rax;
    ML_M8(rsp, 0x38) = rax;
    rax = ML_M8(rax, 0x8);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x61)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L85;
L92:
{
    const uint64_t a = (uint64_t)(ML_M1(rbx, 0x61)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L96;
    rax = ML_CALL(1418233c0);
    goto L98;
L96:
    rbx = rax;
    ML_M8(rsp, 0x38) = rax;
L98:
    rax = (uint64_t)(uint32_t)(ML_M4(r14, 0x0));
{
    const uint64_t a = (uint64_t)(ML_M4(rbx, 0x18)) & 0xFFFFFFFFULL, b = (uint64_t)((uint32_t)rax) & 0xFFFFFFFFULL;
    const uint64_t d = (a - b) & 0xFFFFFFFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80000000ULL) != 0);
}
    if (!f_cf) goto L105;
    ML_M8(rsp, 0x20) = r14;
    r9 = rdi;
    r8 = (uint8_t)rbp;
    goto L48;
L105:
    rcx = rsp + 0x30;
    ML_M1(r12, 0x10) = 0x0ULL;
    rax = ML_M8(rcx, 0x0);
    ML_M8(r12, 0x0) = rax;
    rax = ML_M8(rcx, 0x8);
L110:
    rbx = ML_M8(rsp, 0x78);
    rbp = ML_M8(rsp, 0x80);
    ML_M8(r12, 0x8) = rax;
    rax = r12;
    rsp = rsp + (0x40ULL);
    { const uint64_t v = ML_M8(rsp, 0); rsp += 8; r15 = v; }
    { const uint64_t v = ML_M8(rsp, 0); rsp += 8; r14 = v; }
    { const uint64_t v = ML_M8(rsp, 0); rsp += 8; r12 = v; }
    { const uint64_t v = ML_M8(rsp, 0); rsp += 8; rdi = v; }
    { const uint64_t v = ML_M8(rsp, 0); rsp += 8; rsi = v; }
    return rax;
#undef ML_CALL
    return rax;
}

__attribute__((weak)) uint64_t (*g_fnLIFT_141771050)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t) = nullptr;
uint64_t SynLift_141773cb0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A) {
    uint64_t rax = 0, rbx = 0, rbp = 0, rsi = 0, rdi = 0, r10 = 0, r11 = 0, r12 = 0, r13 = 0, r14 = 0, r15 = 0;
    uint64_t rcx = rcxA, rdx = rdxA, r8 = r8A, r9 = r9A;
    bool f_zf = false, f_cf = false, f_sf = false, f_of = false;
    uint8_t xmm0[16] = {0}, xmm1[16] = {0}, xmm2[16] = {0}, xmm3[16] = {0}, xmm4[16] = {0}, xmm5[16] = {0};
    alignas(16) uint8_t stkFrame[0x400] = {0};
    uint64_t rsp = (uint64_t)(uintptr_t)(stkFrame + 0x200);
#define ML_CALL(t) g_fnLIFT_##t(rcx, rdx, r8, r9, ML_M8(rsp, 0x20), ML_M8(rsp, 0x28))
    ML_M8(rsp, 0x10) = rbx;
    ML_M8(rsp, 0x18) = rbp;
    rsp -= 8; ML_M8(rsp, 0) = rsi;
    rsp -= 8; ML_M8(rsp, 0) = rdi;
    rsp -= 8; ML_M8(rsp, 0) = r12;
    rsp -= 8; ML_M8(rsp, 0) = r14;
    rsp -= 8; ML_M8(rsp, 0) = r15;
    rsp = rsp - (0x40ULL);
    rdi = ML_M8(rcx, 0x30);
    r14 = r8;
    r12 = rdx;
    rax = ML_M8(rdi, 0x8);
    r15 = rcx;
    rbp = (rbp & ~(uint64_t)0xFFULL) | (uint64_t)(uint8_t)(0x1ULL);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x61)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L28;
    r9 = (uint64_t)(uint32_t)(ML_M4(r8, 0x0));
    /* padding */
L18:
{
    const uint64_t a = (uint64_t)((uint32_t)r9) & 0xFFFFFFFFULL, b = (uint64_t)(ML_M4(rax, 0x18)) & 0xFFFFFFFFULL;
    const uint64_t d = (a - b) & 0xFFFFFFFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80000000ULL) != 0);
}
    rdi = rax;
    rbp = (rbp & ~(uint64_t)0xFFULL) | (uint64_t)(uint8_t)((f_cf) ? 1 : 0);
{
    const uint64_t r = ((uint64_t)((uint8_t)rbp) & 0xFFULL) & ((uint64_t)((uint8_t)rbp) & 0xFFULL);
    f_zf = (r == 0); f_cf = false; f_sf = ((r & 0x80ULL) != 0);
    f_of = false;
}
    if (f_zf) goto L25;
    rax = ML_M8(rax, 0x0);
    goto L26;
L25:
    rax = ML_M8(rax, 0x10);
L26:
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x61)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L18;
L28:
    rsi = ML_M8(rcx, 0x0);
    rbx = rdi;
    ML_M8(rsp, 0x30) = rsi;
    ML_M8(rsp, 0x38) = rbx;
{
    const uint64_t r = ((uint64_t)((uint8_t)rbp) & 0xFFULL) & ((uint64_t)((uint8_t)rbp) & 0xFFULL);
    f_zf = (r == 0); f_cf = false; f_sf = ((r & 0x80ULL) != 0);
    f_of = false;
}
    if (f_zf) goto L98;
    rax = ML_M8(rcx, 0x30);
    ML_M8(rsp, 0x70) = r13;
    r13 = ML_M8(rax, 0x0);
{
    const uint64_t r = ((uint64_t)(rsi) & ~0ULL) & ((uint64_t)(rsi) & ~0ULL);
    f_zf = (r == 0); f_cf = false; f_sf = ((r & 0x8000000000000000ULL) != 0);
    f_of = false;
}
    if (f_zf) goto L41;
{
    const uint64_t a = (uint64_t)(rsi) & ~0ULL, b = (uint64_t)(rsi) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (f_zf) goto L42;
L41:
    rax = ML_CALL(1418233c0);
L42:
{
    const uint64_t a = (uint64_t)(rdi) & ~0ULL, b = (uint64_t)(r13) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    r13 = ML_M8(rsp, 0x70);
    if (!f_zf) goto L56;
    ML_M8(rsp, 0x20) = r14;
    r9 = rdi;
    r8 = (r8 & ~(uint64_t)0xFFULL) | (uint64_t)(uint8_t)(0x1ULL);
L48:
    rdx = rsp + 0x30;
    rcx = r15;
    rax = ML_CALL(141771050);
    ML_M1(r12, 0x10) = 0x1ULL;
    rcx = ML_M8(rax, 0x0);
    rax = ML_M8(rax, 0x8);
    ML_M8(r12, 0x0) = rcx;
    goto L110;
L56:
{
    const uint64_t r = ((uint64_t)(rsi) & ~0ULL) & ((uint64_t)(rsi) & ~0ULL);
    f_zf = (r == 0); f_cf = false; f_sf = ((r & 0x8000000000000000ULL) != 0);
    f_of = false;
}
    if (!f_zf) goto L59;
    rax = ML_CALL(1418233c0);
L59:
{
    const uint64_t a = (uint64_t)(ML_M1(rdi, 0x61)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L67;
    rbx = ML_M8(rdi, 0x10);
    ML_M8(rsp, 0x38) = rbx;
{
    const uint64_t a = (uint64_t)(ML_M1(rbx, 0x61)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L98;
    rax = ML_CALL(1418233c0);
    goto L98;
L67:
    rax = ML_M8(rdi, 0x0);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x61)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L81;
    rbx = rax;
    rax = ML_M8(rax, 0x10);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x61)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L79;
    /* padding */
L75:
    rbx = rax;
    rax = ML_M8(rax, 0x10);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x61)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L75;
L79:
    ML_M8(rsp, 0x38) = rbx;
    goto L98;
L81:
    rax = ML_M8(rdi, 0x8);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x61)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L92;
    ;
L85:
{
    const uint64_t a = (uint64_t)(rbx) & ~0ULL, b = (uint64_t)(ML_M8(rax, 0x0)) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L92;
    rbx = rax;
    ML_M8(rsp, 0x38) = rax;
    rax = ML_M8(rax, 0x8);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x61)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L85;
L92:
{
    const uint64_t a = (uint64_t)(ML_M1(rbx, 0x61)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L96;
    rax = ML_CALL(1418233c0);
    goto L98;
L96:
    rbx = rax;
    ML_M8(rsp, 0x38) = rax;
L98:
    rax = (uint64_t)(uint32_t)(ML_M4(r14, 0x0));
{
    const uint64_t a = (uint64_t)(ML_M4(rbx, 0x18)) & 0xFFFFFFFFULL, b = (uint64_t)((uint32_t)rax) & 0xFFFFFFFFULL;
    const uint64_t d = (a - b) & 0xFFFFFFFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80000000ULL) != 0);
}
    if (!f_cf) goto L105;
    ML_M8(rsp, 0x20) = r14;
    r9 = rdi;
    r8 = (uint8_t)rbp;
    goto L48;
L105:
    rcx = rsp + 0x30;
    ML_M1(r12, 0x10) = 0x0ULL;
    rax = ML_M8(rcx, 0x0);
    ML_M8(r12, 0x0) = rax;
    rax = ML_M8(rcx, 0x8);
L110:
    rbx = ML_M8(rsp, 0x78);
    rbp = ML_M8(rsp, 0x80);
    ML_M8(r12, 0x8) = rax;
    rax = r12;
    rsp = rsp + (0x40ULL);
    { const uint64_t v = ML_M8(rsp, 0); rsp += 8; r15 = v; }
    { const uint64_t v = ML_M8(rsp, 0); rsp += 8; r14 = v; }
    { const uint64_t v = ML_M8(rsp, 0); rsp += 8; r12 = v; }
    { const uint64_t v = ML_M8(rsp, 0); rsp += 8; rdi = v; }
    { const uint64_t v = ML_M8(rsp, 0); rsp += 8; rsi = v; }
    return rax;
#undef ML_CALL
    return rax;
}

__attribute__((weak)) uint64_t (*g_fnLIFT_14177af70)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t) = nullptr;
uint64_t SynLift_14177b650(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A) {
    uint64_t rax = 0, rbx = 0, rbp = 0, rsi = 0, rdi = 0, r10 = 0, r11 = 0, r12 = 0, r13 = 0, r14 = 0, r15 = 0;
    uint64_t rcx = rcxA, rdx = rdxA, r8 = r8A, r9 = r9A;
    bool f_zf = false, f_cf = false, f_sf = false, f_of = false;
    uint8_t xmm0[16] = {0}, xmm1[16] = {0}, xmm2[16] = {0}, xmm3[16] = {0}, xmm4[16] = {0}, xmm5[16] = {0};
    alignas(16) uint8_t stkFrame[0x400] = {0};
    uint64_t rsp = (uint64_t)(uintptr_t)(stkFrame + 0x200);
#define ML_CALL(t) g_fnLIFT_##t(rcx, rdx, r8, r9, ML_M8(rsp, 0x20), ML_M8(rsp, 0x28))
    ML_M8(rsp, 0x10) = rbx;
    ML_M8(rsp, 0x18) = rbp;
    rsp -= 8; ML_M8(rsp, 0) = rsi;
    rsp -= 8; ML_M8(rsp, 0) = rdi;
    rsp -= 8; ML_M8(rsp, 0) = r12;
    rsp -= 8; ML_M8(rsp, 0) = r14;
    rsp -= 8; ML_M8(rsp, 0) = r15;
    rsp = rsp - (0x40ULL);
    rdi = ML_M8(rcx, 0x30);
    r14 = r8;
    r12 = rdx;
    rax = ML_M8(rdi, 0x8);
    r15 = rcx;
    rbp = (rbp & ~(uint64_t)0xFFULL) | (uint64_t)(uint8_t)(0x1ULL);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L28;
    r9 = (uint64_t)(uint32_t)(ML_M4(r8, 0x0));
    /* padding */
L18:
{
    const uint64_t a = (uint64_t)((uint32_t)r9) & 0xFFFFFFFFULL, b = (uint64_t)(ML_M4(rax, 0x18)) & 0xFFFFFFFFULL;
    const uint64_t d = (a - b) & 0xFFFFFFFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80000000ULL) != 0);
}
    rdi = rax;
    rbp = (rbp & ~(uint64_t)0xFFULL) | (uint64_t)(uint8_t)((f_cf) ? 1 : 0);
{
    const uint64_t r = ((uint64_t)((uint8_t)rbp) & 0xFFULL) & ((uint64_t)((uint8_t)rbp) & 0xFFULL);
    f_zf = (r == 0); f_cf = false; f_sf = ((r & 0x80ULL) != 0);
    f_of = false;
}
    if (f_zf) goto L25;
    rax = ML_M8(rax, 0x0);
    goto L26;
L25:
    rax = ML_M8(rax, 0x10);
L26:
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L18;
L28:
    rsi = ML_M8(rcx, 0x0);
    rbx = rdi;
    ML_M8(rsp, 0x30) = rsi;
    ML_M8(rsp, 0x38) = rbx;
{
    const uint64_t r = ((uint64_t)((uint8_t)rbp) & 0xFFULL) & ((uint64_t)((uint8_t)rbp) & 0xFFULL);
    f_zf = (r == 0); f_cf = false; f_sf = ((r & 0x80ULL) != 0);
    f_of = false;
}
    if (f_zf) goto L98;
    rax = ML_M8(rcx, 0x30);
    ML_M8(rsp, 0x70) = r13;
    r13 = ML_M8(rax, 0x0);
{
    const uint64_t r = ((uint64_t)(rsi) & ~0ULL) & ((uint64_t)(rsi) & ~0ULL);
    f_zf = (r == 0); f_cf = false; f_sf = ((r & 0x8000000000000000ULL) != 0);
    f_of = false;
}
    if (f_zf) goto L41;
{
    const uint64_t a = (uint64_t)(rsi) & ~0ULL, b = (uint64_t)(rsi) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (f_zf) goto L42;
L41:
    rax = ML_CALL(1418233c0);
L42:
{
    const uint64_t a = (uint64_t)(rdi) & ~0ULL, b = (uint64_t)(r13) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    r13 = ML_M8(rsp, 0x70);
    if (!f_zf) goto L56;
    ML_M8(rsp, 0x20) = r14;
    r9 = rdi;
    r8 = (r8 & ~(uint64_t)0xFFULL) | (uint64_t)(uint8_t)(0x1ULL);
L48:
    rdx = rsp + 0x30;
    rcx = r15;
    rax = ML_CALL(14177af70);
    ML_M1(r12, 0x10) = 0x1ULL;
    rcx = ML_M8(rax, 0x0);
    rax = ML_M8(rax, 0x8);
    ML_M8(r12, 0x0) = rcx;
    goto L110;
L56:
{
    const uint64_t r = ((uint64_t)(rsi) & ~0ULL) & ((uint64_t)(rsi) & ~0ULL);
    f_zf = (r == 0); f_cf = false; f_sf = ((r & 0x8000000000000000ULL) != 0);
    f_of = false;
}
    if (!f_zf) goto L59;
    rax = ML_CALL(1418233c0);
L59:
{
    const uint64_t a = (uint64_t)(ML_M1(rdi, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L67;
    rbx = ML_M8(rdi, 0x10);
    ML_M8(rsp, 0x38) = rbx;
{
    const uint64_t a = (uint64_t)(ML_M1(rbx, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L98;
    rax = ML_CALL(1418233c0);
    goto L98;
L67:
    rax = ML_M8(rdi, 0x0);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L81;
    rbx = rax;
    rax = ML_M8(rax, 0x10);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L79;
    /* padding */
L75:
    rbx = rax;
    rax = ML_M8(rax, 0x10);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L75;
L79:
    ML_M8(rsp, 0x38) = rbx;
    goto L98;
L81:
    rax = ML_M8(rdi, 0x8);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L92;
    ;
L85:
{
    const uint64_t a = (uint64_t)(rbx) & ~0ULL, b = (uint64_t)(ML_M8(rax, 0x0)) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L92;
    rbx = rax;
    ML_M8(rsp, 0x38) = rax;
    rax = ML_M8(rax, 0x8);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L85;
L92:
{
    const uint64_t a = (uint64_t)(ML_M1(rbx, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L96;
    rax = ML_CALL(1418233c0);
    goto L98;
L96:
    rbx = rax;
    ML_M8(rsp, 0x38) = rax;
L98:
    rax = (uint64_t)(uint32_t)(ML_M4(r14, 0x0));
{
    const uint64_t a = (uint64_t)(ML_M4(rbx, 0x18)) & 0xFFFFFFFFULL, b = (uint64_t)((uint32_t)rax) & 0xFFFFFFFFULL;
    const uint64_t d = (a - b) & 0xFFFFFFFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80000000ULL) != 0);
}
    if (!f_cf) goto L105;
    ML_M8(rsp, 0x20) = r14;
    r9 = rdi;
    r8 = (uint8_t)rbp;
    goto L48;
L105:
    rcx = rsp + 0x30;
    ML_M1(r12, 0x10) = 0x0ULL;
    rax = ML_M8(rcx, 0x0);
    ML_M8(r12, 0x0) = rax;
    rax = ML_M8(rcx, 0x8);
L110:
    rbx = ML_M8(rsp, 0x78);
    rbp = ML_M8(rsp, 0x80);
    ML_M8(r12, 0x8) = rax;
    rax = r12;
    rsp = rsp + (0x40ULL);
    { const uint64_t v = ML_M8(rsp, 0); rsp += 8; r15 = v; }
    { const uint64_t v = ML_M8(rsp, 0); rsp += 8; r14 = v; }
    { const uint64_t v = ML_M8(rsp, 0); rsp += 8; r12 = v; }
    { const uint64_t v = ML_M8(rsp, 0); rsp += 8; rdi = v; }
    { const uint64_t v = ML_M8(rsp, 0); rsp += 8; rsi = v; }
    return rax;
#undef ML_CALL
    return rax;
}

__attribute__((weak)) uint64_t (*g_fnLIFT_14178ba80)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t) = nullptr;
uint64_t SynLift_14178cb80(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A) {
    uint64_t rax = 0, rbx = 0, rbp = 0, rsi = 0, rdi = 0, r10 = 0, r11 = 0, r12 = 0, r13 = 0, r14 = 0, r15 = 0;
    uint64_t rcx = rcxA, rdx = rdxA, r8 = r8A, r9 = r9A;
    bool f_zf = false, f_cf = false, f_sf = false, f_of = false;
    uint8_t xmm0[16] = {0}, xmm1[16] = {0}, xmm2[16] = {0}, xmm3[16] = {0}, xmm4[16] = {0}, xmm5[16] = {0};
    alignas(16) uint8_t stkFrame[0x400] = {0};
    uint64_t rsp = (uint64_t)(uintptr_t)(stkFrame + 0x200);
#define ML_CALL(t) g_fnLIFT_##t(rcx, rdx, r8, r9, ML_M8(rsp, 0x20), ML_M8(rsp, 0x28))
    ML_M8(rsp, 0x10) = rbx;
    ML_M8(rsp, 0x18) = rbp;
    rsp -= 8; ML_M8(rsp, 0) = rsi;
    rsp -= 8; ML_M8(rsp, 0) = rdi;
    rsp -= 8; ML_M8(rsp, 0) = r12;
    rsp -= 8; ML_M8(rsp, 0) = r14;
    rsp -= 8; ML_M8(rsp, 0) = r15;
    rsp = rsp - (0x40ULL);
    rdi = ML_M8(rcx, 0x30);
    r14 = r8;
    r12 = rdx;
    rax = ML_M8(rdi, 0x8);
    r15 = rcx;
    rbp = (rbp & ~(uint64_t)0xFFULL) | (uint64_t)(uint8_t)(0x1ULL);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L28;
    r9 = (uint64_t)(uint32_t)(ML_M4(r8, 0x0));
    /* padding */
L18:
{
    const uint64_t a = (uint64_t)((uint32_t)r9) & 0xFFFFFFFFULL, b = (uint64_t)(ML_M4(rax, 0x18)) & 0xFFFFFFFFULL;
    const uint64_t d = (a - b) & 0xFFFFFFFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80000000ULL) != 0);
}
    rdi = rax;
    rbp = (rbp & ~(uint64_t)0xFFULL) | (uint64_t)(uint8_t)((f_cf) ? 1 : 0);
{
    const uint64_t r = ((uint64_t)((uint8_t)rbp) & 0xFFULL) & ((uint64_t)((uint8_t)rbp) & 0xFFULL);
    f_zf = (r == 0); f_cf = false; f_sf = ((r & 0x80ULL) != 0);
    f_of = false;
}
    if (f_zf) goto L25;
    rax = ML_M8(rax, 0x0);
    goto L26;
L25:
    rax = ML_M8(rax, 0x10);
L26:
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L18;
L28:
    rsi = ML_M8(rcx, 0x0);
    rbx = rdi;
    ML_M8(rsp, 0x30) = rsi;
    ML_M8(rsp, 0x38) = rbx;
{
    const uint64_t r = ((uint64_t)((uint8_t)rbp) & 0xFFULL) & ((uint64_t)((uint8_t)rbp) & 0xFFULL);
    f_zf = (r == 0); f_cf = false; f_sf = ((r & 0x80ULL) != 0);
    f_of = false;
}
    if (f_zf) goto L98;
    rax = ML_M8(rcx, 0x30);
    ML_M8(rsp, 0x70) = r13;
    r13 = ML_M8(rax, 0x0);
{
    const uint64_t r = ((uint64_t)(rsi) & ~0ULL) & ((uint64_t)(rsi) & ~0ULL);
    f_zf = (r == 0); f_cf = false; f_sf = ((r & 0x8000000000000000ULL) != 0);
    f_of = false;
}
    if (f_zf) goto L41;
{
    const uint64_t a = (uint64_t)(rsi) & ~0ULL, b = (uint64_t)(rsi) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (f_zf) goto L42;
L41:
    rax = ML_CALL(1418233c0);
L42:
{
    const uint64_t a = (uint64_t)(rdi) & ~0ULL, b = (uint64_t)(r13) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    r13 = ML_M8(rsp, 0x70);
    if (!f_zf) goto L56;
    ML_M8(rsp, 0x20) = r14;
    r9 = rdi;
    r8 = (r8 & ~(uint64_t)0xFFULL) | (uint64_t)(uint8_t)(0x1ULL);
L48:
    rdx = rsp + 0x30;
    rcx = r15;
    rax = ML_CALL(14178ba80);
    ML_M1(r12, 0x10) = 0x1ULL;
    rcx = ML_M8(rax, 0x0);
    rax = ML_M8(rax, 0x8);
    ML_M8(r12, 0x0) = rcx;
    goto L110;
L56:
{
    const uint64_t r = ((uint64_t)(rsi) & ~0ULL) & ((uint64_t)(rsi) & ~0ULL);
    f_zf = (r == 0); f_cf = false; f_sf = ((r & 0x8000000000000000ULL) != 0);
    f_of = false;
}
    if (!f_zf) goto L59;
    rax = ML_CALL(1418233c0);
L59:
{
    const uint64_t a = (uint64_t)(ML_M1(rdi, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L67;
    rbx = ML_M8(rdi, 0x10);
    ML_M8(rsp, 0x38) = rbx;
{
    const uint64_t a = (uint64_t)(ML_M1(rbx, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L98;
    rax = ML_CALL(1418233c0);
    goto L98;
L67:
    rax = ML_M8(rdi, 0x0);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L81;
    rbx = rax;
    rax = ML_M8(rax, 0x10);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L79;
    /* padding */
L75:
    rbx = rax;
    rax = ML_M8(rax, 0x10);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L75;
L79:
    ML_M8(rsp, 0x38) = rbx;
    goto L98;
L81:
    rax = ML_M8(rdi, 0x8);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L92;
    ;
L85:
{
    const uint64_t a = (uint64_t)(rbx) & ~0ULL, b = (uint64_t)(ML_M8(rax, 0x0)) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L92;
    rbx = rax;
    ML_M8(rsp, 0x38) = rax;
    rax = ML_M8(rax, 0x8);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L85;
L92:
{
    const uint64_t a = (uint64_t)(ML_M1(rbx, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L96;
    rax = ML_CALL(1418233c0);
    goto L98;
L96:
    rbx = rax;
    ML_M8(rsp, 0x38) = rax;
L98:
    rax = (uint64_t)(uint32_t)(ML_M4(r14, 0x0));
{
    const uint64_t a = (uint64_t)(ML_M4(rbx, 0x18)) & 0xFFFFFFFFULL, b = (uint64_t)((uint32_t)rax) & 0xFFFFFFFFULL;
    const uint64_t d = (a - b) & 0xFFFFFFFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80000000ULL) != 0);
}
    if (!f_cf) goto L105;
    ML_M8(rsp, 0x20) = r14;
    r9 = rdi;
    r8 = (uint8_t)rbp;
    goto L48;
L105:
    rcx = rsp + 0x30;
    ML_M1(r12, 0x10) = 0x0ULL;
    rax = ML_M8(rcx, 0x0);
    ML_M8(r12, 0x0) = rax;
    rax = ML_M8(rcx, 0x8);
L110:
    rbx = ML_M8(rsp, 0x78);
    rbp = ML_M8(rsp, 0x80);
    ML_M8(r12, 0x8) = rax;
    rax = r12;
    rsp = rsp + (0x40ULL);
    { const uint64_t v = ML_M8(rsp, 0); rsp += 8; r15 = v; }
    { const uint64_t v = ML_M8(rsp, 0); rsp += 8; r14 = v; }
    { const uint64_t v = ML_M8(rsp, 0); rsp += 8; r12 = v; }
    { const uint64_t v = ML_M8(rsp, 0); rsp += 8; rdi = v; }
    { const uint64_t v = ML_M8(rsp, 0); rsp += 8; rsi = v; }
    return rax;
#undef ML_CALL
    return rax;
}

__attribute__((weak)) uint64_t (*g_fnLIFT_141794e10)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t) = nullptr;
uint64_t SynLift_1417970d0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A) {
    uint64_t rax = 0, rbx = 0, rbp = 0, rsi = 0, rdi = 0, r10 = 0, r11 = 0, r12 = 0, r13 = 0, r14 = 0, r15 = 0;
    uint64_t rcx = rcxA, rdx = rdxA, r8 = r8A, r9 = r9A;
    bool f_zf = false, f_cf = false, f_sf = false, f_of = false;
    uint8_t xmm0[16] = {0}, xmm1[16] = {0}, xmm2[16] = {0}, xmm3[16] = {0}, xmm4[16] = {0}, xmm5[16] = {0};
    alignas(16) uint8_t stkFrame[0x400] = {0};
    uint64_t rsp = (uint64_t)(uintptr_t)(stkFrame + 0x200);
#define ML_CALL(t) g_fnLIFT_##t(rcx, rdx, r8, r9, ML_M8(rsp, 0x20), ML_M8(rsp, 0x28))
    ML_M8(rsp, 0x10) = rbx;
    ML_M8(rsp, 0x18) = rbp;
    rsp -= 8; ML_M8(rsp, 0) = rsi;
    rsp -= 8; ML_M8(rsp, 0) = rdi;
    rsp -= 8; ML_M8(rsp, 0) = r12;
    rsp -= 8; ML_M8(rsp, 0) = r14;
    rsp -= 8; ML_M8(rsp, 0) = r15;
    rsp = rsp - (0x40ULL);
    rdi = ML_M8(rcx, 0x30);
    r14 = r8;
    r12 = rdx;
    rax = ML_M8(rdi, 0x8);
    r15 = rcx;
    rbp = (rbp & ~(uint64_t)0xFFULL) | (uint64_t)(uint8_t)(0x1ULL);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x21)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L28;
    r9 = (uint64_t)(uint32_t)(ML_M4(r8, 0x0));
    /* padding */
L18:
{
    const uint64_t a = (uint64_t)((uint32_t)r9) & 0xFFFFFFFFULL, b = (uint64_t)(ML_M4(rax, 0x18)) & 0xFFFFFFFFULL;
    const uint64_t d = (a - b) & 0xFFFFFFFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80000000ULL) != 0);
}
    rdi = rax;
    rbp = (rbp & ~(uint64_t)0xFFULL) | (uint64_t)(uint8_t)((f_cf) ? 1 : 0);
{
    const uint64_t r = ((uint64_t)((uint8_t)rbp) & 0xFFULL) & ((uint64_t)((uint8_t)rbp) & 0xFFULL);
    f_zf = (r == 0); f_cf = false; f_sf = ((r & 0x80ULL) != 0);
    f_of = false;
}
    if (f_zf) goto L25;
    rax = ML_M8(rax, 0x0);
    goto L26;
L25:
    rax = ML_M8(rax, 0x10);
L26:
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x21)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L18;
L28:
    rsi = ML_M8(rcx, 0x0);
    rbx = rdi;
    ML_M8(rsp, 0x30) = rsi;
    ML_M8(rsp, 0x38) = rbx;
{
    const uint64_t r = ((uint64_t)((uint8_t)rbp) & 0xFFULL) & ((uint64_t)((uint8_t)rbp) & 0xFFULL);
    f_zf = (r == 0); f_cf = false; f_sf = ((r & 0x80ULL) != 0);
    f_of = false;
}
    if (f_zf) goto L98;
    rax = ML_M8(rcx, 0x30);
    ML_M8(rsp, 0x70) = r13;
    r13 = ML_M8(rax, 0x0);
{
    const uint64_t r = ((uint64_t)(rsi) & ~0ULL) & ((uint64_t)(rsi) & ~0ULL);
    f_zf = (r == 0); f_cf = false; f_sf = ((r & 0x8000000000000000ULL) != 0);
    f_of = false;
}
    if (f_zf) goto L41;
{
    const uint64_t a = (uint64_t)(rsi) & ~0ULL, b = (uint64_t)(rsi) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (f_zf) goto L42;
L41:
    rax = ML_CALL(1418233c0);
L42:
{
    const uint64_t a = (uint64_t)(rdi) & ~0ULL, b = (uint64_t)(r13) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    r13 = ML_M8(rsp, 0x70);
    if (!f_zf) goto L56;
    ML_M8(rsp, 0x20) = r14;
    r9 = rdi;
    r8 = (r8 & ~(uint64_t)0xFFULL) | (uint64_t)(uint8_t)(0x1ULL);
L48:
    rdx = rsp + 0x30;
    rcx = r15;
    rax = ML_CALL(141794e10);
    ML_M1(r12, 0x10) = 0x1ULL;
    rcx = ML_M8(rax, 0x0);
    rax = ML_M8(rax, 0x8);
    ML_M8(r12, 0x0) = rcx;
    goto L110;
L56:
{
    const uint64_t r = ((uint64_t)(rsi) & ~0ULL) & ((uint64_t)(rsi) & ~0ULL);
    f_zf = (r == 0); f_cf = false; f_sf = ((r & 0x8000000000000000ULL) != 0);
    f_of = false;
}
    if (!f_zf) goto L59;
    rax = ML_CALL(1418233c0);
L59:
{
    const uint64_t a = (uint64_t)(ML_M1(rdi, 0x21)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L67;
    rbx = ML_M8(rdi, 0x10);
    ML_M8(rsp, 0x38) = rbx;
{
    const uint64_t a = (uint64_t)(ML_M1(rbx, 0x21)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L98;
    rax = ML_CALL(1418233c0);
    goto L98;
L67:
    rax = ML_M8(rdi, 0x0);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x21)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L81;
    rbx = rax;
    rax = ML_M8(rax, 0x10);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x21)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L79;
    /* padding */
L75:
    rbx = rax;
    rax = ML_M8(rax, 0x10);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x21)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L75;
L79:
    ML_M8(rsp, 0x38) = rbx;
    goto L98;
L81:
    rax = ML_M8(rdi, 0x8);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x21)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L92;
    ;
L85:
{
    const uint64_t a = (uint64_t)(rbx) & ~0ULL, b = (uint64_t)(ML_M8(rax, 0x0)) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L92;
    rbx = rax;
    ML_M8(rsp, 0x38) = rax;
    rax = ML_M8(rax, 0x8);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x21)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L85;
L92:
{
    const uint64_t a = (uint64_t)(ML_M1(rbx, 0x21)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L96;
    rax = ML_CALL(1418233c0);
    goto L98;
L96:
    rbx = rax;
    ML_M8(rsp, 0x38) = rax;
L98:
    rax = (uint64_t)(uint32_t)(ML_M4(r14, 0x0));
{
    const uint64_t a = (uint64_t)(ML_M4(rbx, 0x18)) & 0xFFFFFFFFULL, b = (uint64_t)((uint32_t)rax) & 0xFFFFFFFFULL;
    const uint64_t d = (a - b) & 0xFFFFFFFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80000000ULL) != 0);
}
    if (!f_cf) goto L105;
    ML_M8(rsp, 0x20) = r14;
    r9 = rdi;
    r8 = (uint8_t)rbp;
    goto L48;
L105:
    rcx = rsp + 0x30;
    ML_M1(r12, 0x10) = 0x0ULL;
    rax = ML_M8(rcx, 0x0);
    ML_M8(r12, 0x0) = rax;
    rax = ML_M8(rcx, 0x8);
L110:
    rbx = ML_M8(rsp, 0x78);
    rbp = ML_M8(rsp, 0x80);
    ML_M8(r12, 0x8) = rax;
    rax = r12;
    rsp = rsp + (0x40ULL);
    { const uint64_t v = ML_M8(rsp, 0); rsp += 8; r15 = v; }
    { const uint64_t v = ML_M8(rsp, 0); rsp += 8; r14 = v; }
    { const uint64_t v = ML_M8(rsp, 0); rsp += 8; r12 = v; }
    { const uint64_t v = ML_M8(rsp, 0); rsp += 8; rdi = v; }
    { const uint64_t v = ML_M8(rsp, 0); rsp += 8; rsi = v; }
    return rax;
#undef ML_CALL
    return rax;
}

__attribute__((weak)) uint64_t (*g_fnLIFT_141796d90)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t) = nullptr;
uint64_t SynLift_1417995c0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A) {
    uint64_t rax = 0, rbx = 0, rbp = 0, rsi = 0, rdi = 0, r10 = 0, r11 = 0, r12 = 0, r13 = 0, r14 = 0, r15 = 0;
    uint64_t rcx = rcxA, rdx = rdxA, r8 = r8A, r9 = r9A;
    bool f_zf = false, f_cf = false, f_sf = false, f_of = false;
    uint8_t xmm0[16] = {0}, xmm1[16] = {0}, xmm2[16] = {0}, xmm3[16] = {0}, xmm4[16] = {0}, xmm5[16] = {0};
    alignas(16) uint8_t stkFrame[0x400] = {0};
    uint64_t rsp = (uint64_t)(uintptr_t)(stkFrame + 0x200);
#define ML_CALL(t) g_fnLIFT_##t(rcx, rdx, r8, r9, ML_M8(rsp, 0x20), ML_M8(rsp, 0x28))
    ML_M8(rsp, 0x10) = rbx;
    ML_M8(rsp, 0x18) = rbp;
    rsp -= 8; ML_M8(rsp, 0) = rsi;
    rsp -= 8; ML_M8(rsp, 0) = rdi;
    rsp -= 8; ML_M8(rsp, 0) = r12;
    rsp -= 8; ML_M8(rsp, 0) = r14;
    rsp -= 8; ML_M8(rsp, 0) = r15;
    rsp = rsp - (0x40ULL);
    rdi = ML_M8(rcx, 0x30);
    r14 = r8;
    r12 = rdx;
    rax = ML_M8(rdi, 0x8);
    r15 = rcx;
    rbp = (rbp & ~(uint64_t)0xFFULL) | (uint64_t)(uint8_t)(0x1ULL);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L28;
    r9 = (uint64_t)(uint32_t)(ML_M4(r8, 0x0));
    /* padding */
L18:
{
    const uint64_t a = (uint64_t)((uint32_t)r9) & 0xFFFFFFFFULL, b = (uint64_t)(ML_M4(rax, 0x18)) & 0xFFFFFFFFULL;
    const uint64_t d = (a - b) & 0xFFFFFFFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80000000ULL) != 0);
}
    rdi = rax;
    rbp = (rbp & ~(uint64_t)0xFFULL) | (uint64_t)(uint8_t)((f_cf) ? 1 : 0);
{
    const uint64_t r = ((uint64_t)((uint8_t)rbp) & 0xFFULL) & ((uint64_t)((uint8_t)rbp) & 0xFFULL);
    f_zf = (r == 0); f_cf = false; f_sf = ((r & 0x80ULL) != 0);
    f_of = false;
}
    if (f_zf) goto L25;
    rax = ML_M8(rax, 0x0);
    goto L26;
L25:
    rax = ML_M8(rax, 0x10);
L26:
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L18;
L28:
    rsi = ML_M8(rcx, 0x0);
    rbx = rdi;
    ML_M8(rsp, 0x30) = rsi;
    ML_M8(rsp, 0x38) = rbx;
{
    const uint64_t r = ((uint64_t)((uint8_t)rbp) & 0xFFULL) & ((uint64_t)((uint8_t)rbp) & 0xFFULL);
    f_zf = (r == 0); f_cf = false; f_sf = ((r & 0x80ULL) != 0);
    f_of = false;
}
    if (f_zf) goto L98;
    rax = ML_M8(rcx, 0x30);
    ML_M8(rsp, 0x70) = r13;
    r13 = ML_M8(rax, 0x0);
{
    const uint64_t r = ((uint64_t)(rsi) & ~0ULL) & ((uint64_t)(rsi) & ~0ULL);
    f_zf = (r == 0); f_cf = false; f_sf = ((r & 0x8000000000000000ULL) != 0);
    f_of = false;
}
    if (f_zf) goto L41;
{
    const uint64_t a = (uint64_t)(rsi) & ~0ULL, b = (uint64_t)(rsi) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (f_zf) goto L42;
L41:
    rax = ML_CALL(1418233c0);
L42:
{
    const uint64_t a = (uint64_t)(rdi) & ~0ULL, b = (uint64_t)(r13) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    r13 = ML_M8(rsp, 0x70);
    if (!f_zf) goto L56;
    ML_M8(rsp, 0x20) = r14;
    r9 = rdi;
    r8 = (r8 & ~(uint64_t)0xFFULL) | (uint64_t)(uint8_t)(0x1ULL);
L48:
    rdx = rsp + 0x30;
    rcx = r15;
    rax = ML_CALL(141796d90);
    ML_M1(r12, 0x10) = 0x1ULL;
    rcx = ML_M8(rax, 0x0);
    rax = ML_M8(rax, 0x8);
    ML_M8(r12, 0x0) = rcx;
    goto L110;
L56:
{
    const uint64_t r = ((uint64_t)(rsi) & ~0ULL) & ((uint64_t)(rsi) & ~0ULL);
    f_zf = (r == 0); f_cf = false; f_sf = ((r & 0x8000000000000000ULL) != 0);
    f_of = false;
}
    if (!f_zf) goto L59;
    rax = ML_CALL(1418233c0);
L59:
{
    const uint64_t a = (uint64_t)(ML_M1(rdi, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L67;
    rbx = ML_M8(rdi, 0x10);
    ML_M8(rsp, 0x38) = rbx;
{
    const uint64_t a = (uint64_t)(ML_M1(rbx, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L98;
    rax = ML_CALL(1418233c0);
    goto L98;
L67:
    rax = ML_M8(rdi, 0x0);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L81;
    rbx = rax;
    rax = ML_M8(rax, 0x10);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L79;
    /* padding */
L75:
    rbx = rax;
    rax = ML_M8(rax, 0x10);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L75;
L79:
    ML_M8(rsp, 0x38) = rbx;
    goto L98;
L81:
    rax = ML_M8(rdi, 0x8);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L92;
    ;
L85:
{
    const uint64_t a = (uint64_t)(rbx) & ~0ULL, b = (uint64_t)(ML_M8(rax, 0x0)) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L92;
    rbx = rax;
    ML_M8(rsp, 0x38) = rax;
    rax = ML_M8(rax, 0x8);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L85;
L92:
{
    const uint64_t a = (uint64_t)(ML_M1(rbx, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L96;
    rax = ML_CALL(1418233c0);
    goto L98;
L96:
    rbx = rax;
    ML_M8(rsp, 0x38) = rax;
L98:
    rax = (uint64_t)(uint32_t)(ML_M4(r14, 0x0));
{
    const uint64_t a = (uint64_t)(ML_M4(rbx, 0x18)) & 0xFFFFFFFFULL, b = (uint64_t)((uint32_t)rax) & 0xFFFFFFFFULL;
    const uint64_t d = (a - b) & 0xFFFFFFFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80000000ULL) != 0);
}
    if (!f_cf) goto L105;
    ML_M8(rsp, 0x20) = r14;
    r9 = rdi;
    r8 = (uint8_t)rbp;
    goto L48;
L105:
    rcx = rsp + 0x30;
    ML_M1(r12, 0x10) = 0x0ULL;
    rax = ML_M8(rcx, 0x0);
    ML_M8(r12, 0x0) = rax;
    rax = ML_M8(rcx, 0x8);
L110:
    rbx = ML_M8(rsp, 0x78);
    rbp = ML_M8(rsp, 0x80);
    ML_M8(r12, 0x8) = rax;
    rax = r12;
    rsp = rsp + (0x40ULL);
    { const uint64_t v = ML_M8(rsp, 0); rsp += 8; r15 = v; }
    { const uint64_t v = ML_M8(rsp, 0); rsp += 8; r14 = v; }
    { const uint64_t v = ML_M8(rsp, 0); rsp += 8; r12 = v; }
    { const uint64_t v = ML_M8(rsp, 0); rsp += 8; rdi = v; }
    { const uint64_t v = ML_M8(rsp, 0); rsp += 8; rsi = v; }
    return rax;
#undef ML_CALL
    return rax;
}

__attribute__((weak)) uint64_t (*g_fnLIFT_1417a79e0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t) = nullptr;
uint64_t SynLift_1417a7fb0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A) {
    uint64_t rax = 0, rbx = 0, rbp = 0, rsi = 0, rdi = 0, r10 = 0, r11 = 0, r12 = 0, r13 = 0, r14 = 0, r15 = 0;
    uint64_t rcx = rcxA, rdx = rdxA, r8 = r8A, r9 = r9A;
    bool f_zf = false, f_cf = false, f_sf = false, f_of = false;
    uint8_t xmm0[16] = {0}, xmm1[16] = {0}, xmm2[16] = {0}, xmm3[16] = {0}, xmm4[16] = {0}, xmm5[16] = {0};
    alignas(16) uint8_t stkFrame[0x400] = {0};
    uint64_t rsp = (uint64_t)(uintptr_t)(stkFrame + 0x200);
#define ML_CALL(t) g_fnLIFT_##t(rcx, rdx, r8, r9, ML_M8(rsp, 0x20), ML_M8(rsp, 0x28))
    ML_M8(rsp, 0x10) = rbx;
    ML_M8(rsp, 0x18) = rbp;
    rsp -= 8; ML_M8(rsp, 0) = rsi;
    rsp -= 8; ML_M8(rsp, 0) = rdi;
    rsp -= 8; ML_M8(rsp, 0) = r12;
    rsp -= 8; ML_M8(rsp, 0) = r14;
    rsp -= 8; ML_M8(rsp, 0) = r15;
    rsp = rsp - (0x40ULL);
    rdi = ML_M8(rcx, 0x30);
    r14 = r8;
    r12 = rdx;
    rax = ML_M8(rdi, 0x8);
    r15 = rcx;
    rbp = (rbp & ~(uint64_t)0xFFULL) | (uint64_t)(uint8_t)(0x1ULL);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L28;
    r9 = (uint64_t)(uint32_t)(ML_M4(r8, 0x0));
    /* padding */
L18:
{
    const uint64_t a = (uint64_t)((uint32_t)r9) & 0xFFFFFFFFULL, b = (uint64_t)(ML_M4(rax, 0x18)) & 0xFFFFFFFFULL;
    const uint64_t d = (a - b) & 0xFFFFFFFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80000000ULL) != 0);
}
    rdi = rax;
    rbp = (rbp & ~(uint64_t)0xFFULL) | (uint64_t)(uint8_t)((f_cf) ? 1 : 0);
{
    const uint64_t r = ((uint64_t)((uint8_t)rbp) & 0xFFULL) & ((uint64_t)((uint8_t)rbp) & 0xFFULL);
    f_zf = (r == 0); f_cf = false; f_sf = ((r & 0x80ULL) != 0);
    f_of = false;
}
    if (f_zf) goto L25;
    rax = ML_M8(rax, 0x0);
    goto L26;
L25:
    rax = ML_M8(rax, 0x10);
L26:
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L18;
L28:
    rsi = ML_M8(rcx, 0x0);
    rbx = rdi;
    ML_M8(rsp, 0x30) = rsi;
    ML_M8(rsp, 0x38) = rbx;
{
    const uint64_t r = ((uint64_t)((uint8_t)rbp) & 0xFFULL) & ((uint64_t)((uint8_t)rbp) & 0xFFULL);
    f_zf = (r == 0); f_cf = false; f_sf = ((r & 0x80ULL) != 0);
    f_of = false;
}
    if (f_zf) goto L98;
    rax = ML_M8(rcx, 0x30);
    ML_M8(rsp, 0x70) = r13;
    r13 = ML_M8(rax, 0x0);
{
    const uint64_t r = ((uint64_t)(rsi) & ~0ULL) & ((uint64_t)(rsi) & ~0ULL);
    f_zf = (r == 0); f_cf = false; f_sf = ((r & 0x8000000000000000ULL) != 0);
    f_of = false;
}
    if (f_zf) goto L41;
{
    const uint64_t a = (uint64_t)(rsi) & ~0ULL, b = (uint64_t)(rsi) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (f_zf) goto L42;
L41:
    rax = ML_CALL(1418233c0);
L42:
{
    const uint64_t a = (uint64_t)(rdi) & ~0ULL, b = (uint64_t)(r13) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    r13 = ML_M8(rsp, 0x70);
    if (!f_zf) goto L56;
    ML_M8(rsp, 0x20) = r14;
    r9 = rdi;
    r8 = (r8 & ~(uint64_t)0xFFULL) | (uint64_t)(uint8_t)(0x1ULL);
L48:
    rdx = rsp + 0x30;
    rcx = r15;
    rax = ML_CALL(1417a79e0);
    ML_M1(r12, 0x10) = 0x1ULL;
    rcx = ML_M8(rax, 0x0);
    rax = ML_M8(rax, 0x8);
    ML_M8(r12, 0x0) = rcx;
    goto L110;
L56:
{
    const uint64_t r = ((uint64_t)(rsi) & ~0ULL) & ((uint64_t)(rsi) & ~0ULL);
    f_zf = (r == 0); f_cf = false; f_sf = ((r & 0x8000000000000000ULL) != 0);
    f_of = false;
}
    if (!f_zf) goto L59;
    rax = ML_CALL(1418233c0);
L59:
{
    const uint64_t a = (uint64_t)(ML_M1(rdi, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L67;
    rbx = ML_M8(rdi, 0x10);
    ML_M8(rsp, 0x38) = rbx;
{
    const uint64_t a = (uint64_t)(ML_M1(rbx, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L98;
    rax = ML_CALL(1418233c0);
    goto L98;
L67:
    rax = ML_M8(rdi, 0x0);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L81;
    rbx = rax;
    rax = ML_M8(rax, 0x10);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L79;
    /* padding */
L75:
    rbx = rax;
    rax = ML_M8(rax, 0x10);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L75;
L79:
    ML_M8(rsp, 0x38) = rbx;
    goto L98;
L81:
    rax = ML_M8(rdi, 0x8);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L92;
    ;
L85:
{
    const uint64_t a = (uint64_t)(rbx) & ~0ULL, b = (uint64_t)(ML_M8(rax, 0x0)) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L92;
    rbx = rax;
    ML_M8(rsp, 0x38) = rax;
    rax = ML_M8(rax, 0x8);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L85;
L92:
{
    const uint64_t a = (uint64_t)(ML_M1(rbx, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L96;
    rax = ML_CALL(1418233c0);
    goto L98;
L96:
    rbx = rax;
    ML_M8(rsp, 0x38) = rax;
L98:
    rax = (uint64_t)(uint32_t)(ML_M4(r14, 0x0));
{
    const uint64_t a = (uint64_t)(ML_M4(rbx, 0x18)) & 0xFFFFFFFFULL, b = (uint64_t)((uint32_t)rax) & 0xFFFFFFFFULL;
    const uint64_t d = (a - b) & 0xFFFFFFFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80000000ULL) != 0);
}
    if (!f_cf) goto L105;
    ML_M8(rsp, 0x20) = r14;
    r9 = rdi;
    r8 = (uint8_t)rbp;
    goto L48;
L105:
    rcx = rsp + 0x30;
    ML_M1(r12, 0x10) = 0x0ULL;
    rax = ML_M8(rcx, 0x0);
    ML_M8(r12, 0x0) = rax;
    rax = ML_M8(rcx, 0x8);
L110:
    rbx = ML_M8(rsp, 0x78);
    rbp = ML_M8(rsp, 0x80);
    ML_M8(r12, 0x8) = rax;
    rax = r12;
    rsp = rsp + (0x40ULL);
    { const uint64_t v = ML_M8(rsp, 0); rsp += 8; r15 = v; }
    { const uint64_t v = ML_M8(rsp, 0); rsp += 8; r14 = v; }
    { const uint64_t v = ML_M8(rsp, 0); rsp += 8; r12 = v; }
    { const uint64_t v = ML_M8(rsp, 0); rsp += 8; rdi = v; }
    { const uint64_t v = ML_M8(rsp, 0); rsp += 8; rsi = v; }
    return rax;
#undef ML_CALL
    return rax;
}

__attribute__((weak)) uint64_t (*g_fnLIFT_1417cbb60)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t) = nullptr;
uint64_t SynLift_1417cd520(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A) {
    uint64_t rax = 0, rbx = 0, rbp = 0, rsi = 0, rdi = 0, r10 = 0, r11 = 0, r12 = 0, r13 = 0, r14 = 0, r15 = 0;
    uint64_t rcx = rcxA, rdx = rdxA, r8 = r8A, r9 = r9A;
    bool f_zf = false, f_cf = false, f_sf = false, f_of = false;
    uint8_t xmm0[16] = {0}, xmm1[16] = {0}, xmm2[16] = {0}, xmm3[16] = {0}, xmm4[16] = {0}, xmm5[16] = {0};
    alignas(16) uint8_t stkFrame[0x400] = {0};
    uint64_t rsp = (uint64_t)(uintptr_t)(stkFrame + 0x200);
#define ML_CALL(t) g_fnLIFT_##t(rcx, rdx, r8, r9, ML_M8(rsp, 0x20), ML_M8(rsp, 0x28))
    ML_M8(rsp, 0x10) = rbx;
    ML_M8(rsp, 0x18) = rbp;
    rsp -= 8; ML_M8(rsp, 0) = rsi;
    rsp -= 8; ML_M8(rsp, 0) = rdi;
    rsp -= 8; ML_M8(rsp, 0) = r12;
    rsp -= 8; ML_M8(rsp, 0) = r14;
    rsp -= 8; ML_M8(rsp, 0) = r15;
    rsp = rsp - (0x40ULL);
    rdi = ML_M8(rcx, 0x30);
    r14 = r8;
    r12 = rdx;
    rax = ML_M8(rdi, 0x8);
    r15 = rcx;
    rbp = (rbp & ~(uint64_t)0xFFULL) | (uint64_t)(uint8_t)(0x1ULL);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x21)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L28;
    r9 = (uint64_t)(uint32_t)(ML_M4(r8, 0x0));
    /* padding */
L18:
{
    const uint64_t a = (uint64_t)((uint32_t)r9) & 0xFFFFFFFFULL, b = (uint64_t)(ML_M4(rax, 0x18)) & 0xFFFFFFFFULL;
    const uint64_t d = (a - b) & 0xFFFFFFFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80000000ULL) != 0);
}
    rdi = rax;
    rbp = (rbp & ~(uint64_t)0xFFULL) | (uint64_t)(uint8_t)((f_cf) ? 1 : 0);
{
    const uint64_t r = ((uint64_t)((uint8_t)rbp) & 0xFFULL) & ((uint64_t)((uint8_t)rbp) & 0xFFULL);
    f_zf = (r == 0); f_cf = false; f_sf = ((r & 0x80ULL) != 0);
    f_of = false;
}
    if (f_zf) goto L25;
    rax = ML_M8(rax, 0x0);
    goto L26;
L25:
    rax = ML_M8(rax, 0x10);
L26:
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x21)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L18;
L28:
    rsi = ML_M8(rcx, 0x0);
    rbx = rdi;
    ML_M8(rsp, 0x30) = rsi;
    ML_M8(rsp, 0x38) = rbx;
{
    const uint64_t r = ((uint64_t)((uint8_t)rbp) & 0xFFULL) & ((uint64_t)((uint8_t)rbp) & 0xFFULL);
    f_zf = (r == 0); f_cf = false; f_sf = ((r & 0x80ULL) != 0);
    f_of = false;
}
    if (f_zf) goto L98;
    rax = ML_M8(rcx, 0x30);
    ML_M8(rsp, 0x70) = r13;
    r13 = ML_M8(rax, 0x0);
{
    const uint64_t r = ((uint64_t)(rsi) & ~0ULL) & ((uint64_t)(rsi) & ~0ULL);
    f_zf = (r == 0); f_cf = false; f_sf = ((r & 0x8000000000000000ULL) != 0);
    f_of = false;
}
    if (f_zf) goto L41;
{
    const uint64_t a = (uint64_t)(rsi) & ~0ULL, b = (uint64_t)(rsi) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (f_zf) goto L42;
L41:
    rax = ML_CALL(1418233c0);
L42:
{
    const uint64_t a = (uint64_t)(rdi) & ~0ULL, b = (uint64_t)(r13) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    r13 = ML_M8(rsp, 0x70);
    if (!f_zf) goto L56;
    ML_M8(rsp, 0x20) = r14;
    r9 = rdi;
    r8 = (r8 & ~(uint64_t)0xFFULL) | (uint64_t)(uint8_t)(0x1ULL);
L48:
    rdx = rsp + 0x30;
    rcx = r15;
    rax = ML_CALL(1417cbb60);
    ML_M1(r12, 0x10) = 0x1ULL;
    rcx = ML_M8(rax, 0x0);
    rax = ML_M8(rax, 0x8);
    ML_M8(r12, 0x0) = rcx;
    goto L110;
L56:
{
    const uint64_t r = ((uint64_t)(rsi) & ~0ULL) & ((uint64_t)(rsi) & ~0ULL);
    f_zf = (r == 0); f_cf = false; f_sf = ((r & 0x8000000000000000ULL) != 0);
    f_of = false;
}
    if (!f_zf) goto L59;
    rax = ML_CALL(1418233c0);
L59:
{
    const uint64_t a = (uint64_t)(ML_M1(rdi, 0x21)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L67;
    rbx = ML_M8(rdi, 0x10);
    ML_M8(rsp, 0x38) = rbx;
{
    const uint64_t a = (uint64_t)(ML_M1(rbx, 0x21)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L98;
    rax = ML_CALL(1418233c0);
    goto L98;
L67:
    rax = ML_M8(rdi, 0x0);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x21)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L81;
    rbx = rax;
    rax = ML_M8(rax, 0x10);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x21)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L79;
    /* padding */
L75:
    rbx = rax;
    rax = ML_M8(rax, 0x10);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x21)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L75;
L79:
    ML_M8(rsp, 0x38) = rbx;
    goto L98;
L81:
    rax = ML_M8(rdi, 0x8);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x21)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L92;
    ;
L85:
{
    const uint64_t a = (uint64_t)(rbx) & ~0ULL, b = (uint64_t)(ML_M8(rax, 0x0)) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L92;
    rbx = rax;
    ML_M8(rsp, 0x38) = rax;
    rax = ML_M8(rax, 0x8);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x21)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L85;
L92:
{
    const uint64_t a = (uint64_t)(ML_M1(rbx, 0x21)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L96;
    rax = ML_CALL(1418233c0);
    goto L98;
L96:
    rbx = rax;
    ML_M8(rsp, 0x38) = rax;
L98:
    rax = (uint64_t)(uint32_t)(ML_M4(r14, 0x0));
{
    const uint64_t a = (uint64_t)(ML_M4(rbx, 0x18)) & 0xFFFFFFFFULL, b = (uint64_t)((uint32_t)rax) & 0xFFFFFFFFULL;
    const uint64_t d = (a - b) & 0xFFFFFFFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80000000ULL) != 0);
}
    if (!f_cf) goto L105;
    ML_M8(rsp, 0x20) = r14;
    r9 = rdi;
    r8 = (uint8_t)rbp;
    goto L48;
L105:
    rcx = rsp + 0x30;
    ML_M1(r12, 0x10) = 0x0ULL;
    rax = ML_M8(rcx, 0x0);
    ML_M8(r12, 0x0) = rax;
    rax = ML_M8(rcx, 0x8);
L110:
    rbx = ML_M8(rsp, 0x78);
    rbp = ML_M8(rsp, 0x80);
    ML_M8(r12, 0x8) = rax;
    rax = r12;
    rsp = rsp + (0x40ULL);
    { const uint64_t v = ML_M8(rsp, 0); rsp += 8; r15 = v; }
    { const uint64_t v = ML_M8(rsp, 0); rsp += 8; r14 = v; }
    { const uint64_t v = ML_M8(rsp, 0); rsp += 8; r12 = v; }
    { const uint64_t v = ML_M8(rsp, 0); rsp += 8; rdi = v; }
    { const uint64_t v = ML_M8(rsp, 0); rsp += 8; rsi = v; }
    return rax;
#undef ML_CALL
    return rax;
}

}  // namespace tq
