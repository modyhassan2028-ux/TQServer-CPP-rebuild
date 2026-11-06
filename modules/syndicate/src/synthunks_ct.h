// synthunks_ct.h — RAW Syndicate.dll v6159 · 53 container constructors (family CT).
// Small owning node in this->f00, sentinel in this->f30 wired to itself, this->f38 cleared.
#ifndef TQ_SYN_THUNKS_CT_H
#define TQ_SYN_THUNKS_CT_H

#include <cstdint>

namespace tq {

extern void* (*g_fnCT_small_1417f3166)(uint32_t uSize);
extern void* (*g_fnCT_sent_141726c30)(void* pThis);
extern void* (*g_fnCT_sent_141726c90)(void* pThis);
extern void* (*g_fnCT_sent_141726cf0)(void* pThis);
extern void* (*g_fnCT_sent_141726d50)(void* pThis);
extern void* (*g_fnCT_sent_141726db0)(void* pThis);
extern void* (*g_fnCT_sent_141726ec0)(void* pThis);
extern void* (*g_fnCT_sent_14173bc00)(void* pThis);
extern void* (*g_fnCT_sent_14173bcb0)(void* pThis);
extern void* (*g_fnCT_sent_141746a00)(void* pThis);
extern void* (*g_fnCT_sent_141746a60)(void* pThis);
extern void* (*g_fnCT_sent_141755f90)(void* pThis);
extern void* (*g_fnCT_sent_141756200)(void* pThis);
extern void* (*g_fnCT_sent_141756260)(void* pThis);
extern void* (*g_fnCT_sent_1417562c0)(void* pThis);
extern void* (*g_fnCT_sent_1417563b0)(void* pThis);
extern void* (*g_fnCT_sent_141756410)(void* pThis);
extern void* (*g_fnCT_sent_141756470)(void* pThis);
extern void* (*g_fnCT_sent_1417564d0)(void* pThis);
extern void* (*g_fnCT_sent_1417565b0)(void* pThis);
extern void* (*g_fnCT_sent_141756610)(void* pThis);
extern void* (*g_fnCT_sent_141776670)(void* pThis);
extern void* (*g_fnCT_sent_14177ace0)(void* pThis);
extern void* (*g_fnCT_sent_14178a6a0)(void* pThis);
extern void* (*g_fnCT_sent_14178a700)(void* pThis);
extern void* (*g_fnCT_sent_1417935d0)(void* pThis);
extern void* (*g_fnCT_sent_141793680)(void* pThis);
extern void* (*g_fnCT_sent_141793760)(void* pThis);
extern void* (*g_fnCT_sent_1417a76e0)(void* pThis);
extern void* (*g_fnCT_sent_1417c8590)(void* pThis);

inline void* SynContainerCtor_141730c50(void* pThis) {   // 0x141730c50
    void* pSmall = g_fnCT_small_1417f3166(0x8);                        // insn 6-7
    if (pSmall == nullptr)                                       // both paths yield a null here
        pSmall = nullptr;                                        //   (xor eax,eax)
    *(void**)pThis = pSmall;                                     // insn 15
    void* const pSent = g_fnCT_sent_141726c30(pThis);                   // insn 16-17 (rcx = this)
    *(void**)((uint8_t*)pThis + 0x30) = pSent;                   // insn 18
    *(uint8_t*)((uint8_t*)pSent + 0x1d) = 0x1;                  // insn 19
    *(void**)((uint8_t*)pSent + 0x8) = pSent;                    // insn 20-21
    *(void**)pSent = pSent;                                      // insn 22-23
    *(void**)((uint8_t*)pSent + 0x10) = pSent;                   // insn 24-25
    *(void**)((uint8_t*)pThis + 0x38) = (void*)0x0;              // insn 26
    return pThis;                                                // insn 27
}
inline void* SynContainerCtor_141730e00(void* pThis) {   // 0x141730e00
    void* pSmall = g_fnCT_small_1417f3166(0x8);                        // insn 6-7
    if (pSmall == nullptr)                                       // both paths yield a null here
        pSmall = nullptr;                                        //   (xor eax,eax)
    *(void**)pThis = pSmall;                                     // insn 15
    void* const pSent = g_fnCT_sent_141726c90(pThis);                   // insn 16-17 (rcx = this)
    *(void**)((uint8_t*)pThis + 0x30) = pSent;                   // insn 18
    *(uint8_t*)((uint8_t*)pSent + 0x29) = 0x1;                  // insn 19
    *(void**)((uint8_t*)pSent + 0x8) = pSent;                    // insn 20-21
    *(void**)pSent = pSent;                                      // insn 22-23
    *(void**)((uint8_t*)pSent + 0x10) = pSent;                   // insn 24-25
    *(void**)((uint8_t*)pThis + 0x38) = (void*)0x0;              // insn 26
    return pThis;                                                // insn 27
}
inline void* SynContainerCtor_141730ef0(void* pThis) {   // 0x141730ef0
    void* pSmall = g_fnCT_small_1417f3166(0x8);                        // insn 6-7
    if (pSmall == nullptr)                                       // both paths yield a null here
        pSmall = nullptr;                                        //   (xor eax,eax)
    *(void**)pThis = pSmall;                                     // insn 15
    void* const pSent = g_fnCT_sent_141726cf0(pThis);                   // insn 16-17 (rcx = this)
    *(void**)((uint8_t*)pThis + 0x30) = pSent;                   // insn 18
    *(uint8_t*)((uint8_t*)pSent + 0x51) = 0x1;                  // insn 19
    *(void**)((uint8_t*)pSent + 0x8) = pSent;                    // insn 20-21
    *(void**)pSent = pSent;                                      // insn 22-23
    *(void**)((uint8_t*)pSent + 0x10) = pSent;                   // insn 24-25
    *(void**)((uint8_t*)pThis + 0x38) = (void*)0x0;              // insn 26
    return pThis;                                                // insn 27
}
inline void* SynContainerCtor_141730f70(void* pThis) {   // 0x141730f70
    void* pSmall = g_fnCT_small_1417f3166(0x8);                        // insn 6-7
    if (pSmall == nullptr)                                       // both paths yield a null here
        pSmall = nullptr;                                        //   (xor eax,eax)
    *(void**)pThis = pSmall;                                     // insn 15
    void* const pSent = g_fnCT_sent_141726d50(pThis);                   // insn 16-17 (rcx = this)
    *(void**)((uint8_t*)pThis + 0x30) = pSent;                   // insn 18
    *(uint8_t*)((uint8_t*)pSent + 0x49) = 0x1;                  // insn 19
    *(void**)((uint8_t*)pSent + 0x8) = pSent;                    // insn 20-21
    *(void**)pSent = pSent;                                      // insn 22-23
    *(void**)((uint8_t*)pSent + 0x10) = pSent;                   // insn 24-25
    *(void**)((uint8_t*)pThis + 0x38) = (void*)0x0;              // insn 26
    return pThis;                                                // insn 27
}
inline void* SynContainerCtor_141731060(void* pThis) {   // 0x141731060
    void* pSmall = g_fnCT_small_1417f3166(0x8);                        // insn 6-7
    if (pSmall == nullptr)                                       // both paths yield a null here
        pSmall = nullptr;                                        //   (xor eax,eax)
    *(void**)pThis = pSmall;                                     // insn 15
    void* const pSent = g_fnCT_sent_141726db0(pThis);                   // insn 16-17 (rcx = this)
    *(void**)((uint8_t*)pThis + 0x30) = pSent;                   // insn 18
    *(uint8_t*)((uint8_t*)pSent + 0x1d) = 0x1;                  // insn 19
    *(void**)((uint8_t*)pSent + 0x8) = pSent;                    // insn 20-21
    *(void**)pSent = pSent;                                      // insn 22-23
    *(void**)((uint8_t*)pSent + 0x10) = pSent;                   // insn 24-25
    *(void**)((uint8_t*)pThis + 0x38) = (void*)0x0;              // insn 26
    return pThis;                                                // insn 27
}
inline void* SynContainerCtor_141731150(void* pThis) {   // 0x141731150
    void* pSmall = g_fnCT_small_1417f3166(0x8);                        // insn 6-7
    if (pSmall == nullptr)                                       // both paths yield a null here
        pSmall = nullptr;                                        //   (xor eax,eax)
    *(void**)pThis = pSmall;                                     // insn 15
    void* const pSent = g_fnCT_sent_141726ec0(pThis);                   // insn 16-17 (rcx = this)
    *(void**)((uint8_t*)pThis + 0x30) = pSent;                   // insn 18
    *(uint8_t*)((uint8_t*)pSent + 0x1b) = 0x1;                  // insn 19
    *(void**)((uint8_t*)pSent + 0x8) = pSent;                    // insn 20-21
    *(void**)pSent = pSent;                                      // insn 22-23
    *(void**)((uint8_t*)pSent + 0x10) = pSent;                   // insn 24-25
    *(void**)((uint8_t*)pThis + 0x38) = (void*)0x0;              // insn 26
    return pThis;                                                // insn 27
}
inline void* SynContainerCtor_141732180(void* pThis) {   // 0x141732180
    void* pSmall = g_fnCT_small_1417f3166(0x8);                        // insn 5-6
    if (pSmall == nullptr)                                       // both paths yield a null here
        pSmall = nullptr;                                        //   (xor eax,eax)
    *(void**)pThis = pSmall;                                     // insn 14
    void* const pSent = g_fnCT_sent_141726ec0(pThis);                   // insn 15-16 (rcx = this)
    *(void**)((uint8_t*)pThis + 0x30) = pSent;                   // insn 17
    *(uint8_t*)((uint8_t*)pSent + 0x1b) = 0x1;                  // insn 18
    *(void**)((uint8_t*)pSent + 0x8) = pSent;                    // insn 19-20
    *(void**)pSent = pSent;                                      // insn 21-22
    *(void**)((uint8_t*)pSent + 0x10) = pSent;                   // insn 23-24
    *(void**)((uint8_t*)pThis + 0x38) = (void*)0x0;              // insn 25
    return pThis;                                                // insn 26
}
inline void* SynContainerCtor_141733570(void* pThis) {   // 0x141733570
    void* pSmall = g_fnCT_small_1417f3166(0x8);                        // insn 5-6
    if (pSmall == nullptr)                                       // both paths yield a null here
        pSmall = nullptr;                                        //   (xor eax,eax)
    *(void**)pThis = pSmall;                                     // insn 14
    void* const pSent = g_fnCT_sent_141726c90(pThis);                   // insn 15-16 (rcx = this)
    *(void**)((uint8_t*)pThis + 0x30) = pSent;                   // insn 17
    *(uint8_t*)((uint8_t*)pSent + 0x29) = 0x1;                  // insn 18
    *(void**)((uint8_t*)pSent + 0x8) = pSent;                    // insn 19-20
    *(void**)pSent = pSent;                                      // insn 21-22
    *(void**)((uint8_t*)pSent + 0x10) = pSent;                   // insn 23-24
    *(void**)((uint8_t*)pThis + 0x38) = (void*)0x0;              // insn 25
    return pThis;                                                // insn 26
}
inline void* SynContainerCtor_141733630(void* pThis) {   // 0x141733630
    void* pSmall = g_fnCT_small_1417f3166(0x8);                        // insn 5-6
    if (pSmall == nullptr)                                       // both paths yield a null here
        pSmall = nullptr;                                        //   (xor eax,eax)
    *(void**)pThis = pSmall;                                     // insn 14
    void* const pSent = g_fnCT_sent_141726d50(pThis);                   // insn 15-16 (rcx = this)
    *(void**)((uint8_t*)pThis + 0x30) = pSent;                   // insn 17
    *(uint8_t*)((uint8_t*)pSent + 0x49) = 0x1;                  // insn 18
    *(void**)((uint8_t*)pSent + 0x8) = pSent;                    // insn 19-20
    *(void**)pSent = pSent;                                      // insn 21-22
    *(void**)((uint8_t*)pSent + 0x10) = pSent;                   // insn 23-24
    *(void**)((uint8_t*)pThis + 0x38) = (void*)0x0;              // insn 25
    return pThis;                                                // insn 26
}
inline void* SynContainerCtor_1417336b0(void* pThis) {   // 0x1417336b0
    void* pSmall = g_fnCT_small_1417f3166(0x8);                        // insn 5-6
    if (pSmall == nullptr)                                       // both paths yield a null here
        pSmall = nullptr;                                        //   (xor eax,eax)
    *(void**)pThis = pSmall;                                     // insn 14
    void* const pSent = g_fnCT_sent_141726db0(pThis);                   // insn 15-16 (rcx = this)
    *(void**)((uint8_t*)pThis + 0x30) = pSent;                   // insn 17
    *(uint8_t*)((uint8_t*)pSent + 0x1d) = 0x1;                  // insn 18
    *(void**)((uint8_t*)pSent + 0x8) = pSent;                    // insn 19-20
    *(void**)pSent = pSent;                                      // insn 21-22
    *(void**)((uint8_t*)pSent + 0x10) = pSent;                   // insn 23-24
    *(void**)((uint8_t*)pThis + 0x38) = (void*)0x0;              // insn 25
    return pThis;                                                // insn 26
}
inline void* SynContainerCtor_141735800(void* pThis) {   // 0x141735800
    void* pSmall = g_fnCT_small_1417f3166(0x8);                        // insn 5-6
    if (pSmall == nullptr)                                       // both paths yield a null here
        pSmall = nullptr;                                        //   (xor eax,eax)
    *(void**)pThis = pSmall;                                     // insn 14
    void* const pSent = g_fnCT_sent_141726cf0(pThis);                   // insn 15-16 (rcx = this)
    *(void**)((uint8_t*)pThis + 0x30) = pSent;                   // insn 17
    *(uint8_t*)((uint8_t*)pSent + 0x51) = 0x1;                  // insn 18
    *(void**)((uint8_t*)pSent + 0x8) = pSent;                    // insn 19-20
    *(void**)pSent = pSent;                                      // insn 21-22
    *(void**)((uint8_t*)pSent + 0x10) = pSent;                   // insn 23-24
    *(void**)((uint8_t*)pThis + 0x38) = (void*)0x0;              // insn 25
    return pThis;                                                // insn 26
}
inline void* SynContainerCtor_14173dd50(void* pThis) {   // 0x14173dd50
    void* pSmall = g_fnCT_small_1417f3166(0x8);                        // insn 6-7
    if (pSmall == nullptr)                                       // both paths yield a null here
        pSmall = nullptr;                                        //   (xor eax,eax)
    *(void**)pThis = pSmall;                                     // insn 15
    void* const pSent = g_fnCT_sent_14173bc00(pThis);                   // insn 16-17 (rcx = this)
    *(void**)((uint8_t*)pThis + 0x30) = pSent;                   // insn 18
    *(uint8_t*)((uint8_t*)pSent + 0x61) = 0x1;                  // insn 19
    *(void**)((uint8_t*)pSent + 0x8) = pSent;                    // insn 20-21
    *(void**)pSent = pSent;                                      // insn 22-23
    *(void**)((uint8_t*)pSent + 0x10) = pSent;                   // insn 24-25
    *(void**)((uint8_t*)pThis + 0x38) = (void*)0x0;              // insn 26
    return pThis;                                                // insn 27
}
inline void* SynContainerCtor_14173ddd0(void* pThis) {   // 0x14173ddd0
    void* pSmall = g_fnCT_small_1417f3166(0x8);                        // insn 6-7
    if (pSmall == nullptr)                                       // both paths yield a null here
        pSmall = nullptr;                                        //   (xor eax,eax)
    *(void**)pThis = pSmall;                                     // insn 15
    void* const pSent = g_fnCT_sent_14173bcb0(pThis);                   // insn 16-17 (rcx = this)
    *(void**)((uint8_t*)pThis + 0x30) = pSent;                   // insn 18
    *(uint8_t*)((uint8_t*)pSent + 0x21) = 0x1;                  // insn 19
    *(void**)((uint8_t*)pSent + 0x8) = pSent;                    // insn 20-21
    *(void**)pSent = pSent;                                      // insn 22-23
    *(void**)((uint8_t*)pSent + 0x10) = pSent;                   // insn 24-25
    *(void**)((uint8_t*)pThis + 0x38) = (void*)0x0;              // insn 26
    return pThis;                                                // insn 27
}
inline void* SynContainerCtor_14173df20(void* pThis) {   // 0x14173df20
    void* pSmall = g_fnCT_small_1417f3166(0x8);                        // insn 5-6
    if (pSmall == nullptr)                                       // both paths yield a null here
        pSmall = nullptr;                                        //   (xor eax,eax)
    *(void**)pThis = pSmall;                                     // insn 14
    void* const pSent = g_fnCT_sent_14173bcb0(pThis);                   // insn 15-16 (rcx = this)
    *(void**)((uint8_t*)pThis + 0x30) = pSent;                   // insn 17
    *(uint8_t*)((uint8_t*)pSent + 0x21) = 0x1;                  // insn 18
    *(void**)((uint8_t*)pSent + 0x8) = pSent;                    // insn 19-20
    *(void**)pSent = pSent;                                      // insn 21-22
    *(void**)((uint8_t*)pSent + 0x10) = pSent;                   // insn 23-24
    *(void**)((uint8_t*)pThis + 0x38) = (void*)0x0;              // insn 25
    return pThis;                                                // insn 26
}
inline void* SynContainerCtor_14173f600(void* pThis) {   // 0x14173f600
    void* pSmall = g_fnCT_small_1417f3166(0x8);                        // insn 5-6
    if (pSmall == nullptr)                                       // both paths yield a null here
        pSmall = nullptr;                                        //   (xor eax,eax)
    *(void**)pThis = pSmall;                                     // insn 14
    void* const pSent = g_fnCT_sent_14173bc00(pThis);                   // insn 15-16 (rcx = this)
    *(void**)((uint8_t*)pThis + 0x30) = pSent;                   // insn 17
    *(uint8_t*)((uint8_t*)pSent + 0x61) = 0x1;                  // insn 18
    *(void**)((uint8_t*)pSent + 0x8) = pSent;                    // insn 19-20
    *(void**)pSent = pSent;                                      // insn 21-22
    *(void**)((uint8_t*)pSent + 0x10) = pSent;                   // insn 23-24
    *(void**)((uint8_t*)pThis + 0x38) = (void*)0x0;              // insn 25
    return pThis;                                                // insn 26
}
inline void* SynContainerCtor_14174c430(void* pThis) {   // 0x14174c430
    void* pSmall = g_fnCT_small_1417f3166(0x8);                        // insn 6-7
    if (pSmall == nullptr)                                       // both paths yield a null here
        pSmall = nullptr;                                        //   (xor eax,eax)
    *(void**)pThis = pSmall;                                     // insn 15
    void* const pSent = g_fnCT_sent_141746a00(pThis);                   // insn 16-17 (rcx = this)
    *(void**)((uint8_t*)pThis + 0x30) = pSent;                   // insn 18
    *(uint8_t*)((uint8_t*)pSent + 0x3d) = 0x1;                  // insn 19
    *(void**)((uint8_t*)pSent + 0x8) = pSent;                    // insn 20-21
    *(void**)pSent = pSent;                                      // insn 22-23
    *(void**)((uint8_t*)pSent + 0x10) = pSent;                   // insn 24-25
    *(void**)((uint8_t*)pThis + 0x38) = (void*)0x0;              // insn 26
    return pThis;                                                // insn 27
}
inline void* SynContainerCtor_14174c4b0(void* pThis) {   // 0x14174c4b0
    void* pSmall = g_fnCT_small_1417f3166(0x8);                        // insn 6-7
    if (pSmall == nullptr)                                       // both paths yield a null here
        pSmall = nullptr;                                        //   (xor eax,eax)
    *(void**)pThis = pSmall;                                     // insn 15
    void* const pSent = g_fnCT_sent_141746a60(pThis);                   // insn 16-17 (rcx = this)
    *(void**)((uint8_t*)pThis + 0x30) = pSent;                   // insn 18
    *(uint8_t*)((uint8_t*)pSent + 0x29) = 0x1;                  // insn 19
    *(void**)((uint8_t*)pSent + 0x8) = pSent;                    // insn 20-21
    *(void**)pSent = pSent;                                      // insn 22-23
    *(void**)((uint8_t*)pSent + 0x10) = pSent;                   // insn 24-25
    *(void**)((uint8_t*)pThis + 0x38) = (void*)0x0;              // insn 26
    return pThis;                                                // insn 27
}
inline void* SynContainerCtor_14174cc70(void* pThis) {   // 0x14174cc70
    void* pSmall = g_fnCT_small_1417f3166(0x8);                        // insn 5-6
    if (pSmall == nullptr)                                       // both paths yield a null here
        pSmall = nullptr;                                        //   (xor eax,eax)
    *(void**)pThis = pSmall;                                     // insn 14
    void* const pSent = g_fnCT_sent_141746a00(pThis);                   // insn 15-16 (rcx = this)
    *(void**)((uint8_t*)pThis + 0x30) = pSent;                   // insn 17
    *(uint8_t*)((uint8_t*)pSent + 0x3d) = 0x1;                  // insn 18
    *(void**)((uint8_t*)pSent + 0x8) = pSent;                    // insn 19-20
    *(void**)pSent = pSent;                                      // insn 21-22
    *(void**)((uint8_t*)pSent + 0x10) = pSent;                   // insn 23-24
    *(void**)((uint8_t*)pThis + 0x38) = (void*)0x0;              // insn 25
    return pThis;                                                // insn 26
}
inline void* SynContainerCtor_14174d6b0(void* pThis) {   // 0x14174d6b0
    void* pSmall = g_fnCT_small_1417f3166(0x8);                        // insn 5-6
    if (pSmall == nullptr)                                       // both paths yield a null here
        pSmall = nullptr;                                        //   (xor eax,eax)
    *(void**)pThis = pSmall;                                     // insn 14
    void* const pSent = g_fnCT_sent_141746a60(pThis);                   // insn 15-16 (rcx = this)
    *(void**)((uint8_t*)pThis + 0x30) = pSent;                   // insn 17
    *(uint8_t*)((uint8_t*)pSent + 0x29) = 0x1;                  // insn 18
    *(void**)((uint8_t*)pSent + 0x8) = pSent;                    // insn 19-20
    *(void**)pSent = pSent;                                      // insn 21-22
    *(void**)((uint8_t*)pSent + 0x10) = pSent;                   // insn 23-24
    *(void**)((uint8_t*)pThis + 0x38) = (void*)0x0;              // insn 25
    return pThis;                                                // insn 26
}
inline void* SynContainerCtor_141769b70(void* pThis) {   // 0x141769b70
    void* pSmall = g_fnCT_small_1417f3166(0x8);                        // insn 6-7
    if (pSmall == nullptr)                                       // both paths yield a null here
        pSmall = nullptr;                                        //   (xor eax,eax)
    *(void**)pThis = pSmall;                                     // insn 15
    void* const pSent = g_fnCT_sent_141756200(pThis);                   // insn 16-17 (rcx = this)
    *(void**)((uint8_t*)pThis + 0x30) = pSent;                   // insn 18
    *(uint8_t*)((uint8_t*)pSent + 0x29) = 0x1;                  // insn 19
    *(void**)((uint8_t*)pSent + 0x8) = pSent;                    // insn 20-21
    *(void**)pSent = pSent;                                      // insn 22-23
    *(void**)((uint8_t*)pSent + 0x10) = pSent;                   // insn 24-25
    *(void**)((uint8_t*)pThis + 0x38) = (void*)0x0;              // insn 26
    return pThis;                                                // insn 27
}
inline void* SynContainerCtor_141769d20(void* pThis) {   // 0x141769d20
    void* pSmall = g_fnCT_small_1417f3166(0x8);                        // insn 6-7
    if (pSmall == nullptr)                                       // both paths yield a null here
        pSmall = nullptr;                                        //   (xor eax,eax)
    *(void**)pThis = pSmall;                                     // insn 15
    void* const pSent = g_fnCT_sent_141756260(pThis);                   // insn 16-17 (rcx = this)
    *(void**)((uint8_t*)pThis + 0x30) = pSent;                   // insn 18
    *(uint8_t*)((uint8_t*)pSent + 0x59) = 0x1;                  // insn 19
    *(void**)((uint8_t*)pSent + 0x8) = pSent;                    // insn 20-21
    *(void**)pSent = pSent;                                      // insn 22-23
    *(void**)((uint8_t*)pSent + 0x10) = pSent;                   // insn 24-25
    *(void**)((uint8_t*)pThis + 0x38) = (void*)0x0;              // insn 26
    return pThis;                                                // insn 27
}
inline void* SynContainerCtor_141769da0(void* pThis) {   // 0x141769da0
    void* pSmall = g_fnCT_small_1417f3166(0x8);                        // insn 6-7
    if (pSmall == nullptr)                                       // both paths yield a null here
        pSmall = nullptr;                                        //   (xor eax,eax)
    *(void**)pThis = pSmall;                                     // insn 15
    void* const pSent = g_fnCT_sent_1417562c0(pThis);                   // insn 16-17 (rcx = this)
    *(void**)((uint8_t*)pThis + 0x30) = pSent;                   // insn 18
    *(uint8_t*)((uint8_t*)pSent + 0x29) = 0x1;                  // insn 19
    *(void**)((uint8_t*)pSent + 0x8) = pSent;                    // insn 20-21
    *(void**)pSent = pSent;                                      // insn 22-23
    *(void**)((uint8_t*)pSent + 0x10) = pSent;                   // insn 24-25
    *(void**)((uint8_t*)pThis + 0x38) = (void*)0x0;              // insn 26
    return pThis;                                                // insn 27
}
inline void* SynContainerCtor_141769e20(void* pThis) {   // 0x141769e20
    void* pSmall = g_fnCT_small_1417f3166(0x8);                        // insn 6-7
    if (pSmall == nullptr)                                       // both paths yield a null here
        pSmall = nullptr;                                        //   (xor eax,eax)
    *(void**)pThis = pSmall;                                     // insn 15
    void* const pSent = g_fnCT_sent_1417563b0(pThis);                   // insn 16-17 (rcx = this)
    *(void**)((uint8_t*)pThis + 0x30) = pSent;                   // insn 18
    *(uint8_t*)((uint8_t*)pSent + 0x61) = 0x1;                  // insn 19
    *(void**)((uint8_t*)pSent + 0x8) = pSent;                    // insn 20-21
    *(void**)pSent = pSent;                                      // insn 22-23
    *(void**)((uint8_t*)pSent + 0x10) = pSent;                   // insn 24-25
    *(void**)((uint8_t*)pThis + 0x38) = (void*)0x0;              // insn 26
    return pThis;                                                // insn 27
}
inline void* SynContainerCtor_141769ea0(void* pThis) {   // 0x141769ea0
    void* pSmall = g_fnCT_small_1417f3166(0x8);                        // insn 6-7
    if (pSmall == nullptr)                                       // both paths yield a null here
        pSmall = nullptr;                                        //   (xor eax,eax)
    *(void**)pThis = pSmall;                                     // insn 15
    void* const pSent = g_fnCT_sent_141756410(pThis);                   // insn 16-17 (rcx = this)
    *(void**)((uint8_t*)pThis + 0x30) = pSent;                   // insn 18
    *(uint8_t*)((uint8_t*)pSent + 0x29) = 0x1;                  // insn 19
    *(void**)((uint8_t*)pSent + 0x8) = pSent;                    // insn 20-21
    *(void**)pSent = pSent;                                      // insn 22-23
    *(void**)((uint8_t*)pSent + 0x10) = pSent;                   // insn 24-25
    *(void**)((uint8_t*)pThis + 0x38) = (void*)0x0;              // insn 26
    return pThis;                                                // insn 27
}
inline void* SynContainerCtor_141769f20(void* pThis) {   // 0x141769f20
    void* pSmall = g_fnCT_small_1417f3166(0x8);                        // insn 6-7
    if (pSmall == nullptr)                                       // both paths yield a null here
        pSmall = nullptr;                                        //   (xor eax,eax)
    *(void**)pThis = pSmall;                                     // insn 15
    void* const pSent = g_fnCT_sent_141756470(pThis);                   // insn 16-17 (rcx = this)
    *(void**)((uint8_t*)pThis + 0x30) = pSent;                   // insn 18
    *(uint8_t*)((uint8_t*)pSent + 0x61) = 0x1;                  // insn 19
    *(void**)((uint8_t*)pSent + 0x8) = pSent;                    // insn 20-21
    *(void**)pSent = pSent;                                      // insn 22-23
    *(void**)((uint8_t*)pSent + 0x10) = pSent;                   // insn 24-25
    *(void**)((uint8_t*)pThis + 0x38) = (void*)0x0;              // insn 26
    return pThis;                                                // insn 27
}
inline void* SynContainerCtor_141769fa0(void* pThis) {   // 0x141769fa0
    void* pSmall = g_fnCT_small_1417f3166(0x8);                        // insn 6-7
    if (pSmall == nullptr)                                       // both paths yield a null here
        pSmall = nullptr;                                        //   (xor eax,eax)
    *(void**)pThis = pSmall;                                     // insn 15
    void* const pSent = g_fnCT_sent_1417564d0(pThis);                   // insn 16-17 (rcx = this)
    *(void**)((uint8_t*)pThis + 0x30) = pSent;                   // insn 18
    *(uint8_t*)((uint8_t*)pSent + 0x29) = 0x1;                  // insn 19
    *(void**)((uint8_t*)pSent + 0x8) = pSent;                    // insn 20-21
    *(void**)pSent = pSent;                                      // insn 22-23
    *(void**)((uint8_t*)pSent + 0x10) = pSent;                   // insn 24-25
    *(void**)((uint8_t*)pThis + 0x38) = (void*)0x0;              // insn 26
    return pThis;                                                // insn 27
}
inline void* SynContainerCtor_14176a020(void* pThis) {   // 0x14176a020
    void* pSmall = g_fnCT_small_1417f3166(0x8);                        // insn 6-7
    if (pSmall == nullptr)                                       // both paths yield a null here
        pSmall = nullptr;                                        //   (xor eax,eax)
    *(void**)pThis = pSmall;                                     // insn 15
    void* const pSent = g_fnCT_sent_1417565b0(pThis);                   // insn 16-17 (rcx = this)
    *(void**)((uint8_t*)pThis + 0x30) = pSent;                   // insn 18
    *(uint8_t*)((uint8_t*)pSent + 0x69) = 0x1;                  // insn 19
    *(void**)((uint8_t*)pSent + 0x8) = pSent;                    // insn 20-21
    *(void**)pSent = pSent;                                      // insn 22-23
    *(void**)((uint8_t*)pSent + 0x10) = pSent;                   // insn 24-25
    *(void**)((uint8_t*)pThis + 0x38) = (void*)0x0;              // insn 26
    return pThis;                                                // insn 27
}
inline void* SynContainerCtor_14176a0a0(void* pThis) {   // 0x14176a0a0
    void* pSmall = g_fnCT_small_1417f3166(0x8);                        // insn 6-7
    if (pSmall == nullptr)                                       // both paths yield a null here
        pSmall = nullptr;                                        //   (xor eax,eax)
    *(void**)pThis = pSmall;                                     // insn 15
    void* const pSent = g_fnCT_sent_141756610(pThis);                   // insn 16-17 (rcx = this)
    *(void**)((uint8_t*)pThis + 0x30) = pSent;                   // insn 18
    *(uint8_t*)((uint8_t*)pSent + 0x29) = 0x1;                  // insn 19
    *(void**)((uint8_t*)pSent + 0x8) = pSent;                    // insn 20-21
    *(void**)pSent = pSent;                                      // insn 22-23
    *(void**)((uint8_t*)pSent + 0x10) = pSent;                   // insn 24-25
    *(void**)((uint8_t*)pThis + 0x38) = (void*)0x0;              // insn 26
    return pThis;                                                // insn 27
}
inline void* SynContainerCtor_14176a120(void* pThis) {   // 0x14176a120
    void* pSmall = g_fnCT_small_1417f3166(0x8);                        // insn 6-7
    if (pSmall == nullptr)                                       // both paths yield a null here
        pSmall = nullptr;                                        //   (xor eax,eax)
    *(void**)pThis = pSmall;                                     // insn 15
    void* const pSent = g_fnCT_sent_141755f90(pThis);                   // insn 16-17 (rcx = this)
    *(void**)((uint8_t*)pThis + 0x30) = pSent;                   // insn 18
    *(uint8_t*)((uint8_t*)pSent + 0x2d) = 0x1;                  // insn 19
    *(void**)((uint8_t*)pSent + 0x8) = pSent;                    // insn 20-21
    *(void**)pSent = pSent;                                      // insn 22-23
    *(void**)((uint8_t*)pSent + 0x10) = pSent;                   // insn 24-25
    *(void**)((uint8_t*)pThis + 0x38) = (void*)0x0;              // insn 26
    return pThis;                                                // insn 27
}
inline void* SynContainerCtor_14176dbc0(void* pThis) {   // 0x14176dbc0
    void* pSmall = g_fnCT_small_1417f3166(0x8);                        // insn 5-6
    if (pSmall == nullptr)                                       // both paths yield a null here
        pSmall = nullptr;                                        //   (xor eax,eax)
    *(void**)pThis = pSmall;                                     // insn 14
    void* const pSent = g_fnCT_sent_141756200(pThis);                   // insn 15-16 (rcx = this)
    *(void**)((uint8_t*)pThis + 0x30) = pSent;                   // insn 17
    *(uint8_t*)((uint8_t*)pSent + 0x29) = 0x1;                  // insn 18
    *(void**)((uint8_t*)pSent + 0x8) = pSent;                    // insn 19-20
    *(void**)pSent = pSent;                                      // insn 21-22
    *(void**)((uint8_t*)pSent + 0x10) = pSent;                   // insn 23-24
    *(void**)((uint8_t*)pThis + 0x38) = (void*)0x0;              // insn 25
    return pThis;                                                // insn 26
}
inline void* SynContainerCtor_14176dcf0(void* pThis) {   // 0x14176dcf0
    void* pSmall = g_fnCT_small_1417f3166(0x8);                        // insn 5-6
    if (pSmall == nullptr)                                       // both paths yield a null here
        pSmall = nullptr;                                        //   (xor eax,eax)
    *(void**)pThis = pSmall;                                     // insn 14
    void* const pSent = g_fnCT_sent_141756260(pThis);                   // insn 15-16 (rcx = this)
    *(void**)((uint8_t*)pThis + 0x30) = pSent;                   // insn 17
    *(uint8_t*)((uint8_t*)pSent + 0x59) = 0x1;                  // insn 18
    *(void**)((uint8_t*)pSent + 0x8) = pSent;                    // insn 19-20
    *(void**)pSent = pSent;                                      // insn 21-22
    *(void**)((uint8_t*)pSent + 0x10) = pSent;                   // insn 23-24
    *(void**)((uint8_t*)pThis + 0x38) = (void*)0x0;              // insn 25
    return pThis;                                                // insn 26
}
inline void* SynContainerCtor_14176dd70(void* pThis) {   // 0x14176dd70
    void* pSmall = g_fnCT_small_1417f3166(0x8);                        // insn 5-6
    if (pSmall == nullptr)                                       // both paths yield a null here
        pSmall = nullptr;                                        //   (xor eax,eax)
    *(void**)pThis = pSmall;                                     // insn 14
    void* const pSent = g_fnCT_sent_1417562c0(pThis);                   // insn 15-16 (rcx = this)
    *(void**)((uint8_t*)pThis + 0x30) = pSent;                   // insn 17
    *(uint8_t*)((uint8_t*)pSent + 0x29) = 0x1;                  // insn 18
    *(void**)((uint8_t*)pSent + 0x8) = pSent;                    // insn 19-20
    *(void**)pSent = pSent;                                      // insn 21-22
    *(void**)((uint8_t*)pSent + 0x10) = pSent;                   // insn 23-24
    *(void**)((uint8_t*)pThis + 0x38) = (void*)0x0;              // insn 25
    return pThis;                                                // insn 26
}
inline void* SynContainerCtor_14176ddf0(void* pThis) {   // 0x14176ddf0
    void* pSmall = g_fnCT_small_1417f3166(0x8);                        // insn 5-6
    if (pSmall == nullptr)                                       // both paths yield a null here
        pSmall = nullptr;                                        //   (xor eax,eax)
    *(void**)pThis = pSmall;                                     // insn 14
    void* const pSent = g_fnCT_sent_141756410(pThis);                   // insn 15-16 (rcx = this)
    *(void**)((uint8_t*)pThis + 0x30) = pSent;                   // insn 17
    *(uint8_t*)((uint8_t*)pSent + 0x29) = 0x1;                  // insn 18
    *(void**)((uint8_t*)pSent + 0x8) = pSent;                    // insn 19-20
    *(void**)pSent = pSent;                                      // insn 21-22
    *(void**)((uint8_t*)pSent + 0x10) = pSent;                   // insn 23-24
    *(void**)((uint8_t*)pThis + 0x38) = (void*)0x0;              // insn 25
    return pThis;                                                // insn 26
}
inline void* SynContainerCtor_14176de70(void* pThis) {   // 0x14176de70
    void* pSmall = g_fnCT_small_1417f3166(0x8);                        // insn 5-6
    if (pSmall == nullptr)                                       // both paths yield a null here
        pSmall = nullptr;                                        //   (xor eax,eax)
    *(void**)pThis = pSmall;                                     // insn 14
    void* const pSent = g_fnCT_sent_1417564d0(pThis);                   // insn 15-16 (rcx = this)
    *(void**)((uint8_t*)pThis + 0x30) = pSent;                   // insn 17
    *(uint8_t*)((uint8_t*)pSent + 0x29) = 0x1;                  // insn 18
    *(void**)((uint8_t*)pSent + 0x8) = pSent;                    // insn 19-20
    *(void**)pSent = pSent;                                      // insn 21-22
    *(void**)((uint8_t*)pSent + 0x10) = pSent;                   // insn 23-24
    *(void**)((uint8_t*)pThis + 0x38) = (void*)0x0;              // insn 25
    return pThis;                                                // insn 26
}
inline void* SynContainerCtor_14176def0(void* pThis) {   // 0x14176def0
    void* pSmall = g_fnCT_small_1417f3166(0x8);                        // insn 5-6
    if (pSmall == nullptr)                                       // both paths yield a null here
        pSmall = nullptr;                                        //   (xor eax,eax)
    *(void**)pThis = pSmall;                                     // insn 14
    void* const pSent = g_fnCT_sent_1417565b0(pThis);                   // insn 15-16 (rcx = this)
    *(void**)((uint8_t*)pThis + 0x30) = pSent;                   // insn 17
    *(uint8_t*)((uint8_t*)pSent + 0x69) = 0x1;                  // insn 18
    *(void**)((uint8_t*)pSent + 0x8) = pSent;                    // insn 19-20
    *(void**)pSent = pSent;                                      // insn 21-22
    *(void**)((uint8_t*)pSent + 0x10) = pSent;                   // insn 23-24
    *(void**)((uint8_t*)pThis + 0x38) = (void*)0x0;              // insn 25
    return pThis;                                                // insn 26
}
inline void* SynContainerCtor_14176df70(void* pThis) {   // 0x14176df70
    void* pSmall = g_fnCT_small_1417f3166(0x8);                        // insn 5-6
    if (pSmall == nullptr)                                       // both paths yield a null here
        pSmall = nullptr;                                        //   (xor eax,eax)
    *(void**)pThis = pSmall;                                     // insn 14
    void* const pSent = g_fnCT_sent_141756610(pThis);                   // insn 15-16 (rcx = this)
    *(void**)((uint8_t*)pThis + 0x30) = pSent;                   // insn 17
    *(uint8_t*)((uint8_t*)pSent + 0x29) = 0x1;                  // insn 18
    *(void**)((uint8_t*)pSent + 0x8) = pSent;                    // insn 19-20
    *(void**)pSent = pSent;                                      // insn 21-22
    *(void**)((uint8_t*)pSent + 0x10) = pSent;                   // insn 23-24
    *(void**)((uint8_t*)pThis + 0x38) = (void*)0x0;              // insn 25
    return pThis;                                                // insn 26
}
inline void* SynContainerCtor_14176f530(void* pThis) {   // 0x14176f530
    void* pSmall = g_fnCT_small_1417f3166(0x8);                        // insn 5-6
    if (pSmall == nullptr)                                       // both paths yield a null here
        pSmall = nullptr;                                        //   (xor eax,eax)
    *(void**)pThis = pSmall;                                     // insn 14
    void* const pSent = g_fnCT_sent_141755f90(pThis);                   // insn 15-16 (rcx = this)
    *(void**)((uint8_t*)pThis + 0x30) = pSent;                   // insn 17
    *(uint8_t*)((uint8_t*)pSent + 0x2d) = 0x1;                  // insn 18
    *(void**)((uint8_t*)pSent + 0x8) = pSent;                    // insn 19-20
    *(void**)pSent = pSent;                                      // insn 21-22
    *(void**)((uint8_t*)pSent + 0x10) = pSent;                   // insn 23-24
    *(void**)((uint8_t*)pThis + 0x38) = (void*)0x0;              // insn 25
    return pThis;                                                // insn 26
}
inline void* SynContainerCtor_141775750(void* pThis) {   // 0x141775750
    void* pSmall = g_fnCT_small_1417f3166(0x8);                        // insn 5-6
    if (pSmall == nullptr)                                       // both paths yield a null here
        pSmall = nullptr;                                        //   (xor eax,eax)
    *(void**)pThis = pSmall;                                     // insn 14
    void* const pSent = g_fnCT_sent_141756470(pThis);                   // insn 15-16 (rcx = this)
    *(void**)((uint8_t*)pThis + 0x30) = pSent;                   // insn 17
    *(uint8_t*)((uint8_t*)pSent + 0x61) = 0x1;                  // insn 18
    *(void**)((uint8_t*)pSent + 0x8) = pSent;                    // insn 19-20
    *(void**)pSent = pSent;                                      // insn 21-22
    *(void**)((uint8_t*)pSent + 0x10) = pSent;                   // insn 23-24
    *(void**)((uint8_t*)pThis + 0x38) = (void*)0x0;              // insn 25
    return pThis;                                                // insn 26
}
inline void* SynContainerCtor_141775ac0(void* pThis) {   // 0x141775ac0
    void* pSmall = g_fnCT_small_1417f3166(0x8);                        // insn 5-6
    if (pSmall == nullptr)                                       // both paths yield a null here
        pSmall = nullptr;                                        //   (xor eax,eax)
    *(void**)pThis = pSmall;                                     // insn 14
    void* const pSent = g_fnCT_sent_1417563b0(pThis);                   // insn 15-16 (rcx = this)
    *(void**)((uint8_t*)pThis + 0x30) = pSent;                   // insn 17
    *(uint8_t*)((uint8_t*)pSent + 0x61) = 0x1;                  // insn 18
    *(void**)((uint8_t*)pSent + 0x8) = pSent;                    // insn 19-20
    *(void**)pSent = pSent;                                      // insn 21-22
    *(void**)((uint8_t*)pSent + 0x10) = pSent;                   // insn 23-24
    *(void**)((uint8_t*)pThis + 0x38) = (void*)0x0;              // insn 25
    return pThis;                                                // insn 26
}
inline void* SynContainerCtor_141777e60(void* pThis) {   // 0x141777e60
    void* pSmall = g_fnCT_small_1417f3166(0x8);                        // insn 6-7
    if (pSmall == nullptr)                                       // both paths yield a null here
        pSmall = nullptr;                                        //   (xor eax,eax)
    *(void**)pThis = pSmall;                                     // insn 15
    void* const pSent = g_fnCT_sent_141776670(pThis);                   // insn 16-17 (rcx = this)
    *(void**)((uint8_t*)pThis + 0x30) = pSent;                   // insn 18
    *(uint8_t*)((uint8_t*)pSent + 0x39) = 0x1;                  // insn 19
    *(void**)((uint8_t*)pSent + 0x8) = pSent;                    // insn 20-21
    *(void**)pSent = pSent;                                      // insn 22-23
    *(void**)((uint8_t*)pSent + 0x10) = pSent;                   // insn 24-25
    *(void**)((uint8_t*)pThis + 0x38) = (void*)0x0;              // insn 26
    return pThis;                                                // insn 27
}
inline void* SynContainerCtor_141777f20(void* pThis) {   // 0x141777f20
    void* pSmall = g_fnCT_small_1417f3166(0x8);                        // insn 5-6
    if (pSmall == nullptr)                                       // both paths yield a null here
        pSmall = nullptr;                                        //   (xor eax,eax)
    *(void**)pThis = pSmall;                                     // insn 14
    void* const pSent = g_fnCT_sent_141776670(pThis);                   // insn 15-16 (rcx = this)
    *(void**)((uint8_t*)pThis + 0x30) = pSent;                   // insn 17
    *(uint8_t*)((uint8_t*)pSent + 0x39) = 0x1;                  // insn 18
    *(void**)((uint8_t*)pSent + 0x8) = pSent;                    // insn 19-20
    *(void**)pSent = pSent;                                      // insn 21-22
    *(void**)((uint8_t*)pSent + 0x10) = pSent;                   // insn 23-24
    *(void**)((uint8_t*)pThis + 0x38) = (void*)0x0;              // insn 25
    return pThis;                                                // insn 26
}
inline void* SynContainerCtor_14177c1b0(void* pThis) {   // 0x14177c1b0
    void* pSmall = g_fnCT_small_1417f3166(0x8);                        // insn 6-7
    if (pSmall == nullptr)                                       // both paths yield a null here
        pSmall = nullptr;                                        //   (xor eax,eax)
    *(void**)pThis = pSmall;                                     // insn 15
    void* const pSent = g_fnCT_sent_14177ace0(pThis);                   // insn 16-17 (rcx = this)
    *(void**)((uint8_t*)pThis + 0x30) = pSent;                   // insn 18
    *(uint8_t*)((uint8_t*)pSent + 0x29) = 0x1;                  // insn 19
    *(void**)((uint8_t*)pSent + 0x8) = pSent;                    // insn 20-21
    *(void**)pSent = pSent;                                      // insn 22-23
    *(void**)((uint8_t*)pSent + 0x10) = pSent;                   // insn 24-25
    *(void**)((uint8_t*)pThis + 0x38) = (void*)0x0;              // insn 26
    return pThis;                                                // insn 27
}
inline void* SynContainerCtor_14177c6c0(void* pThis) {   // 0x14177c6c0
    void* pSmall = g_fnCT_small_1417f3166(0x8);                        // insn 5-6
    if (pSmall == nullptr)                                       // both paths yield a null here
        pSmall = nullptr;                                        //   (xor eax,eax)
    *(void**)pThis = pSmall;                                     // insn 14
    void* const pSent = g_fnCT_sent_14177ace0(pThis);                   // insn 15-16 (rcx = this)
    *(void**)((uint8_t*)pThis + 0x30) = pSent;                   // insn 17
    *(uint8_t*)((uint8_t*)pSent + 0x29) = 0x1;                  // insn 18
    *(void**)((uint8_t*)pSent + 0x8) = pSent;                    // insn 19-20
    *(void**)pSent = pSent;                                      // insn 21-22
    *(void**)((uint8_t*)pSent + 0x10) = pSent;                   // insn 23-24
    *(void**)((uint8_t*)pThis + 0x38) = (void*)0x0;              // insn 25
    return pThis;                                                // insn 26
}
inline void* SynContainerCtor_14178d990(void* pThis) {   // 0x14178d990
    void* pSmall = g_fnCT_small_1417f3166(0x8);                        // insn 6-7
    if (pSmall == nullptr)                                       // both paths yield a null here
        pSmall = nullptr;                                        //   (xor eax,eax)
    *(void**)pThis = pSmall;                                     // insn 15
    void* const pSent = g_fnCT_sent_14178a6a0(pThis);                   // insn 16-17 (rcx = this)
    *(void**)((uint8_t*)pThis + 0x30) = pSent;                   // insn 18
    *(uint8_t*)((uint8_t*)pSent + 0x29) = 0x1;                  // insn 19
    *(void**)((uint8_t*)pSent + 0x8) = pSent;                    // insn 20-21
    *(void**)pSent = pSent;                                      // insn 22-23
    *(void**)((uint8_t*)pSent + 0x10) = pSent;                   // insn 24-25
    *(void**)((uint8_t*)pThis + 0x38) = (void*)0x0;              // insn 26
    return pThis;                                                // insn 27
}
inline void* SynContainerCtor_14178da10(void* pThis) {   // 0x14178da10
    void* pSmall = g_fnCT_small_1417f3166(0x8);                        // insn 6-7
    if (pSmall == nullptr)                                       // both paths yield a null here
        pSmall = nullptr;                                        //   (xor eax,eax)
    *(void**)pThis = pSmall;                                     // insn 15
    void* const pSent = g_fnCT_sent_14178a700(pThis);                   // insn 16-17 (rcx = this)
    *(void**)((uint8_t*)pThis + 0x30) = pSent;                   // insn 18
    *(uint8_t*)((uint8_t*)pSent + 0x49) = 0x1;                  // insn 19
    *(void**)((uint8_t*)pSent + 0x8) = pSent;                    // insn 20-21
    *(void**)pSent = pSent;                                      // insn 22-23
    *(void**)((uint8_t*)pSent + 0x10) = pSent;                   // insn 24-25
    *(void**)((uint8_t*)pThis + 0x38) = (void*)0x0;              // insn 26
    return pThis;                                                // insn 27
}
inline void* SynContainerCtor_14178dc50(void* pThis) {   // 0x14178dc50
    void* pSmall = g_fnCT_small_1417f3166(0x8);                        // insn 5-6
    if (pSmall == nullptr)                                       // both paths yield a null here
        pSmall = nullptr;                                        //   (xor eax,eax)
    *(void**)pThis = pSmall;                                     // insn 14
    void* const pSent = g_fnCT_sent_14178a6a0(pThis);                   // insn 15-16 (rcx = this)
    *(void**)((uint8_t*)pThis + 0x30) = pSent;                   // insn 17
    *(uint8_t*)((uint8_t*)pSent + 0x29) = 0x1;                  // insn 18
    *(void**)((uint8_t*)pSent + 0x8) = pSent;                    // insn 19-20
    *(void**)pSent = pSent;                                      // insn 21-22
    *(void**)((uint8_t*)pSent + 0x10) = pSent;                   // insn 23-24
    *(void**)((uint8_t*)pThis + 0x38) = (void*)0x0;              // insn 25
    return pThis;                                                // insn 26
}
inline void* SynContainerCtor_14178dcd0(void* pThis) {   // 0x14178dcd0
    void* pSmall = g_fnCT_small_1417f3166(0x8);                        // insn 5-6
    if (pSmall == nullptr)                                       // both paths yield a null here
        pSmall = nullptr;                                        //   (xor eax,eax)
    *(void**)pThis = pSmall;                                     // insn 14
    void* const pSent = g_fnCT_sent_14178a700(pThis);                   // insn 15-16 (rcx = this)
    *(void**)((uint8_t*)pThis + 0x30) = pSent;                   // insn 17
    *(uint8_t*)((uint8_t*)pSent + 0x49) = 0x1;                  // insn 18
    *(void**)((uint8_t*)pSent + 0x8) = pSent;                    // insn 19-20
    *(void**)pSent = pSent;                                      // insn 21-22
    *(void**)((uint8_t*)pSent + 0x10) = pSent;                   // insn 23-24
    *(void**)((uint8_t*)pThis + 0x38) = (void*)0x0;              // insn 25
    return pThis;                                                // insn 26
}
inline void* SynContainerCtor_14179cc60(void* pThis) {   // 0x14179cc60
    void* pSmall = g_fnCT_small_1417f3166(0x8);                        // insn 6-7
    if (pSmall == nullptr)                                       // both paths yield a null here
        pSmall = nullptr;                                        //   (xor eax,eax)
    *(void**)pThis = pSmall;                                     // insn 15
    void* const pSent = g_fnCT_sent_1417935d0(pThis);                   // insn 16-17 (rcx = this)
    *(void**)((uint8_t*)pThis + 0x30) = pSent;                   // insn 18
    *(uint8_t*)((uint8_t*)pSent + 0x61) = 0x1;                  // insn 19
    *(void**)((uint8_t*)pSent + 0x8) = pSent;                    // insn 20-21
    *(void**)pSent = pSent;                                      // insn 22-23
    *(void**)((uint8_t*)pSent + 0x10) = pSent;                   // insn 24-25
    *(void**)((uint8_t*)pThis + 0x38) = (void*)0x0;              // insn 26
    return pThis;                                                // insn 27
}
inline void* SynContainerCtor_14179cce0(void* pThis) {   // 0x14179cce0
    void* pSmall = g_fnCT_small_1417f3166(0x8);                        // insn 6-7
    if (pSmall == nullptr)                                       // both paths yield a null here
        pSmall = nullptr;                                        //   (xor eax,eax)
    *(void**)pThis = pSmall;                                     // insn 15
    void* const pSent = g_fnCT_sent_141793680(pThis);                   // insn 16-17 (rcx = this)
    *(void**)((uint8_t*)pThis + 0x30) = pSent;                   // insn 18
    *(uint8_t*)((uint8_t*)pSent + 0x21) = 0x1;                  // insn 19
    *(void**)((uint8_t*)pSent + 0x8) = pSent;                    // insn 20-21
    *(void**)pSent = pSent;                                      // insn 22-23
    *(void**)((uint8_t*)pSent + 0x10) = pSent;                   // insn 24-25
    *(void**)((uint8_t*)pThis + 0x38) = (void*)0x0;              // insn 26
    return pThis;                                                // insn 27
}
inline void* SynContainerCtor_14179cd60(void* pThis) {   // 0x14179cd60
    void* pSmall = g_fnCT_small_1417f3166(0x8);                        // insn 6-7
    if (pSmall == nullptr)                                       // both paths yield a null here
        pSmall = nullptr;                                        //   (xor eax,eax)
    *(void**)pThis = pSmall;                                     // insn 15
    void* const pSent = g_fnCT_sent_141793760(pThis);                   // insn 16-17 (rcx = this)
    *(void**)((uint8_t*)pThis + 0x30) = pSent;                   // insn 18
    *(uint8_t*)((uint8_t*)pSent + 0x29) = 0x1;                  // insn 19
    *(void**)((uint8_t*)pSent + 0x8) = pSent;                    // insn 20-21
    *(void**)pSent = pSent;                                      // insn 22-23
    *(void**)((uint8_t*)pSent + 0x10) = pSent;                   // insn 24-25
    *(void**)((uint8_t*)pThis + 0x38) = (void*)0x0;              // insn 26
    return pThis;                                                // insn 27
}
inline void* SynContainerCtor_1417a90d0(void* pThis) {   // 0x1417a90d0
    void* pSmall = g_fnCT_small_1417f3166(0x8);                        // insn 6-7
    if (pSmall == nullptr)                                       // both paths yield a null here
        pSmall = nullptr;                                        //   (xor eax,eax)
    *(void**)pThis = pSmall;                                     // insn 15
    void* const pSent = g_fnCT_sent_1417a76e0(pThis);                   // insn 16-17 (rcx = this)
    *(void**)((uint8_t*)pThis + 0x30) = pSent;                   // insn 18
    *(uint8_t*)((uint8_t*)pSent + 0x29) = 0x1;                  // insn 19
    *(void**)((uint8_t*)pSent + 0x8) = pSent;                    // insn 20-21
    *(void**)pSent = pSent;                                      // insn 22-23
    *(void**)((uint8_t*)pSent + 0x10) = pSent;                   // insn 24-25
    *(void**)((uint8_t*)pThis + 0x38) = (void*)0x0;              // insn 26
    return pThis;                                                // insn 27
}
inline void* SynContainerCtor_1417a93c0(void* pThis) {   // 0x1417a93c0
    void* pSmall = g_fnCT_small_1417f3166(0x8);                        // insn 5-6
    if (pSmall == nullptr)                                       // both paths yield a null here
        pSmall = nullptr;                                        //   (xor eax,eax)
    *(void**)pThis = pSmall;                                     // insn 14
    void* const pSent = g_fnCT_sent_1417a76e0(pThis);                   // insn 15-16 (rcx = this)
    *(void**)((uint8_t*)pThis + 0x30) = pSent;                   // insn 17
    *(uint8_t*)((uint8_t*)pSent + 0x29) = 0x1;                  // insn 18
    *(void**)((uint8_t*)pSent + 0x8) = pSent;                    // insn 19-20
    *(void**)pSent = pSent;                                      // insn 21-22
    *(void**)((uint8_t*)pSent + 0x10) = pSent;                   // insn 23-24
    *(void**)((uint8_t*)pThis + 0x38) = (void*)0x0;              // insn 25
    return pThis;                                                // insn 26
}
inline void* SynContainerCtor_1417cea20(void* pThis) {   // 0x1417cea20
    void* pSmall = g_fnCT_small_1417f3166(0x8);                        // insn 6-7
    if (pSmall == nullptr)                                       // both paths yield a null here
        pSmall = nullptr;                                        //   (xor eax,eax)
    *(void**)pThis = pSmall;                                     // insn 15
    void* const pSent = g_fnCT_sent_1417c8590(pThis);                   // insn 16-17 (rcx = this)
    *(void**)((uint8_t*)pThis + 0x30) = pSent;                   // insn 18
    *(uint8_t*)((uint8_t*)pSent + 0x21) = 0x1;                  // insn 19
    *(void**)((uint8_t*)pSent + 0x8) = pSent;                    // insn 20-21
    *(void**)pSent = pSent;                                      // insn 22-23
    *(void**)((uint8_t*)pSent + 0x10) = pSent;                   // insn 24-25
    *(void**)((uint8_t*)pThis + 0x38) = (void*)0x0;              // insn 26
    return pThis;                                                // insn 27
}

}  // namespace tq

#endif
