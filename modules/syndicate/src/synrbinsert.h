// synrbinsert.h — RAW Syndicate.dll v6159 · 0x141727e60 — insert a keyed node into the ordered tree and rebalance.
//
// This routine is a register-level transcription: every x86-64 instruction of the original body becomes one
// statement, the original register names are kept as locals, and the branch targets become labels with the
// original instruction numbers. The listing therefore diffs one-to-one against the disassembly, and the two
// rotations keep the exact statement order of the raw (including the repeated reloads of the same field).
//
// Node layout, as produced by the factory at 0x141726e10 (family NF):
//   +0x00 left · +0x08 parent · +0x10 right · +0x18 key (dword) · +0x1c colour (1 = black) · +0x1d nil mark
// Container layout used by the body: this+0x30 = head sentinel, this+0x38 = element count.
//
// One part is not reproduced statement by statement: insns 14-28 build a std::string, a std::exception and a
// derived exception through the MSVCP90 imports (0x141823270 = string(char const*), 0x1418233f8 = exception(),
// 0x141823288 = string(string const&)) and then call 0x1417f3154, which never returns. That whole block is the
// "too many elements" throw; it is modelled by a noreturn seam because the CRT exception machinery is not part
// of this module. Control flow is preserved: the seam never returns, exactly like the raw.
#pragma once
#include <cstdint>

namespace tq {

// 0x141726e10 — the node factory, with the argument mapping that routine actually reads.
extern void* (*g_fnRB_141726e10)(void* a1_unused, void* a2_left, void* a3_parent, void* a4_right,
                                 const uint32_t* pKey, uint8_t bColour);
// 0x1417f3154 — the tail of the throw path. Never returns.
extern void (*g_fnRB_1417f3154)(void);

#define RB_Q(p, off) (*(void**)((uint8_t*)(p) + (off)))
#define RB_B(p, off) (*(uint8_t*)((uint8_t*)(p) + (off)))

inline void* SynRbInsert_141727e60(void* pThis, void* pOutIter, uint8_t bLeft, void* pParent,
                                   const uint32_t* pKey) {
    // insn 1-10: frame plus argument unpacking
    void* rbx = pParent;                       // insn 7   mov rbx,r9
    const uint8_t dil = bLeft;                 // insn 8   movzx edi,r8b
    void* rbp = pOutIter;                      // insn 9   mov rbp,rdx
    void* rsi = pThis;                         // insn 10  mov rsi,rcx
    void* rax = nullptr;
    void* rcx = pThis;
    void* rdx = pOutIter;
    void* r8 = pParent;
    void* r9 = pParent;
    void* r11 = nullptr;

    // insn 11-13   movabs rax,0x3ffffffffffffffe ; cmp [rcx+0x38],rax ; jb 29
    if (RB_Q(rsi, 0x38) >= (void*)0x3ffffffffffffffeULL)
        g_fnRB_1417f3154();                    // insn 14-28, noreturn

L29:
    rdx = RB_Q(rcx, 0x30);                     // insn 29
    r9 = rdx;                                  // insn 33
    r8 = rbx;                                  // insn 34
    rax = g_fnRB_141726e10(rcx, rdx, r8, r9, pKey, 0x0);   // insn 30-35 (a6 = the byte stored at insn 30)
    r11 = rax;                                 // insn 36
    ++*(uint64_t*)((uint8_t*)rsi + 0x38);      // insn 37
    rcx = RB_Q(rsi, 0x30);                     // insn 38
    if (rbx != rcx) goto L47;                  // insn 39-40
    RB_Q(rcx, 0x8) = rax;                      // insn 41
    rcx = RB_Q(rsi, 0x30);                     // insn 42
    RB_Q(rcx, 0x0) = rax;                      // insn 43
    rcx = RB_Q(rsi, 0x30);                     // insn 44
    RB_Q(rcx, 0x10) = rax;                     // insn 45
    goto L60;                                  // insn 46

L47:
    if (!dil) goto L55;                        // insn 47-48
    RB_Q(rbx, 0x0) = rax;                      // insn 49
    rax = RB_Q(rsi, 0x30);                     // insn 50
    if (rbx != RB_Q(rax, 0x0)) goto L60;       // insn 51-52
    RB_Q(rax, 0x0) = r11;                      // insn 53
    goto L60;                                  // insn 54

L55:
    RB_Q(rbx, 0x10) = rax;                     // insn 55
    rax = RB_Q(rsi, 0x30);                     // insn 56
    if (rbx != RB_Q(rax, 0x10)) goto L60;      // insn 57-58
    RB_Q(rax, 0x10) = r11;                     // insn 59

L60:
    rdx = r11;                                 // insn 60
    r8 = (uint8_t*)r11 + 0x8;                  // insn 61   lea r8,[r11+0x8]
    rax = RB_Q(r8, 0x0);                       // insn 62
    if (RB_B(rax, 0x1c) != 0) goto L206;       // insn 63-64
    // the loop body is entered at 65; insn 60-64 only run for the first iteration

L65:
    rax = RB_Q(r8, 0x0);                       // insn 65
    rcx = RB_Q(rax, 0x8);                      // insn 66
    if (rax != RB_Q(rcx, 0x0)) goto L136;      // insn 67-68
    r9 = RB_Q(rcx, 0x10);                      // insn 69
    if (RB_B(r9, 0x1c) != 0) goto L80;         // insn 70-71
    RB_B(rax, 0x1c) = 0x1;                     // insn 72
    RB_B(r9, 0x1c) = 0x1;                      // insn 73
    rax = RB_Q(r8, 0x0);                       // insn 74
    rcx = RB_Q(rax, 0x8);                      // insn 75
    RB_B(rcx, 0x1c) = 0x0;                     // insn 76
    rax = RB_Q(r8, 0x0);                       // insn 77
    rdx = RB_Q(rax, 0x8);                      // insn 78
    goto L202;                                 // insn 79

L80:
    if (rdx != RB_Q(rax, 0x10)) goto L106;     // insn 80-81
    rdx = rax;                                 // insn 82
    rcx = RB_Q(rax, 0x10);                     // insn 83
    rax = RB_Q(rcx, 0x0);                      // insn 84
    RB_Q(rdx, 0x10) = rax;                     // insn 85
    rax = RB_Q(rcx, 0x0);                      // insn 86
    if (RB_B(rax, 0x1d) != 0) goto L90;        // insn 87-88
    RB_Q(rax, 0x8) = rdx;                      // insn 89
L90:
    r8 = (uint8_t*)rdx + 0x8;                  // insn 90
    rax = RB_Q(r8, 0x0);                       // insn 91
    RB_Q(rcx, 0x8) = rax;                      // insn 92
    rax = RB_Q(rsi, 0x30);                     // insn 93
    if (rdx != RB_Q(rax, 0x8)) goto L98;       // insn 94-95
    RB_Q(rax, 0x8) = rcx;                      // insn 96
    goto L104;                                 // insn 97
L98:
    rax = RB_Q(r8, 0x0);                       // insn 98
    if (rdx != RB_Q(rax, 0x0)) goto L103;      // insn 99-100
    RB_Q(rax, 0x0) = rcx;                      // insn 101
    goto L104;                                 // insn 102
L103:
    RB_Q(rax, 0x10) = rcx;                     // insn 103
L104:
    RB_Q(rcx, 0x0) = rdx;                      // insn 104
    RB_Q(r8, 0x0) = rcx;                       // insn 105

L106:
    rax = RB_Q(r8, 0x0);                       // insn 106
    RB_B(rax, 0x1c) = 0x1;                     // insn 107
    rax = RB_Q(r8, 0x0);                       // insn 108
    rcx = RB_Q(rax, 0x8);                      // insn 109
    RB_B(rcx, 0x1c) = 0x0;                     // insn 110
    rax = RB_Q(r8, 0x0);                       // insn 111
    rcx = RB_Q(rax, 0x8);                      // insn 112
    r8 = RB_Q(rcx, 0x0);                       // insn 113
    rax = RB_Q(r8, 0x10);                      // insn 114
    RB_Q(rcx, 0x0) = rax;                      // insn 115
    rax = RB_Q(r8, 0x10);                      // insn 116
    if (RB_B(rax, 0x1d) != 0) goto L120;       // insn 117-118
    RB_Q(rax, 0x8) = rcx;                      // insn 119
L120:
    rax = RB_Q(rcx, 0x8);                      // insn 120
    RB_Q(r8, 0x8) = rax;                       // insn 121
    rax = RB_Q(rsi, 0x30);                     // insn 122
    if (rcx != RB_Q(rax, 0x8)) goto L127;      // insn 123-124
    RB_Q(rax, 0x8) = r8;                       // insn 125
    goto L133;                                 // insn 126
L127:
    rax = RB_Q(rcx, 0x8);                      // insn 127
    if (rcx != RB_Q(rax, 0x10)) goto L132;     // insn 128-129
    RB_Q(rax, 0x10) = r8;                      // insn 130
    goto L133;                                 // insn 131
L132:
    RB_Q(rax, 0x0) = r8;                       // insn 132
L133:
    RB_Q(r8, 0x10) = rcx;                      // insn 133
    RB_Q(rcx, 0x8) = r8;                       // insn 134
    goto L202;                                 // insn 135

L136:
    r9 = RB_Q(rcx, 0x0);                       // insn 136
    if (RB_B(r9, 0x1c) != 0) goto L147;        // insn 137-138
    RB_B(rax, 0x1c) = 0x1;                     // insn 139
    RB_B(r9, 0x1c) = 0x1;                      // insn 140
    rax = RB_Q(r8, 0x0);                       // insn 141
    rcx = RB_Q(rax, 0x8);                      // insn 142
    RB_B(rcx, 0x1c) = 0x0;                     // insn 143
    rax = RB_Q(r8, 0x0);                       // insn 144
    rdx = RB_Q(rax, 0x8);                      // insn 145
    goto L202;                                 // insn 146

L147:
    if (rdx != RB_Q(rax, 0x0)) goto L173;      // insn 147-148
    rdx = rax;                                 // insn 149
    rcx = RB_Q(rax, 0x0);                      // insn 150
    rax = RB_Q(rcx, 0x10);                     // insn 151
    RB_Q(rdx, 0x0) = rax;                      // insn 152
    rax = RB_Q(rcx, 0x10);                     // insn 153
    if (RB_B(rax, 0x1d) != 0) goto L157;       // insn 154-155
    RB_Q(rax, 0x8) = rdx;                      // insn 156
L157:
    r8 = (uint8_t*)rdx + 0x8;                  // insn 157
    rax = RB_Q(r8, 0x0);                       // insn 158
    RB_Q(rcx, 0x8) = rax;                      // insn 159
    rax = RB_Q(rsi, 0x30);                     // insn 160
    if (rdx != RB_Q(rax, 0x8)) goto L165;      // insn 161-162
    RB_Q(rax, 0x8) = rcx;                      // insn 163
    goto L171;                                 // insn 164
L165:
    rax = RB_Q(r8, 0x0);                       // insn 165
    if (rdx != RB_Q(rax, 0x10)) goto L170;     // insn 166-167
    RB_Q(rax, 0x10) = rcx;                     // insn 168
    goto L171;                                 // insn 169
L170:
    RB_Q(rax, 0x0) = rcx;                      // insn 170
L171:
    RB_Q(rcx, 0x10) = rdx;                     // insn 171
    RB_Q(r8, 0x0) = rcx;                       // insn 172

L173:
    rax = RB_Q(r8, 0x0);                       // insn 173
    RB_B(rax, 0x1c) = 0x1;                     // insn 174
    rax = RB_Q(r8, 0x0);                       // insn 175
    rcx = RB_Q(rax, 0x8);                      // insn 176
    RB_B(rcx, 0x1c) = 0x0;                     // insn 177
    rax = RB_Q(r8, 0x0);                       // insn 178
    rcx = RB_Q(rax, 0x8);                      // insn 179
    r8 = RB_Q(rcx, 0x10);                      // insn 180
    rax = RB_Q(r8, 0x0);                       // insn 181
    RB_Q(rcx, 0x10) = rax;                     // insn 182
    rax = RB_Q(r8, 0x0);                       // insn 183
    if (RB_B(rax, 0x1d) != 0) goto L187;       // insn 184-185
    RB_Q(rax, 0x8) = rcx;                      // insn 186
L187:
    rax = RB_Q(rcx, 0x8);                      // insn 187
    RB_Q(r8, 0x8) = rax;                       // insn 188
    rax = RB_Q(rsi, 0x30);                     // insn 189
    if (rcx != RB_Q(rax, 0x8)) goto L194;      // insn 190-191
    RB_Q(rax, 0x8) = r8;                       // insn 192
    goto L200;                                 // insn 193
L194:
    rax = RB_Q(rcx, 0x8);                      // insn 194
    if (rcx != RB_Q(rax, 0x0)) goto L199;      // insn 195-196
    RB_Q(rax, 0x0) = r8;                       // insn 197
    goto L200;                                 // insn 198
L199:
    RB_Q(rax, 0x10) = r8;                      // insn 199
L200:
    RB_Q(r8, 0x0) = rcx;                       // insn 200
    RB_Q(rcx, 0x8) = r8;                       // insn 201

L202:
    r8 = (uint8_t*)rdx + 0x8;                  // insn 202
    rax = RB_Q(r8, 0x0);                       // insn 203
    if (RB_B(rax, 0x1c) == 0) goto L65;        // insn 204-205

L206:
    rax = RB_Q(rsi, 0x30);                     // insn 206
    rcx = RB_Q(rax, 0x8);                      // insn 207
    RB_B(rcx, 0x1c) = 0x1;                     // insn 208
    RB_Q(rbp, 0x8) = r11;                      // insn 209
    rax = RB_Q(rsi, 0x0);                      // insn 210
    RB_Q(rbp, 0x0) = rax;                      // insn 211
    rax = rbp;                                 // insn 212
    return rax;                                // insn 213-219
}

#undef RB_Q
#undef RB_B

}  // namespace tq
