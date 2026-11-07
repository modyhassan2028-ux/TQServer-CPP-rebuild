#include "modules/syndicate/src/synlift_stage.h"

namespace tq {

uint64_t (*g_fnLIFT_1417293c0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t) = nullptr;
uint64_t (*g_fnLIFT_1418233c0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t) = nullptr;
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

uint64_t (*g_fnLIFT_141729790)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t) = nullptr;
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

uint64_t (*g_fnLIFT_141729ba0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t) = nullptr;
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

uint64_t (*g_fnLIFT_14173c5c0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t) = nullptr;
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

uint64_t (*g_fnLIFT_14173e790)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t) = nullptr;
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

uint64_t (*g_fnLIFT_1417483e0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t) = nullptr;
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

uint64_t (*g_fnLIFT_141748820)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t) = nullptr;
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

uint64_t (*g_fnLIFT_1417585d0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t) = nullptr;
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

uint64_t (*g_fnLIFT_141758a10)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t) = nullptr;
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

uint64_t (*g_fnLIFT_14175bfb0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t) = nullptr;
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

uint64_t (*g_fnLIFT_14175c600)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t) = nullptr;
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

uint64_t (*g_fnLIFT_14175ca70)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t) = nullptr;
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

uint64_t (*g_fnLIFT_14175d350)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t) = nullptr;
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

uint64_t (*g_fnLIFT_141770600)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t) = nullptr;
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

uint64_t (*g_fnLIFT_141771050)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t) = nullptr;
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

uint64_t (*g_fnLIFT_14177af70)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t) = nullptr;
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

uint64_t (*g_fnLIFT_14178ba80)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t) = nullptr;
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

uint64_t (*g_fnLIFT_141794e10)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t) = nullptr;
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

uint64_t (*g_fnLIFT_141796d90)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t) = nullptr;
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

uint64_t (*g_fnLIFT_1417a79e0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t) = nullptr;
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

uint64_t (*g_fnLIFT_1417c9310)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t) = nullptr;
uint64_t SynLift_1417cb580(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A) {
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
    rax = ML_CALL(1417c9310);
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

uint64_t (*g_fnLIFT_1417cbb60)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t) = nullptr;
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
