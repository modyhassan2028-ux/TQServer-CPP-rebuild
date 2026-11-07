#include "modules/syndicate/src/synlift.h"

namespace tq {

uint64_t (*g_fnLIFT_141724c50)(uint64_t, uint64_t, uint64_t, uint64_t) = nullptr;
uint64_t (*g_fnLIFT_141724cb0)(uint64_t, uint64_t, uint64_t, uint64_t) = nullptr;
uint64_t (*g_fnLIFT_141724ed0)(uint64_t, uint64_t, uint64_t, uint64_t) = nullptr;
uint64_t (*g_fnLIFT_1417f2fdc)(uint64_t, uint64_t, uint64_t, uint64_t) = nullptr;
uint64_t (*g_fnLIFT_1417f3154)(uint64_t, uint64_t, uint64_t, uint64_t) = nullptr;
uint64_t (*g_fnLIFT_141823270)(uint64_t, uint64_t, uint64_t, uint64_t) = nullptr;
uint64_t (*g_fnLIFT_141823288)(uint64_t, uint64_t, uint64_t, uint64_t) = nullptr;
uint64_t (*g_fnLIFT_1418233f8)(uint64_t, uint64_t, uint64_t, uint64_t) = nullptr;
uint64_t SynLift_141728290(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A) {
    uint64_t rax = 0, rbx = 0, rbp = 0, rsi = 0, rdi = 0, r10 = 0, r11 = 0, r12 = 0, r13 = 0, r14 = 0, r15 = 0;
    uint64_t rcx = rcxA, rdx = rdxA, r8 = r8A, r9 = r9A;
    bool f_zf = false, f_cf = false, f_sf = false, f_of = false;
    alignas(16) uint8_t stkFrame[0x400] = {0};
    uint64_t rsp = (uint64_t)(uintptr_t)(stkFrame + 0x200);
#define ML_CALL(t) g_fnLIFT_##t(rcx, rdx, r8, r9)
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

}  // namespace tq
