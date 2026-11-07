#include "modules/syndicate/src/synlift_stage.h"

namespace tq {

__attribute__((weak)) uint64_t (*g_fnLIFT_1417c9310)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t) = nullptr;
__attribute__((weak)) uint64_t (*g_fnLIFT_1418233c0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t) = nullptr;
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

__attribute__((weak)) uint64_t (*g_fnLIFT_141727640)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t) = nullptr;
__attribute__((weak)) uint64_t (*g_fnLIFT_141728290)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t) = nullptr;
uint64_t SynLift_14172a410(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A) {
    uint64_t rax = 0, rbx = 0, rbp = 0, rsi = 0, rdi = 0, r10 = 0, r11 = 0, r12 = 0, r13 = 0, r14 = 0, r15 = 0;
    uint64_t rcx = rcxA, rdx = rdxA, r8 = r8A, r9 = r9A;
    bool f_zf = false, f_cf = false, f_sf = false, f_of = false;
    uint8_t xmm0[16] = {0}, xmm1[16] = {0}, xmm2[16] = {0}, xmm3[16] = {0}, xmm4[16] = {0}, xmm5[16] = {0};
    alignas(16) uint8_t stkFrame[0x400] = {0};
    uint64_t rsp = (uint64_t)(uintptr_t)(stkFrame + 0x200);
#define ML_CALL(t) g_fnLIFT_##t(rcx, rdx, r8, r9, ML_M8(rsp, 0x20), ML_M8(rsp, 0x28))
    ML_M8(rsp, 0x8) = rbx;
    ML_M8(rsp, 0x10) = rbp;
    ML_M8(rsp, 0x18) = rsi;
    ML_M8(rsp, 0x20) = rdi;
    rsp -= 8; ML_M8(rsp, 0) = r12;
    rsp = rsp - (0x50ULL);
    rax = ML_M8(rcx, 0x30);
    rsi = r9;
    rbx = r8;
    rdi = ML_M8(rax, 0x0);
    rax = ML_M8(r8, 0x0);
    r12 = rdx;
    rbp = rcx;
{
    const uint64_t r = ((uint64_t)(rax) & ~0ULL) & ((uint64_t)(rax) & ~0ULL);
    f_zf = (r == 0); f_cf = false; f_sf = ((r & 0x8000000000000000ULL) != 0);
    f_of = false;
}
    if (f_zf) goto L17;
{
    const uint64_t a = (uint64_t)(rax) & ~0ULL, b = (uint64_t)(ML_M8(rcx, 0x0)) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (f_zf) goto L18;
L17:
    rax = ML_CALL(1418233c0);
L18:
{
    const uint64_t a = (uint64_t)(ML_M8(rbx, 0x8)) & ~0ULL, b = (uint64_t)(rdi) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L37;
    rax = ML_M8(rsi, 0x0);
    rdi = ML_M8(rbp, 0x30);
{
    const uint64_t r = ((uint64_t)(rax) & ~0ULL) & ((uint64_t)(rax) & ~0ULL);
    f_zf = (r == 0); f_cf = false; f_sf = ((r & 0x8000000000000000ULL) != 0);
    f_of = false;
}
    if (f_zf) goto L26;
{
    const uint64_t a = (uint64_t)(rax) & ~0ULL, b = (uint64_t)(ML_M8(rbp, 0x0)) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (f_zf) goto L27;
L26:
    rax = ML_CALL(1418233c0);
L27:
{
    const uint64_t a = (uint64_t)(ML_M8(rsi, 0x8)) & ~0ULL, b = (uint64_t)(rdi) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L37;
    rcx = rbp;
    rax = ML_CALL(141727640);
    r11 = ML_M8(rbp, 0x30);
    rax = ML_M8(r11, 0x0);
    ML_M8(r12, 0x8) = rax;
    rax = ML_M8(rbp, 0x0);
    ML_M8(r12, 0x0) = rax;
    goto L101;
L37:
    rax = ML_M8(rbx, 0x0);
{
    const uint64_t r = ((uint64_t)(rax) & ~0ULL) & ((uint64_t)(rax) & ~0ULL);
    f_zf = (r == 0); f_cf = false; f_sf = ((r & 0x8000000000000000ULL) != 0);
    f_of = false;
}
    if (f_zf) goto L42;
{
    const uint64_t a = (uint64_t)(rax) & ~0ULL, b = (uint64_t)(ML_M8(rsi, 0x0)) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (f_zf) goto L43;
L42:
    rax = ML_CALL(1418233c0);
L43:
    rax = ML_M8(rsi, 0x8);
{
    const uint64_t a = (uint64_t)(ML_M8(rbx, 0x8)) & ~0ULL, b = (uint64_t)(rax) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    rax = ML_M8(rbx, 0x0);
    if (f_zf) goto L88;
{
    const uint64_t a = (uint64_t)(ML_M8(rbx, 0x0)) & ~0ULL, b = (uint64_t)(0x0ULL) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    rcx = rsp + 0x20;
    ML_M8(rcx, 0x0) = rax;
    rax = ML_M8(rbx, 0x8);
    ML_M8(rcx, 0x8) = rax;
    if (!f_zf) goto L54;
    rax = ML_CALL(1418233c0);
L54:
    rax = ML_M8(rbx, 0x8);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x1d)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L59;
    rax = ML_CALL(1418233c0);
    goto L81;
L59:
    rcx = ML_M8(rax, 0x10);
{
    const uint64_t a = (uint64_t)(ML_M1(rcx, 0x1d)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L70;
    rax = ML_M8(rcx, 0x0);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x1d)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L80;
L65:
    rcx = rax;
    rax = ML_M8(rax, 0x0);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x1d)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L65;
    goto L80;
L70:
    rcx = ML_M8(rax, 0x8);
{
    const uint64_t a = (uint64_t)(ML_M1(rcx, 0x1d)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L80;
L73:
    rax = ML_M8(rcx, 0x10);
{
    const uint64_t a = (uint64_t)(ML_M8(rbx, 0x8)) & ~0ULL, b = (uint64_t)(rax) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L80;
    ML_M8(rbx, 0x8) = rcx;
    rcx = ML_M8(rcx, 0x8);
{
    const uint64_t a = (uint64_t)(ML_M1(rcx, 0x1d)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L73;
L80:
    ML_M8(rbx, 0x8) = rcx;
L81:
    __builtin_memcpy(xmm0, (uint8_t*)((uintptr_t)rsp + 32), 16);
    r8 = rsp + 0x30;
    rdx = rsp + 0x40;
    rcx = rbp;
    __builtin_memcpy((uint8_t*)((uintptr_t)rsp + 48), xmm0, 16);
    rax = ML_CALL(141728290);
    goto L37;
L88:
    rcx = rsp + 0x30;
    ML_M8(rcx, 0x0) = rax;
    rax = ML_M8(rbx, 0x8);
    ML_M8(rcx, 0x8) = rax;
    rax = ML_M8(rsp, 0x38);
    rcx = rsp + 0x20;
    ML_M8(rsp, 0x28) = rax;
    rax = ML_M8(rbp, 0x0);
    ML_M8(rsp, 0x20) = rax;
    rax = ML_M8(rcx, 0x0);
    ML_M8(r12, 0x0) = rax;
    rax = ML_M8(rcx, 0x8);
    ML_M8(r12, 0x8) = rax;
L101:
    rbx = ML_M8(rsp, 0x60);
    rbp = ML_M8(rsp, 0x68);
    rsi = ML_M8(rsp, 0x70);
    rdi = ML_M8(rsp, 0x78);
    rax = r12;
    rsp = rsp + (0x50ULL);
    { const uint64_t v = ML_M8(rsp, 0); rsp += 8; r12 = v; }
    return rax;
#undef ML_CALL
    return rax;
}

__attribute__((weak)) uint64_t (*g_fnLIFT_141728750)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t) = nullptr;
__attribute__((weak)) uint64_t (*g_fnLIFT_141728b10)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t) = nullptr;
uint64_t SynLift_14172a7c0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A) {
    uint64_t rax = 0, rbx = 0, rbp = 0, rsi = 0, rdi = 0, r10 = 0, r11 = 0, r12 = 0, r13 = 0, r14 = 0, r15 = 0;
    uint64_t rcx = rcxA, rdx = rdxA, r8 = r8A, r9 = r9A;
    bool f_zf = false, f_cf = false, f_sf = false, f_of = false;
    uint8_t xmm0[16] = {0}, xmm1[16] = {0}, xmm2[16] = {0}, xmm3[16] = {0}, xmm4[16] = {0}, xmm5[16] = {0};
    alignas(16) uint8_t stkFrame[0x400] = {0};
    uint64_t rsp = (uint64_t)(uintptr_t)(stkFrame + 0x200);
#define ML_CALL(t) g_fnLIFT_##t(rcx, rdx, r8, r9, ML_M8(rsp, 0x20), ML_M8(rsp, 0x28))
    ML_M8(rsp, 0x8) = rbx;
    ML_M8(rsp, 0x10) = rbp;
    ML_M8(rsp, 0x18) = rsi;
    ML_M8(rsp, 0x20) = rdi;
    rsp -= 8; ML_M8(rsp, 0) = r12;
    rsp = rsp - (0x50ULL);
    rax = ML_M8(rcx, 0x30);
    rsi = r9;
    rbx = r8;
    rdi = ML_M8(rax, 0x0);
    rax = ML_M8(r8, 0x0);
    r12 = rdx;
    rbp = rcx;
{
    const uint64_t r = ((uint64_t)(rax) & ~0ULL) & ((uint64_t)(rax) & ~0ULL);
    f_zf = (r == 0); f_cf = false; f_sf = ((r & 0x8000000000000000ULL) != 0);
    f_of = false;
}
    if (f_zf) goto L17;
{
    const uint64_t a = (uint64_t)(rax) & ~0ULL, b = (uint64_t)(ML_M8(rcx, 0x0)) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (f_zf) goto L18;
L17:
    rax = ML_CALL(1418233c0);
L18:
{
    const uint64_t a = (uint64_t)(ML_M8(rbx, 0x8)) & ~0ULL, b = (uint64_t)(rdi) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L37;
    rax = ML_M8(rsi, 0x0);
    rdi = ML_M8(rbp, 0x30);
{
    const uint64_t r = ((uint64_t)(rax) & ~0ULL) & ((uint64_t)(rax) & ~0ULL);
    f_zf = (r == 0); f_cf = false; f_sf = ((r & 0x8000000000000000ULL) != 0);
    f_of = false;
}
    if (f_zf) goto L26;
{
    const uint64_t a = (uint64_t)(rax) & ~0ULL, b = (uint64_t)(ML_M8(rbp, 0x0)) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (f_zf) goto L27;
L26:
    rax = ML_CALL(1418233c0);
L27:
{
    const uint64_t a = (uint64_t)(ML_M8(rsi, 0x8)) & ~0ULL, b = (uint64_t)(rdi) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L37;
    rcx = rbp;
    rax = ML_CALL(141728b10);
    r11 = ML_M8(rbp, 0x30);
    rax = ML_M8(r11, 0x0);
    ML_M8(r12, 0x8) = rax;
    rax = ML_M8(rbp, 0x0);
    ML_M8(r12, 0x0) = rax;
    goto L101;
L37:
    rax = ML_M8(rbx, 0x0);
{
    const uint64_t r = ((uint64_t)(rax) & ~0ULL) & ((uint64_t)(rax) & ~0ULL);
    f_zf = (r == 0); f_cf = false; f_sf = ((r & 0x8000000000000000ULL) != 0);
    f_of = false;
}
    if (f_zf) goto L42;
{
    const uint64_t a = (uint64_t)(rax) & ~0ULL, b = (uint64_t)(ML_M8(rsi, 0x0)) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (f_zf) goto L43;
L42:
    rax = ML_CALL(1418233c0);
L43:
    rax = ML_M8(rsi, 0x8);
{
    const uint64_t a = (uint64_t)(ML_M8(rbx, 0x8)) & ~0ULL, b = (uint64_t)(rax) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    rax = ML_M8(rbx, 0x0);
    if (f_zf) goto L88;
{
    const uint64_t a = (uint64_t)(ML_M8(rbx, 0x0)) & ~0ULL, b = (uint64_t)(0x0ULL) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    rcx = rsp + 0x20;
    ML_M8(rcx, 0x0) = rax;
    rax = ML_M8(rbx, 0x8);
    ML_M8(rcx, 0x8) = rax;
    if (!f_zf) goto L54;
    rax = ML_CALL(1418233c0);
L54:
    rax = ML_M8(rbx, 0x8);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x1b)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L59;
    rax = ML_CALL(1418233c0);
    goto L81;
L59:
    rcx = ML_M8(rax, 0x10);
{
    const uint64_t a = (uint64_t)(ML_M1(rcx, 0x1b)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L70;
    rax = ML_M8(rcx, 0x0);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x1b)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L80;
L65:
    rcx = rax;
    rax = ML_M8(rax, 0x0);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x1b)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L65;
    goto L80;
L70:
    rcx = ML_M8(rax, 0x8);
{
    const uint64_t a = (uint64_t)(ML_M1(rcx, 0x1b)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L80;
L73:
    rax = ML_M8(rcx, 0x10);
{
    const uint64_t a = (uint64_t)(ML_M8(rbx, 0x8)) & ~0ULL, b = (uint64_t)(rax) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L80;
    ML_M8(rbx, 0x8) = rcx;
    rcx = ML_M8(rcx, 0x8);
{
    const uint64_t a = (uint64_t)(ML_M1(rcx, 0x1b)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L73;
L80:
    ML_M8(rbx, 0x8) = rcx;
L81:
    __builtin_memcpy(xmm0, (uint8_t*)((uintptr_t)rsp + 32), 16);
    r8 = rsp + 0x30;
    rdx = rsp + 0x40;
    rcx = rbp;
    __builtin_memcpy((uint8_t*)((uintptr_t)rsp + 48), xmm0, 16);
    rax = ML_CALL(141728750);
    goto L37;
L88:
    rcx = rsp + 0x30;
    ML_M8(rcx, 0x0) = rax;
    rax = ML_M8(rbx, 0x8);
    ML_M8(rcx, 0x8) = rax;
    rax = ML_M8(rsp, 0x38);
    rcx = rsp + 0x20;
    ML_M8(rsp, 0x28) = rax;
    rax = ML_M8(rbp, 0x0);
    ML_M8(rsp, 0x20) = rax;
    rax = ML_M8(rcx, 0x0);
    ML_M8(r12, 0x0) = rax;
    rax = ML_M8(rcx, 0x8);
    ML_M8(r12, 0x8) = rax;
L101:
    rbx = ML_M8(rsp, 0x60);
    rbp = ML_M8(rsp, 0x68);
    rsi = ML_M8(rsp, 0x70);
    rdi = ML_M8(rsp, 0x78);
    rax = r12;
    rsp = rsp + (0x50ULL);
    { const uint64_t v = ML_M8(rsp, 0); rsp += 8; r12 = v; }
    return rax;
#undef ML_CALL
    return rax;
}

__attribute__((weak)) uint64_t (*g_fnLIFT_1417276c0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t) = nullptr;
__attribute__((weak)) uint64_t (*g_fnLIFT_14172b160)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t) = nullptr;
uint64_t SynLift_14172d3c0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A) {
    uint64_t rax = 0, rbx = 0, rbp = 0, rsi = 0, rdi = 0, r10 = 0, r11 = 0, r12 = 0, r13 = 0, r14 = 0, r15 = 0;
    uint64_t rcx = rcxA, rdx = rdxA, r8 = r8A, r9 = r9A;
    bool f_zf = false, f_cf = false, f_sf = false, f_of = false;
    uint8_t xmm0[16] = {0}, xmm1[16] = {0}, xmm2[16] = {0}, xmm3[16] = {0}, xmm4[16] = {0}, xmm5[16] = {0};
    alignas(16) uint8_t stkFrame[0x400] = {0};
    uint64_t rsp = (uint64_t)(uintptr_t)(stkFrame + 0x200);
#define ML_CALL(t) g_fnLIFT_##t(rcx, rdx, r8, r9, ML_M8(rsp, 0x20), ML_M8(rsp, 0x28))
    ML_M8(rsp, 0x8) = rbx;
    ML_M8(rsp, 0x10) = rbp;
    ML_M8(rsp, 0x18) = rsi;
    ML_M8(rsp, 0x20) = rdi;
    rsp -= 8; ML_M8(rsp, 0) = r12;
    rsp = rsp - (0x50ULL);
    rax = ML_M8(rcx, 0x30);
    rsi = r9;
    rbx = r8;
    rdi = ML_M8(rax, 0x0);
    rax = ML_M8(r8, 0x0);
    r12 = rdx;
    rbp = rcx;
{
    const uint64_t r = ((uint64_t)(rax) & ~0ULL) & ((uint64_t)(rax) & ~0ULL);
    f_zf = (r == 0); f_cf = false; f_sf = ((r & 0x8000000000000000ULL) != 0);
    f_of = false;
}
    if (f_zf) goto L17;
{
    const uint64_t a = (uint64_t)(rax) & ~0ULL, b = (uint64_t)(ML_M8(rcx, 0x0)) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (f_zf) goto L18;
L17:
    rax = ML_CALL(1418233c0);
L18:
{
    const uint64_t a = (uint64_t)(ML_M8(rbx, 0x8)) & ~0ULL, b = (uint64_t)(rdi) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L37;
    rax = ML_M8(rsi, 0x0);
    rdi = ML_M8(rbp, 0x30);
{
    const uint64_t r = ((uint64_t)(rax) & ~0ULL) & ((uint64_t)(rax) & ~0ULL);
    f_zf = (r == 0); f_cf = false; f_sf = ((r & 0x8000000000000000ULL) != 0);
    f_of = false;
}
    if (f_zf) goto L26;
{
    const uint64_t a = (uint64_t)(rax) & ~0ULL, b = (uint64_t)(ML_M8(rbp, 0x0)) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (f_zf) goto L27;
L26:
    rax = ML_CALL(1418233c0);
L27:
{
    const uint64_t a = (uint64_t)(ML_M8(rsi, 0x8)) & ~0ULL, b = (uint64_t)(rdi) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L37;
    rcx = rbp;
    rax = ML_CALL(1417276c0);
    r11 = ML_M8(rbp, 0x30);
    rax = ML_M8(r11, 0x0);
    ML_M8(r12, 0x8) = rax;
    rax = ML_M8(rbp, 0x0);
    ML_M8(r12, 0x0) = rax;
    goto L101;
L37:
    rax = ML_M8(rbx, 0x0);
{
    const uint64_t r = ((uint64_t)(rax) & ~0ULL) & ((uint64_t)(rax) & ~0ULL);
    f_zf = (r == 0); f_cf = false; f_sf = ((r & 0x8000000000000000ULL) != 0);
    f_of = false;
}
    if (f_zf) goto L42;
{
    const uint64_t a = (uint64_t)(rax) & ~0ULL, b = (uint64_t)(ML_M8(rsi, 0x0)) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (f_zf) goto L43;
L42:
    rax = ML_CALL(1418233c0);
L43:
    rax = ML_M8(rsi, 0x8);
{
    const uint64_t a = (uint64_t)(ML_M8(rbx, 0x8)) & ~0ULL, b = (uint64_t)(rax) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    rax = ML_M8(rbx, 0x0);
    if (f_zf) goto L88;
{
    const uint64_t a = (uint64_t)(ML_M8(rbx, 0x0)) & ~0ULL, b = (uint64_t)(0x0ULL) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    rcx = rsp + 0x20;
    ML_M8(rcx, 0x0) = rax;
    rax = ML_M8(rbx, 0x8);
    ML_M8(rcx, 0x8) = rax;
    if (!f_zf) goto L54;
    rax = ML_CALL(1418233c0);
L54:
    rax = ML_M8(rbx, 0x8);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L59;
    rax = ML_CALL(1418233c0);
    goto L81;
L59:
    rcx = ML_M8(rax, 0x10);
{
    const uint64_t a = (uint64_t)(ML_M1(rcx, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L70;
    rax = ML_M8(rcx, 0x0);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L80;
L65:
    rcx = rax;
    rax = ML_M8(rax, 0x0);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L65;
    goto L80;
L70:
    rcx = ML_M8(rax, 0x8);
{
    const uint64_t a = (uint64_t)(ML_M1(rcx, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L80;
L73:
    rax = ML_M8(rcx, 0x10);
{
    const uint64_t a = (uint64_t)(ML_M8(rbx, 0x8)) & ~0ULL, b = (uint64_t)(rax) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L80;
    ML_M8(rbx, 0x8) = rcx;
    rcx = ML_M8(rcx, 0x8);
{
    const uint64_t a = (uint64_t)(ML_M1(rcx, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L73;
L80:
    ML_M8(rbx, 0x8) = rcx;
L81:
    __builtin_memcpy(xmm0, (uint8_t*)((uintptr_t)rsp + 32), 16);
    r8 = rsp + 0x30;
    rdx = rsp + 0x40;
    rcx = rbp;
    __builtin_memcpy((uint8_t*)((uintptr_t)rsp + 48), xmm0, 16);
    rax = ML_CALL(14172b160);
    goto L37;
L88:
    rcx = rsp + 0x30;
    ML_M8(rcx, 0x0) = rax;
    rax = ML_M8(rbx, 0x8);
    ML_M8(rcx, 0x8) = rax;
    rax = ML_M8(rsp, 0x38);
    rcx = rsp + 0x20;
    ML_M8(rsp, 0x28) = rax;
    rax = ML_M8(rbp, 0x0);
    ML_M8(rsp, 0x20) = rax;
    rax = ML_M8(rcx, 0x0);
    ML_M8(r12, 0x0) = rax;
    rax = ML_M8(rcx, 0x8);
    ML_M8(r12, 0x8) = rax;
L101:
    rbx = ML_M8(rsp, 0x60);
    rbp = ML_M8(rsp, 0x68);
    rsi = ML_M8(rsp, 0x70);
    rdi = ML_M8(rsp, 0x78);
    rax = r12;
    rsp = rsp + (0x50ULL);
    { const uint64_t v = ML_M8(rsp, 0); rsp += 8; r12 = v; }
    return rax;
#undef ML_CALL
    return rax;
}

__attribute__((weak)) uint64_t (*g_fnLIFT_141727740)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t) = nullptr;
__attribute__((weak)) uint64_t (*g_fnLIFT_14172b870)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t) = nullptr;
uint64_t SynLift_14172d610(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A) {
    uint64_t rax = 0, rbx = 0, rbp = 0, rsi = 0, rdi = 0, r10 = 0, r11 = 0, r12 = 0, r13 = 0, r14 = 0, r15 = 0;
    uint64_t rcx = rcxA, rdx = rdxA, r8 = r8A, r9 = r9A;
    bool f_zf = false, f_cf = false, f_sf = false, f_of = false;
    uint8_t xmm0[16] = {0}, xmm1[16] = {0}, xmm2[16] = {0}, xmm3[16] = {0}, xmm4[16] = {0}, xmm5[16] = {0};
    alignas(16) uint8_t stkFrame[0x400] = {0};
    uint64_t rsp = (uint64_t)(uintptr_t)(stkFrame + 0x200);
#define ML_CALL(t) g_fnLIFT_##t(rcx, rdx, r8, r9, ML_M8(rsp, 0x20), ML_M8(rsp, 0x28))
    ML_M8(rsp, 0x8) = rbx;
    ML_M8(rsp, 0x10) = rbp;
    ML_M8(rsp, 0x18) = rsi;
    ML_M8(rsp, 0x20) = rdi;
    rsp -= 8; ML_M8(rsp, 0) = r12;
    rsp = rsp - (0x50ULL);
    rax = ML_M8(rcx, 0x30);
    rsi = r9;
    rbx = r8;
    rdi = ML_M8(rax, 0x0);
    rax = ML_M8(r8, 0x0);
    r12 = rdx;
    rbp = rcx;
{
    const uint64_t r = ((uint64_t)(rax) & ~0ULL) & ((uint64_t)(rax) & ~0ULL);
    f_zf = (r == 0); f_cf = false; f_sf = ((r & 0x8000000000000000ULL) != 0);
    f_of = false;
}
    if (f_zf) goto L17;
{
    const uint64_t a = (uint64_t)(rax) & ~0ULL, b = (uint64_t)(ML_M8(rcx, 0x0)) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (f_zf) goto L18;
L17:
    rax = ML_CALL(1418233c0);
L18:
{
    const uint64_t a = (uint64_t)(ML_M8(rbx, 0x8)) & ~0ULL, b = (uint64_t)(rdi) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L37;
    rax = ML_M8(rsi, 0x0);
    rdi = ML_M8(rbp, 0x30);
{
    const uint64_t r = ((uint64_t)(rax) & ~0ULL) & ((uint64_t)(rax) & ~0ULL);
    f_zf = (r == 0); f_cf = false; f_sf = ((r & 0x8000000000000000ULL) != 0);
    f_of = false;
}
    if (f_zf) goto L26;
{
    const uint64_t a = (uint64_t)(rax) & ~0ULL, b = (uint64_t)(ML_M8(rbp, 0x0)) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (f_zf) goto L27;
L26:
    rax = ML_CALL(1418233c0);
L27:
{
    const uint64_t a = (uint64_t)(ML_M8(rsi, 0x8)) & ~0ULL, b = (uint64_t)(rdi) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L37;
    rcx = rbp;
    rax = ML_CALL(141727740);
    r11 = ML_M8(rbp, 0x30);
    rax = ML_M8(r11, 0x0);
    ML_M8(r12, 0x8) = rax;
    rax = ML_M8(rbp, 0x0);
    ML_M8(r12, 0x0) = rax;
    goto L101;
L37:
    rax = ML_M8(rbx, 0x0);
{
    const uint64_t r = ((uint64_t)(rax) & ~0ULL) & ((uint64_t)(rax) & ~0ULL);
    f_zf = (r == 0); f_cf = false; f_sf = ((r & 0x8000000000000000ULL) != 0);
    f_of = false;
}
    if (f_zf) goto L42;
{
    const uint64_t a = (uint64_t)(rax) & ~0ULL, b = (uint64_t)(ML_M8(rsi, 0x0)) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (f_zf) goto L43;
L42:
    rax = ML_CALL(1418233c0);
L43:
    rax = ML_M8(rsi, 0x8);
{
    const uint64_t a = (uint64_t)(ML_M8(rbx, 0x8)) & ~0ULL, b = (uint64_t)(rax) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    rax = ML_M8(rbx, 0x0);
    if (f_zf) goto L88;
{
    const uint64_t a = (uint64_t)(ML_M8(rbx, 0x0)) & ~0ULL, b = (uint64_t)(0x0ULL) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    rcx = rsp + 0x20;
    ML_M8(rcx, 0x0) = rax;
    rax = ML_M8(rbx, 0x8);
    ML_M8(rcx, 0x8) = rax;
    if (!f_zf) goto L54;
    rax = ML_CALL(1418233c0);
L54:
    rax = ML_M8(rbx, 0x8);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x49)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L59;
    rax = ML_CALL(1418233c0);
    goto L81;
L59:
    rcx = ML_M8(rax, 0x10);
{
    const uint64_t a = (uint64_t)(ML_M1(rcx, 0x49)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L70;
    rax = ML_M8(rcx, 0x0);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x49)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L80;
L65:
    rcx = rax;
    rax = ML_M8(rax, 0x0);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x49)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L65;
    goto L80;
L70:
    rcx = ML_M8(rax, 0x8);
{
    const uint64_t a = (uint64_t)(ML_M1(rcx, 0x49)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L80;
L73:
    rax = ML_M8(rcx, 0x10);
{
    const uint64_t a = (uint64_t)(ML_M8(rbx, 0x8)) & ~0ULL, b = (uint64_t)(rax) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L80;
    ML_M8(rbx, 0x8) = rcx;
    rcx = ML_M8(rcx, 0x8);
{
    const uint64_t a = (uint64_t)(ML_M1(rcx, 0x49)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L73;
L80:
    ML_M8(rbx, 0x8) = rcx;
L81:
    __builtin_memcpy(xmm0, (uint8_t*)((uintptr_t)rsp + 32), 16);
    r8 = rsp + 0x30;
    rdx = rsp + 0x40;
    rcx = rbp;
    __builtin_memcpy((uint8_t*)((uintptr_t)rsp + 48), xmm0, 16);
    rax = ML_CALL(14172b870);
    goto L37;
L88:
    rcx = rsp + 0x30;
    ML_M8(rcx, 0x0) = rax;
    rax = ML_M8(rbx, 0x8);
    ML_M8(rcx, 0x8) = rax;
    rax = ML_M8(rsp, 0x38);
    rcx = rsp + 0x20;
    ML_M8(rsp, 0x28) = rax;
    rax = ML_M8(rbp, 0x0);
    ML_M8(rsp, 0x20) = rax;
    rax = ML_M8(rcx, 0x0);
    ML_M8(r12, 0x0) = rax;
    rax = ML_M8(rcx, 0x8);
    ML_M8(r12, 0x8) = rax;
L101:
    rbx = ML_M8(rsp, 0x60);
    rbp = ML_M8(rsp, 0x68);
    rsi = ML_M8(rsp, 0x70);
    rdi = ML_M8(rsp, 0x78);
    rax = r12;
    rsp = rsp + (0x50ULL);
    { const uint64_t v = ML_M8(rsp, 0); rsp += 8; r12 = v; }
    return rax;
#undef ML_CALL
    return rax;
}

__attribute__((weak)) uint64_t (*g_fnLIFT_1417277c0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t) = nullptr;
__attribute__((weak)) uint64_t (*g_fnLIFT_14172bd00)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t) = nullptr;
uint64_t SynLift_14172d810(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A) {
    uint64_t rax = 0, rbx = 0, rbp = 0, rsi = 0, rdi = 0, r10 = 0, r11 = 0, r12 = 0, r13 = 0, r14 = 0, r15 = 0;
    uint64_t rcx = rcxA, rdx = rdxA, r8 = r8A, r9 = r9A;
    bool f_zf = false, f_cf = false, f_sf = false, f_of = false;
    uint8_t xmm0[16] = {0}, xmm1[16] = {0}, xmm2[16] = {0}, xmm3[16] = {0}, xmm4[16] = {0}, xmm5[16] = {0};
    alignas(16) uint8_t stkFrame[0x400] = {0};
    uint64_t rsp = (uint64_t)(uintptr_t)(stkFrame + 0x200);
#define ML_CALL(t) g_fnLIFT_##t(rcx, rdx, r8, r9, ML_M8(rsp, 0x20), ML_M8(rsp, 0x28))
    ML_M8(rsp, 0x8) = rbx;
    ML_M8(rsp, 0x10) = rbp;
    ML_M8(rsp, 0x18) = rsi;
    ML_M8(rsp, 0x20) = rdi;
    rsp -= 8; ML_M8(rsp, 0) = r12;
    rsp = rsp - (0x50ULL);
    rax = ML_M8(rcx, 0x30);
    rsi = r9;
    rbx = r8;
    rdi = ML_M8(rax, 0x0);
    rax = ML_M8(r8, 0x0);
    r12 = rdx;
    rbp = rcx;
{
    const uint64_t r = ((uint64_t)(rax) & ~0ULL) & ((uint64_t)(rax) & ~0ULL);
    f_zf = (r == 0); f_cf = false; f_sf = ((r & 0x8000000000000000ULL) != 0);
    f_of = false;
}
    if (f_zf) goto L17;
{
    const uint64_t a = (uint64_t)(rax) & ~0ULL, b = (uint64_t)(ML_M8(rcx, 0x0)) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (f_zf) goto L18;
L17:
    rax = ML_CALL(1418233c0);
L18:
{
    const uint64_t a = (uint64_t)(ML_M8(rbx, 0x8)) & ~0ULL, b = (uint64_t)(rdi) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L37;
    rax = ML_M8(rsi, 0x0);
    rdi = ML_M8(rbp, 0x30);
{
    const uint64_t r = ((uint64_t)(rax) & ~0ULL) & ((uint64_t)(rax) & ~0ULL);
    f_zf = (r == 0); f_cf = false; f_sf = ((r & 0x8000000000000000ULL) != 0);
    f_of = false;
}
    if (f_zf) goto L26;
{
    const uint64_t a = (uint64_t)(rax) & ~0ULL, b = (uint64_t)(ML_M8(rbp, 0x0)) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (f_zf) goto L27;
L26:
    rax = ML_CALL(1418233c0);
L27:
{
    const uint64_t a = (uint64_t)(ML_M8(rsi, 0x8)) & ~0ULL, b = (uint64_t)(rdi) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L37;
    rcx = rbp;
    rax = ML_CALL(1417277c0);
    r11 = ML_M8(rbp, 0x30);
    rax = ML_M8(r11, 0x0);
    ML_M8(r12, 0x8) = rax;
    rax = ML_M8(rbp, 0x0);
    ML_M8(r12, 0x0) = rax;
    goto L101;
L37:
    rax = ML_M8(rbx, 0x0);
{
    const uint64_t r = ((uint64_t)(rax) & ~0ULL) & ((uint64_t)(rax) & ~0ULL);
    f_zf = (r == 0); f_cf = false; f_sf = ((r & 0x8000000000000000ULL) != 0);
    f_of = false;
}
    if (f_zf) goto L42;
{
    const uint64_t a = (uint64_t)(rax) & ~0ULL, b = (uint64_t)(ML_M8(rsi, 0x0)) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (f_zf) goto L43;
L42:
    rax = ML_CALL(1418233c0);
L43:
    rax = ML_M8(rsi, 0x8);
{
    const uint64_t a = (uint64_t)(ML_M8(rbx, 0x8)) & ~0ULL, b = (uint64_t)(rax) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    rax = ML_M8(rbx, 0x0);
    if (f_zf) goto L88;
{
    const uint64_t a = (uint64_t)(ML_M8(rbx, 0x0)) & ~0ULL, b = (uint64_t)(0x0ULL) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    rcx = rsp + 0x20;
    ML_M8(rcx, 0x0) = rax;
    rax = ML_M8(rbx, 0x8);
    ML_M8(rcx, 0x8) = rax;
    if (!f_zf) goto L54;
    rax = ML_CALL(1418233c0);
L54:
    rax = ML_M8(rbx, 0x8);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x1d)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L59;
    rax = ML_CALL(1418233c0);
    goto L81;
L59:
    rcx = ML_M8(rax, 0x10);
{
    const uint64_t a = (uint64_t)(ML_M1(rcx, 0x1d)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L70;
    rax = ML_M8(rcx, 0x0);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x1d)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L80;
L65:
    rcx = rax;
    rax = ML_M8(rax, 0x0);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x1d)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L65;
    goto L80;
L70:
    rcx = ML_M8(rax, 0x8);
{
    const uint64_t a = (uint64_t)(ML_M1(rcx, 0x1d)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L80;
L73:
    rax = ML_M8(rcx, 0x10);
{
    const uint64_t a = (uint64_t)(ML_M8(rbx, 0x8)) & ~0ULL, b = (uint64_t)(rax) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L80;
    ML_M8(rbx, 0x8) = rcx;
    rcx = ML_M8(rcx, 0x8);
{
    const uint64_t a = (uint64_t)(ML_M1(rcx, 0x1d)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L73;
L80:
    ML_M8(rbx, 0x8) = rcx;
L81:
    __builtin_memcpy(xmm0, (uint8_t*)((uintptr_t)rsp + 32), 16);
    r8 = rsp + 0x30;
    rdx = rsp + 0x40;
    rcx = rbp;
    __builtin_memcpy((uint8_t*)((uintptr_t)rsp + 48), xmm0, 16);
    rax = ML_CALL(14172bd00);
    goto L37;
L88:
    rcx = rsp + 0x30;
    ML_M8(rcx, 0x0) = rax;
    rax = ML_M8(rbx, 0x8);
    ML_M8(rcx, 0x8) = rax;
    rax = ML_M8(rsp, 0x38);
    rcx = rsp + 0x20;
    ML_M8(rsp, 0x28) = rax;
    rax = ML_M8(rbp, 0x0);
    ML_M8(rsp, 0x20) = rax;
    rax = ML_M8(rcx, 0x0);
    ML_M8(r12, 0x0) = rax;
    rax = ML_M8(rcx, 0x8);
    ML_M8(r12, 0x8) = rax;
L101:
    rbx = ML_M8(rsp, 0x60);
    rbp = ML_M8(rsp, 0x68);
    rsi = ML_M8(rsp, 0x70);
    rdi = ML_M8(rsp, 0x78);
    rax = r12;
    rsp = rsp + (0x50ULL);
    { const uint64_t v = ML_M8(rsp, 0); rsp += 8; r12 = v; }
    return rax;
#undef ML_CALL
    return rax;
}

__attribute__((weak)) uint64_t (*g_fnLIFT_14173c0b0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t) = nullptr;
__attribute__((weak)) uint64_t (*g_fnLIFT_14173c470)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t) = nullptr;
uint64_t SynLift_14173cb90(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A) {
    uint64_t rax = 0, rbx = 0, rbp = 0, rsi = 0, rdi = 0, r10 = 0, r11 = 0, r12 = 0, r13 = 0, r14 = 0, r15 = 0;
    uint64_t rcx = rcxA, rdx = rdxA, r8 = r8A, r9 = r9A;
    bool f_zf = false, f_cf = false, f_sf = false, f_of = false;
    uint8_t xmm0[16] = {0}, xmm1[16] = {0}, xmm2[16] = {0}, xmm3[16] = {0}, xmm4[16] = {0}, xmm5[16] = {0};
    alignas(16) uint8_t stkFrame[0x400] = {0};
    uint64_t rsp = (uint64_t)(uintptr_t)(stkFrame + 0x200);
#define ML_CALL(t) g_fnLIFT_##t(rcx, rdx, r8, r9, ML_M8(rsp, 0x20), ML_M8(rsp, 0x28))
    ML_M8(rsp, 0x8) = rbx;
    ML_M8(rsp, 0x10) = rbp;
    ML_M8(rsp, 0x18) = rsi;
    ML_M8(rsp, 0x20) = rdi;
    rsp -= 8; ML_M8(rsp, 0) = r12;
    rsp = rsp - (0x50ULL);
    rax = ML_M8(rcx, 0x30);
    rsi = r9;
    rbx = r8;
    rdi = ML_M8(rax, 0x0);
    rax = ML_M8(r8, 0x0);
    r12 = rdx;
    rbp = rcx;
{
    const uint64_t r = ((uint64_t)(rax) & ~0ULL) & ((uint64_t)(rax) & ~0ULL);
    f_zf = (r == 0); f_cf = false; f_sf = ((r & 0x8000000000000000ULL) != 0);
    f_of = false;
}
    if (f_zf) goto L17;
{
    const uint64_t a = (uint64_t)(rax) & ~0ULL, b = (uint64_t)(ML_M8(rcx, 0x0)) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (f_zf) goto L18;
L17:
    rax = ML_CALL(1418233c0);
L18:
{
    const uint64_t a = (uint64_t)(ML_M8(rbx, 0x8)) & ~0ULL, b = (uint64_t)(rdi) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L37;
    rax = ML_M8(rsi, 0x0);
    rdi = ML_M8(rbp, 0x30);
{
    const uint64_t r = ((uint64_t)(rax) & ~0ULL) & ((uint64_t)(rax) & ~0ULL);
    f_zf = (r == 0); f_cf = false; f_sf = ((r & 0x8000000000000000ULL) != 0);
    f_of = false;
}
    if (f_zf) goto L26;
{
    const uint64_t a = (uint64_t)(rax) & ~0ULL, b = (uint64_t)(ML_M8(rbp, 0x0)) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (f_zf) goto L27;
L26:
    rax = ML_CALL(1418233c0);
L27:
{
    const uint64_t a = (uint64_t)(ML_M8(rsi, 0x8)) & ~0ULL, b = (uint64_t)(rdi) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L37;
    rcx = rbp;
    rax = ML_CALL(14173c470);
    r11 = ML_M8(rbp, 0x30);
    rax = ML_M8(r11, 0x0);
    ML_M8(r12, 0x8) = rax;
    rax = ML_M8(rbp, 0x0);
    ML_M8(r12, 0x0) = rax;
    goto L101;
L37:
    rax = ML_M8(rbx, 0x0);
{
    const uint64_t r = ((uint64_t)(rax) & ~0ULL) & ((uint64_t)(rax) & ~0ULL);
    f_zf = (r == 0); f_cf = false; f_sf = ((r & 0x8000000000000000ULL) != 0);
    f_of = false;
}
    if (f_zf) goto L42;
{
    const uint64_t a = (uint64_t)(rax) & ~0ULL, b = (uint64_t)(ML_M8(rsi, 0x0)) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (f_zf) goto L43;
L42:
    rax = ML_CALL(1418233c0);
L43:
    rax = ML_M8(rsi, 0x8);
{
    const uint64_t a = (uint64_t)(ML_M8(rbx, 0x8)) & ~0ULL, b = (uint64_t)(rax) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    rax = ML_M8(rbx, 0x0);
    if (f_zf) goto L88;
{
    const uint64_t a = (uint64_t)(ML_M8(rbx, 0x0)) & ~0ULL, b = (uint64_t)(0x0ULL) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    rcx = rsp + 0x20;
    ML_M8(rcx, 0x0) = rax;
    rax = ML_M8(rbx, 0x8);
    ML_M8(rcx, 0x8) = rax;
    if (!f_zf) goto L54;
    rax = ML_CALL(1418233c0);
L54:
    rax = ML_M8(rbx, 0x8);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x21)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L59;
    rax = ML_CALL(1418233c0);
    goto L81;
L59:
    rcx = ML_M8(rax, 0x10);
{
    const uint64_t a = (uint64_t)(ML_M1(rcx, 0x21)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L70;
    rax = ML_M8(rcx, 0x0);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x21)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L80;
L65:
    rcx = rax;
    rax = ML_M8(rax, 0x0);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x21)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L65;
    goto L80;
L70:
    rcx = ML_M8(rax, 0x8);
{
    const uint64_t a = (uint64_t)(ML_M1(rcx, 0x21)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L80;
L73:
    rax = ML_M8(rcx, 0x10);
{
    const uint64_t a = (uint64_t)(ML_M8(rbx, 0x8)) & ~0ULL, b = (uint64_t)(rax) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L80;
    ML_M8(rbx, 0x8) = rcx;
    rcx = ML_M8(rcx, 0x8);
{
    const uint64_t a = (uint64_t)(ML_M1(rcx, 0x21)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L73;
L80:
    ML_M8(rbx, 0x8) = rcx;
L81:
    __builtin_memcpy(xmm0, (uint8_t*)((uintptr_t)rsp + 32), 16);
    r8 = rsp + 0x30;
    rdx = rsp + 0x40;
    rcx = rbp;
    __builtin_memcpy((uint8_t*)((uintptr_t)rsp + 48), xmm0, 16);
    rax = ML_CALL(14173c0b0);
    goto L37;
L88:
    rcx = rsp + 0x30;
    ML_M8(rcx, 0x0) = rax;
    rax = ML_M8(rbx, 0x8);
    ML_M8(rcx, 0x8) = rax;
    rax = ML_M8(rsp, 0x38);
    rcx = rsp + 0x20;
    ML_M8(rsp, 0x28) = rax;
    rax = ML_M8(rbp, 0x0);
    ML_M8(rsp, 0x20) = rax;
    rax = ML_M8(rcx, 0x0);
    ML_M8(r12, 0x0) = rax;
    rax = ML_M8(rcx, 0x8);
    ML_M8(r12, 0x8) = rax;
L101:
    rbx = ML_M8(rsp, 0x60);
    rbp = ML_M8(rsp, 0x68);
    rsi = ML_M8(rsp, 0x70);
    rdi = ML_M8(rsp, 0x78);
    rax = r12;
    rsp = rsp + (0x50ULL);
    { const uint64_t v = ML_M8(rsp, 0); rsp += 8; r12 = v; }
    return rax;
#undef ML_CALL
    return rax;
}

__attribute__((weak)) uint64_t (*g_fnLIFT_1417471f0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t) = nullptr;
__attribute__((weak)) uint64_t (*g_fnLIFT_141747400)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t) = nullptr;
uint64_t SynLift_1417481d0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A) {
    uint64_t rax = 0, rbx = 0, rbp = 0, rsi = 0, rdi = 0, r10 = 0, r11 = 0, r12 = 0, r13 = 0, r14 = 0, r15 = 0;
    uint64_t rcx = rcxA, rdx = rdxA, r8 = r8A, r9 = r9A;
    bool f_zf = false, f_cf = false, f_sf = false, f_of = false;
    uint8_t xmm0[16] = {0}, xmm1[16] = {0}, xmm2[16] = {0}, xmm3[16] = {0}, xmm4[16] = {0}, xmm5[16] = {0};
    alignas(16) uint8_t stkFrame[0x400] = {0};
    uint64_t rsp = (uint64_t)(uintptr_t)(stkFrame + 0x200);
#define ML_CALL(t) g_fnLIFT_##t(rcx, rdx, r8, r9, ML_M8(rsp, 0x20), ML_M8(rsp, 0x28))
    ML_M8(rsp, 0x8) = rbx;
    ML_M8(rsp, 0x10) = rbp;
    ML_M8(rsp, 0x18) = rsi;
    ML_M8(rsp, 0x20) = rdi;
    rsp -= 8; ML_M8(rsp, 0) = r12;
    rsp = rsp - (0x50ULL);
    rax = ML_M8(rcx, 0x30);
    rsi = r9;
    rbx = r8;
    rdi = ML_M8(rax, 0x0);
    rax = ML_M8(r8, 0x0);
    r12 = rdx;
    rbp = rcx;
{
    const uint64_t r = ((uint64_t)(rax) & ~0ULL) & ((uint64_t)(rax) & ~0ULL);
    f_zf = (r == 0); f_cf = false; f_sf = ((r & 0x8000000000000000ULL) != 0);
    f_of = false;
}
    if (f_zf) goto L17;
{
    const uint64_t a = (uint64_t)(rax) & ~0ULL, b = (uint64_t)(ML_M8(rcx, 0x0)) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (f_zf) goto L18;
L17:
    rax = ML_CALL(1418233c0);
L18:
{
    const uint64_t a = (uint64_t)(ML_M8(rbx, 0x8)) & ~0ULL, b = (uint64_t)(rdi) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L37;
    rax = ML_M8(rsi, 0x0);
    rdi = ML_M8(rbp, 0x30);
{
    const uint64_t r = ((uint64_t)(rax) & ~0ULL) & ((uint64_t)(rax) & ~0ULL);
    f_zf = (r == 0); f_cf = false; f_sf = ((r & 0x8000000000000000ULL) != 0);
    f_of = false;
}
    if (f_zf) goto L26;
{
    const uint64_t a = (uint64_t)(rax) & ~0ULL, b = (uint64_t)(ML_M8(rbp, 0x0)) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (f_zf) goto L27;
L26:
    rax = ML_CALL(1418233c0);
L27:
{
    const uint64_t a = (uint64_t)(ML_M8(rsi, 0x8)) & ~0ULL, b = (uint64_t)(rdi) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L37;
    rcx = rbp;
    rax = ML_CALL(1417471f0);
    r11 = ML_M8(rbp, 0x30);
    rax = ML_M8(r11, 0x0);
    ML_M8(r12, 0x8) = rax;
    rax = ML_M8(rbp, 0x0);
    ML_M8(r12, 0x0) = rax;
    goto L101;
L37:
    rax = ML_M8(rbx, 0x0);
{
    const uint64_t r = ((uint64_t)(rax) & ~0ULL) & ((uint64_t)(rax) & ~0ULL);
    f_zf = (r == 0); f_cf = false; f_sf = ((r & 0x8000000000000000ULL) != 0);
    f_of = false;
}
    if (f_zf) goto L42;
{
    const uint64_t a = (uint64_t)(rax) & ~0ULL, b = (uint64_t)(ML_M8(rsi, 0x0)) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (f_zf) goto L43;
L42:
    rax = ML_CALL(1418233c0);
L43:
    rax = ML_M8(rsi, 0x8);
{
    const uint64_t a = (uint64_t)(ML_M8(rbx, 0x8)) & ~0ULL, b = (uint64_t)(rax) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    rax = ML_M8(rbx, 0x0);
    if (f_zf) goto L88;
{
    const uint64_t a = (uint64_t)(ML_M8(rbx, 0x0)) & ~0ULL, b = (uint64_t)(0x0ULL) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    rcx = rsp + 0x20;
    ML_M8(rcx, 0x0) = rax;
    rax = ML_M8(rbx, 0x8);
    ML_M8(rcx, 0x8) = rax;
    if (!f_zf) goto L54;
    rax = ML_CALL(1418233c0);
L54:
    rax = ML_M8(rbx, 0x8);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x3d)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L59;
    rax = ML_CALL(1418233c0);
    goto L81;
L59:
    rcx = ML_M8(rax, 0x10);
{
    const uint64_t a = (uint64_t)(ML_M1(rcx, 0x3d)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L70;
    rax = ML_M8(rcx, 0x0);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x3d)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L80;
L65:
    rcx = rax;
    rax = ML_M8(rax, 0x0);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x3d)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L65;
    goto L80;
L70:
    rcx = ML_M8(rax, 0x8);
{
    const uint64_t a = (uint64_t)(ML_M1(rcx, 0x3d)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L80;
L73:
    rax = ML_M8(rcx, 0x10);
{
    const uint64_t a = (uint64_t)(ML_M8(rbx, 0x8)) & ~0ULL, b = (uint64_t)(rax) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L80;
    ML_M8(rbx, 0x8) = rcx;
    rcx = ML_M8(rcx, 0x8);
{
    const uint64_t a = (uint64_t)(ML_M1(rcx, 0x3d)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L73;
L80:
    ML_M8(rbx, 0x8) = rcx;
L81:
    __builtin_memcpy(xmm0, (uint8_t*)((uintptr_t)rsp + 32), 16);
    r8 = rsp + 0x30;
    rdx = rsp + 0x40;
    rcx = rbp;
    __builtin_memcpy((uint8_t*)((uintptr_t)rsp + 48), xmm0, 16);
    rax = ML_CALL(141747400);
    goto L37;
L88:
    rcx = rsp + 0x30;
    ML_M8(rcx, 0x0) = rax;
    rax = ML_M8(rbx, 0x8);
    ML_M8(rcx, 0x8) = rax;
    rax = ML_M8(rsp, 0x38);
    rcx = rsp + 0x20;
    ML_M8(rsp, 0x28) = rax;
    rax = ML_M8(rbp, 0x0);
    ML_M8(rsp, 0x20) = rax;
    rax = ML_M8(rcx, 0x0);
    ML_M8(r12, 0x0) = rax;
    rax = ML_M8(rcx, 0x8);
    ML_M8(r12, 0x8) = rax;
L101:
    rbx = ML_M8(rsp, 0x60);
    rbp = ML_M8(rsp, 0x68);
    rsi = ML_M8(rsp, 0x70);
    rdi = ML_M8(rsp, 0x78);
    rax = r12;
    rsp = rsp + (0x50ULL);
    { const uint64_t v = ML_M8(rsp, 0); rsp += 8; r12 = v; }
    return rax;
#undef ML_CALL
    return rax;
}

__attribute__((weak)) uint64_t (*g_fnLIFT_141747270)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t) = nullptr;
__attribute__((weak)) uint64_t (*g_fnLIFT_141749c00)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t) = nullptr;
uint64_t SynLift_14174a150(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A) {
    uint64_t rax = 0, rbx = 0, rbp = 0, rsi = 0, rdi = 0, r10 = 0, r11 = 0, r12 = 0, r13 = 0, r14 = 0, r15 = 0;
    uint64_t rcx = rcxA, rdx = rdxA, r8 = r8A, r9 = r9A;
    bool f_zf = false, f_cf = false, f_sf = false, f_of = false;
    uint8_t xmm0[16] = {0}, xmm1[16] = {0}, xmm2[16] = {0}, xmm3[16] = {0}, xmm4[16] = {0}, xmm5[16] = {0};
    alignas(16) uint8_t stkFrame[0x400] = {0};
    uint64_t rsp = (uint64_t)(uintptr_t)(stkFrame + 0x200);
#define ML_CALL(t) g_fnLIFT_##t(rcx, rdx, r8, r9, ML_M8(rsp, 0x20), ML_M8(rsp, 0x28))
    ML_M8(rsp, 0x8) = rbx;
    ML_M8(rsp, 0x10) = rbp;
    ML_M8(rsp, 0x18) = rsi;
    ML_M8(rsp, 0x20) = rdi;
    rsp -= 8; ML_M8(rsp, 0) = r12;
    rsp = rsp - (0x50ULL);
    rax = ML_M8(rcx, 0x30);
    rsi = r9;
    rbx = r8;
    rdi = ML_M8(rax, 0x0);
    rax = ML_M8(r8, 0x0);
    r12 = rdx;
    rbp = rcx;
{
    const uint64_t r = ((uint64_t)(rax) & ~0ULL) & ((uint64_t)(rax) & ~0ULL);
    f_zf = (r == 0); f_cf = false; f_sf = ((r & 0x8000000000000000ULL) != 0);
    f_of = false;
}
    if (f_zf) goto L17;
{
    const uint64_t a = (uint64_t)(rax) & ~0ULL, b = (uint64_t)(ML_M8(rcx, 0x0)) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (f_zf) goto L18;
L17:
    rax = ML_CALL(1418233c0);
L18:
{
    const uint64_t a = (uint64_t)(ML_M8(rbx, 0x8)) & ~0ULL, b = (uint64_t)(rdi) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L37;
    rax = ML_M8(rsi, 0x0);
    rdi = ML_M8(rbp, 0x30);
{
    const uint64_t r = ((uint64_t)(rax) & ~0ULL) & ((uint64_t)(rax) & ~0ULL);
    f_zf = (r == 0); f_cf = false; f_sf = ((r & 0x8000000000000000ULL) != 0);
    f_of = false;
}
    if (f_zf) goto L26;
{
    const uint64_t a = (uint64_t)(rax) & ~0ULL, b = (uint64_t)(ML_M8(rbp, 0x0)) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (f_zf) goto L27;
L26:
    rax = ML_CALL(1418233c0);
L27:
{
    const uint64_t a = (uint64_t)(ML_M8(rsi, 0x8)) & ~0ULL, b = (uint64_t)(rdi) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L37;
    rcx = rbp;
    rax = ML_CALL(141747270);
    r11 = ML_M8(rbp, 0x30);
    rax = ML_M8(r11, 0x0);
    ML_M8(r12, 0x8) = rax;
    rax = ML_M8(rbp, 0x0);
    ML_M8(r12, 0x0) = rax;
    goto L101;
L37:
    rax = ML_M8(rbx, 0x0);
{
    const uint64_t r = ((uint64_t)(rax) & ~0ULL) & ((uint64_t)(rax) & ~0ULL);
    f_zf = (r == 0); f_cf = false; f_sf = ((r & 0x8000000000000000ULL) != 0);
    f_of = false;
}
    if (f_zf) goto L42;
{
    const uint64_t a = (uint64_t)(rax) & ~0ULL, b = (uint64_t)(ML_M8(rsi, 0x0)) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (f_zf) goto L43;
L42:
    rax = ML_CALL(1418233c0);
L43:
    rax = ML_M8(rsi, 0x8);
{
    const uint64_t a = (uint64_t)(ML_M8(rbx, 0x8)) & ~0ULL, b = (uint64_t)(rax) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    rax = ML_M8(rbx, 0x0);
    if (f_zf) goto L88;
{
    const uint64_t a = (uint64_t)(ML_M8(rbx, 0x0)) & ~0ULL, b = (uint64_t)(0x0ULL) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    rcx = rsp + 0x20;
    ML_M8(rcx, 0x0) = rax;
    rax = ML_M8(rbx, 0x8);
    ML_M8(rcx, 0x8) = rax;
    if (!f_zf) goto L54;
    rax = ML_CALL(1418233c0);
L54:
    rax = ML_M8(rbx, 0x8);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L59;
    rax = ML_CALL(1418233c0);
    goto L81;
L59:
    rcx = ML_M8(rax, 0x10);
{
    const uint64_t a = (uint64_t)(ML_M1(rcx, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L70;
    rax = ML_M8(rcx, 0x0);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L80;
L65:
    rcx = rax;
    rax = ML_M8(rax, 0x0);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L65;
    goto L80;
L70:
    rcx = ML_M8(rax, 0x8);
{
    const uint64_t a = (uint64_t)(ML_M1(rcx, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L80;
L73:
    rax = ML_M8(rcx, 0x10);
{
    const uint64_t a = (uint64_t)(ML_M8(rbx, 0x8)) & ~0ULL, b = (uint64_t)(rax) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L80;
    ML_M8(rbx, 0x8) = rcx;
    rcx = ML_M8(rcx, 0x8);
{
    const uint64_t a = (uint64_t)(ML_M1(rcx, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L73;
L80:
    ML_M8(rbx, 0x8) = rcx;
L81:
    __builtin_memcpy(xmm0, (uint8_t*)((uintptr_t)rsp + 32), 16);
    r8 = rsp + 0x30;
    rdx = rsp + 0x40;
    rcx = rbp;
    __builtin_memcpy((uint8_t*)((uintptr_t)rsp + 48), xmm0, 16);
    rax = ML_CALL(141749c00);
    goto L37;
L88:
    rcx = rsp + 0x30;
    ML_M8(rcx, 0x0) = rax;
    rax = ML_M8(rbx, 0x8);
    ML_M8(rcx, 0x8) = rax;
    rax = ML_M8(rsp, 0x38);
    rcx = rsp + 0x20;
    ML_M8(rsp, 0x28) = rax;
    rax = ML_M8(rbp, 0x0);
    ML_M8(rsp, 0x20) = rax;
    rax = ML_M8(rcx, 0x0);
    ML_M8(r12, 0x0) = rax;
    rax = ML_M8(rcx, 0x8);
    ML_M8(r12, 0x8) = rax;
L101:
    rbx = ML_M8(rsp, 0x60);
    rbp = ML_M8(rsp, 0x68);
    rsi = ML_M8(rsp, 0x70);
    rdi = ML_M8(rsp, 0x78);
    rax = r12;
    rsp = rsp + (0x50ULL);
    { const uint64_t v = ML_M8(rsp, 0); rsp += 8; r12 = v; }
    return rax;
#undef ML_CALL
    return rax;
}

__attribute__((weak)) uint64_t (*g_fnLIFT_141757580)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t) = nullptr;
__attribute__((weak)) uint64_t (*g_fnLIFT_141758050)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t) = nullptr;
uint64_t SynLift_14175bda0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A) {
    uint64_t rax = 0, rbx = 0, rbp = 0, rsi = 0, rdi = 0, r10 = 0, r11 = 0, r12 = 0, r13 = 0, r14 = 0, r15 = 0;
    uint64_t rcx = rcxA, rdx = rdxA, r8 = r8A, r9 = r9A;
    bool f_zf = false, f_cf = false, f_sf = false, f_of = false;
    uint8_t xmm0[16] = {0}, xmm1[16] = {0}, xmm2[16] = {0}, xmm3[16] = {0}, xmm4[16] = {0}, xmm5[16] = {0};
    alignas(16) uint8_t stkFrame[0x400] = {0};
    uint64_t rsp = (uint64_t)(uintptr_t)(stkFrame + 0x200);
#define ML_CALL(t) g_fnLIFT_##t(rcx, rdx, r8, r9, ML_M8(rsp, 0x20), ML_M8(rsp, 0x28))
    ML_M8(rsp, 0x8) = rbx;
    ML_M8(rsp, 0x10) = rbp;
    ML_M8(rsp, 0x18) = rsi;
    ML_M8(rsp, 0x20) = rdi;
    rsp -= 8; ML_M8(rsp, 0) = r12;
    rsp = rsp - (0x50ULL);
    rax = ML_M8(rcx, 0x30);
    rsi = r9;
    rbx = r8;
    rdi = ML_M8(rax, 0x0);
    rax = ML_M8(r8, 0x0);
    r12 = rdx;
    rbp = rcx;
{
    const uint64_t r = ((uint64_t)(rax) & ~0ULL) & ((uint64_t)(rax) & ~0ULL);
    f_zf = (r == 0); f_cf = false; f_sf = ((r & 0x8000000000000000ULL) != 0);
    f_of = false;
}
    if (f_zf) goto L17;
{
    const uint64_t a = (uint64_t)(rax) & ~0ULL, b = (uint64_t)(ML_M8(rcx, 0x0)) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (f_zf) goto L18;
L17:
    rax = ML_CALL(1418233c0);
L18:
{
    const uint64_t a = (uint64_t)(ML_M8(rbx, 0x8)) & ~0ULL, b = (uint64_t)(rdi) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L37;
    rax = ML_M8(rsi, 0x0);
    rdi = ML_M8(rbp, 0x30);
{
    const uint64_t r = ((uint64_t)(rax) & ~0ULL) & ((uint64_t)(rax) & ~0ULL);
    f_zf = (r == 0); f_cf = false; f_sf = ((r & 0x8000000000000000ULL) != 0);
    f_of = false;
}
    if (f_zf) goto L26;
{
    const uint64_t a = (uint64_t)(rax) & ~0ULL, b = (uint64_t)(ML_M8(rbp, 0x0)) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (f_zf) goto L27;
L26:
    rax = ML_CALL(1418233c0);
L27:
{
    const uint64_t a = (uint64_t)(ML_M8(rsi, 0x8)) & ~0ULL, b = (uint64_t)(rdi) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L37;
    rcx = rbp;
    rax = ML_CALL(141757580);
    r11 = ML_M8(rbp, 0x30);
    rax = ML_M8(r11, 0x0);
    ML_M8(r12, 0x8) = rax;
    rax = ML_M8(rbp, 0x0);
    ML_M8(r12, 0x0) = rax;
    goto L101;
L37:
    rax = ML_M8(rbx, 0x0);
{
    const uint64_t r = ((uint64_t)(rax) & ~0ULL) & ((uint64_t)(rax) & ~0ULL);
    f_zf = (r == 0); f_cf = false; f_sf = ((r & 0x8000000000000000ULL) != 0);
    f_of = false;
}
    if (f_zf) goto L42;
{
    const uint64_t a = (uint64_t)(rax) & ~0ULL, b = (uint64_t)(ML_M8(rsi, 0x0)) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (f_zf) goto L43;
L42:
    rax = ML_CALL(1418233c0);
L43:
    rax = ML_M8(rsi, 0x8);
{
    const uint64_t a = (uint64_t)(ML_M8(rbx, 0x8)) & ~0ULL, b = (uint64_t)(rax) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    rax = ML_M8(rbx, 0x0);
    if (f_zf) goto L88;
{
    const uint64_t a = (uint64_t)(ML_M8(rbx, 0x0)) & ~0ULL, b = (uint64_t)(0x0ULL) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    rcx = rsp + 0x20;
    ML_M8(rcx, 0x0) = rax;
    rax = ML_M8(rbx, 0x8);
    ML_M8(rcx, 0x8) = rax;
    if (!f_zf) goto L54;
    rax = ML_CALL(1418233c0);
L54:
    rax = ML_M8(rbx, 0x8);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L59;
    rax = ML_CALL(1418233c0);
    goto L81;
L59:
    rcx = ML_M8(rax, 0x10);
{
    const uint64_t a = (uint64_t)(ML_M1(rcx, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L70;
    rax = ML_M8(rcx, 0x0);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L80;
L65:
    rcx = rax;
    rax = ML_M8(rax, 0x0);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L65;
    goto L80;
L70:
    rcx = ML_M8(rax, 0x8);
{
    const uint64_t a = (uint64_t)(ML_M1(rcx, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L80;
L73:
    rax = ML_M8(rcx, 0x10);
{
    const uint64_t a = (uint64_t)(ML_M8(rbx, 0x8)) & ~0ULL, b = (uint64_t)(rax) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L80;
    ML_M8(rbx, 0x8) = rcx;
    rcx = ML_M8(rcx, 0x8);
{
    const uint64_t a = (uint64_t)(ML_M1(rcx, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L73;
L80:
    ML_M8(rbx, 0x8) = rcx;
L81:
    __builtin_memcpy(xmm0, (uint8_t*)((uintptr_t)rsp + 32), 16);
    r8 = rsp + 0x30;
    rdx = rsp + 0x40;
    rcx = rbp;
    __builtin_memcpy((uint8_t*)((uintptr_t)rsp + 48), xmm0, 16);
    rax = ML_CALL(141758050);
    goto L37;
L88:
    rcx = rsp + 0x30;
    ML_M8(rcx, 0x0) = rax;
    rax = ML_M8(rbx, 0x8);
    ML_M8(rcx, 0x8) = rax;
    rax = ML_M8(rsp, 0x38);
    rcx = rsp + 0x20;
    ML_M8(rsp, 0x28) = rax;
    rax = ML_M8(rbp, 0x0);
    ML_M8(rsp, 0x20) = rax;
    rax = ML_M8(rcx, 0x0);
    ML_M8(r12, 0x0) = rax;
    rax = ML_M8(rcx, 0x8);
    ML_M8(r12, 0x8) = rax;
L101:
    rbx = ML_M8(rsp, 0x60);
    rbp = ML_M8(rsp, 0x68);
    rsi = ML_M8(rsp, 0x70);
    rdi = ML_M8(rsp, 0x78);
    rax = r12;
    rsp = rsp + (0x50ULL);
    { const uint64_t v = ML_M8(rsp, 0); rsp += 8; r12 = v; }
    return rax;
#undef ML_CALL
    return rax;
}

__attribute__((weak)) uint64_t (*g_fnLIFT_141757640)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t) = nullptr;
__attribute__((weak)) uint64_t (*g_fnLIFT_1417591f0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t) = nullptr;
uint64_t SynLift_14175d690(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A) {
    uint64_t rax = 0, rbx = 0, rbp = 0, rsi = 0, rdi = 0, r10 = 0, r11 = 0, r12 = 0, r13 = 0, r14 = 0, r15 = 0;
    uint64_t rcx = rcxA, rdx = rdxA, r8 = r8A, r9 = r9A;
    bool f_zf = false, f_cf = false, f_sf = false, f_of = false;
    uint8_t xmm0[16] = {0}, xmm1[16] = {0}, xmm2[16] = {0}, xmm3[16] = {0}, xmm4[16] = {0}, xmm5[16] = {0};
    alignas(16) uint8_t stkFrame[0x400] = {0};
    uint64_t rsp = (uint64_t)(uintptr_t)(stkFrame + 0x200);
#define ML_CALL(t) g_fnLIFT_##t(rcx, rdx, r8, r9, ML_M8(rsp, 0x20), ML_M8(rsp, 0x28))
    ML_M8(rsp, 0x8) = rbx;
    ML_M8(rsp, 0x10) = rbp;
    ML_M8(rsp, 0x18) = rsi;
    ML_M8(rsp, 0x20) = rdi;
    rsp -= 8; ML_M8(rsp, 0) = r12;
    rsp = rsp - (0x50ULL);
    rax = ML_M8(rcx, 0x30);
    rsi = r9;
    rbx = r8;
    rdi = ML_M8(rax, 0x0);
    rax = ML_M8(r8, 0x0);
    r12 = rdx;
    rbp = rcx;
{
    const uint64_t r = ((uint64_t)(rax) & ~0ULL) & ((uint64_t)(rax) & ~0ULL);
    f_zf = (r == 0); f_cf = false; f_sf = ((r & 0x8000000000000000ULL) != 0);
    f_of = false;
}
    if (f_zf) goto L17;
{
    const uint64_t a = (uint64_t)(rax) & ~0ULL, b = (uint64_t)(ML_M8(rcx, 0x0)) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (f_zf) goto L18;
L17:
    rax = ML_CALL(1418233c0);
L18:
{
    const uint64_t a = (uint64_t)(ML_M8(rbx, 0x8)) & ~0ULL, b = (uint64_t)(rdi) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L37;
    rax = ML_M8(rsi, 0x0);
    rdi = ML_M8(rbp, 0x30);
{
    const uint64_t r = ((uint64_t)(rax) & ~0ULL) & ((uint64_t)(rax) & ~0ULL);
    f_zf = (r == 0); f_cf = false; f_sf = ((r & 0x8000000000000000ULL) != 0);
    f_of = false;
}
    if (f_zf) goto L26;
{
    const uint64_t a = (uint64_t)(rax) & ~0ULL, b = (uint64_t)(ML_M8(rbp, 0x0)) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (f_zf) goto L27;
L26:
    rax = ML_CALL(1418233c0);
L27:
{
    const uint64_t a = (uint64_t)(ML_M8(rsi, 0x8)) & ~0ULL, b = (uint64_t)(rdi) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L37;
    rcx = rbp;
    rax = ML_CALL(141757640);
    r11 = ML_M8(rbp, 0x30);
    rax = ML_M8(r11, 0x0);
    ML_M8(r12, 0x8) = rax;
    rax = ML_M8(rbp, 0x0);
    ML_M8(r12, 0x0) = rax;
    goto L101;
L37:
    rax = ML_M8(rbx, 0x0);
{
    const uint64_t r = ((uint64_t)(rax) & ~0ULL) & ((uint64_t)(rax) & ~0ULL);
    f_zf = (r == 0); f_cf = false; f_sf = ((r & 0x8000000000000000ULL) != 0);
    f_of = false;
}
    if (f_zf) goto L42;
{
    const uint64_t a = (uint64_t)(rax) & ~0ULL, b = (uint64_t)(ML_M8(rsi, 0x0)) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (f_zf) goto L43;
L42:
    rax = ML_CALL(1418233c0);
L43:
    rax = ML_M8(rsi, 0x8);
{
    const uint64_t a = (uint64_t)(ML_M8(rbx, 0x8)) & ~0ULL, b = (uint64_t)(rax) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    rax = ML_M8(rbx, 0x0);
    if (f_zf) goto L88;
{
    const uint64_t a = (uint64_t)(ML_M8(rbx, 0x0)) & ~0ULL, b = (uint64_t)(0x0ULL) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    rcx = rsp + 0x20;
    ML_M8(rcx, 0x0) = rax;
    rax = ML_M8(rbx, 0x8);
    ML_M8(rcx, 0x8) = rax;
    if (!f_zf) goto L54;
    rax = ML_CALL(1418233c0);
L54:
    rax = ML_M8(rbx, 0x8);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x59)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L59;
    rax = ML_CALL(1418233c0);
    goto L81;
L59:
    rcx = ML_M8(rax, 0x10);
{
    const uint64_t a = (uint64_t)(ML_M1(rcx, 0x59)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L70;
    rax = ML_M8(rcx, 0x0);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x59)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L80;
L65:
    rcx = rax;
    rax = ML_M8(rax, 0x0);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x59)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L65;
    goto L80;
L70:
    rcx = ML_M8(rax, 0x8);
{
    const uint64_t a = (uint64_t)(ML_M1(rcx, 0x59)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L80;
L73:
    rax = ML_M8(rcx, 0x10);
{
    const uint64_t a = (uint64_t)(ML_M8(rbx, 0x8)) & ~0ULL, b = (uint64_t)(rax) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L80;
    ML_M8(rbx, 0x8) = rcx;
    rcx = ML_M8(rcx, 0x8);
{
    const uint64_t a = (uint64_t)(ML_M1(rcx, 0x59)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L73;
L80:
    ML_M8(rbx, 0x8) = rcx;
L81:
    __builtin_memcpy(xmm0, (uint8_t*)((uintptr_t)rsp + 32), 16);
    r8 = rsp + 0x30;
    rdx = rsp + 0x40;
    rcx = rbp;
    __builtin_memcpy((uint8_t*)((uintptr_t)rsp + 48), xmm0, 16);
    rax = ML_CALL(1417591f0);
    goto L37;
L88:
    rcx = rsp + 0x30;
    ML_M8(rcx, 0x0) = rax;
    rax = ML_M8(rbx, 0x8);
    ML_M8(rcx, 0x8) = rax;
    rax = ML_M8(rsp, 0x38);
    rcx = rsp + 0x20;
    ML_M8(rsp, 0x28) = rax;
    rax = ML_M8(rbp, 0x0);
    ML_M8(rsp, 0x20) = rax;
    rax = ML_M8(rcx, 0x0);
    ML_M8(r12, 0x0) = rax;
    rax = ML_M8(rcx, 0x8);
    ML_M8(r12, 0x8) = rax;
L101:
    rbx = ML_M8(rsp, 0x60);
    rbp = ML_M8(rsp, 0x68);
    rsi = ML_M8(rsp, 0x70);
    rdi = ML_M8(rsp, 0x78);
    rax = r12;
    rsp = rsp + (0x50ULL);
    { const uint64_t v = ML_M8(rsp, 0); rsp += 8; r12 = v; }
    return rax;
#undef ML_CALL
    return rax;
}

__attribute__((weak)) uint64_t (*g_fnLIFT_141759600)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t) = nullptr;
__attribute__((weak)) uint64_t (*g_fnLIFT_1417599c0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t) = nullptr;
uint64_t SynLift_14175d9f0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A) {
    uint64_t rax = 0, rbx = 0, rbp = 0, rsi = 0, rdi = 0, r10 = 0, r11 = 0, r12 = 0, r13 = 0, r14 = 0, r15 = 0;
    uint64_t rcx = rcxA, rdx = rdxA, r8 = r8A, r9 = r9A;
    bool f_zf = false, f_cf = false, f_sf = false, f_of = false;
    uint8_t xmm0[16] = {0}, xmm1[16] = {0}, xmm2[16] = {0}, xmm3[16] = {0}, xmm4[16] = {0}, xmm5[16] = {0};
    alignas(16) uint8_t stkFrame[0x400] = {0};
    uint64_t rsp = (uint64_t)(uintptr_t)(stkFrame + 0x200);
#define ML_CALL(t) g_fnLIFT_##t(rcx, rdx, r8, r9, ML_M8(rsp, 0x20), ML_M8(rsp, 0x28))
    ML_M8(rsp, 0x8) = rbx;
    ML_M8(rsp, 0x10) = rbp;
    ML_M8(rsp, 0x18) = rsi;
    ML_M8(rsp, 0x20) = rdi;
    rsp -= 8; ML_M8(rsp, 0) = r12;
    rsp = rsp - (0x50ULL);
    rax = ML_M8(rcx, 0x30);
    rsi = r9;
    rbx = r8;
    rdi = ML_M8(rax, 0x0);
    rax = ML_M8(r8, 0x0);
    r12 = rdx;
    rbp = rcx;
{
    const uint64_t r = ((uint64_t)(rax) & ~0ULL) & ((uint64_t)(rax) & ~0ULL);
    f_zf = (r == 0); f_cf = false; f_sf = ((r & 0x8000000000000000ULL) != 0);
    f_of = false;
}
    if (f_zf) goto L17;
{
    const uint64_t a = (uint64_t)(rax) & ~0ULL, b = (uint64_t)(ML_M8(rcx, 0x0)) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (f_zf) goto L18;
L17:
    rax = ML_CALL(1418233c0);
L18:
{
    const uint64_t a = (uint64_t)(ML_M8(rbx, 0x8)) & ~0ULL, b = (uint64_t)(rdi) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L37;
    rax = ML_M8(rsi, 0x0);
    rdi = ML_M8(rbp, 0x30);
{
    const uint64_t r = ((uint64_t)(rax) & ~0ULL) & ((uint64_t)(rax) & ~0ULL);
    f_zf = (r == 0); f_cf = false; f_sf = ((r & 0x8000000000000000ULL) != 0);
    f_of = false;
}
    if (f_zf) goto L26;
{
    const uint64_t a = (uint64_t)(rax) & ~0ULL, b = (uint64_t)(ML_M8(rbp, 0x0)) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (f_zf) goto L27;
L26:
    rax = ML_CALL(1418233c0);
L27:
{
    const uint64_t a = (uint64_t)(ML_M8(rsi, 0x8)) & ~0ULL, b = (uint64_t)(rdi) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L37;
    rcx = rbp;
    rax = ML_CALL(1417599c0);
    r11 = ML_M8(rbp, 0x30);
    rax = ML_M8(r11, 0x0);
    ML_M8(r12, 0x8) = rax;
    rax = ML_M8(rbp, 0x0);
    ML_M8(r12, 0x0) = rax;
    goto L101;
L37:
    rax = ML_M8(rbx, 0x0);
{
    const uint64_t r = ((uint64_t)(rax) & ~0ULL) & ((uint64_t)(rax) & ~0ULL);
    f_zf = (r == 0); f_cf = false; f_sf = ((r & 0x8000000000000000ULL) != 0);
    f_of = false;
}
    if (f_zf) goto L42;
{
    const uint64_t a = (uint64_t)(rax) & ~0ULL, b = (uint64_t)(ML_M8(rsi, 0x0)) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (f_zf) goto L43;
L42:
    rax = ML_CALL(1418233c0);
L43:
    rax = ML_M8(rsi, 0x8);
{
    const uint64_t a = (uint64_t)(ML_M8(rbx, 0x8)) & ~0ULL, b = (uint64_t)(rax) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    rax = ML_M8(rbx, 0x0);
    if (f_zf) goto L88;
{
    const uint64_t a = (uint64_t)(ML_M8(rbx, 0x0)) & ~0ULL, b = (uint64_t)(0x0ULL) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    rcx = rsp + 0x20;
    ML_M8(rcx, 0x0) = rax;
    rax = ML_M8(rbx, 0x8);
    ML_M8(rcx, 0x8) = rax;
    if (!f_zf) goto L54;
    rax = ML_CALL(1418233c0);
L54:
    rax = ML_M8(rbx, 0x8);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L59;
    rax = ML_CALL(1418233c0);
    goto L81;
L59:
    rcx = ML_M8(rax, 0x10);
{
    const uint64_t a = (uint64_t)(ML_M1(rcx, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L70;
    rax = ML_M8(rcx, 0x0);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L80;
L65:
    rcx = rax;
    rax = ML_M8(rax, 0x0);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L65;
    goto L80;
L70:
    rcx = ML_M8(rax, 0x8);
{
    const uint64_t a = (uint64_t)(ML_M1(rcx, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L80;
L73:
    rax = ML_M8(rcx, 0x10);
{
    const uint64_t a = (uint64_t)(ML_M8(rbx, 0x8)) & ~0ULL, b = (uint64_t)(rax) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L80;
    ML_M8(rbx, 0x8) = rcx;
    rcx = ML_M8(rcx, 0x8);
{
    const uint64_t a = (uint64_t)(ML_M1(rcx, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L73;
L80:
    ML_M8(rbx, 0x8) = rcx;
L81:
    __builtin_memcpy(xmm0, (uint8_t*)((uintptr_t)rsp + 32), 16);
    r8 = rsp + 0x30;
    rdx = rsp + 0x40;
    rcx = rbp;
    __builtin_memcpy((uint8_t*)((uintptr_t)rsp + 48), xmm0, 16);
    rax = ML_CALL(141759600);
    goto L37;
L88:
    rcx = rsp + 0x30;
    ML_M8(rcx, 0x0) = rax;
    rax = ML_M8(rbx, 0x8);
    ML_M8(rcx, 0x8) = rax;
    rax = ML_M8(rsp, 0x38);
    rcx = rsp + 0x20;
    ML_M8(rsp, 0x28) = rax;
    rax = ML_M8(rbp, 0x0);
    ML_M8(rsp, 0x20) = rax;
    rax = ML_M8(rcx, 0x0);
    ML_M8(r12, 0x0) = rax;
    rax = ML_M8(rcx, 0x8);
    ML_M8(r12, 0x8) = rax;
L101:
    rbx = ML_M8(rsp, 0x60);
    rbp = ML_M8(rsp, 0x68);
    rsi = ML_M8(rsp, 0x70);
    rdi = ML_M8(rsp, 0x78);
    rax = r12;
    rsp = rsp + (0x50ULL);
    { const uint64_t v = ML_M8(rsp, 0); rsp += 8; r12 = v; }
    return rax;
#undef ML_CALL
    return rax;
}

__attribute__((weak)) uint64_t (*g_fnLIFT_1417576c0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t) = nullptr;
__attribute__((weak)) uint64_t (*g_fnLIFT_141759a90)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t) = nullptr;
uint64_t SynLift_14175dba0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A) {
    uint64_t rax = 0, rbx = 0, rbp = 0, rsi = 0, rdi = 0, r10 = 0, r11 = 0, r12 = 0, r13 = 0, r14 = 0, r15 = 0;
    uint64_t rcx = rcxA, rdx = rdxA, r8 = r8A, r9 = r9A;
    bool f_zf = false, f_cf = false, f_sf = false, f_of = false;
    uint8_t xmm0[16] = {0}, xmm1[16] = {0}, xmm2[16] = {0}, xmm3[16] = {0}, xmm4[16] = {0}, xmm5[16] = {0};
    alignas(16) uint8_t stkFrame[0x400] = {0};
    uint64_t rsp = (uint64_t)(uintptr_t)(stkFrame + 0x200);
#define ML_CALL(t) g_fnLIFT_##t(rcx, rdx, r8, r9, ML_M8(rsp, 0x20), ML_M8(rsp, 0x28))
    ML_M8(rsp, 0x8) = rbx;
    ML_M8(rsp, 0x10) = rbp;
    ML_M8(rsp, 0x18) = rsi;
    ML_M8(rsp, 0x20) = rdi;
    rsp -= 8; ML_M8(rsp, 0) = r12;
    rsp = rsp - (0x50ULL);
    rax = ML_M8(rcx, 0x30);
    rsi = r9;
    rbx = r8;
    rdi = ML_M8(rax, 0x0);
    rax = ML_M8(r8, 0x0);
    r12 = rdx;
    rbp = rcx;
{
    const uint64_t r = ((uint64_t)(rax) & ~0ULL) & ((uint64_t)(rax) & ~0ULL);
    f_zf = (r == 0); f_cf = false; f_sf = ((r & 0x8000000000000000ULL) != 0);
    f_of = false;
}
    if (f_zf) goto L17;
{
    const uint64_t a = (uint64_t)(rax) & ~0ULL, b = (uint64_t)(ML_M8(rcx, 0x0)) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (f_zf) goto L18;
L17:
    rax = ML_CALL(1418233c0);
L18:
{
    const uint64_t a = (uint64_t)(ML_M8(rbx, 0x8)) & ~0ULL, b = (uint64_t)(rdi) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L37;
    rax = ML_M8(rsi, 0x0);
    rdi = ML_M8(rbp, 0x30);
{
    const uint64_t r = ((uint64_t)(rax) & ~0ULL) & ((uint64_t)(rax) & ~0ULL);
    f_zf = (r == 0); f_cf = false; f_sf = ((r & 0x8000000000000000ULL) != 0);
    f_of = false;
}
    if (f_zf) goto L26;
{
    const uint64_t a = (uint64_t)(rax) & ~0ULL, b = (uint64_t)(ML_M8(rbp, 0x0)) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (f_zf) goto L27;
L26:
    rax = ML_CALL(1418233c0);
L27:
{
    const uint64_t a = (uint64_t)(ML_M8(rsi, 0x8)) & ~0ULL, b = (uint64_t)(rdi) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L37;
    rcx = rbp;
    rax = ML_CALL(1417576c0);
    r11 = ML_M8(rbp, 0x30);
    rax = ML_M8(r11, 0x0);
    ML_M8(r12, 0x8) = rax;
    rax = ML_M8(rbp, 0x0);
    ML_M8(r12, 0x0) = rax;
    goto L101;
L37:
    rax = ML_M8(rbx, 0x0);
{
    const uint64_t r = ((uint64_t)(rax) & ~0ULL) & ((uint64_t)(rax) & ~0ULL);
    f_zf = (r == 0); f_cf = false; f_sf = ((r & 0x8000000000000000ULL) != 0);
    f_of = false;
}
    if (f_zf) goto L42;
{
    const uint64_t a = (uint64_t)(rax) & ~0ULL, b = (uint64_t)(ML_M8(rsi, 0x0)) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (f_zf) goto L43;
L42:
    rax = ML_CALL(1418233c0);
L43:
    rax = ML_M8(rsi, 0x8);
{
    const uint64_t a = (uint64_t)(ML_M8(rbx, 0x8)) & ~0ULL, b = (uint64_t)(rax) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    rax = ML_M8(rbx, 0x0);
    if (f_zf) goto L88;
{
    const uint64_t a = (uint64_t)(ML_M8(rbx, 0x0)) & ~0ULL, b = (uint64_t)(0x0ULL) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    rcx = rsp + 0x20;
    ML_M8(rcx, 0x0) = rax;
    rax = ML_M8(rbx, 0x8);
    ML_M8(rcx, 0x8) = rax;
    if (!f_zf) goto L54;
    rax = ML_CALL(1418233c0);
L54:
    rax = ML_M8(rbx, 0x8);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L59;
    rax = ML_CALL(1418233c0);
    goto L81;
L59:
    rcx = ML_M8(rax, 0x10);
{
    const uint64_t a = (uint64_t)(ML_M1(rcx, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L70;
    rax = ML_M8(rcx, 0x0);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L80;
L65:
    rcx = rax;
    rax = ML_M8(rax, 0x0);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L65;
    goto L80;
L70:
    rcx = ML_M8(rax, 0x8);
{
    const uint64_t a = (uint64_t)(ML_M1(rcx, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L80;
L73:
    rax = ML_M8(rcx, 0x10);
{
    const uint64_t a = (uint64_t)(ML_M8(rbx, 0x8)) & ~0ULL, b = (uint64_t)(rax) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L80;
    ML_M8(rbx, 0x8) = rcx;
    rcx = ML_M8(rcx, 0x8);
{
    const uint64_t a = (uint64_t)(ML_M1(rcx, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L73;
L80:
    ML_M8(rbx, 0x8) = rcx;
L81:
    __builtin_memcpy(xmm0, (uint8_t*)((uintptr_t)rsp + 32), 16);
    r8 = rsp + 0x30;
    rdx = rsp + 0x40;
    rcx = rbp;
    __builtin_memcpy((uint8_t*)((uintptr_t)rsp + 48), xmm0, 16);
    rax = ML_CALL(141759a90);
    goto L37;
L88:
    rcx = rsp + 0x30;
    ML_M8(rcx, 0x0) = rax;
    rax = ML_M8(rbx, 0x8);
    ML_M8(rcx, 0x8) = rax;
    rax = ML_M8(rsp, 0x38);
    rcx = rsp + 0x20;
    ML_M8(rsp, 0x28) = rax;
    rax = ML_M8(rbp, 0x0);
    ML_M8(rsp, 0x20) = rax;
    rax = ML_M8(rcx, 0x0);
    ML_M8(r12, 0x0) = rax;
    rax = ML_M8(rcx, 0x8);
    ML_M8(r12, 0x8) = rax;
L101:
    rbx = ML_M8(rsp, 0x60);
    rbp = ML_M8(rsp, 0x68);
    rsi = ML_M8(rsp, 0x70);
    rdi = ML_M8(rsp, 0x78);
    rax = r12;
    rsp = rsp + (0x50ULL);
    { const uint64_t v = ML_M8(rsp, 0); rsp += 8; r12 = v; }
    return rax;
#undef ML_CALL
    return rax;
}

__attribute__((weak)) uint64_t (*g_fnLIFT_141757740)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t) = nullptr;
__attribute__((weak)) uint64_t (*g_fnLIFT_141759ef0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t) = nullptr;
uint64_t SynLift_14175df00(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A) {
    uint64_t rax = 0, rbx = 0, rbp = 0, rsi = 0, rdi = 0, r10 = 0, r11 = 0, r12 = 0, r13 = 0, r14 = 0, r15 = 0;
    uint64_t rcx = rcxA, rdx = rdxA, r8 = r8A, r9 = r9A;
    bool f_zf = false, f_cf = false, f_sf = false, f_of = false;
    uint8_t xmm0[16] = {0}, xmm1[16] = {0}, xmm2[16] = {0}, xmm3[16] = {0}, xmm4[16] = {0}, xmm5[16] = {0};
    alignas(16) uint8_t stkFrame[0x400] = {0};
    uint64_t rsp = (uint64_t)(uintptr_t)(stkFrame + 0x200);
#define ML_CALL(t) g_fnLIFT_##t(rcx, rdx, r8, r9, ML_M8(rsp, 0x20), ML_M8(rsp, 0x28))
    ML_M8(rsp, 0x8) = rbx;
    ML_M8(rsp, 0x10) = rbp;
    ML_M8(rsp, 0x18) = rsi;
    ML_M8(rsp, 0x20) = rdi;
    rsp -= 8; ML_M8(rsp, 0) = r12;
    rsp = rsp - (0x50ULL);
    rax = ML_M8(rcx, 0x30);
    rsi = r9;
    rbx = r8;
    rdi = ML_M8(rax, 0x0);
    rax = ML_M8(r8, 0x0);
    r12 = rdx;
    rbp = rcx;
{
    const uint64_t r = ((uint64_t)(rax) & ~0ULL) & ((uint64_t)(rax) & ~0ULL);
    f_zf = (r == 0); f_cf = false; f_sf = ((r & 0x8000000000000000ULL) != 0);
    f_of = false;
}
    if (f_zf) goto L17;
{
    const uint64_t a = (uint64_t)(rax) & ~0ULL, b = (uint64_t)(ML_M8(rcx, 0x0)) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (f_zf) goto L18;
L17:
    rax = ML_CALL(1418233c0);
L18:
{
    const uint64_t a = (uint64_t)(ML_M8(rbx, 0x8)) & ~0ULL, b = (uint64_t)(rdi) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L37;
    rax = ML_M8(rsi, 0x0);
    rdi = ML_M8(rbp, 0x30);
{
    const uint64_t r = ((uint64_t)(rax) & ~0ULL) & ((uint64_t)(rax) & ~0ULL);
    f_zf = (r == 0); f_cf = false; f_sf = ((r & 0x8000000000000000ULL) != 0);
    f_of = false;
}
    if (f_zf) goto L26;
{
    const uint64_t a = (uint64_t)(rax) & ~0ULL, b = (uint64_t)(ML_M8(rbp, 0x0)) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (f_zf) goto L27;
L26:
    rax = ML_CALL(1418233c0);
L27:
{
    const uint64_t a = (uint64_t)(ML_M8(rsi, 0x8)) & ~0ULL, b = (uint64_t)(rdi) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L37;
    rcx = rbp;
    rax = ML_CALL(141757740);
    r11 = ML_M8(rbp, 0x30);
    rax = ML_M8(r11, 0x0);
    ML_M8(r12, 0x8) = rax;
    rax = ML_M8(rbp, 0x0);
    ML_M8(r12, 0x0) = rax;
    goto L101;
L37:
    rax = ML_M8(rbx, 0x0);
{
    const uint64_t r = ((uint64_t)(rax) & ~0ULL) & ((uint64_t)(rax) & ~0ULL);
    f_zf = (r == 0); f_cf = false; f_sf = ((r & 0x8000000000000000ULL) != 0);
    f_of = false;
}
    if (f_zf) goto L42;
{
    const uint64_t a = (uint64_t)(rax) & ~0ULL, b = (uint64_t)(ML_M8(rsi, 0x0)) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (f_zf) goto L43;
L42:
    rax = ML_CALL(1418233c0);
L43:
    rax = ML_M8(rsi, 0x8);
{
    const uint64_t a = (uint64_t)(ML_M8(rbx, 0x8)) & ~0ULL, b = (uint64_t)(rax) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    rax = ML_M8(rbx, 0x0);
    if (f_zf) goto L88;
{
    const uint64_t a = (uint64_t)(ML_M8(rbx, 0x0)) & ~0ULL, b = (uint64_t)(0x0ULL) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    rcx = rsp + 0x20;
    ML_M8(rcx, 0x0) = rax;
    rax = ML_M8(rbx, 0x8);
    ML_M8(rcx, 0x8) = rax;
    if (!f_zf) goto L54;
    rax = ML_CALL(1418233c0);
L54:
    rax = ML_M8(rbx, 0x8);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L59;
    rax = ML_CALL(1418233c0);
    goto L81;
L59:
    rcx = ML_M8(rax, 0x10);
{
    const uint64_t a = (uint64_t)(ML_M1(rcx, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L70;
    rax = ML_M8(rcx, 0x0);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L80;
L65:
    rcx = rax;
    rax = ML_M8(rax, 0x0);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L65;
    goto L80;
L70:
    rcx = ML_M8(rax, 0x8);
{
    const uint64_t a = (uint64_t)(ML_M1(rcx, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L80;
L73:
    rax = ML_M8(rcx, 0x10);
{
    const uint64_t a = (uint64_t)(ML_M8(rbx, 0x8)) & ~0ULL, b = (uint64_t)(rax) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L80;
    ML_M8(rbx, 0x8) = rcx;
    rcx = ML_M8(rcx, 0x8);
{
    const uint64_t a = (uint64_t)(ML_M1(rcx, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L73;
L80:
    ML_M8(rbx, 0x8) = rcx;
L81:
    __builtin_memcpy(xmm0, (uint8_t*)((uintptr_t)rsp + 32), 16);
    r8 = rsp + 0x30;
    rdx = rsp + 0x40;
    rcx = rbp;
    __builtin_memcpy((uint8_t*)((uintptr_t)rsp + 48), xmm0, 16);
    rax = ML_CALL(141759ef0);
    goto L37;
L88:
    rcx = rsp + 0x30;
    ML_M8(rcx, 0x0) = rax;
    rax = ML_M8(rbx, 0x8);
    ML_M8(rcx, 0x8) = rax;
    rax = ML_M8(rsp, 0x38);
    rcx = rsp + 0x20;
    ML_M8(rsp, 0x28) = rax;
    rax = ML_M8(rbp, 0x0);
    ML_M8(rsp, 0x20) = rax;
    rax = ML_M8(rcx, 0x0);
    ML_M8(r12, 0x0) = rax;
    rax = ML_M8(rcx, 0x8);
    ML_M8(r12, 0x8) = rax;
L101:
    rbx = ML_M8(rsp, 0x60);
    rbp = ML_M8(rsp, 0x68);
    rsi = ML_M8(rsp, 0x70);
    rdi = ML_M8(rsp, 0x78);
    rax = r12;
    rsp = rsp + (0x50ULL);
    { const uint64_t v = ML_M8(rsp, 0); rsp += 8; r12 = v; }
    return rax;
#undef ML_CALL
    return rax;
}

__attribute__((weak)) uint64_t (*g_fnLIFT_1417577c0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t) = nullptr;
__attribute__((weak)) uint64_t (*g_fnLIFT_14175a300)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t) = nullptr;
uint64_t SynLift_14175e0b0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A) {
    uint64_t rax = 0, rbx = 0, rbp = 0, rsi = 0, rdi = 0, r10 = 0, r11 = 0, r12 = 0, r13 = 0, r14 = 0, r15 = 0;
    uint64_t rcx = rcxA, rdx = rdxA, r8 = r8A, r9 = r9A;
    bool f_zf = false, f_cf = false, f_sf = false, f_of = false;
    uint8_t xmm0[16] = {0}, xmm1[16] = {0}, xmm2[16] = {0}, xmm3[16] = {0}, xmm4[16] = {0}, xmm5[16] = {0};
    alignas(16) uint8_t stkFrame[0x400] = {0};
    uint64_t rsp = (uint64_t)(uintptr_t)(stkFrame + 0x200);
#define ML_CALL(t) g_fnLIFT_##t(rcx, rdx, r8, r9, ML_M8(rsp, 0x20), ML_M8(rsp, 0x28))
    ML_M8(rsp, 0x8) = rbx;
    ML_M8(rsp, 0x10) = rbp;
    ML_M8(rsp, 0x18) = rsi;
    ML_M8(rsp, 0x20) = rdi;
    rsp -= 8; ML_M8(rsp, 0) = r12;
    rsp = rsp - (0x50ULL);
    rax = ML_M8(rcx, 0x30);
    rsi = r9;
    rbx = r8;
    rdi = ML_M8(rax, 0x0);
    rax = ML_M8(r8, 0x0);
    r12 = rdx;
    rbp = rcx;
{
    const uint64_t r = ((uint64_t)(rax) & ~0ULL) & ((uint64_t)(rax) & ~0ULL);
    f_zf = (r == 0); f_cf = false; f_sf = ((r & 0x8000000000000000ULL) != 0);
    f_of = false;
}
    if (f_zf) goto L17;
{
    const uint64_t a = (uint64_t)(rax) & ~0ULL, b = (uint64_t)(ML_M8(rcx, 0x0)) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (f_zf) goto L18;
L17:
    rax = ML_CALL(1418233c0);
L18:
{
    const uint64_t a = (uint64_t)(ML_M8(rbx, 0x8)) & ~0ULL, b = (uint64_t)(rdi) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L37;
    rax = ML_M8(rsi, 0x0);
    rdi = ML_M8(rbp, 0x30);
{
    const uint64_t r = ((uint64_t)(rax) & ~0ULL) & ((uint64_t)(rax) & ~0ULL);
    f_zf = (r == 0); f_cf = false; f_sf = ((r & 0x8000000000000000ULL) != 0);
    f_of = false;
}
    if (f_zf) goto L26;
{
    const uint64_t a = (uint64_t)(rax) & ~0ULL, b = (uint64_t)(ML_M8(rbp, 0x0)) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (f_zf) goto L27;
L26:
    rax = ML_CALL(1418233c0);
L27:
{
    const uint64_t a = (uint64_t)(ML_M8(rsi, 0x8)) & ~0ULL, b = (uint64_t)(rdi) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L37;
    rcx = rbp;
    rax = ML_CALL(1417577c0);
    r11 = ML_M8(rbp, 0x30);
    rax = ML_M8(r11, 0x0);
    ML_M8(r12, 0x8) = rax;
    rax = ML_M8(rbp, 0x0);
    ML_M8(r12, 0x0) = rax;
    goto L101;
L37:
    rax = ML_M8(rbx, 0x0);
{
    const uint64_t r = ((uint64_t)(rax) & ~0ULL) & ((uint64_t)(rax) & ~0ULL);
    f_zf = (r == 0); f_cf = false; f_sf = ((r & 0x8000000000000000ULL) != 0);
    f_of = false;
}
    if (f_zf) goto L42;
{
    const uint64_t a = (uint64_t)(rax) & ~0ULL, b = (uint64_t)(ML_M8(rsi, 0x0)) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (f_zf) goto L43;
L42:
    rax = ML_CALL(1418233c0);
L43:
    rax = ML_M8(rsi, 0x8);
{
    const uint64_t a = (uint64_t)(ML_M8(rbx, 0x8)) & ~0ULL, b = (uint64_t)(rax) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    rax = ML_M8(rbx, 0x0);
    if (f_zf) goto L88;
{
    const uint64_t a = (uint64_t)(ML_M8(rbx, 0x0)) & ~0ULL, b = (uint64_t)(0x0ULL) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    rcx = rsp + 0x20;
    ML_M8(rcx, 0x0) = rax;
    rax = ML_M8(rbx, 0x8);
    ML_M8(rcx, 0x8) = rax;
    if (!f_zf) goto L54;
    rax = ML_CALL(1418233c0);
L54:
    rax = ML_M8(rbx, 0x8);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x69)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L59;
    rax = ML_CALL(1418233c0);
    goto L81;
L59:
    rcx = ML_M8(rax, 0x10);
{
    const uint64_t a = (uint64_t)(ML_M1(rcx, 0x69)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L70;
    rax = ML_M8(rcx, 0x0);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x69)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L80;
L65:
    rcx = rax;
    rax = ML_M8(rax, 0x0);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x69)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L65;
    goto L80;
L70:
    rcx = ML_M8(rax, 0x8);
{
    const uint64_t a = (uint64_t)(ML_M1(rcx, 0x69)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L80;
L73:
    rax = ML_M8(rcx, 0x10);
{
    const uint64_t a = (uint64_t)(ML_M8(rbx, 0x8)) & ~0ULL, b = (uint64_t)(rax) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L80;
    ML_M8(rbx, 0x8) = rcx;
    rcx = ML_M8(rcx, 0x8);
{
    const uint64_t a = (uint64_t)(ML_M1(rcx, 0x69)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L73;
L80:
    ML_M8(rbx, 0x8) = rcx;
L81:
    __builtin_memcpy(xmm0, (uint8_t*)((uintptr_t)rsp + 32), 16);
    r8 = rsp + 0x30;
    rdx = rsp + 0x40;
    rcx = rbp;
    __builtin_memcpy((uint8_t*)((uintptr_t)rsp + 48), xmm0, 16);
    rax = ML_CALL(14175a300);
    goto L37;
L88:
    rcx = rsp + 0x30;
    ML_M8(rcx, 0x0) = rax;
    rax = ML_M8(rbx, 0x8);
    ML_M8(rcx, 0x8) = rax;
    rax = ML_M8(rsp, 0x38);
    rcx = rsp + 0x20;
    ML_M8(rsp, 0x28) = rax;
    rax = ML_M8(rbp, 0x0);
    ML_M8(rsp, 0x20) = rax;
    rax = ML_M8(rcx, 0x0);
    ML_M8(r12, 0x0) = rax;
    rax = ML_M8(rcx, 0x8);
    ML_M8(r12, 0x8) = rax;
L101:
    rbx = ML_M8(rsp, 0x60);
    rbp = ML_M8(rsp, 0x68);
    rsi = ML_M8(rsp, 0x70);
    rdi = ML_M8(rsp, 0x78);
    rax = r12;
    rsp = rsp + (0x50ULL);
    { const uint64_t v = ML_M8(rsp, 0); rsp += 8; r12 = v; }
    return rax;
#undef ML_CALL
    return rax;
}

__attribute__((weak)) uint64_t (*g_fnLIFT_141757840)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t) = nullptr;
__attribute__((weak)) uint64_t (*g_fnLIFT_14175a710)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t) = nullptr;
uint64_t SynLift_14175e410(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A) {
    uint64_t rax = 0, rbx = 0, rbp = 0, rsi = 0, rdi = 0, r10 = 0, r11 = 0, r12 = 0, r13 = 0, r14 = 0, r15 = 0;
    uint64_t rcx = rcxA, rdx = rdxA, r8 = r8A, r9 = r9A;
    bool f_zf = false, f_cf = false, f_sf = false, f_of = false;
    uint8_t xmm0[16] = {0}, xmm1[16] = {0}, xmm2[16] = {0}, xmm3[16] = {0}, xmm4[16] = {0}, xmm5[16] = {0};
    alignas(16) uint8_t stkFrame[0x400] = {0};
    uint64_t rsp = (uint64_t)(uintptr_t)(stkFrame + 0x200);
#define ML_CALL(t) g_fnLIFT_##t(rcx, rdx, r8, r9, ML_M8(rsp, 0x20), ML_M8(rsp, 0x28))
    ML_M8(rsp, 0x8) = rbx;
    ML_M8(rsp, 0x10) = rbp;
    ML_M8(rsp, 0x18) = rsi;
    ML_M8(rsp, 0x20) = rdi;
    rsp -= 8; ML_M8(rsp, 0) = r12;
    rsp = rsp - (0x50ULL);
    rax = ML_M8(rcx, 0x30);
    rsi = r9;
    rbx = r8;
    rdi = ML_M8(rax, 0x0);
    rax = ML_M8(r8, 0x0);
    r12 = rdx;
    rbp = rcx;
{
    const uint64_t r = ((uint64_t)(rax) & ~0ULL) & ((uint64_t)(rax) & ~0ULL);
    f_zf = (r == 0); f_cf = false; f_sf = ((r & 0x8000000000000000ULL) != 0);
    f_of = false;
}
    if (f_zf) goto L17;
{
    const uint64_t a = (uint64_t)(rax) & ~0ULL, b = (uint64_t)(ML_M8(rcx, 0x0)) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (f_zf) goto L18;
L17:
    rax = ML_CALL(1418233c0);
L18:
{
    const uint64_t a = (uint64_t)(ML_M8(rbx, 0x8)) & ~0ULL, b = (uint64_t)(rdi) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L37;
    rax = ML_M8(rsi, 0x0);
    rdi = ML_M8(rbp, 0x30);
{
    const uint64_t r = ((uint64_t)(rax) & ~0ULL) & ((uint64_t)(rax) & ~0ULL);
    f_zf = (r == 0); f_cf = false; f_sf = ((r & 0x8000000000000000ULL) != 0);
    f_of = false;
}
    if (f_zf) goto L26;
{
    const uint64_t a = (uint64_t)(rax) & ~0ULL, b = (uint64_t)(ML_M8(rbp, 0x0)) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (f_zf) goto L27;
L26:
    rax = ML_CALL(1418233c0);
L27:
{
    const uint64_t a = (uint64_t)(ML_M8(rsi, 0x8)) & ~0ULL, b = (uint64_t)(rdi) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L37;
    rcx = rbp;
    rax = ML_CALL(141757840);
    r11 = ML_M8(rbp, 0x30);
    rax = ML_M8(r11, 0x0);
    ML_M8(r12, 0x8) = rax;
    rax = ML_M8(rbp, 0x0);
    ML_M8(r12, 0x0) = rax;
    goto L101;
L37:
    rax = ML_M8(rbx, 0x0);
{
    const uint64_t r = ((uint64_t)(rax) & ~0ULL) & ((uint64_t)(rax) & ~0ULL);
    f_zf = (r == 0); f_cf = false; f_sf = ((r & 0x8000000000000000ULL) != 0);
    f_of = false;
}
    if (f_zf) goto L42;
{
    const uint64_t a = (uint64_t)(rax) & ~0ULL, b = (uint64_t)(ML_M8(rsi, 0x0)) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (f_zf) goto L43;
L42:
    rax = ML_CALL(1418233c0);
L43:
    rax = ML_M8(rsi, 0x8);
{
    const uint64_t a = (uint64_t)(ML_M8(rbx, 0x8)) & ~0ULL, b = (uint64_t)(rax) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    rax = ML_M8(rbx, 0x0);
    if (f_zf) goto L88;
{
    const uint64_t a = (uint64_t)(ML_M8(rbx, 0x0)) & ~0ULL, b = (uint64_t)(0x0ULL) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    rcx = rsp + 0x20;
    ML_M8(rcx, 0x0) = rax;
    rax = ML_M8(rbx, 0x8);
    ML_M8(rcx, 0x8) = rax;
    if (!f_zf) goto L54;
    rax = ML_CALL(1418233c0);
L54:
    rax = ML_M8(rbx, 0x8);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L59;
    rax = ML_CALL(1418233c0);
    goto L81;
L59:
    rcx = ML_M8(rax, 0x10);
{
    const uint64_t a = (uint64_t)(ML_M1(rcx, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L70;
    rax = ML_M8(rcx, 0x0);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L80;
L65:
    rcx = rax;
    rax = ML_M8(rax, 0x0);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L65;
    goto L80;
L70:
    rcx = ML_M8(rax, 0x8);
{
    const uint64_t a = (uint64_t)(ML_M1(rcx, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L80;
L73:
    rax = ML_M8(rcx, 0x10);
{
    const uint64_t a = (uint64_t)(ML_M8(rbx, 0x8)) & ~0ULL, b = (uint64_t)(rax) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L80;
    ML_M8(rbx, 0x8) = rcx;
    rcx = ML_M8(rcx, 0x8);
{
    const uint64_t a = (uint64_t)(ML_M1(rcx, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L73;
L80:
    ML_M8(rbx, 0x8) = rcx;
L81:
    __builtin_memcpy(xmm0, (uint8_t*)((uintptr_t)rsp + 32), 16);
    r8 = rsp + 0x30;
    rdx = rsp + 0x40;
    rcx = rbp;
    __builtin_memcpy((uint8_t*)((uintptr_t)rsp + 48), xmm0, 16);
    rax = ML_CALL(14175a710);
    goto L37;
L88:
    rcx = rsp + 0x30;
    ML_M8(rcx, 0x0) = rax;
    rax = ML_M8(rbx, 0x8);
    ML_M8(rcx, 0x8) = rax;
    rax = ML_M8(rsp, 0x38);
    rcx = rsp + 0x20;
    ML_M8(rsp, 0x28) = rax;
    rax = ML_M8(rbp, 0x0);
    ML_M8(rsp, 0x20) = rax;
    rax = ML_M8(rcx, 0x0);
    ML_M8(r12, 0x0) = rax;
    rax = ML_M8(rcx, 0x8);
    ML_M8(r12, 0x8) = rax;
L101:
    rbx = ML_M8(rsp, 0x60);
    rbp = ML_M8(rsp, 0x68);
    rsi = ML_M8(rsp, 0x70);
    rdi = ML_M8(rsp, 0x78);
    rax = r12;
    rsp = rsp + (0x50ULL);
    { const uint64_t v = ML_M8(rsp, 0); rsp += 8; r12 = v; }
    return rax;
#undef ML_CALL
    return rax;
}

__attribute__((weak)) uint64_t (*g_fnLIFT_1417567f0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t) = nullptr;
__attribute__((weak)) uint64_t (*g_fnLIFT_1417614e0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t) = nullptr;
uint64_t SynLift_141762db0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A) {
    uint64_t rax = 0, rbx = 0, rbp = 0, rsi = 0, rdi = 0, r10 = 0, r11 = 0, r12 = 0, r13 = 0, r14 = 0, r15 = 0;
    uint64_t rcx = rcxA, rdx = rdxA, r8 = r8A, r9 = r9A;
    bool f_zf = false, f_cf = false, f_sf = false, f_of = false;
    uint8_t xmm0[16] = {0}, xmm1[16] = {0}, xmm2[16] = {0}, xmm3[16] = {0}, xmm4[16] = {0}, xmm5[16] = {0};
    alignas(16) uint8_t stkFrame[0x400] = {0};
    uint64_t rsp = (uint64_t)(uintptr_t)(stkFrame + 0x200);
#define ML_CALL(t) g_fnLIFT_##t(rcx, rdx, r8, r9, ML_M8(rsp, 0x20), ML_M8(rsp, 0x28))
    ML_M8(rsp, 0x8) = rbx;
    ML_M8(rsp, 0x10) = rbp;
    ML_M8(rsp, 0x18) = rsi;
    ML_M8(rsp, 0x20) = rdi;
    rsp -= 8; ML_M8(rsp, 0) = r12;
    rsp = rsp - (0x50ULL);
    rax = ML_M8(rcx, 0x30);
    rsi = r9;
    rbx = r8;
    rdi = ML_M8(rax, 0x0);
    rax = ML_M8(r8, 0x0);
    r12 = rdx;
    rbp = rcx;
{
    const uint64_t r = ((uint64_t)(rax) & ~0ULL) & ((uint64_t)(rax) & ~0ULL);
    f_zf = (r == 0); f_cf = false; f_sf = ((r & 0x8000000000000000ULL) != 0);
    f_of = false;
}
    if (f_zf) goto L17;
{
    const uint64_t a = (uint64_t)(rax) & ~0ULL, b = (uint64_t)(ML_M8(rcx, 0x0)) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (f_zf) goto L18;
L17:
    rax = ML_CALL(1418233c0);
L18:
{
    const uint64_t a = (uint64_t)(ML_M8(rbx, 0x8)) & ~0ULL, b = (uint64_t)(rdi) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L37;
    rax = ML_M8(rsi, 0x0);
    rdi = ML_M8(rbp, 0x30);
{
    const uint64_t r = ((uint64_t)(rax) & ~0ULL) & ((uint64_t)(rax) & ~0ULL);
    f_zf = (r == 0); f_cf = false; f_sf = ((r & 0x8000000000000000ULL) != 0);
    f_of = false;
}
    if (f_zf) goto L26;
{
    const uint64_t a = (uint64_t)(rax) & ~0ULL, b = (uint64_t)(ML_M8(rbp, 0x0)) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (f_zf) goto L27;
L26:
    rax = ML_CALL(1418233c0);
L27:
{
    const uint64_t a = (uint64_t)(ML_M8(rsi, 0x8)) & ~0ULL, b = (uint64_t)(rdi) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L37;
    rcx = rbp;
    rax = ML_CALL(1417567f0);
    r11 = ML_M8(rbp, 0x30);
    rax = ML_M8(r11, 0x0);
    ML_M8(r12, 0x8) = rax;
    rax = ML_M8(rbp, 0x0);
    ML_M8(r12, 0x0) = rax;
    goto L101;
L37:
    rax = ML_M8(rbx, 0x0);
{
    const uint64_t r = ((uint64_t)(rax) & ~0ULL) & ((uint64_t)(rax) & ~0ULL);
    f_zf = (r == 0); f_cf = false; f_sf = ((r & 0x8000000000000000ULL) != 0);
    f_of = false;
}
    if (f_zf) goto L42;
{
    const uint64_t a = (uint64_t)(rax) & ~0ULL, b = (uint64_t)(ML_M8(rsi, 0x0)) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (f_zf) goto L43;
L42:
    rax = ML_CALL(1418233c0);
L43:
    rax = ML_M8(rsi, 0x8);
{
    const uint64_t a = (uint64_t)(ML_M8(rbx, 0x8)) & ~0ULL, b = (uint64_t)(rax) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    rax = ML_M8(rbx, 0x0);
    if (f_zf) goto L88;
{
    const uint64_t a = (uint64_t)(ML_M8(rbx, 0x0)) & ~0ULL, b = (uint64_t)(0x0ULL) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    rcx = rsp + 0x20;
    ML_M8(rcx, 0x0) = rax;
    rax = ML_M8(rbx, 0x8);
    ML_M8(rcx, 0x8) = rax;
    if (!f_zf) goto L54;
    rax = ML_CALL(1418233c0);
L54:
    rax = ML_M8(rbx, 0x8);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x2d)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L59;
    rax = ML_CALL(1418233c0);
    goto L81;
L59:
    rcx = ML_M8(rax, 0x10);
{
    const uint64_t a = (uint64_t)(ML_M1(rcx, 0x2d)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L70;
    rax = ML_M8(rcx, 0x0);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x2d)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L80;
L65:
    rcx = rax;
    rax = ML_M8(rax, 0x0);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x2d)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L65;
    goto L80;
L70:
    rcx = ML_M8(rax, 0x8);
{
    const uint64_t a = (uint64_t)(ML_M1(rcx, 0x2d)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L80;
L73:
    rax = ML_M8(rcx, 0x10);
{
    const uint64_t a = (uint64_t)(ML_M8(rbx, 0x8)) & ~0ULL, b = (uint64_t)(rax) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L80;
    ML_M8(rbx, 0x8) = rcx;
    rcx = ML_M8(rcx, 0x8);
{
    const uint64_t a = (uint64_t)(ML_M1(rcx, 0x2d)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L73;
L80:
    ML_M8(rbx, 0x8) = rcx;
L81:
    __builtin_memcpy(xmm0, (uint8_t*)((uintptr_t)rsp + 32), 16);
    r8 = rsp + 0x30;
    rdx = rsp + 0x40;
    rcx = rbp;
    __builtin_memcpy((uint8_t*)((uintptr_t)rsp + 48), xmm0, 16);
    rax = ML_CALL(1417614e0);
    goto L37;
L88:
    rcx = rsp + 0x30;
    ML_M8(rcx, 0x0) = rax;
    rax = ML_M8(rbx, 0x8);
    ML_M8(rcx, 0x8) = rax;
    rax = ML_M8(rsp, 0x38);
    rcx = rsp + 0x20;
    ML_M8(rsp, 0x28) = rax;
    rax = ML_M8(rbp, 0x0);
    ML_M8(rsp, 0x20) = rax;
    rax = ML_M8(rcx, 0x0);
    ML_M8(r12, 0x0) = rax;
    rax = ML_M8(rcx, 0x8);
    ML_M8(r12, 0x8) = rax;
L101:
    rbx = ML_M8(rsp, 0x60);
    rbp = ML_M8(rsp, 0x68);
    rsi = ML_M8(rsp, 0x70);
    rdi = ML_M8(rsp, 0x78);
    rax = r12;
    rsp = rsp + (0x50ULL);
    { const uint64_t v = ML_M8(rsp, 0); rsp += 8; r12 = v; }
    return rax;
#undef ML_CALL
    return rax;
}

__attribute__((weak)) uint64_t (*g_fnLIFT_141776c90)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t) = nullptr;
__attribute__((weak)) uint64_t (*g_fnLIFT_141777050)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t) = nullptr;
uint64_t SynLift_141777350(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A) {
    uint64_t rax = 0, rbx = 0, rbp = 0, rsi = 0, rdi = 0, r10 = 0, r11 = 0, r12 = 0, r13 = 0, r14 = 0, r15 = 0;
    uint64_t rcx = rcxA, rdx = rdxA, r8 = r8A, r9 = r9A;
    bool f_zf = false, f_cf = false, f_sf = false, f_of = false;
    uint8_t xmm0[16] = {0}, xmm1[16] = {0}, xmm2[16] = {0}, xmm3[16] = {0}, xmm4[16] = {0}, xmm5[16] = {0};
    alignas(16) uint8_t stkFrame[0x400] = {0};
    uint64_t rsp = (uint64_t)(uintptr_t)(stkFrame + 0x200);
#define ML_CALL(t) g_fnLIFT_##t(rcx, rdx, r8, r9, ML_M8(rsp, 0x20), ML_M8(rsp, 0x28))
    ML_M8(rsp, 0x8) = rbx;
    ML_M8(rsp, 0x10) = rbp;
    ML_M8(rsp, 0x18) = rsi;
    ML_M8(rsp, 0x20) = rdi;
    rsp -= 8; ML_M8(rsp, 0) = r12;
    rsp = rsp - (0x50ULL);
    rax = ML_M8(rcx, 0x30);
    rsi = r9;
    rbx = r8;
    rdi = ML_M8(rax, 0x0);
    rax = ML_M8(r8, 0x0);
    r12 = rdx;
    rbp = rcx;
{
    const uint64_t r = ((uint64_t)(rax) & ~0ULL) & ((uint64_t)(rax) & ~0ULL);
    f_zf = (r == 0); f_cf = false; f_sf = ((r & 0x8000000000000000ULL) != 0);
    f_of = false;
}
    if (f_zf) goto L17;
{
    const uint64_t a = (uint64_t)(rax) & ~0ULL, b = (uint64_t)(ML_M8(rcx, 0x0)) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (f_zf) goto L18;
L17:
    rax = ML_CALL(1418233c0);
L18:
{
    const uint64_t a = (uint64_t)(ML_M8(rbx, 0x8)) & ~0ULL, b = (uint64_t)(rdi) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L37;
    rax = ML_M8(rsi, 0x0);
    rdi = ML_M8(rbp, 0x30);
{
    const uint64_t r = ((uint64_t)(rax) & ~0ULL) & ((uint64_t)(rax) & ~0ULL);
    f_zf = (r == 0); f_cf = false; f_sf = ((r & 0x8000000000000000ULL) != 0);
    f_of = false;
}
    if (f_zf) goto L26;
{
    const uint64_t a = (uint64_t)(rax) & ~0ULL, b = (uint64_t)(ML_M8(rbp, 0x0)) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (f_zf) goto L27;
L26:
    rax = ML_CALL(1418233c0);
L27:
{
    const uint64_t a = (uint64_t)(ML_M8(rsi, 0x8)) & ~0ULL, b = (uint64_t)(rdi) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L37;
    rcx = rbp;
    rax = ML_CALL(141777050);
    r11 = ML_M8(rbp, 0x30);
    rax = ML_M8(r11, 0x0);
    ML_M8(r12, 0x8) = rax;
    rax = ML_M8(rbp, 0x0);
    ML_M8(r12, 0x0) = rax;
    goto L101;
L37:
    rax = ML_M8(rbx, 0x0);
{
    const uint64_t r = ((uint64_t)(rax) & ~0ULL) & ((uint64_t)(rax) & ~0ULL);
    f_zf = (r == 0); f_cf = false; f_sf = ((r & 0x8000000000000000ULL) != 0);
    f_of = false;
}
    if (f_zf) goto L42;
{
    const uint64_t a = (uint64_t)(rax) & ~0ULL, b = (uint64_t)(ML_M8(rsi, 0x0)) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (f_zf) goto L43;
L42:
    rax = ML_CALL(1418233c0);
L43:
    rax = ML_M8(rsi, 0x8);
{
    const uint64_t a = (uint64_t)(ML_M8(rbx, 0x8)) & ~0ULL, b = (uint64_t)(rax) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    rax = ML_M8(rbx, 0x0);
    if (f_zf) goto L88;
{
    const uint64_t a = (uint64_t)(ML_M8(rbx, 0x0)) & ~0ULL, b = (uint64_t)(0x0ULL) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    rcx = rsp + 0x20;
    ML_M8(rcx, 0x0) = rax;
    rax = ML_M8(rbx, 0x8);
    ML_M8(rcx, 0x8) = rax;
    if (!f_zf) goto L54;
    rax = ML_CALL(1418233c0);
L54:
    rax = ML_M8(rbx, 0x8);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x39)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L59;
    rax = ML_CALL(1418233c0);
    goto L81;
L59:
    rcx = ML_M8(rax, 0x10);
{
    const uint64_t a = (uint64_t)(ML_M1(rcx, 0x39)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L70;
    rax = ML_M8(rcx, 0x0);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x39)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L80;
L65:
    rcx = rax;
    rax = ML_M8(rax, 0x0);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x39)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L65;
    goto L80;
L70:
    rcx = ML_M8(rax, 0x8);
{
    const uint64_t a = (uint64_t)(ML_M1(rcx, 0x39)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L80;
L73:
    rax = ML_M8(rcx, 0x10);
{
    const uint64_t a = (uint64_t)(ML_M8(rbx, 0x8)) & ~0ULL, b = (uint64_t)(rax) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L80;
    ML_M8(rbx, 0x8) = rcx;
    rcx = ML_M8(rcx, 0x8);
{
    const uint64_t a = (uint64_t)(ML_M1(rcx, 0x39)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L73;
L80:
    ML_M8(rbx, 0x8) = rcx;
L81:
    __builtin_memcpy(xmm0, (uint8_t*)((uintptr_t)rsp + 32), 16);
    r8 = rsp + 0x30;
    rdx = rsp + 0x40;
    rcx = rbp;
    __builtin_memcpy((uint8_t*)((uintptr_t)rsp + 48), xmm0, 16);
    rax = ML_CALL(141776c90);
    goto L37;
L88:
    rcx = rsp + 0x30;
    ML_M8(rcx, 0x0) = rax;
    rax = ML_M8(rbx, 0x8);
    ML_M8(rcx, 0x8) = rax;
    rax = ML_M8(rsp, 0x38);
    rcx = rsp + 0x20;
    ML_M8(rsp, 0x28) = rax;
    rax = ML_M8(rbp, 0x0);
    ML_M8(rsp, 0x20) = rax;
    rax = ML_M8(rcx, 0x0);
    ML_M8(r12, 0x0) = rax;
    rax = ML_M8(rcx, 0x8);
    ML_M8(r12, 0x8) = rax;
L101:
    rbx = ML_M8(rsp, 0x60);
    rbp = ML_M8(rsp, 0x68);
    rsi = ML_M8(rsp, 0x70);
    rdi = ML_M8(rsp, 0x78);
    rax = r12;
    rsp = rsp + (0x50ULL);
    { const uint64_t v = ML_M8(rsp, 0); rsp += 8; r12 = v; }
    return rax;
#undef ML_CALL
    return rax;
}

__attribute__((weak)) uint64_t (*g_fnLIFT_14177ac60)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t) = nullptr;
__attribute__((weak)) uint64_t (*g_fnLIFT_14177b800)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t) = nullptr;
uint64_t SynLift_14177bcb0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A) {
    uint64_t rax = 0, rbx = 0, rbp = 0, rsi = 0, rdi = 0, r10 = 0, r11 = 0, r12 = 0, r13 = 0, r14 = 0, r15 = 0;
    uint64_t rcx = rcxA, rdx = rdxA, r8 = r8A, r9 = r9A;
    bool f_zf = false, f_cf = false, f_sf = false, f_of = false;
    uint8_t xmm0[16] = {0}, xmm1[16] = {0}, xmm2[16] = {0}, xmm3[16] = {0}, xmm4[16] = {0}, xmm5[16] = {0};
    alignas(16) uint8_t stkFrame[0x400] = {0};
    uint64_t rsp = (uint64_t)(uintptr_t)(stkFrame + 0x200);
#define ML_CALL(t) g_fnLIFT_##t(rcx, rdx, r8, r9, ML_M8(rsp, 0x20), ML_M8(rsp, 0x28))
    ML_M8(rsp, 0x8) = rbx;
    ML_M8(rsp, 0x10) = rbp;
    ML_M8(rsp, 0x18) = rsi;
    ML_M8(rsp, 0x20) = rdi;
    rsp -= 8; ML_M8(rsp, 0) = r12;
    rsp = rsp - (0x50ULL);
    rax = ML_M8(rcx, 0x30);
    rsi = r9;
    rbx = r8;
    rdi = ML_M8(rax, 0x0);
    rax = ML_M8(r8, 0x0);
    r12 = rdx;
    rbp = rcx;
{
    const uint64_t r = ((uint64_t)(rax) & ~0ULL) & ((uint64_t)(rax) & ~0ULL);
    f_zf = (r == 0); f_cf = false; f_sf = ((r & 0x8000000000000000ULL) != 0);
    f_of = false;
}
    if (f_zf) goto L17;
{
    const uint64_t a = (uint64_t)(rax) & ~0ULL, b = (uint64_t)(ML_M8(rcx, 0x0)) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (f_zf) goto L18;
L17:
    rax = ML_CALL(1418233c0);
L18:
{
    const uint64_t a = (uint64_t)(ML_M8(rbx, 0x8)) & ~0ULL, b = (uint64_t)(rdi) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L37;
    rax = ML_M8(rsi, 0x0);
    rdi = ML_M8(rbp, 0x30);
{
    const uint64_t r = ((uint64_t)(rax) & ~0ULL) & ((uint64_t)(rax) & ~0ULL);
    f_zf = (r == 0); f_cf = false; f_sf = ((r & 0x8000000000000000ULL) != 0);
    f_of = false;
}
    if (f_zf) goto L26;
{
    const uint64_t a = (uint64_t)(rax) & ~0ULL, b = (uint64_t)(ML_M8(rbp, 0x0)) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (f_zf) goto L27;
L26:
    rax = ML_CALL(1418233c0);
L27:
{
    const uint64_t a = (uint64_t)(ML_M8(rsi, 0x8)) & ~0ULL, b = (uint64_t)(rdi) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L37;
    rcx = rbp;
    rax = ML_CALL(14177ac60);
    r11 = ML_M8(rbp, 0x30);
    rax = ML_M8(r11, 0x0);
    ML_M8(r12, 0x8) = rax;
    rax = ML_M8(rbp, 0x0);
    ML_M8(r12, 0x0) = rax;
    goto L101;
L37:
    rax = ML_M8(rbx, 0x0);
{
    const uint64_t r = ((uint64_t)(rax) & ~0ULL) & ((uint64_t)(rax) & ~0ULL);
    f_zf = (r == 0); f_cf = false; f_sf = ((r & 0x8000000000000000ULL) != 0);
    f_of = false;
}
    if (f_zf) goto L42;
{
    const uint64_t a = (uint64_t)(rax) & ~0ULL, b = (uint64_t)(ML_M8(rsi, 0x0)) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (f_zf) goto L43;
L42:
    rax = ML_CALL(1418233c0);
L43:
    rax = ML_M8(rsi, 0x8);
{
    const uint64_t a = (uint64_t)(ML_M8(rbx, 0x8)) & ~0ULL, b = (uint64_t)(rax) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    rax = ML_M8(rbx, 0x0);
    if (f_zf) goto L88;
{
    const uint64_t a = (uint64_t)(ML_M8(rbx, 0x0)) & ~0ULL, b = (uint64_t)(0x0ULL) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    rcx = rsp + 0x20;
    ML_M8(rcx, 0x0) = rax;
    rax = ML_M8(rbx, 0x8);
    ML_M8(rcx, 0x8) = rax;
    if (!f_zf) goto L54;
    rax = ML_CALL(1418233c0);
L54:
    rax = ML_M8(rbx, 0x8);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L59;
    rax = ML_CALL(1418233c0);
    goto L81;
L59:
    rcx = ML_M8(rax, 0x10);
{
    const uint64_t a = (uint64_t)(ML_M1(rcx, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L70;
    rax = ML_M8(rcx, 0x0);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L80;
L65:
    rcx = rax;
    rax = ML_M8(rax, 0x0);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L65;
    goto L80;
L70:
    rcx = ML_M8(rax, 0x8);
{
    const uint64_t a = (uint64_t)(ML_M1(rcx, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L80;
L73:
    rax = ML_M8(rcx, 0x10);
{
    const uint64_t a = (uint64_t)(ML_M8(rbx, 0x8)) & ~0ULL, b = (uint64_t)(rax) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L80;
    ML_M8(rbx, 0x8) = rcx;
    rcx = ML_M8(rcx, 0x8);
{
    const uint64_t a = (uint64_t)(ML_M1(rcx, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L73;
L80:
    ML_M8(rbx, 0x8) = rcx;
L81:
    __builtin_memcpy(xmm0, (uint8_t*)((uintptr_t)rsp + 32), 16);
    r8 = rsp + 0x30;
    rdx = rsp + 0x40;
    rcx = rbp;
    __builtin_memcpy((uint8_t*)((uintptr_t)rsp + 48), xmm0, 16);
    rax = ML_CALL(14177b800);
    goto L37;
L88:
    rcx = rsp + 0x30;
    ML_M8(rcx, 0x0) = rax;
    rax = ML_M8(rbx, 0x8);
    ML_M8(rcx, 0x8) = rax;
    rax = ML_M8(rsp, 0x38);
    rcx = rsp + 0x20;
    ML_M8(rsp, 0x28) = rax;
    rax = ML_M8(rbp, 0x0);
    ML_M8(rsp, 0x20) = rax;
    rax = ML_M8(rcx, 0x0);
    ML_M8(r12, 0x0) = rax;
    rax = ML_M8(rcx, 0x8);
    ML_M8(r12, 0x8) = rax;
L101:
    rbx = ML_M8(rsp, 0x60);
    rbp = ML_M8(rsp, 0x68);
    rsi = ML_M8(rsp, 0x70);
    rdi = ML_M8(rsp, 0x78);
    rax = r12;
    rsp = rsp + (0x50ULL);
    { const uint64_t v = ML_M8(rsp, 0); rsp += 8; r12 = v; }
    return rax;
#undef ML_CALL
    return rax;
}

__attribute__((weak)) uint64_t (*g_fnLIFT_14178ab70)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t) = nullptr;
__attribute__((weak)) uint64_t (*g_fnLIFT_14178af30)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t) = nullptr;
uint64_t SynLift_14178b8b0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A) {
    uint64_t rax = 0, rbx = 0, rbp = 0, rsi = 0, rdi = 0, r10 = 0, r11 = 0, r12 = 0, r13 = 0, r14 = 0, r15 = 0;
    uint64_t rcx = rcxA, rdx = rdxA, r8 = r8A, r9 = r9A;
    bool f_zf = false, f_cf = false, f_sf = false, f_of = false;
    uint8_t xmm0[16] = {0}, xmm1[16] = {0}, xmm2[16] = {0}, xmm3[16] = {0}, xmm4[16] = {0}, xmm5[16] = {0};
    alignas(16) uint8_t stkFrame[0x400] = {0};
    uint64_t rsp = (uint64_t)(uintptr_t)(stkFrame + 0x200);
#define ML_CALL(t) g_fnLIFT_##t(rcx, rdx, r8, r9, ML_M8(rsp, 0x20), ML_M8(rsp, 0x28))
    ML_M8(rsp, 0x8) = rbx;
    ML_M8(rsp, 0x10) = rbp;
    ML_M8(rsp, 0x18) = rsi;
    ML_M8(rsp, 0x20) = rdi;
    rsp -= 8; ML_M8(rsp, 0) = r12;
    rsp = rsp - (0x50ULL);
    rax = ML_M8(rcx, 0x30);
    rsi = r9;
    rbx = r8;
    rdi = ML_M8(rax, 0x0);
    rax = ML_M8(r8, 0x0);
    r12 = rdx;
    rbp = rcx;
{
    const uint64_t r = ((uint64_t)(rax) & ~0ULL) & ((uint64_t)(rax) & ~0ULL);
    f_zf = (r == 0); f_cf = false; f_sf = ((r & 0x8000000000000000ULL) != 0);
    f_of = false;
}
    if (f_zf) goto L17;
{
    const uint64_t a = (uint64_t)(rax) & ~0ULL, b = (uint64_t)(ML_M8(rcx, 0x0)) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (f_zf) goto L18;
L17:
    rax = ML_CALL(1418233c0);
L18:
{
    const uint64_t a = (uint64_t)(ML_M8(rbx, 0x8)) & ~0ULL, b = (uint64_t)(rdi) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L37;
    rax = ML_M8(rsi, 0x0);
    rdi = ML_M8(rbp, 0x30);
{
    const uint64_t r = ((uint64_t)(rax) & ~0ULL) & ((uint64_t)(rax) & ~0ULL);
    f_zf = (r == 0); f_cf = false; f_sf = ((r & 0x8000000000000000ULL) != 0);
    f_of = false;
}
    if (f_zf) goto L26;
{
    const uint64_t a = (uint64_t)(rax) & ~0ULL, b = (uint64_t)(ML_M8(rbp, 0x0)) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (f_zf) goto L27;
L26:
    rax = ML_CALL(1418233c0);
L27:
{
    const uint64_t a = (uint64_t)(ML_M8(rsi, 0x8)) & ~0ULL, b = (uint64_t)(rdi) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L37;
    rcx = rbp;
    rax = ML_CALL(14178af30);
    r11 = ML_M8(rbp, 0x30);
    rax = ML_M8(r11, 0x0);
    ML_M8(r12, 0x8) = rax;
    rax = ML_M8(rbp, 0x0);
    ML_M8(r12, 0x0) = rax;
    goto L101;
L37:
    rax = ML_M8(rbx, 0x0);
{
    const uint64_t r = ((uint64_t)(rax) & ~0ULL) & ((uint64_t)(rax) & ~0ULL);
    f_zf = (r == 0); f_cf = false; f_sf = ((r & 0x8000000000000000ULL) != 0);
    f_of = false;
}
    if (f_zf) goto L42;
{
    const uint64_t a = (uint64_t)(rax) & ~0ULL, b = (uint64_t)(ML_M8(rsi, 0x0)) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (f_zf) goto L43;
L42:
    rax = ML_CALL(1418233c0);
L43:
    rax = ML_M8(rsi, 0x8);
{
    const uint64_t a = (uint64_t)(ML_M8(rbx, 0x8)) & ~0ULL, b = (uint64_t)(rax) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    rax = ML_M8(rbx, 0x0);
    if (f_zf) goto L88;
{
    const uint64_t a = (uint64_t)(ML_M8(rbx, 0x0)) & ~0ULL, b = (uint64_t)(0x0ULL) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    rcx = rsp + 0x20;
    ML_M8(rcx, 0x0) = rax;
    rax = ML_M8(rbx, 0x8);
    ML_M8(rcx, 0x8) = rax;
    if (!f_zf) goto L54;
    rax = ML_CALL(1418233c0);
L54:
    rax = ML_M8(rbx, 0x8);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L59;
    rax = ML_CALL(1418233c0);
    goto L81;
L59:
    rcx = ML_M8(rax, 0x10);
{
    const uint64_t a = (uint64_t)(ML_M1(rcx, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L70;
    rax = ML_M8(rcx, 0x0);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L80;
L65:
    rcx = rax;
    rax = ML_M8(rax, 0x0);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L65;
    goto L80;
L70:
    rcx = ML_M8(rax, 0x8);
{
    const uint64_t a = (uint64_t)(ML_M1(rcx, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L80;
L73:
    rax = ML_M8(rcx, 0x10);
{
    const uint64_t a = (uint64_t)(ML_M8(rbx, 0x8)) & ~0ULL, b = (uint64_t)(rax) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L80;
    ML_M8(rbx, 0x8) = rcx;
    rcx = ML_M8(rcx, 0x8);
{
    const uint64_t a = (uint64_t)(ML_M1(rcx, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L73;
L80:
    ML_M8(rbx, 0x8) = rcx;
L81:
    __builtin_memcpy(xmm0, (uint8_t*)((uintptr_t)rsp + 32), 16);
    r8 = rsp + 0x30;
    rdx = rsp + 0x40;
    rcx = rbp;
    __builtin_memcpy((uint8_t*)((uintptr_t)rsp + 48), xmm0, 16);
    rax = ML_CALL(14178ab70);
    goto L37;
L88:
    rcx = rsp + 0x30;
    ML_M8(rcx, 0x0) = rax;
    rax = ML_M8(rbx, 0x8);
    ML_M8(rcx, 0x8) = rax;
    rax = ML_M8(rsp, 0x38);
    rcx = rsp + 0x20;
    ML_M8(rsp, 0x28) = rax;
    rax = ML_M8(rbp, 0x0);
    ML_M8(rsp, 0x20) = rax;
    rax = ML_M8(rcx, 0x0);
    ML_M8(r12, 0x0) = rax;
    rax = ML_M8(rcx, 0x8);
    ML_M8(r12, 0x8) = rax;
L101:
    rbx = ML_M8(rsp, 0x60);
    rbp = ML_M8(rsp, 0x68);
    rsi = ML_M8(rsp, 0x70);
    rdi = ML_M8(rsp, 0x78);
    rax = r12;
    rsp = rsp + (0x50ULL);
    { const uint64_t v = ML_M8(rsp, 0); rsp += 8; r12 = v; }
    return rax;
#undef ML_CALL
    return rax;
}

__attribute__((weak)) uint64_t (*g_fnLIFT_1417948b0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t) = nullptr;
__attribute__((weak)) uint64_t (*g_fnLIFT_141794c70)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t) = nullptr;
uint64_t SynLift_141796b10(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A) {
    uint64_t rax = 0, rbx = 0, rbp = 0, rsi = 0, rdi = 0, r10 = 0, r11 = 0, r12 = 0, r13 = 0, r14 = 0, r15 = 0;
    uint64_t rcx = rcxA, rdx = rdxA, r8 = r8A, r9 = r9A;
    bool f_zf = false, f_cf = false, f_sf = false, f_of = false;
    uint8_t xmm0[16] = {0}, xmm1[16] = {0}, xmm2[16] = {0}, xmm3[16] = {0}, xmm4[16] = {0}, xmm5[16] = {0};
    alignas(16) uint8_t stkFrame[0x400] = {0};
    uint64_t rsp = (uint64_t)(uintptr_t)(stkFrame + 0x200);
#define ML_CALL(t) g_fnLIFT_##t(rcx, rdx, r8, r9, ML_M8(rsp, 0x20), ML_M8(rsp, 0x28))
    ML_M8(rsp, 0x8) = rbx;
    ML_M8(rsp, 0x10) = rbp;
    ML_M8(rsp, 0x18) = rsi;
    ML_M8(rsp, 0x20) = rdi;
    rsp -= 8; ML_M8(rsp, 0) = r12;
    rsp = rsp - (0x50ULL);
    rax = ML_M8(rcx, 0x30);
    rsi = r9;
    rbx = r8;
    rdi = ML_M8(rax, 0x0);
    rax = ML_M8(r8, 0x0);
    r12 = rdx;
    rbp = rcx;
{
    const uint64_t r = ((uint64_t)(rax) & ~0ULL) & ((uint64_t)(rax) & ~0ULL);
    f_zf = (r == 0); f_cf = false; f_sf = ((r & 0x8000000000000000ULL) != 0);
    f_of = false;
}
    if (f_zf) goto L17;
{
    const uint64_t a = (uint64_t)(rax) & ~0ULL, b = (uint64_t)(ML_M8(rcx, 0x0)) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (f_zf) goto L18;
L17:
    rax = ML_CALL(1418233c0);
L18:
{
    const uint64_t a = (uint64_t)(ML_M8(rbx, 0x8)) & ~0ULL, b = (uint64_t)(rdi) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L37;
    rax = ML_M8(rsi, 0x0);
    rdi = ML_M8(rbp, 0x30);
{
    const uint64_t r = ((uint64_t)(rax) & ~0ULL) & ((uint64_t)(rax) & ~0ULL);
    f_zf = (r == 0); f_cf = false; f_sf = ((r & 0x8000000000000000ULL) != 0);
    f_of = false;
}
    if (f_zf) goto L26;
{
    const uint64_t a = (uint64_t)(rax) & ~0ULL, b = (uint64_t)(ML_M8(rbp, 0x0)) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (f_zf) goto L27;
L26:
    rax = ML_CALL(1418233c0);
L27:
{
    const uint64_t a = (uint64_t)(ML_M8(rsi, 0x8)) & ~0ULL, b = (uint64_t)(rdi) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L37;
    rcx = rbp;
    rax = ML_CALL(141794c70);
    r11 = ML_M8(rbp, 0x30);
    rax = ML_M8(r11, 0x0);
    ML_M8(r12, 0x8) = rax;
    rax = ML_M8(rbp, 0x0);
    ML_M8(r12, 0x0) = rax;
    goto L101;
L37:
    rax = ML_M8(rbx, 0x0);
{
    const uint64_t r = ((uint64_t)(rax) & ~0ULL) & ((uint64_t)(rax) & ~0ULL);
    f_zf = (r == 0); f_cf = false; f_sf = ((r & 0x8000000000000000ULL) != 0);
    f_of = false;
}
    if (f_zf) goto L42;
{
    const uint64_t a = (uint64_t)(rax) & ~0ULL, b = (uint64_t)(ML_M8(rsi, 0x0)) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (f_zf) goto L43;
L42:
    rax = ML_CALL(1418233c0);
L43:
    rax = ML_M8(rsi, 0x8);
{
    const uint64_t a = (uint64_t)(ML_M8(rbx, 0x8)) & ~0ULL, b = (uint64_t)(rax) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    rax = ML_M8(rbx, 0x0);
    if (f_zf) goto L88;
{
    const uint64_t a = (uint64_t)(ML_M8(rbx, 0x0)) & ~0ULL, b = (uint64_t)(0x0ULL) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    rcx = rsp + 0x20;
    ML_M8(rcx, 0x0) = rax;
    rax = ML_M8(rbx, 0x8);
    ML_M8(rcx, 0x8) = rax;
    if (!f_zf) goto L54;
    rax = ML_CALL(1418233c0);
L54:
    rax = ML_M8(rbx, 0x8);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x21)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L59;
    rax = ML_CALL(1418233c0);
    goto L81;
L59:
    rcx = ML_M8(rax, 0x10);
{
    const uint64_t a = (uint64_t)(ML_M1(rcx, 0x21)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L70;
    rax = ML_M8(rcx, 0x0);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x21)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L80;
L65:
    rcx = rax;
    rax = ML_M8(rax, 0x0);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x21)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L65;
    goto L80;
L70:
    rcx = ML_M8(rax, 0x8);
{
    const uint64_t a = (uint64_t)(ML_M1(rcx, 0x21)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L80;
L73:
    rax = ML_M8(rcx, 0x10);
{
    const uint64_t a = (uint64_t)(ML_M8(rbx, 0x8)) & ~0ULL, b = (uint64_t)(rax) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L80;
    ML_M8(rbx, 0x8) = rcx;
    rcx = ML_M8(rcx, 0x8);
{
    const uint64_t a = (uint64_t)(ML_M1(rcx, 0x21)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L73;
L80:
    ML_M8(rbx, 0x8) = rcx;
L81:
    __builtin_memcpy(xmm0, (uint8_t*)((uintptr_t)rsp + 32), 16);
    r8 = rsp + 0x30;
    rdx = rsp + 0x40;
    rcx = rbp;
    __builtin_memcpy((uint8_t*)((uintptr_t)rsp + 48), xmm0, 16);
    rax = ML_CALL(1417948b0);
    goto L37;
L88:
    rcx = rsp + 0x30;
    ML_M8(rcx, 0x0) = rax;
    rax = ML_M8(rbx, 0x8);
    ML_M8(rcx, 0x8) = rax;
    rax = ML_M8(rsp, 0x38);
    rcx = rsp + 0x20;
    ML_M8(rsp, 0x28) = rax;
    rax = ML_M8(rbp, 0x0);
    ML_M8(rsp, 0x20) = rax;
    rax = ML_M8(rcx, 0x0);
    ML_M8(r12, 0x0) = rax;
    rax = ML_M8(rcx, 0x8);
    ML_M8(r12, 0x8) = rax;
L101:
    rbx = ML_M8(rsp, 0x60);
    rbp = ML_M8(rsp, 0x68);
    rsi = ML_M8(rsp, 0x70);
    rdi = ML_M8(rsp, 0x78);
    rax = r12;
    rsp = rsp + (0x50ULL);
    { const uint64_t v = ML_M8(rsp, 0); rsp += 8; r12 = v; }
    return rax;
#undef ML_CALL
    return rax;
}

__attribute__((weak)) uint64_t (*g_fnLIFT_141794280)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t) = nullptr;
__attribute__((weak)) uint64_t (*g_fnLIFT_141795230)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t) = nullptr;
uint64_t SynLift_141797280(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A) {
    uint64_t rax = 0, rbx = 0, rbp = 0, rsi = 0, rdi = 0, r10 = 0, r11 = 0, r12 = 0, r13 = 0, r14 = 0, r15 = 0;
    uint64_t rcx = rcxA, rdx = rdxA, r8 = r8A, r9 = r9A;
    bool f_zf = false, f_cf = false, f_sf = false, f_of = false;
    uint8_t xmm0[16] = {0}, xmm1[16] = {0}, xmm2[16] = {0}, xmm3[16] = {0}, xmm4[16] = {0}, xmm5[16] = {0};
    alignas(16) uint8_t stkFrame[0x400] = {0};
    uint64_t rsp = (uint64_t)(uintptr_t)(stkFrame + 0x200);
#define ML_CALL(t) g_fnLIFT_##t(rcx, rdx, r8, r9, ML_M8(rsp, 0x20), ML_M8(rsp, 0x28))
    ML_M8(rsp, 0x8) = rbx;
    ML_M8(rsp, 0x10) = rbp;
    ML_M8(rsp, 0x18) = rsi;
    ML_M8(rsp, 0x20) = rdi;
    rsp -= 8; ML_M8(rsp, 0) = r12;
    rsp = rsp - (0x50ULL);
    rax = ML_M8(rcx, 0x30);
    rsi = r9;
    rbx = r8;
    rdi = ML_M8(rax, 0x0);
    rax = ML_M8(r8, 0x0);
    r12 = rdx;
    rbp = rcx;
{
    const uint64_t r = ((uint64_t)(rax) & ~0ULL) & ((uint64_t)(rax) & ~0ULL);
    f_zf = (r == 0); f_cf = false; f_sf = ((r & 0x8000000000000000ULL) != 0);
    f_of = false;
}
    if (f_zf) goto L17;
{
    const uint64_t a = (uint64_t)(rax) & ~0ULL, b = (uint64_t)(ML_M8(rcx, 0x0)) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (f_zf) goto L18;
L17:
    rax = ML_CALL(1418233c0);
L18:
{
    const uint64_t a = (uint64_t)(ML_M8(rbx, 0x8)) & ~0ULL, b = (uint64_t)(rdi) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L37;
    rax = ML_M8(rsi, 0x0);
    rdi = ML_M8(rbp, 0x30);
{
    const uint64_t r = ((uint64_t)(rax) & ~0ULL) & ((uint64_t)(rax) & ~0ULL);
    f_zf = (r == 0); f_cf = false; f_sf = ((r & 0x8000000000000000ULL) != 0);
    f_of = false;
}
    if (f_zf) goto L26;
{
    const uint64_t a = (uint64_t)(rax) & ~0ULL, b = (uint64_t)(ML_M8(rbp, 0x0)) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (f_zf) goto L27;
L26:
    rax = ML_CALL(1418233c0);
L27:
{
    const uint64_t a = (uint64_t)(ML_M8(rsi, 0x8)) & ~0ULL, b = (uint64_t)(rdi) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L37;
    rcx = rbp;
    rax = ML_CALL(141794280);
    r11 = ML_M8(rbp, 0x30);
    rax = ML_M8(r11, 0x0);
    ML_M8(r12, 0x8) = rax;
    rax = ML_M8(rbp, 0x0);
    ML_M8(r12, 0x0) = rax;
    goto L101;
L37:
    rax = ML_M8(rbx, 0x0);
{
    const uint64_t r = ((uint64_t)(rax) & ~0ULL) & ((uint64_t)(rax) & ~0ULL);
    f_zf = (r == 0); f_cf = false; f_sf = ((r & 0x8000000000000000ULL) != 0);
    f_of = false;
}
    if (f_zf) goto L42;
{
    const uint64_t a = (uint64_t)(rax) & ~0ULL, b = (uint64_t)(ML_M8(rsi, 0x0)) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (f_zf) goto L43;
L42:
    rax = ML_CALL(1418233c0);
L43:
    rax = ML_M8(rsi, 0x8);
{
    const uint64_t a = (uint64_t)(ML_M8(rbx, 0x8)) & ~0ULL, b = (uint64_t)(rax) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    rax = ML_M8(rbx, 0x0);
    if (f_zf) goto L88;
{
    const uint64_t a = (uint64_t)(ML_M8(rbx, 0x0)) & ~0ULL, b = (uint64_t)(0x0ULL) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    rcx = rsp + 0x20;
    ML_M8(rcx, 0x0) = rax;
    rax = ML_M8(rbx, 0x8);
    ML_M8(rcx, 0x8) = rax;
    if (!f_zf) goto L54;
    rax = ML_CALL(1418233c0);
L54:
    rax = ML_M8(rbx, 0x8);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L59;
    rax = ML_CALL(1418233c0);
    goto L81;
L59:
    rcx = ML_M8(rax, 0x10);
{
    const uint64_t a = (uint64_t)(ML_M1(rcx, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L70;
    rax = ML_M8(rcx, 0x0);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L80;
L65:
    rcx = rax;
    rax = ML_M8(rax, 0x0);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L65;
    goto L80;
L70:
    rcx = ML_M8(rax, 0x8);
{
    const uint64_t a = (uint64_t)(ML_M1(rcx, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L80;
L73:
    rax = ML_M8(rcx, 0x10);
{
    const uint64_t a = (uint64_t)(ML_M8(rbx, 0x8)) & ~0ULL, b = (uint64_t)(rax) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L80;
    ML_M8(rbx, 0x8) = rcx;
    rcx = ML_M8(rcx, 0x8);
{
    const uint64_t a = (uint64_t)(ML_M1(rcx, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L73;
L80:
    ML_M8(rbx, 0x8) = rcx;
L81:
    __builtin_memcpy(xmm0, (uint8_t*)((uintptr_t)rsp + 32), 16);
    r8 = rsp + 0x30;
    rdx = rsp + 0x40;
    rcx = rbp;
    __builtin_memcpy((uint8_t*)((uintptr_t)rsp + 48), xmm0, 16);
    rax = ML_CALL(141795230);
    goto L37;
L88:
    rcx = rsp + 0x30;
    ML_M8(rcx, 0x0) = rax;
    rax = ML_M8(rbx, 0x8);
    ML_M8(rcx, 0x8) = rax;
    rax = ML_M8(rsp, 0x38);
    rcx = rsp + 0x20;
    ML_M8(rsp, 0x28) = rax;
    rax = ML_M8(rbp, 0x0);
    ML_M8(rsp, 0x20) = rax;
    rax = ML_M8(rcx, 0x0);
    ML_M8(r12, 0x0) = rax;
    rax = ML_M8(rcx, 0x8);
    ML_M8(r12, 0x8) = rax;
L101:
    rbx = ML_M8(rsp, 0x60);
    rbp = ML_M8(rsp, 0x68);
    rsi = ML_M8(rsp, 0x70);
    rdi = ML_M8(rsp, 0x78);
    rax = r12;
    rsp = rsp + (0x50ULL);
    { const uint64_t v = ML_M8(rsp, 0); rsp += 8; r12 = v; }
    return rax;
#undef ML_CALL
    return rax;
}

__attribute__((weak)) uint64_t (*g_fnLIFT_1417a7780)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t) = nullptr;
__attribute__((weak)) uint64_t (*g_fnLIFT_1417a8160)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t) = nullptr;
uint64_t SynLift_1417a8610(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A) {
    uint64_t rax = 0, rbx = 0, rbp = 0, rsi = 0, rdi = 0, r10 = 0, r11 = 0, r12 = 0, r13 = 0, r14 = 0, r15 = 0;
    uint64_t rcx = rcxA, rdx = rdxA, r8 = r8A, r9 = r9A;
    bool f_zf = false, f_cf = false, f_sf = false, f_of = false;
    uint8_t xmm0[16] = {0}, xmm1[16] = {0}, xmm2[16] = {0}, xmm3[16] = {0}, xmm4[16] = {0}, xmm5[16] = {0};
    alignas(16) uint8_t stkFrame[0x400] = {0};
    uint64_t rsp = (uint64_t)(uintptr_t)(stkFrame + 0x200);
#define ML_CALL(t) g_fnLIFT_##t(rcx, rdx, r8, r9, ML_M8(rsp, 0x20), ML_M8(rsp, 0x28))
    ML_M8(rsp, 0x8) = rbx;
    ML_M8(rsp, 0x10) = rbp;
    ML_M8(rsp, 0x18) = rsi;
    ML_M8(rsp, 0x20) = rdi;
    rsp -= 8; ML_M8(rsp, 0) = r12;
    rsp = rsp - (0x50ULL);
    rax = ML_M8(rcx, 0x30);
    rsi = r9;
    rbx = r8;
    rdi = ML_M8(rax, 0x0);
    rax = ML_M8(r8, 0x0);
    r12 = rdx;
    rbp = rcx;
{
    const uint64_t r = ((uint64_t)(rax) & ~0ULL) & ((uint64_t)(rax) & ~0ULL);
    f_zf = (r == 0); f_cf = false; f_sf = ((r & 0x8000000000000000ULL) != 0);
    f_of = false;
}
    if (f_zf) goto L17;
{
    const uint64_t a = (uint64_t)(rax) & ~0ULL, b = (uint64_t)(ML_M8(rcx, 0x0)) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (f_zf) goto L18;
L17:
    rax = ML_CALL(1418233c0);
L18:
{
    const uint64_t a = (uint64_t)(ML_M8(rbx, 0x8)) & ~0ULL, b = (uint64_t)(rdi) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L37;
    rax = ML_M8(rsi, 0x0);
    rdi = ML_M8(rbp, 0x30);
{
    const uint64_t r = ((uint64_t)(rax) & ~0ULL) & ((uint64_t)(rax) & ~0ULL);
    f_zf = (r == 0); f_cf = false; f_sf = ((r & 0x8000000000000000ULL) != 0);
    f_of = false;
}
    if (f_zf) goto L26;
{
    const uint64_t a = (uint64_t)(rax) & ~0ULL, b = (uint64_t)(ML_M8(rbp, 0x0)) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (f_zf) goto L27;
L26:
    rax = ML_CALL(1418233c0);
L27:
{
    const uint64_t a = (uint64_t)(ML_M8(rsi, 0x8)) & ~0ULL, b = (uint64_t)(rdi) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L37;
    rcx = rbp;
    rax = ML_CALL(1417a7780);
    r11 = ML_M8(rbp, 0x30);
    rax = ML_M8(r11, 0x0);
    ML_M8(r12, 0x8) = rax;
    rax = ML_M8(rbp, 0x0);
    ML_M8(r12, 0x0) = rax;
    goto L101;
L37:
    rax = ML_M8(rbx, 0x0);
{
    const uint64_t r = ((uint64_t)(rax) & ~0ULL) & ((uint64_t)(rax) & ~0ULL);
    f_zf = (r == 0); f_cf = false; f_sf = ((r & 0x8000000000000000ULL) != 0);
    f_of = false;
}
    if (f_zf) goto L42;
{
    const uint64_t a = (uint64_t)(rax) & ~0ULL, b = (uint64_t)(ML_M8(rsi, 0x0)) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (f_zf) goto L43;
L42:
    rax = ML_CALL(1418233c0);
L43:
    rax = ML_M8(rsi, 0x8);
{
    const uint64_t a = (uint64_t)(ML_M8(rbx, 0x8)) & ~0ULL, b = (uint64_t)(rax) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    rax = ML_M8(rbx, 0x0);
    if (f_zf) goto L88;
{
    const uint64_t a = (uint64_t)(ML_M8(rbx, 0x0)) & ~0ULL, b = (uint64_t)(0x0ULL) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    rcx = rsp + 0x20;
    ML_M8(rcx, 0x0) = rax;
    rax = ML_M8(rbx, 0x8);
    ML_M8(rcx, 0x8) = rax;
    if (!f_zf) goto L54;
    rax = ML_CALL(1418233c0);
L54:
    rax = ML_M8(rbx, 0x8);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L59;
    rax = ML_CALL(1418233c0);
    goto L81;
L59:
    rcx = ML_M8(rax, 0x10);
{
    const uint64_t a = (uint64_t)(ML_M1(rcx, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L70;
    rax = ML_M8(rcx, 0x0);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L80;
L65:
    rcx = rax;
    rax = ML_M8(rax, 0x0);
{
    const uint64_t a = (uint64_t)(ML_M1(rax, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L65;
    goto L80;
L70:
    rcx = ML_M8(rax, 0x8);
{
    const uint64_t a = (uint64_t)(ML_M1(rcx, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (!f_zf) goto L80;
L73:
    rax = ML_M8(rcx, 0x10);
{
    const uint64_t a = (uint64_t)(ML_M8(rbx, 0x8)) & ~0ULL, b = (uint64_t)(rax) & ~0ULL;
    const uint64_t d = (a - b) & ~0ULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x8000000000000000ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x8000000000000000ULL) != 0);
}
    if (!f_zf) goto L80;
    ML_M8(rbx, 0x8) = rcx;
    rcx = ML_M8(rcx, 0x8);
{
    const uint64_t a = (uint64_t)(ML_M1(rcx, 0x29)) & 0xFFULL, b = (uint64_t)(0x0ULL) & 0xFFULL;
    const uint64_t d = (a - b) & 0xFFULL;
    f_zf = (d == 0); f_cf = (a < b); f_sf = ((d & 0x80ULL) != 0);
    f_of = (((a ^ b) & (a ^ d) & 0x80ULL) != 0);
}
    if (f_zf) goto L73;
L80:
    ML_M8(rbx, 0x8) = rcx;
L81:
    __builtin_memcpy(xmm0, (uint8_t*)((uintptr_t)rsp + 32), 16);
    r8 = rsp + 0x30;
    rdx = rsp + 0x40;
    rcx = rbp;
    __builtin_memcpy((uint8_t*)((uintptr_t)rsp + 48), xmm0, 16);
    rax = ML_CALL(1417a8160);
    goto L37;
L88:
    rcx = rsp + 0x30;
    ML_M8(rcx, 0x0) = rax;
    rax = ML_M8(rbx, 0x8);
    ML_M8(rcx, 0x8) = rax;
    rax = ML_M8(rsp, 0x38);
    rcx = rsp + 0x20;
    ML_M8(rsp, 0x28) = rax;
    rax = ML_M8(rbp, 0x0);
    ML_M8(rsp, 0x20) = rax;
    rax = ML_M8(rcx, 0x0);
    ML_M8(r12, 0x0) = rax;
    rax = ML_M8(rcx, 0x8);
    ML_M8(r12, 0x8) = rax;
L101:
    rbx = ML_M8(rsp, 0x60);
    rbp = ML_M8(rsp, 0x68);
    rsi = ML_M8(rsp, 0x70);
    rdi = ML_M8(rsp, 0x78);
    rax = r12;
    rsp = rsp + (0x50ULL);
    { const uint64_t v = ML_M8(rsp, 0); rsp += 8; r12 = v; }
    return rax;
#undef ML_CALL
    return rax;
}

}  // namespace tq
