// Generated with tools/bulk/gen_cl.py - ordered-tree clear().
// Every body is the same 31-instruction routine with its own head/count/mark offsets.
#ifndef TQ_SYNTHUNKS_CL_H
#define TQ_SYNTHUNKS_CL_H

#include <cstdint>
#include <cstddef>

namespace tq {

#define CL_Q(p, off) (*(void**)((uint8_t*)(p) + (off)))
#define CL_B(p, off) (*(uint8_t*)((uint8_t*)(p) + (off)))

extern void (*g_fnCL_t_1417262c0)(void*, void*);
extern void (*g_fnCL_t_141726310)(void*, void*);
extern void (*g_fnCL_t_141726360)(void*, void*);
extern void (*g_fnCL_t_1417270a0)(void*, void*);
extern void (*g_fnCL_t_14173bc60)(void*, void*);
extern void (*g_fnCL_t_141746600)(void*, void*);
extern void (*g_fnCL_t_141746650)(void*, void*);
extern void (*g_fnCL_t_1417540c0)(void*, void*);
extern void (*g_fnCL_t_141755490)(void*, void*);
extern void (*g_fnCL_t_1417555f0)(void*, void*);
extern void (*g_fnCL_t_141755640)(void*, void*);
extern void (*g_fnCL_t_141755690)(void*, void*);
extern void (*g_fnCL_t_1417556e0)(void*, void*);
extern void (*g_fnCL_t_141755730)(void*, void*);
extern void (*g_fnCL_t_141756920)(void*, void*);
extern void (*g_fnCL_t_1417767b0)(void*, void*);
extern void (*g_fnCL_t_14177aa60)(void*, void*);
extern void (*g_fnCL_t_14178a650)(void*, void*);
extern void (*g_fnCL_t_141793220)(void*, void*);
extern void (*g_fnCL_t_141793630)(void*, void*);
extern void (*g_fnCL_t_1417a75b0)(void*, void*);
extern void (*g_fnCL_d_1417f2fdc)(void*);

inline void* SynTreeClear_1417276c0(void* pThis) {   // 0x1417276c0
    void* const pHead = CL_Q(pThis, 0x30);                        // insn 4
    void* rsi = CL_Q(pHead, 0x8);                               // insn 6
    void* rdi = rsi;                                          // insn 7
    if (CL_B(rsi, 0x29) == 0) {                               // insn 8-9
        do {
            void* const rdx = CL_Q(rdi, 0x10);                   // insn 10
            g_fnCL_t_1417262c0(pThis, rdx);                            // insn 11-12
            rdi = CL_Q(rdi, 0x00);                             // insn 13 (before the free)
            g_fnCL_d_1417f2fdc(rsi);                                  // insn 14-15
            rsi = rdi;                                        // insn 17
        } while (CL_B(rdi, 0x29) == 0);                          // insn 16-18
    }
    void* h = CL_Q(pThis, 0x30);                                // insn 19
    CL_Q(h, 0x8) = h;                                          // insn 21
    h = CL_Q(pThis, 0x30);                                     // insn 22
    *(uint64_t*)((uint8_t*)pThis + 0x38) = 0x0;               // insn 23
    CL_Q(h, 0x00) = h;                                         // insn 24
    h = CL_Q(pThis, 0x30);                                     // insn 25
    CL_Q(h, 0x10) = h;                                         // insn 27
    return h;                                                  // rax
}

inline void* SynTreeClear_141727740(void* pThis) {   // 0x141727740
    void* const pHead = CL_Q(pThis, 0x30);                        // insn 4
    void* rsi = CL_Q(pHead, 0x8);                               // insn 6
    void* rdi = rsi;                                          // insn 7
    if (CL_B(rsi, 0x49) == 0) {                               // insn 8-9
        do {
            void* const rdx = CL_Q(rdi, 0x10);                   // insn 10
            g_fnCL_t_141726310(pThis, rdx);                            // insn 11-12
            rdi = CL_Q(rdi, 0x00);                             // insn 13 (before the free)
            g_fnCL_d_1417f2fdc(rsi);                                  // insn 14-15
            rsi = rdi;                                        // insn 17
        } while (CL_B(rdi, 0x49) == 0);                          // insn 16-18
    }
    void* h = CL_Q(pThis, 0x30);                                // insn 19
    CL_Q(h, 0x8) = h;                                          // insn 21
    h = CL_Q(pThis, 0x30);                                     // insn 22
    *(uint64_t*)((uint8_t*)pThis + 0x38) = 0x0;               // insn 23
    CL_Q(h, 0x00) = h;                                         // insn 24
    h = CL_Q(pThis, 0x30);                                     // insn 25
    CL_Q(h, 0x10) = h;                                         // insn 27
    return h;                                                  // rax
}

inline void* SynTreeClear_1417277c0(void* pThis) {   // 0x1417277c0
    void* const pHead = CL_Q(pThis, 0x30);                        // insn 4
    void* rsi = CL_Q(pHead, 0x8);                               // insn 6
    void* rdi = rsi;                                          // insn 7
    if (CL_B(rsi, 0x1d) == 0) {                               // insn 8-9
        do {
            void* const rdx = CL_Q(rdi, 0x10);                   // insn 10
            g_fnCL_t_141726360(pThis, rdx);                            // insn 11-12
            rdi = CL_Q(rdi, 0x00);                             // insn 13 (before the free)
            g_fnCL_d_1417f2fdc(rsi);                                  // insn 14-15
            rsi = rdi;                                        // insn 17
        } while (CL_B(rdi, 0x1d) == 0);                          // insn 16-18
    }
    void* h = CL_Q(pThis, 0x30);                                // insn 19
    CL_Q(h, 0x8) = h;                                          // insn 21
    h = CL_Q(pThis, 0x30);                                     // insn 22
    *(uint64_t*)((uint8_t*)pThis + 0x38) = 0x0;               // insn 23
    CL_Q(h, 0x00) = h;                                         // insn 24
    h = CL_Q(pThis, 0x30);                                     // insn 25
    CL_Q(h, 0x10) = h;                                         // insn 27
    return h;                                                  // rax
}

inline void* SynTreeClear_141728b10(void* pThis) {   // 0x141728b10
    void* const pHead = CL_Q(pThis, 0x30);                        // insn 4
    void* rsi = CL_Q(pHead, 0x8);                               // insn 6
    void* rdi = rsi;                                          // insn 7
    if (CL_B(rsi, 0x1b) == 0) {                               // insn 8-9
        do {
            void* const rdx = CL_Q(rdi, 0x10);                   // insn 10
            g_fnCL_t_1417270a0(pThis, rdx);                            // insn 11-12
            rdi = CL_Q(rdi, 0x00);                             // insn 13 (before the free)
            g_fnCL_d_1417f2fdc(rsi);                                  // insn 14-15
            rsi = rdi;                                        // insn 17
        } while (CL_B(rdi, 0x1b) == 0);                          // insn 16-18
    }
    void* h = CL_Q(pThis, 0x30);                                // insn 19
    CL_Q(h, 0x8) = h;                                          // insn 21
    h = CL_Q(pThis, 0x30);                                     // insn 22
    *(uint64_t*)((uint8_t*)pThis + 0x38) = 0x0;               // insn 23
    CL_Q(h, 0x00) = h;                                         // insn 24
    h = CL_Q(pThis, 0x30);                                     // insn 25
    CL_Q(h, 0x10) = h;                                         // insn 27
    return h;                                                  // rax
}

inline void* SynTreeClear_14173c470(void* pThis) {   // 0x14173c470
    void* const pHead = CL_Q(pThis, 0x30);                        // insn 4
    void* rsi = CL_Q(pHead, 0x8);                               // insn 6
    void* rdi = rsi;                                          // insn 7
    if (CL_B(rsi, 0x21) == 0) {                               // insn 8-9
        do {
            void* const rdx = CL_Q(rdi, 0x10);                   // insn 10
            g_fnCL_t_14173bc60(pThis, rdx);                            // insn 11-12
            rdi = CL_Q(rdi, 0x00);                             // insn 13 (before the free)
            g_fnCL_d_1417f2fdc(rsi);                                  // insn 14-15
            rsi = rdi;                                        // insn 17
        } while (CL_B(rdi, 0x21) == 0);                          // insn 16-18
    }
    void* h = CL_Q(pThis, 0x30);                                // insn 19
    CL_Q(h, 0x8) = h;                                          // insn 21
    h = CL_Q(pThis, 0x30);                                     // insn 22
    *(uint64_t*)((uint8_t*)pThis + 0x38) = 0x0;               // insn 23
    CL_Q(h, 0x00) = h;                                         // insn 24
    h = CL_Q(pThis, 0x30);                                     // insn 25
    CL_Q(h, 0x10) = h;                                         // insn 27
    return h;                                                  // rax
}

inline void* SynTreeClear_1417471f0(void* pThis) {   // 0x1417471f0
    void* const pHead = CL_Q(pThis, 0x30);                        // insn 4
    void* rsi = CL_Q(pHead, 0x8);                               // insn 6
    void* rdi = rsi;                                          // insn 7
    if (CL_B(rsi, 0x3d) == 0) {                               // insn 8-9
        do {
            void* const rdx = CL_Q(rdi, 0x10);                   // insn 10
            g_fnCL_t_141746600(pThis, rdx);                            // insn 11-12
            rdi = CL_Q(rdi, 0x00);                             // insn 13 (before the free)
            g_fnCL_d_1417f2fdc(rsi);                                  // insn 14-15
            rsi = rdi;                                        // insn 17
        } while (CL_B(rdi, 0x3d) == 0);                          // insn 16-18
    }
    void* h = CL_Q(pThis, 0x30);                                // insn 19
    CL_Q(h, 0x8) = h;                                          // insn 21
    h = CL_Q(pThis, 0x30);                                     // insn 22
    *(uint64_t*)((uint8_t*)pThis + 0x38) = 0x0;               // insn 23
    CL_Q(h, 0x00) = h;                                         // insn 24
    h = CL_Q(pThis, 0x30);                                     // insn 25
    CL_Q(h, 0x10) = h;                                         // insn 27
    return h;                                                  // rax
}

inline void* SynTreeClear_141747270(void* pThis) {   // 0x141747270
    void* const pHead = CL_Q(pThis, 0x30);                        // insn 4
    void* rsi = CL_Q(pHead, 0x8);                               // insn 6
    void* rdi = rsi;                                          // insn 7
    if (CL_B(rsi, 0x29) == 0) {                               // insn 8-9
        do {
            void* const rdx = CL_Q(rdi, 0x10);                   // insn 10
            g_fnCL_t_141746650(pThis, rdx);                            // insn 11-12
            rdi = CL_Q(rdi, 0x00);                             // insn 13 (before the free)
            g_fnCL_d_1417f2fdc(rsi);                                  // insn 14-15
            rsi = rdi;                                        // insn 17
        } while (CL_B(rdi, 0x29) == 0);                          // insn 16-18
    }
    void* h = CL_Q(pThis, 0x30);                                // insn 19
    CL_Q(h, 0x8) = h;                                          // insn 21
    h = CL_Q(pThis, 0x30);                                     // insn 22
    *(uint64_t*)((uint8_t*)pThis + 0x38) = 0x0;               // insn 23
    CL_Q(h, 0x00) = h;                                         // insn 24
    h = CL_Q(pThis, 0x30);                                     // insn 25
    CL_Q(h, 0x10) = h;                                         // insn 27
    return h;                                                  // rax
}

inline void* SynTreeClear_1417567f0(void* pThis) {   // 0x1417567f0
    void* const pHead = CL_Q(pThis, 0x30);                        // insn 4
    void* rsi = CL_Q(pHead, 0x8);                               // insn 6
    void* rdi = rsi;                                          // insn 7
    if (CL_B(rsi, 0x2d) == 0) {                               // insn 8-9
        do {
            void* const rdx = CL_Q(rdi, 0x10);                   // insn 10
            g_fnCL_t_1417540c0(pThis, rdx);                            // insn 11-12
            rdi = CL_Q(rdi, 0x00);                             // insn 13 (before the free)
            g_fnCL_d_1417f2fdc(rsi);                                  // insn 14-15
            rsi = rdi;                                        // insn 17
        } while (CL_B(rdi, 0x2d) == 0);                          // insn 16-18
    }
    void* h = CL_Q(pThis, 0x30);                                // insn 19
    CL_Q(h, 0x8) = h;                                          // insn 21
    h = CL_Q(pThis, 0x30);                                     // insn 22
    *(uint64_t*)((uint8_t*)pThis + 0x38) = 0x0;               // insn 23
    CL_Q(h, 0x00) = h;                                         // insn 24
    h = CL_Q(pThis, 0x30);                                     // insn 25
    CL_Q(h, 0x10) = h;                                         // insn 27
    return h;                                                  // rax
}

inline void* SynTreeClear_141757580(void* pThis) {   // 0x141757580
    void* const pHead = CL_Q(pThis, 0x30);                        // insn 4
    void* rsi = CL_Q(pHead, 0x8);                               // insn 6
    void* rdi = rsi;                                          // insn 7
    if (CL_B(rsi, 0x29) == 0) {                               // insn 8-9
        do {
            void* const rdx = CL_Q(rdi, 0x10);                   // insn 10
            g_fnCL_t_141755490(pThis, rdx);                            // insn 11-12
            rdi = CL_Q(rdi, 0x00);                             // insn 13 (before the free)
            g_fnCL_d_1417f2fdc(rsi);                                  // insn 14-15
            rsi = rdi;                                        // insn 17
        } while (CL_B(rdi, 0x29) == 0);                          // insn 16-18
    }
    void* h = CL_Q(pThis, 0x30);                                // insn 19
    CL_Q(h, 0x8) = h;                                          // insn 21
    h = CL_Q(pThis, 0x30);                                     // insn 22
    *(uint64_t*)((uint8_t*)pThis + 0x38) = 0x0;               // insn 23
    CL_Q(h, 0x00) = h;                                         // insn 24
    h = CL_Q(pThis, 0x30);                                     // insn 25
    CL_Q(h, 0x10) = h;                                         // insn 27
    return h;                                                  // rax
}

inline void* SynTreeClear_141757640(void* pThis) {   // 0x141757640
    void* const pHead = CL_Q(pThis, 0x30);                        // insn 4
    void* rsi = CL_Q(pHead, 0x8);                               // insn 6
    void* rdi = rsi;                                          // insn 7
    if (CL_B(rsi, 0x59) == 0) {                               // insn 8-9
        do {
            void* const rdx = CL_Q(rdi, 0x10);                   // insn 10
            g_fnCL_t_1417555f0(pThis, rdx);                            // insn 11-12
            rdi = CL_Q(rdi, 0x00);                             // insn 13 (before the free)
            g_fnCL_d_1417f2fdc(rsi);                                  // insn 14-15
            rsi = rdi;                                        // insn 17
        } while (CL_B(rdi, 0x59) == 0);                          // insn 16-18
    }
    void* h = CL_Q(pThis, 0x30);                                // insn 19
    CL_Q(h, 0x8) = h;                                          // insn 21
    h = CL_Q(pThis, 0x30);                                     // insn 22
    *(uint64_t*)((uint8_t*)pThis + 0x38) = 0x0;               // insn 23
    CL_Q(h, 0x00) = h;                                         // insn 24
    h = CL_Q(pThis, 0x30);                                     // insn 25
    CL_Q(h, 0x10) = h;                                         // insn 27
    return h;                                                  // rax
}

inline void* SynTreeClear_1417576c0(void* pThis) {   // 0x1417576c0
    void* const pHead = CL_Q(pThis, 0x30);                        // insn 4
    void* rsi = CL_Q(pHead, 0x8);                               // insn 6
    void* rdi = rsi;                                          // insn 7
    if (CL_B(rsi, 0x29) == 0) {                               // insn 8-9
        do {
            void* const rdx = CL_Q(rdi, 0x10);                   // insn 10
            g_fnCL_t_141755640(pThis, rdx);                            // insn 11-12
            rdi = CL_Q(rdi, 0x00);                             // insn 13 (before the free)
            g_fnCL_d_1417f2fdc(rsi);                                  // insn 14-15
            rsi = rdi;                                        // insn 17
        } while (CL_B(rdi, 0x29) == 0);                          // insn 16-18
    }
    void* h = CL_Q(pThis, 0x30);                                // insn 19
    CL_Q(h, 0x8) = h;                                          // insn 21
    h = CL_Q(pThis, 0x30);                                     // insn 22
    *(uint64_t*)((uint8_t*)pThis + 0x38) = 0x0;               // insn 23
    CL_Q(h, 0x00) = h;                                         // insn 24
    h = CL_Q(pThis, 0x30);                                     // insn 25
    CL_Q(h, 0x10) = h;                                         // insn 27
    return h;                                                  // rax
}

inline void* SynTreeClear_141757740(void* pThis) {   // 0x141757740
    void* const pHead = CL_Q(pThis, 0x30);                        // insn 4
    void* rsi = CL_Q(pHead, 0x8);                               // insn 6
    void* rdi = rsi;                                          // insn 7
    if (CL_B(rsi, 0x29) == 0) {                               // insn 8-9
        do {
            void* const rdx = CL_Q(rdi, 0x10);                   // insn 10
            g_fnCL_t_141755690(pThis, rdx);                            // insn 11-12
            rdi = CL_Q(rdi, 0x00);                             // insn 13 (before the free)
            g_fnCL_d_1417f2fdc(rsi);                                  // insn 14-15
            rsi = rdi;                                        // insn 17
        } while (CL_B(rdi, 0x29) == 0);                          // insn 16-18
    }
    void* h = CL_Q(pThis, 0x30);                                // insn 19
    CL_Q(h, 0x8) = h;                                          // insn 21
    h = CL_Q(pThis, 0x30);                                     // insn 22
    *(uint64_t*)((uint8_t*)pThis + 0x38) = 0x0;               // insn 23
    CL_Q(h, 0x00) = h;                                         // insn 24
    h = CL_Q(pThis, 0x30);                                     // insn 25
    CL_Q(h, 0x10) = h;                                         // insn 27
    return h;                                                  // rax
}

inline void* SynTreeClear_1417577c0(void* pThis) {   // 0x1417577c0
    void* const pHead = CL_Q(pThis, 0x30);                        // insn 4
    void* rsi = CL_Q(pHead, 0x8);                               // insn 6
    void* rdi = rsi;                                          // insn 7
    if (CL_B(rsi, 0x69) == 0) {                               // insn 8-9
        do {
            void* const rdx = CL_Q(rdi, 0x10);                   // insn 10
            g_fnCL_t_1417556e0(pThis, rdx);                            // insn 11-12
            rdi = CL_Q(rdi, 0x00);                             // insn 13 (before the free)
            g_fnCL_d_1417f2fdc(rsi);                                  // insn 14-15
            rsi = rdi;                                        // insn 17
        } while (CL_B(rdi, 0x69) == 0);                          // insn 16-18
    }
    void* h = CL_Q(pThis, 0x30);                                // insn 19
    CL_Q(h, 0x8) = h;                                          // insn 21
    h = CL_Q(pThis, 0x30);                                     // insn 22
    *(uint64_t*)((uint8_t*)pThis + 0x38) = 0x0;               // insn 23
    CL_Q(h, 0x00) = h;                                         // insn 24
    h = CL_Q(pThis, 0x30);                                     // insn 25
    CL_Q(h, 0x10) = h;                                         // insn 27
    return h;                                                  // rax
}

inline void* SynTreeClear_141757840(void* pThis) {   // 0x141757840
    void* const pHead = CL_Q(pThis, 0x30);                        // insn 4
    void* rsi = CL_Q(pHead, 0x8);                               // insn 6
    void* rdi = rsi;                                          // insn 7
    if (CL_B(rsi, 0x29) == 0) {                               // insn 8-9
        do {
            void* const rdx = CL_Q(rdi, 0x10);                   // insn 10
            g_fnCL_t_141755730(pThis, rdx);                            // insn 11-12
            rdi = CL_Q(rdi, 0x00);                             // insn 13 (before the free)
            g_fnCL_d_1417f2fdc(rsi);                                  // insn 14-15
            rsi = rdi;                                        // insn 17
        } while (CL_B(rdi, 0x29) == 0);                          // insn 16-18
    }
    void* h = CL_Q(pThis, 0x30);                                // insn 19
    CL_Q(h, 0x8) = h;                                          // insn 21
    h = CL_Q(pThis, 0x30);                                     // insn 22
    *(uint64_t*)((uint8_t*)pThis + 0x38) = 0x0;               // insn 23
    CL_Q(h, 0x00) = h;                                         // insn 24
    h = CL_Q(pThis, 0x30);                                     // insn 25
    CL_Q(h, 0x10) = h;                                         // insn 27
    return h;                                                  // rax
}

inline void* SynTreeClear_1417599c0(void* pThis) {   // 0x1417599c0
    void* const pHead = CL_Q(pThis, 0x30);                        // insn 4
    void* rsi = CL_Q(pHead, 0x8);                               // insn 6
    void* rdi = rsi;                                          // insn 7
    if (CL_B(rsi, 0x29) == 0) {                               // insn 8-9
        do {
            void* const rdx = CL_Q(rdi, 0x10);                   // insn 10
            g_fnCL_t_141756920(pThis, rdx);                            // insn 11-12
            rdi = CL_Q(rdi, 0x00);                             // insn 13 (before the free)
            g_fnCL_d_1417f2fdc(rsi);                                  // insn 14-15
            rsi = rdi;                                        // insn 17
        } while (CL_B(rdi, 0x29) == 0);                          // insn 16-18
    }
    void* h = CL_Q(pThis, 0x30);                                // insn 19
    CL_Q(h, 0x8) = h;                                          // insn 21
    h = CL_Q(pThis, 0x30);                                     // insn 22
    *(uint64_t*)((uint8_t*)pThis + 0x38) = 0x0;               // insn 23
    CL_Q(h, 0x00) = h;                                         // insn 24
    h = CL_Q(pThis, 0x30);                                     // insn 25
    CL_Q(h, 0x10) = h;                                         // insn 27
    return h;                                                  // rax
}

inline void* SynTreeClear_141777050(void* pThis) {   // 0x141777050
    void* const pHead = CL_Q(pThis, 0x30);                        // insn 4
    void* rsi = CL_Q(pHead, 0x8);                               // insn 6
    void* rdi = rsi;                                          // insn 7
    if (CL_B(rsi, 0x39) == 0) {                               // insn 8-9
        do {
            void* const rdx = CL_Q(rdi, 0x10);                   // insn 10
            g_fnCL_t_1417767b0(pThis, rdx);                            // insn 11-12
            rdi = CL_Q(rdi, 0x00);                             // insn 13 (before the free)
            g_fnCL_d_1417f2fdc(rsi);                                  // insn 14-15
            rsi = rdi;                                        // insn 17
        } while (CL_B(rdi, 0x39) == 0);                          // insn 16-18
    }
    void* h = CL_Q(pThis, 0x30);                                // insn 19
    CL_Q(h, 0x8) = h;                                          // insn 21
    h = CL_Q(pThis, 0x30);                                     // insn 22
    *(uint64_t*)((uint8_t*)pThis + 0x38) = 0x0;               // insn 23
    CL_Q(h, 0x00) = h;                                         // insn 24
    h = CL_Q(pThis, 0x30);                                     // insn 25
    CL_Q(h, 0x10) = h;                                         // insn 27
    return h;                                                  // rax
}

inline void* SynTreeClear_14177ac60(void* pThis) {   // 0x14177ac60
    void* const pHead = CL_Q(pThis, 0x30);                        // insn 4
    void* rsi = CL_Q(pHead, 0x8);                               // insn 6
    void* rdi = rsi;                                          // insn 7
    if (CL_B(rsi, 0x29) == 0) {                               // insn 8-9
        do {
            void* const rdx = CL_Q(rdi, 0x10);                   // insn 10
            g_fnCL_t_14177aa60(pThis, rdx);                            // insn 11-12
            rdi = CL_Q(rdi, 0x00);                             // insn 13 (before the free)
            g_fnCL_d_1417f2fdc(rsi);                                  // insn 14-15
            rsi = rdi;                                        // insn 17
        } while (CL_B(rdi, 0x29) == 0);                          // insn 16-18
    }
    void* h = CL_Q(pThis, 0x30);                                // insn 19
    CL_Q(h, 0x8) = h;                                          // insn 21
    h = CL_Q(pThis, 0x30);                                     // insn 22
    *(uint64_t*)((uint8_t*)pThis + 0x38) = 0x0;               // insn 23
    CL_Q(h, 0x00) = h;                                         // insn 24
    h = CL_Q(pThis, 0x30);                                     // insn 25
    CL_Q(h, 0x10) = h;                                         // insn 27
    return h;                                                  // rax
}

inline void* SynTreeClear_14178af30(void* pThis) {   // 0x14178af30
    void* const pHead = CL_Q(pThis, 0x30);                        // insn 4
    void* rsi = CL_Q(pHead, 0x8);                               // insn 6
    void* rdi = rsi;                                          // insn 7
    if (CL_B(rsi, 0x29) == 0) {                               // insn 8-9
        do {
            void* const rdx = CL_Q(rdi, 0x10);                   // insn 10
            g_fnCL_t_14178a650(pThis, rdx);                            // insn 11-12
            rdi = CL_Q(rdi, 0x00);                             // insn 13 (before the free)
            g_fnCL_d_1417f2fdc(rsi);                                  // insn 14-15
            rsi = rdi;                                        // insn 17
        } while (CL_B(rdi, 0x29) == 0);                          // insn 16-18
    }
    void* h = CL_Q(pThis, 0x30);                                // insn 19
    CL_Q(h, 0x8) = h;                                          // insn 21
    h = CL_Q(pThis, 0x30);                                     // insn 22
    *(uint64_t*)((uint8_t*)pThis + 0x38) = 0x0;               // insn 23
    CL_Q(h, 0x00) = h;                                         // insn 24
    h = CL_Q(pThis, 0x30);                                     // insn 25
    CL_Q(h, 0x10) = h;                                         // insn 27
    return h;                                                  // rax
}

inline void* SynTreeClear_141794280(void* pThis) {   // 0x141794280
    void* const pHead = CL_Q(pThis, 0x30);                        // insn 4
    void* rsi = CL_Q(pHead, 0x8);                               // insn 6
    void* rdi = rsi;                                          // insn 7
    if (CL_B(rsi, 0x29) == 0) {                               // insn 8-9
        do {
            void* const rdx = CL_Q(rdi, 0x10);                   // insn 10
            g_fnCL_t_141793220(pThis, rdx);                            // insn 11-12
            rdi = CL_Q(rdi, 0x00);                             // insn 13 (before the free)
            g_fnCL_d_1417f2fdc(rsi);                                  // insn 14-15
            rsi = rdi;                                        // insn 17
        } while (CL_B(rdi, 0x29) == 0);                          // insn 16-18
    }
    void* h = CL_Q(pThis, 0x30);                                // insn 19
    CL_Q(h, 0x8) = h;                                          // insn 21
    h = CL_Q(pThis, 0x30);                                     // insn 22
    *(uint64_t*)((uint8_t*)pThis + 0x38) = 0x0;               // insn 23
    CL_Q(h, 0x00) = h;                                         // insn 24
    h = CL_Q(pThis, 0x30);                                     // insn 25
    CL_Q(h, 0x10) = h;                                         // insn 27
    return h;                                                  // rax
}

inline void* SynTreeClear_141794c70(void* pThis) {   // 0x141794c70
    void* const pHead = CL_Q(pThis, 0x30);                        // insn 4
    void* rsi = CL_Q(pHead, 0x8);                               // insn 6
    void* rdi = rsi;                                          // insn 7
    if (CL_B(rsi, 0x21) == 0) {                               // insn 8-9
        do {
            void* const rdx = CL_Q(rdi, 0x10);                   // insn 10
            g_fnCL_t_141793630(pThis, rdx);                            // insn 11-12
            rdi = CL_Q(rdi, 0x00);                             // insn 13 (before the free)
            g_fnCL_d_1417f2fdc(rsi);                                  // insn 14-15
            rsi = rdi;                                        // insn 17
        } while (CL_B(rdi, 0x21) == 0);                          // insn 16-18
    }
    void* h = CL_Q(pThis, 0x30);                                // insn 19
    CL_Q(h, 0x8) = h;                                          // insn 21
    h = CL_Q(pThis, 0x30);                                     // insn 22
    *(uint64_t*)((uint8_t*)pThis + 0x38) = 0x0;               // insn 23
    CL_Q(h, 0x00) = h;                                         // insn 24
    h = CL_Q(pThis, 0x30);                                     // insn 25
    CL_Q(h, 0x10) = h;                                         // insn 27
    return h;                                                  // rax
}

inline void* SynTreeClear_1417a7780(void* pThis) {   // 0x1417a7780
    void* const pHead = CL_Q(pThis, 0x30);                        // insn 4
    void* rsi = CL_Q(pHead, 0x8);                               // insn 6
    void* rdi = rsi;                                          // insn 7
    if (CL_B(rsi, 0x29) == 0) {                               // insn 8-9
        do {
            void* const rdx = CL_Q(rdi, 0x10);                   // insn 10
            g_fnCL_t_1417a75b0(pThis, rdx);                            // insn 11-12
            rdi = CL_Q(rdi, 0x00);                             // insn 13 (before the free)
            g_fnCL_d_1417f2fdc(rsi);                                  // insn 14-15
            rsi = rdi;                                        // insn 17
        } while (CL_B(rdi, 0x29) == 0);                          // insn 16-18
    }
    void* h = CL_Q(pThis, 0x30);                                // insn 19
    CL_Q(h, 0x8) = h;                                          // insn 21
    h = CL_Q(pThis, 0x30);                                     // insn 22
    *(uint64_t*)((uint8_t*)pThis + 0x38) = 0x0;               // insn 23
    CL_Q(h, 0x00) = h;                                         // insn 24
    h = CL_Q(pThis, 0x30);                                     // insn 25
    CL_Q(h, 0x10) = h;                                         // insn 27
    return h;                                                  // rax
}

}  // namespace tq

#undef CL_Q
#undef CL_B

#endif