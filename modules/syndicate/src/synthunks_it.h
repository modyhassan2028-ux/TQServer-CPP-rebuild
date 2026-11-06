// synthunks_it.h — RAW Syndicate.dll v6159 · 28 ordered-tree iterator advances (family IT).
// Marker byte at a per-instance offset, always compared against zero; the climb and the left-spine
// descent keep the exact branch order of the original.
#ifndef TQ_SYN_THUNKS_IT_H
#define TQ_SYN_THUNKS_IT_H

#include <cstdint>

namespace tq {

extern int (*g_fnIT_1418233c0)(void* pArg);

inline void SynIterNext_141722ef0(void* pThis) {   // 0x141722ef0
    if (*(void**)pThis == nullptr)                                     // insn 2-5
        g_fnIT_1418233c0(pThis);
    void* pNode = *(void**)((uint8_t*)pThis + 0x8);                   // insn 6
    if (*(uint8_t*)((uint8_t*)pNode + 0x29) != 0) {                    // insn 7-8
        g_fnIT_1418233c0(pNode);                                              // insn 11 (tail)
        return;
    }
    void* pRight = *(void**)((uint8_t*)pNode + 0x10);                  // insn 12
    if (*(uint8_t*)((uint8_t*)pRight + 0x29) == 0) {                   // insn 13-14
        void* pChild = *(void**)pRight;                                // insn 15
        while (*(uint8_t*)((uint8_t*)pChild + 0x29) == 0) {             // insn 16,21-22
            pRight = pChild;                                           // insn 19
            pChild = *(void**)pChild;                                   // insn 20
        }
        *(void**)((uint8_t*)pThis + 0x8) = pRight;                     // insn 23
        return;
    }
    void* pUp = *(void**)((uint8_t*)pNode + 0x8);                     // insn 27
    while (*(uint8_t*)((uint8_t*)pUp + 0x29) == 0                    // insn 28-29,35-36
           && *(void**)((uint8_t*)pThis + 0x8) == *(void**)((uint8_t*)pUp + 0x10)) {  // insn 30-32
        *(void**)((uint8_t*)pThis + 0x8) = pUp;                        // insn 33
        pUp = *(void**)((uint8_t*)pUp + 0x8);                          // insn 34
    }
    *(void**)((uint8_t*)pThis + 0x8) = pUp;                           // insn 37
}
inline void SynIterNext_141722fc0(void* pThis) {   // 0x141722fc0
    if (*(void**)pThis == nullptr)                                     // insn 2-5
        g_fnIT_1418233c0(pThis);
    void* pNode = *(void**)((uint8_t*)pThis + 0x8);                   // insn 6
    if (*(uint8_t*)((uint8_t*)pNode + 0x1d) != 0) {                    // insn 7-8
        g_fnIT_1418233c0(pNode);                                              // insn 11 (tail)
        return;
    }
    void* pRight = *(void**)((uint8_t*)pNode + 0x10);                  // insn 12
    if (*(uint8_t*)((uint8_t*)pRight + 0x1d) == 0) {                   // insn 13-14
        void* pChild = *(void**)pRight;                                // insn 15
        while (*(uint8_t*)((uint8_t*)pChild + 0x1d) == 0) {             // insn 16,21-22
            pRight = pChild;                                           // insn 19
            pChild = *(void**)pChild;                                   // insn 20
        }
        *(void**)((uint8_t*)pThis + 0x8) = pRight;                     // insn 23
        return;
    }
    void* pUp = *(void**)((uint8_t*)pNode + 0x8);                     // insn 27
    while (*(uint8_t*)((uint8_t*)pUp + 0x1d) == 0                    // insn 28-29,35-36
           && *(void**)((uint8_t*)pThis + 0x8) == *(void**)((uint8_t*)pUp + 0x10)) {  // insn 30-32
        *(void**)((uint8_t*)pThis + 0x8) = pUp;                        // insn 33
        pUp = *(void**)((uint8_t*)pUp + 0x8);                          // insn 34
    }
    *(void**)((uint8_t*)pThis + 0x8) = pUp;                           // insn 37
}
inline void SynIterNext_141723090(void* pThis) {   // 0x141723090
    if (*(void**)pThis == nullptr)                                     // insn 2-5
        g_fnIT_1418233c0(pThis);
    void* pNode = *(void**)((uint8_t*)pThis + 0x8);                   // insn 6
    if (*(uint8_t*)((uint8_t*)pNode + 0x49) != 0) {                    // insn 7-8
        g_fnIT_1418233c0(pNode);                                              // insn 11 (tail)
        return;
    }
    void* pRight = *(void**)((uint8_t*)pNode + 0x10);                  // insn 12
    if (*(uint8_t*)((uint8_t*)pRight + 0x49) == 0) {                   // insn 13-14
        void* pChild = *(void**)pRight;                                // insn 15
        while (*(uint8_t*)((uint8_t*)pChild + 0x49) == 0) {             // insn 16,21-22
            pRight = pChild;                                           // insn 19
            pChild = *(void**)pChild;                                   // insn 20
        }
        *(void**)((uint8_t*)pThis + 0x8) = pRight;                     // insn 23
        return;
    }
    void* pUp = *(void**)((uint8_t*)pNode + 0x8);                     // insn 27
    while (*(uint8_t*)((uint8_t*)pUp + 0x49) == 0                    // insn 28-29,35-36
           && *(void**)((uint8_t*)pThis + 0x8) == *(void**)((uint8_t*)pUp + 0x10)) {  // insn 30-32
        *(void**)((uint8_t*)pThis + 0x8) = pUp;                        // insn 33
        pUp = *(void**)((uint8_t*)pUp + 0x8);                          // insn 34
    }
    *(void**)((uint8_t*)pThis + 0x8) = pUp;                           // insn 37
}
inline void SynIterNext_141723a50(void* pThis) {   // 0x141723a50
    if (*(void**)pThis == nullptr)                                     // insn 2-5
        g_fnIT_1418233c0(pThis);
    void* pNode = *(void**)((uint8_t*)pThis + 0x8);                   // insn 6
    if (*(uint8_t*)((uint8_t*)pNode + 0x1b) != 0) {                    // insn 7-8
        g_fnIT_1418233c0(pNode);                                              // insn 11 (tail)
        return;
    }
    void* pRight = *(void**)((uint8_t*)pNode + 0x10);                  // insn 12
    if (*(uint8_t*)((uint8_t*)pRight + 0x1b) == 0) {                   // insn 13-14
        void* pChild = *(void**)pRight;                                // insn 15
        while (*(uint8_t*)((uint8_t*)pChild + 0x1b) == 0) {             // insn 16,21-22
            pRight = pChild;                                           // insn 19
            pChild = *(void**)pChild;                                   // insn 20
        }
        *(void**)((uint8_t*)pThis + 0x8) = pRight;                     // insn 23
        return;
    }
    void* pUp = *(void**)((uint8_t*)pNode + 0x8);                     // insn 27
    while (*(uint8_t*)((uint8_t*)pUp + 0x1b) == 0                    // insn 28-29,35-36
           && *(void**)((uint8_t*)pThis + 0x8) == *(void**)((uint8_t*)pUp + 0x10)) {  // insn 30-32
        *(void**)((uint8_t*)pThis + 0x8) = pUp;                        // insn 33
        pUp = *(void**)((uint8_t*)pUp + 0x8);                          // insn 34
    }
    *(void**)((uint8_t*)pThis + 0x8) = pUp;                           // insn 37
}
inline void SynIterNext_141724ed0(void* pThis) {   // 0x141724ed0
    if (*(void**)pThis == nullptr)                                     // insn 2-5
        g_fnIT_1418233c0(pThis);
    void* pNode = *(void**)((uint8_t*)pThis + 0x8);                   // insn 6
    if (*(uint8_t*)((uint8_t*)pNode + 0x1d) != 0) {                    // insn 7-8
        g_fnIT_1418233c0(pNode);                                              // insn 11 (tail)
        return;
    }
    void* pRight = *(void**)((uint8_t*)pNode + 0x10);                  // insn 12
    if (*(uint8_t*)((uint8_t*)pRight + 0x1d) == 0) {                   // insn 13-14
        void* pChild = *(void**)pRight;                                // insn 15
        while (*(uint8_t*)((uint8_t*)pChild + 0x1d) == 0) {             // insn 16,21-22
            pRight = pChild;                                           // insn 19
            pChild = *(void**)pChild;                                   // insn 20
        }
        *(void**)((uint8_t*)pThis + 0x8) = pRight;                     // insn 23
        return;
    }
    void* pUp = *(void**)((uint8_t*)pNode + 0x8);                     // insn 27
    while (*(uint8_t*)((uint8_t*)pUp + 0x1d) == 0                    // insn 28-29,35-36
           && *(void**)((uint8_t*)pThis + 0x8) == *(void**)((uint8_t*)pUp + 0x10)) {  // insn 30-32
        *(void**)((uint8_t*)pThis + 0x8) = pUp;                        // insn 33
        pUp = *(void**)((uint8_t*)pUp + 0x8);                          // insn 34
    }
    *(void**)((uint8_t*)pThis + 0x8) = pUp;                           // insn 37
}
inline void SynIterNext_1417250d0(void* pThis) {   // 0x1417250d0
    if (*(void**)pThis == nullptr)                                     // insn 2-5
        g_fnIT_1418233c0(pThis);
    void* pNode = *(void**)((uint8_t*)pThis + 0x8);                   // insn 6
    if (*(uint8_t*)((uint8_t*)pNode + 0x51) != 0) {                    // insn 7-8
        g_fnIT_1418233c0(pNode);                                              // insn 11 (tail)
        return;
    }
    void* pRight = *(void**)((uint8_t*)pNode + 0x10);                  // insn 12
    if (*(uint8_t*)((uint8_t*)pRight + 0x51) == 0) {                   // insn 13-14
        void* pChild = *(void**)pRight;                                // insn 15
        while (*(uint8_t*)((uint8_t*)pChild + 0x51) == 0) {             // insn 16,21-22
            pRight = pChild;                                           // insn 19
            pChild = *(void**)pChild;                                   // insn 20
        }
        *(void**)((uint8_t*)pThis + 0x8) = pRight;                     // insn 23
        return;
    }
    void* pUp = *(void**)((uint8_t*)pNode + 0x8);                     // insn 27
    while (*(uint8_t*)((uint8_t*)pUp + 0x51) == 0                    // insn 28-29,35-36
           && *(void**)((uint8_t*)pThis + 0x8) == *(void**)((uint8_t*)pUp + 0x10)) {  // insn 30-32
        *(void**)((uint8_t*)pThis + 0x8) = pUp;                        // insn 33
        pUp = *(void**)((uint8_t*)pUp + 0x8);                          // insn 34
    }
    *(void**)((uint8_t*)pThis + 0x8) = pUp;                           // insn 37
}
inline void SynIterNext_14173b240(void* pThis) {   // 0x14173b240
    if (*(void**)pThis == nullptr)                                     // insn 2-5
        g_fnIT_1418233c0(pThis);
    void* pNode = *(void**)((uint8_t*)pThis + 0x8);                   // insn 6
    if (*(uint8_t*)((uint8_t*)pNode + 0x21) != 0) {                    // insn 7-8
        g_fnIT_1418233c0(pNode);                                              // insn 11 (tail)
        return;
    }
    void* pRight = *(void**)((uint8_t*)pNode + 0x10);                  // insn 12
    if (*(uint8_t*)((uint8_t*)pRight + 0x21) == 0) {                   // insn 13-14
        void* pChild = *(void**)pRight;                                // insn 15
        while (*(uint8_t*)((uint8_t*)pChild + 0x21) == 0) {             // insn 16,21-22
            pRight = pChild;                                           // insn 19
            pChild = *(void**)pChild;                                   // insn 20
        }
        *(void**)((uint8_t*)pThis + 0x8) = pRight;                     // insn 23
        return;
    }
    void* pUp = *(void**)((uint8_t*)pNode + 0x8);                     // insn 27
    while (*(uint8_t*)((uint8_t*)pUp + 0x21) == 0                    // insn 28-29,35-36
           && *(void**)((uint8_t*)pThis + 0x8) == *(void**)((uint8_t*)pUp + 0x10)) {  // insn 30-32
        *(void**)((uint8_t*)pThis + 0x8) = pUp;                        // insn 33
        pUp = *(void**)((uint8_t*)pUp + 0x8);                          // insn 34
    }
    *(void**)((uint8_t*)pThis + 0x8) = pUp;                           // insn 37
}
inline void SynIterNext_14173b6c0(void* pThis) {   // 0x14173b6c0
    if (*(void**)pThis == nullptr)                                     // insn 2-5
        g_fnIT_1418233c0(pThis);
    void* pNode = *(void**)((uint8_t*)pThis + 0x8);                   // insn 6
    if (*(uint8_t*)((uint8_t*)pNode + 0x61) != 0) {                    // insn 7-8
        g_fnIT_1418233c0(pNode);                                              // insn 11 (tail)
        return;
    }
    void* pRight = *(void**)((uint8_t*)pNode + 0x10);                  // insn 12
    if (*(uint8_t*)((uint8_t*)pRight + 0x61) == 0) {                   // insn 13-14
        void* pChild = *(void**)pRight;                                // insn 15
        while (*(uint8_t*)((uint8_t*)pChild + 0x61) == 0) {             // insn 16,21-22
            pRight = pChild;                                           // insn 19
            pChild = *(void**)pChild;                                   // insn 20
        }
        *(void**)((uint8_t*)pThis + 0x8) = pRight;                     // insn 23
        return;
    }
    void* pUp = *(void**)((uint8_t*)pNode + 0x8);                     // insn 27
    while (*(uint8_t*)((uint8_t*)pUp + 0x61) == 0                    // insn 28-29,35-36
           && *(void**)((uint8_t*)pThis + 0x8) == *(void**)((uint8_t*)pUp + 0x10)) {  // insn 30-32
        *(void**)((uint8_t*)pThis + 0x8) = pUp;                        // insn 33
        pUp = *(void**)((uint8_t*)pUp + 0x8);                          // insn 34
    }
    *(void**)((uint8_t*)pThis + 0x8) = pUp;                           // insn 37
}
inline void SynIterNext_1417447d0(void* pThis) {   // 0x1417447d0
    if (*(void**)pThis == nullptr)                                     // insn 2-5
        g_fnIT_1418233c0(pThis);
    void* pNode = *(void**)((uint8_t*)pThis + 0x8);                   // insn 6
    if (*(uint8_t*)((uint8_t*)pNode + 0x29) != 0) {                    // insn 7-8
        g_fnIT_1418233c0(pNode);                                              // insn 11 (tail)
        return;
    }
    void* pRight = *(void**)((uint8_t*)pNode + 0x10);                  // insn 12
    if (*(uint8_t*)((uint8_t*)pRight + 0x29) == 0) {                   // insn 13-14
        void* pChild = *(void**)pRight;                                // insn 15
        while (*(uint8_t*)((uint8_t*)pChild + 0x29) == 0) {             // insn 16,21-22
            pRight = pChild;                                           // insn 19
            pChild = *(void**)pChild;                                   // insn 20
        }
        *(void**)((uint8_t*)pThis + 0x8) = pRight;                     // insn 23
        return;
    }
    void* pUp = *(void**)((uint8_t*)pNode + 0x8);                     // insn 27
    while (*(uint8_t*)((uint8_t*)pUp + 0x29) == 0                    // insn 28-29,35-36
           && *(void**)((uint8_t*)pThis + 0x8) == *(void**)((uint8_t*)pUp + 0x10)) {  // insn 30-32
        *(void**)((uint8_t*)pThis + 0x8) = pUp;                        // insn 33
        pUp = *(void**)((uint8_t*)pUp + 0x8);                          // insn 34
    }
    *(void**)((uint8_t*)pThis + 0x8) = pUp;                           // insn 37
}
inline void SynIterNext_141744cb0(void* pThis) {   // 0x141744cb0
    if (*(void**)pThis == nullptr)                                     // insn 2-5
        g_fnIT_1418233c0(pThis);
    void* pNode = *(void**)((uint8_t*)pThis + 0x8);                   // insn 6
    if (*(uint8_t*)((uint8_t*)pNode + 0x3d) != 0) {                    // insn 7-8
        g_fnIT_1418233c0(pNode);                                              // insn 11 (tail)
        return;
    }
    void* pRight = *(void**)((uint8_t*)pNode + 0x10);                  // insn 12
    if (*(uint8_t*)((uint8_t*)pRight + 0x3d) == 0) {                   // insn 13-14
        void* pChild = *(void**)pRight;                                // insn 15
        while (*(uint8_t*)((uint8_t*)pChild + 0x3d) == 0) {             // insn 16,21-22
            pRight = pChild;                                           // insn 19
            pChild = *(void**)pChild;                                   // insn 20
        }
        *(void**)((uint8_t*)pThis + 0x8) = pRight;                     // insn 23
        return;
    }
    void* pUp = *(void**)((uint8_t*)pNode + 0x8);                     // insn 27
    while (*(uint8_t*)((uint8_t*)pUp + 0x3d) == 0                    // insn 28-29,35-36
           && *(void**)((uint8_t*)pThis + 0x8) == *(void**)((uint8_t*)pUp + 0x10)) {  // insn 30-32
        *(void**)((uint8_t*)pThis + 0x8) = pUp;                        // insn 33
        pUp = *(void**)((uint8_t*)pUp + 0x8);                          // insn 34
    }
    *(void**)((uint8_t*)pThis + 0x8) = pUp;                           // insn 37
}
inline void SynIterNext_141750670(void* pThis) {   // 0x141750670
    if (*(void**)pThis == nullptr)                                     // insn 2-5
        g_fnIT_1418233c0(pThis);
    void* pNode = *(void**)((uint8_t*)pThis + 0x8);                   // insn 6
    if (*(uint8_t*)((uint8_t*)pNode + 0x61) != 0) {                    // insn 7-8
        g_fnIT_1418233c0(pNode);                                              // insn 11 (tail)
        return;
    }
    void* pRight = *(void**)((uint8_t*)pNode + 0x10);                  // insn 12
    if (*(uint8_t*)((uint8_t*)pRight + 0x61) == 0) {                   // insn 13-14
        void* pChild = *(void**)pRight;                                // insn 15
        while (*(uint8_t*)((uint8_t*)pChild + 0x61) == 0) {             // insn 16,21-22
            pRight = pChild;                                           // insn 19
            pChild = *(void**)pChild;                                   // insn 20
        }
        *(void**)((uint8_t*)pThis + 0x8) = pRight;                     // insn 23
        return;
    }
    void* pUp = *(void**)((uint8_t*)pNode + 0x8);                     // insn 27
    while (*(uint8_t*)((uint8_t*)pUp + 0x61) == 0                    // insn 28-29,35-36
           && *(void**)((uint8_t*)pThis + 0x8) == *(void**)((uint8_t*)pUp + 0x10)) {  // insn 30-32
        *(void**)((uint8_t*)pThis + 0x8) = pUp;                        // insn 33
        pUp = *(void**)((uint8_t*)pUp + 0x8);                          // insn 34
    }
    *(void**)((uint8_t*)pThis + 0x8) = pUp;                           // insn 37
}
inline void SynIterNext_141750760(void* pThis) {   // 0x141750760
    if (*(void**)pThis == nullptr)                                     // insn 2-5
        g_fnIT_1418233c0(pThis);
    void* pNode = *(void**)((uint8_t*)pThis + 0x8);                   // insn 6
    if (*(uint8_t*)((uint8_t*)pNode + 0x2d) != 0) {                    // insn 7-8
        g_fnIT_1418233c0(pNode);                                              // insn 11 (tail)
        return;
    }
    void* pRight = *(void**)((uint8_t*)pNode + 0x10);                  // insn 12
    if (*(uint8_t*)((uint8_t*)pRight + 0x2d) == 0) {                   // insn 13-14
        void* pChild = *(void**)pRight;                                // insn 15
        while (*(uint8_t*)((uint8_t*)pChild + 0x2d) == 0) {             // insn 16,21-22
            pRight = pChild;                                           // insn 19
            pChild = *(void**)pChild;                                   // insn 20
        }
        *(void**)((uint8_t*)pThis + 0x8) = pRight;                     // insn 23
        return;
    }
    void* pUp = *(void**)((uint8_t*)pNode + 0x8);                     // insn 27
    while (*(uint8_t*)((uint8_t*)pUp + 0x2d) == 0                    // insn 28-29,35-36
           && *(void**)((uint8_t*)pThis + 0x8) == *(void**)((uint8_t*)pUp + 0x10)) {  // insn 30-32
        *(void**)((uint8_t*)pThis + 0x8) = pUp;                        // insn 33
        pUp = *(void**)((uint8_t*)pUp + 0x8);                          // insn 34
    }
    *(void**)((uint8_t*)pThis + 0x8) = pUp;                           // insn 37
}
inline void SynIterNext_1417512f0(void* pThis) {   // 0x1417512f0
    if (*(void**)pThis == nullptr)                                     // insn 2-5
        g_fnIT_1418233c0(pThis);
    void* pNode = *(void**)((uint8_t*)pThis + 0x8);                   // insn 6
    if (*(uint8_t*)((uint8_t*)pNode + 0x59) != 0) {                    // insn 7-8
        g_fnIT_1418233c0(pNode);                                              // insn 11 (tail)
        return;
    }
    void* pRight = *(void**)((uint8_t*)pNode + 0x10);                  // insn 12
    if (*(uint8_t*)((uint8_t*)pRight + 0x59) == 0) {                   // insn 13-14
        void* pChild = *(void**)pRight;                                // insn 15
        while (*(uint8_t*)((uint8_t*)pChild + 0x59) == 0) {             // insn 16,21-22
            pRight = pChild;                                           // insn 19
            pChild = *(void**)pChild;                                   // insn 20
        }
        *(void**)((uint8_t*)pThis + 0x8) = pRight;                     // insn 23
        return;
    }
    void* pUp = *(void**)((uint8_t*)pNode + 0x8);                     // insn 27
    while (*(uint8_t*)((uint8_t*)pUp + 0x59) == 0                    // insn 28-29,35-36
           && *(void**)((uint8_t*)pThis + 0x8) == *(void**)((uint8_t*)pUp + 0x10)) {  // insn 30-32
        *(void**)((uint8_t*)pThis + 0x8) = pUp;                        // insn 33
        pUp = *(void**)((uint8_t*)pUp + 0x8);                          // insn 34
    }
    *(void**)((uint8_t*)pThis + 0x8) = pUp;                           // insn 37
}
inline void SynIterNext_141751380(void* pThis) {   // 0x141751380
    if (*(void**)pThis == nullptr)                                     // insn 2-5
        g_fnIT_1418233c0(pThis);
    void* pNode = *(void**)((uint8_t*)pThis + 0x8);                   // insn 6
    if (*(uint8_t*)((uint8_t*)pNode + 0x69) != 0) {                    // insn 7-8
        g_fnIT_1418233c0(pNode);                                              // insn 11 (tail)
        return;
    }
    void* pRight = *(void**)((uint8_t*)pNode + 0x10);                  // insn 12
    if (*(uint8_t*)((uint8_t*)pRight + 0x69) == 0) {                   // insn 13-14
        void* pChild = *(void**)pRight;                                // insn 15
        while (*(uint8_t*)((uint8_t*)pChild + 0x69) == 0) {             // insn 16,21-22
            pRight = pChild;                                           // insn 19
            pChild = *(void**)pChild;                                   // insn 20
        }
        *(void**)((uint8_t*)pThis + 0x8) = pRight;                     // insn 23
        return;
    }
    void* pUp = *(void**)((uint8_t*)pNode + 0x8);                     // insn 27
    while (*(uint8_t*)((uint8_t*)pUp + 0x69) == 0                    // insn 28-29,35-36
           && *(void**)((uint8_t*)pThis + 0x8) == *(void**)((uint8_t*)pUp + 0x10)) {  // insn 30-32
        *(void**)((uint8_t*)pThis + 0x8) = pUp;                        // insn 33
        pUp = *(void**)((uint8_t*)pUp + 0x8);                          // insn 34
    }
    *(void**)((uint8_t*)pThis + 0x8) = pUp;                           // insn 37
}
inline void SynIterNext_141753470(void* pThis) {   // 0x141753470
    if (*(void**)pThis == nullptr)                                     // insn 2-5
        g_fnIT_1418233c0(pThis);
    void* pNode = *(void**)((uint8_t*)pThis + 0x8);                   // insn 6
    if (*(uint8_t*)((uint8_t*)pNode + 0x29) != 0) {                    // insn 7-8
        g_fnIT_1418233c0(pNode);                                              // insn 11 (tail)
        return;
    }
    void* pRight = *(void**)((uint8_t*)pNode + 0x10);                  // insn 12
    if (*(uint8_t*)((uint8_t*)pRight + 0x29) == 0) {                   // insn 13-14
        void* pChild = *(void**)pRight;                                // insn 15
        while (*(uint8_t*)((uint8_t*)pChild + 0x29) == 0) {             // insn 16,21-22
            pRight = pChild;                                           // insn 19
            pChild = *(void**)pChild;                                   // insn 20
        }
        *(void**)((uint8_t*)pThis + 0x8) = pRight;                     // insn 23
        return;
    }
    void* pUp = *(void**)((uint8_t*)pNode + 0x8);                     // insn 27
    while (*(uint8_t*)((uint8_t*)pUp + 0x29) == 0                    // insn 28-29,35-36
           && *(void**)((uint8_t*)pThis + 0x8) == *(void**)((uint8_t*)pUp + 0x10)) {  // insn 30-32
        *(void**)((uint8_t*)pThis + 0x8) = pUp;                        // insn 33
        pUp = *(void**)((uint8_t*)pUp + 0x8);                          // insn 34
    }
    *(void**)((uint8_t*)pThis + 0x8) = pUp;                           // insn 37
}
inline void SynIterNext_141753500(void* pThis) {   // 0x141753500
    if (*(void**)pThis == nullptr)                                     // insn 2-5
        g_fnIT_1418233c0(pThis);
    void* pNode = *(void**)((uint8_t*)pThis + 0x8);                   // insn 6
    if (*(uint8_t*)((uint8_t*)pNode + 0x61) != 0) {                    // insn 7-8
        g_fnIT_1418233c0(pNode);                                              // insn 11 (tail)
        return;
    }
    void* pRight = *(void**)((uint8_t*)pNode + 0x10);                  // insn 12
    if (*(uint8_t*)((uint8_t*)pRight + 0x61) == 0) {                   // insn 13-14
        void* pChild = *(void**)pRight;                                // insn 15
        while (*(uint8_t*)((uint8_t*)pChild + 0x61) == 0) {             // insn 16,21-22
            pRight = pChild;                                           // insn 19
            pChild = *(void**)pChild;                                   // insn 20
        }
        *(void**)((uint8_t*)pThis + 0x8) = pRight;                     // insn 23
        return;
    }
    void* pUp = *(void**)((uint8_t*)pNode + 0x8);                     // insn 27
    while (*(uint8_t*)((uint8_t*)pUp + 0x61) == 0                    // insn 28-29,35-36
           && *(void**)((uint8_t*)pThis + 0x8) == *(void**)((uint8_t*)pUp + 0x10)) {  // insn 30-32
        *(void**)((uint8_t*)pThis + 0x8) = pUp;                        // insn 33
        pUp = *(void**)((uint8_t*)pUp + 0x8);                          // insn 34
    }
    *(void**)((uint8_t*)pThis + 0x8) = pUp;                           // insn 37
}
inline void SynIterNext_141753620(void* pThis) {   // 0x141753620
    if (*(void**)pThis == nullptr)                                     // insn 2-5
        g_fnIT_1418233c0(pThis);
    void* pNode = *(void**)((uint8_t*)pThis + 0x8);                   // insn 6
    if (*(uint8_t*)((uint8_t*)pNode + 0x29) != 0) {                    // insn 7-8
        g_fnIT_1418233c0(pNode);                                              // insn 11 (tail)
        return;
    }
    void* pRight = *(void**)((uint8_t*)pNode + 0x10);                  // insn 12
    if (*(uint8_t*)((uint8_t*)pRight + 0x29) == 0) {                   // insn 13-14
        void* pChild = *(void**)pRight;                                // insn 15
        while (*(uint8_t*)((uint8_t*)pChild + 0x29) == 0) {             // insn 16,21-22
            pRight = pChild;                                           // insn 19
            pChild = *(void**)pChild;                                   // insn 20
        }
        *(void**)((uint8_t*)pThis + 0x8) = pRight;                     // insn 23
        return;
    }
    void* pUp = *(void**)((uint8_t*)pNode + 0x8);                     // insn 27
    while (*(uint8_t*)((uint8_t*)pUp + 0x29) == 0                    // insn 28-29,35-36
           && *(void**)((uint8_t*)pThis + 0x8) == *(void**)((uint8_t*)pUp + 0x10)) {  // insn 30-32
        *(void**)((uint8_t*)pThis + 0x8) = pUp;                        // insn 33
        pUp = *(void**)((uint8_t*)pUp + 0x8);                          // insn 34
    }
    *(void**)((uint8_t*)pThis + 0x8) = pUp;                           // insn 37
}
inline void SynIterNext_1417536b0(void* pThis) {   // 0x1417536b0
    if (*(void**)pThis == nullptr)                                     // insn 2-5
        g_fnIT_1418233c0(pThis);
    void* pNode = *(void**)((uint8_t*)pThis + 0x8);                   // insn 6
    if (*(uint8_t*)((uint8_t*)pNode + 0x29) != 0) {                    // insn 7-8
        g_fnIT_1418233c0(pNode);                                              // insn 11 (tail)
        return;
    }
    void* pRight = *(void**)((uint8_t*)pNode + 0x10);                  // insn 12
    if (*(uint8_t*)((uint8_t*)pRight + 0x29) == 0) {                   // insn 13-14
        void* pChild = *(void**)pRight;                                // insn 15
        while (*(uint8_t*)((uint8_t*)pChild + 0x29) == 0) {             // insn 16,21-22
            pRight = pChild;                                           // insn 19
            pChild = *(void**)pChild;                                   // insn 20
        }
        *(void**)((uint8_t*)pThis + 0x8) = pRight;                     // insn 23
        return;
    }
    void* pUp = *(void**)((uint8_t*)pNode + 0x8);                     // insn 27
    while (*(uint8_t*)((uint8_t*)pUp + 0x29) == 0                    // insn 28-29,35-36
           && *(void**)((uint8_t*)pThis + 0x8) == *(void**)((uint8_t*)pUp + 0x10)) {  // insn 30-32
        *(void**)((uint8_t*)pThis + 0x8) = pUp;                        // insn 33
        pUp = *(void**)((uint8_t*)pUp + 0x8);                          // insn 34
    }
    *(void**)((uint8_t*)pThis + 0x8) = pUp;                           // insn 37
}
inline void SynIterNext_141753d70(void* pThis) {   // 0x141753d70
    if (*(void**)pThis == nullptr)                                     // insn 2-5
        g_fnIT_1418233c0(pThis);
    void* pNode = *(void**)((uint8_t*)pThis + 0x8);                   // insn 6
    if (*(uint8_t*)((uint8_t*)pNode + 0x29) != 0) {                    // insn 7-8
        g_fnIT_1418233c0(pNode);                                              // insn 11 (tail)
        return;
    }
    void* pRight = *(void**)((uint8_t*)pNode + 0x10);                  // insn 12
    if (*(uint8_t*)((uint8_t*)pRight + 0x29) == 0) {                   // insn 13-14
        void* pChild = *(void**)pRight;                                // insn 15
        while (*(uint8_t*)((uint8_t*)pChild + 0x29) == 0) {             // insn 16,21-22
            pRight = pChild;                                           // insn 19
            pChild = *(void**)pChild;                                   // insn 20
        }
        *(void**)((uint8_t*)pThis + 0x8) = pRight;                     // insn 23
        return;
    }
    void* pUp = *(void**)((uint8_t*)pNode + 0x8);                     // insn 27
    while (*(uint8_t*)((uint8_t*)pUp + 0x29) == 0                    // insn 28-29,35-36
           && *(void**)((uint8_t*)pThis + 0x8) == *(void**)((uint8_t*)pUp + 0x10)) {  // insn 30-32
        *(void**)((uint8_t*)pThis + 0x8) = pUp;                        // insn 33
        pUp = *(void**)((uint8_t*)pUp + 0x8);                          // insn 34
    }
    *(void**)((uint8_t*)pThis + 0x8) = pUp;                           // insn 37
}
inline void SynIterNext_141754000(void* pThis) {   // 0x141754000
    if (*(void**)pThis == nullptr)                                     // insn 2-5
        g_fnIT_1418233c0(pThis);
    void* pNode = *(void**)((uint8_t*)pThis + 0x8);                   // insn 6
    if (*(uint8_t*)((uint8_t*)pNode + 0x29) != 0) {                    // insn 7-8
        g_fnIT_1418233c0(pNode);                                              // insn 11 (tail)
        return;
    }
    void* pRight = *(void**)((uint8_t*)pNode + 0x10);                  // insn 12
    if (*(uint8_t*)((uint8_t*)pRight + 0x29) == 0) {                   // insn 13-14
        void* pChild = *(void**)pRight;                                // insn 15
        while (*(uint8_t*)((uint8_t*)pChild + 0x29) == 0) {             // insn 16,21-22
            pRight = pChild;                                           // insn 19
            pChild = *(void**)pChild;                                   // insn 20
        }
        *(void**)((uint8_t*)pThis + 0x8) = pRight;                     // insn 23
        return;
    }
    void* pUp = *(void**)((uint8_t*)pNode + 0x8);                     // insn 27
    while (*(uint8_t*)((uint8_t*)pUp + 0x29) == 0                    // insn 28-29,35-36
           && *(void**)((uint8_t*)pThis + 0x8) == *(void**)((uint8_t*)pUp + 0x10)) {  // insn 30-32
        *(void**)((uint8_t*)pThis + 0x8) = pUp;                        // insn 33
        pUp = *(void**)((uint8_t*)pUp + 0x8);                          // insn 34
    }
    *(void**)((uint8_t*)pThis + 0x8) = pUp;                           // insn 37
}
inline void SynIterNext_141776460(void* pThis) {   // 0x141776460
    if (*(void**)pThis == nullptr)                                     // insn 2-5
        g_fnIT_1418233c0(pThis);
    void* pNode = *(void**)((uint8_t*)pThis + 0x8);                   // insn 6
    if (*(uint8_t*)((uint8_t*)pNode + 0x39) != 0) {                    // insn 7-8
        g_fnIT_1418233c0(pNode);                                              // insn 11 (tail)
        return;
    }
    void* pRight = *(void**)((uint8_t*)pNode + 0x10);                  // insn 12
    if (*(uint8_t*)((uint8_t*)pRight + 0x39) == 0) {                   // insn 13-14
        void* pChild = *(void**)pRight;                                // insn 15
        while (*(uint8_t*)((uint8_t*)pChild + 0x39) == 0) {             // insn 16,21-22
            pRight = pChild;                                           // insn 19
            pChild = *(void**)pChild;                                   // insn 20
        }
        *(void**)((uint8_t*)pThis + 0x8) = pRight;                     // insn 23
        return;
    }
    void* pUp = *(void**)((uint8_t*)pNode + 0x8);                     // insn 27
    while (*(uint8_t*)((uint8_t*)pUp + 0x39) == 0                    // insn 28-29,35-36
           && *(void**)((uint8_t*)pThis + 0x8) == *(void**)((uint8_t*)pUp + 0x10)) {  // insn 30-32
        *(void**)((uint8_t*)pThis + 0x8) = pUp;                        // insn 33
        pUp = *(void**)((uint8_t*)pUp + 0x8);                          // insn 34
    }
    *(void**)((uint8_t*)pThis + 0x8) = pUp;                           // insn 37
}
inline void SynIterNext_14177a5c0(void* pThis) {   // 0x14177a5c0
    if (*(void**)pThis == nullptr)                                     // insn 2-5
        g_fnIT_1418233c0(pThis);
    void* pNode = *(void**)((uint8_t*)pThis + 0x8);                   // insn 6
    if (*(uint8_t*)((uint8_t*)pNode + 0x29) != 0) {                    // insn 7-8
        g_fnIT_1418233c0(pNode);                                              // insn 11 (tail)
        return;
    }
    void* pRight = *(void**)((uint8_t*)pNode + 0x10);                  // insn 12
    if (*(uint8_t*)((uint8_t*)pRight + 0x29) == 0) {                   // insn 13-14
        void* pChild = *(void**)pRight;                                // insn 15
        while (*(uint8_t*)((uint8_t*)pChild + 0x29) == 0) {             // insn 16,21-22
            pRight = pChild;                                           // insn 19
            pChild = *(void**)pChild;                                   // insn 20
        }
        *(void**)((uint8_t*)pThis + 0x8) = pRight;                     // insn 23
        return;
    }
    void* pUp = *(void**)((uint8_t*)pNode + 0x8);                     // insn 27
    while (*(uint8_t*)((uint8_t*)pUp + 0x29) == 0                    // insn 28-29,35-36
           && *(void**)((uint8_t*)pThis + 0x8) == *(void**)((uint8_t*)pUp + 0x10)) {  // insn 30-32
        *(void**)((uint8_t*)pThis + 0x8) = pUp;                        // insn 33
        pUp = *(void**)((uint8_t*)pUp + 0x8);                          // insn 34
    }
    *(void**)((uint8_t*)pThis + 0x8) = pUp;                           // insn 37
}
inline void SynIterNext_1417899e0(void* pThis) {   // 0x1417899e0
    if (*(void**)pThis == nullptr)                                     // insn 2-5
        g_fnIT_1418233c0(pThis);
    void* pNode = *(void**)((uint8_t*)pThis + 0x8);                   // insn 6
    if (*(uint8_t*)((uint8_t*)pNode + 0x49) != 0) {                    // insn 7-8
        g_fnIT_1418233c0(pNode);                                              // insn 11 (tail)
        return;
    }
    void* pRight = *(void**)((uint8_t*)pNode + 0x10);                  // insn 12
    if (*(uint8_t*)((uint8_t*)pRight + 0x49) == 0) {                   // insn 13-14
        void* pChild = *(void**)pRight;                                // insn 15
        while (*(uint8_t*)((uint8_t*)pChild + 0x49) == 0) {             // insn 16,21-22
            pRight = pChild;                                           // insn 19
            pChild = *(void**)pChild;                                   // insn 20
        }
        *(void**)((uint8_t*)pThis + 0x8) = pRight;                     // insn 23
        return;
    }
    void* pUp = *(void**)((uint8_t*)pNode + 0x8);                     // insn 27
    while (*(uint8_t*)((uint8_t*)pUp + 0x49) == 0                    // insn 28-29,35-36
           && *(void**)((uint8_t*)pThis + 0x8) == *(void**)((uint8_t*)pUp + 0x10)) {  // insn 30-32
        *(void**)((uint8_t*)pThis + 0x8) = pUp;                        // insn 33
        pUp = *(void**)((uint8_t*)pUp + 0x8);                          // insn 34
    }
    *(void**)((uint8_t*)pThis + 0x8) = pUp;                           // insn 37
}
inline void SynIterNext_141789d70(void* pThis) {   // 0x141789d70
    if (*(void**)pThis == nullptr)                                     // insn 2-5
        g_fnIT_1418233c0(pThis);
    void* pNode = *(void**)((uint8_t*)pThis + 0x8);                   // insn 6
    if (*(uint8_t*)((uint8_t*)pNode + 0x29) != 0) {                    // insn 7-8
        g_fnIT_1418233c0(pNode);                                              // insn 11 (tail)
        return;
    }
    void* pRight = *(void**)((uint8_t*)pNode + 0x10);                  // insn 12
    if (*(uint8_t*)((uint8_t*)pRight + 0x29) == 0) {                   // insn 13-14
        void* pChild = *(void**)pRight;                                // insn 15
        while (*(uint8_t*)((uint8_t*)pChild + 0x29) == 0) {             // insn 16,21-22
            pRight = pChild;                                           // insn 19
            pChild = *(void**)pChild;                                   // insn 20
        }
        *(void**)((uint8_t*)pThis + 0x8) = pRight;                     // insn 23
        return;
    }
    void* pUp = *(void**)((uint8_t*)pNode + 0x8);                     // insn 27
    while (*(uint8_t*)((uint8_t*)pUp + 0x29) == 0                    // insn 28-29,35-36
           && *(void**)((uint8_t*)pThis + 0x8) == *(void**)((uint8_t*)pUp + 0x10)) {  // insn 30-32
        *(void**)((uint8_t*)pThis + 0x8) = pUp;                        // insn 33
        pUp = *(void**)((uint8_t*)pUp + 0x8);                          // insn 34
    }
    *(void**)((uint8_t*)pThis + 0x8) = pUp;                           // insn 37
}
inline void SynIterNext_141790e10(void* pThis) {   // 0x141790e10
    if (*(void**)pThis == nullptr)                                     // insn 2-5
        g_fnIT_1418233c0(pThis);
    void* pNode = *(void**)((uint8_t*)pThis + 0x8);                   // insn 6
    if (*(uint8_t*)((uint8_t*)pNode + 0x21) != 0) {                    // insn 7-8
        g_fnIT_1418233c0(pNode);                                              // insn 11 (tail)
        return;
    }
    void* pRight = *(void**)((uint8_t*)pNode + 0x10);                  // insn 12
    if (*(uint8_t*)((uint8_t*)pRight + 0x21) == 0) {                   // insn 13-14
        void* pChild = *(void**)pRight;                                // insn 15
        while (*(uint8_t*)((uint8_t*)pChild + 0x21) == 0) {             // insn 16,21-22
            pRight = pChild;                                           // insn 19
            pChild = *(void**)pChild;                                   // insn 20
        }
        *(void**)((uint8_t*)pThis + 0x8) = pRight;                     // insn 23
        return;
    }
    void* pUp = *(void**)((uint8_t*)pNode + 0x8);                     // insn 27
    while (*(uint8_t*)((uint8_t*)pUp + 0x21) == 0                    // insn 28-29,35-36
           && *(void**)((uint8_t*)pThis + 0x8) == *(void**)((uint8_t*)pUp + 0x10)) {  // insn 30-32
        *(void**)((uint8_t*)pThis + 0x8) = pUp;                        // insn 33
        pUp = *(void**)((uint8_t*)pUp + 0x8);                          // insn 34
    }
    *(void**)((uint8_t*)pThis + 0x8) = pUp;                           // insn 37
}
inline void SynIterNext_141791080(void* pThis) {   // 0x141791080
    if (*(void**)pThis == nullptr)                                     // insn 2-5
        g_fnIT_1418233c0(pThis);
    void* pNode = *(void**)((uint8_t*)pThis + 0x8);                   // insn 6
    if (*(uint8_t*)((uint8_t*)pNode + 0x61) != 0) {                    // insn 7-8
        g_fnIT_1418233c0(pNode);                                              // insn 11 (tail)
        return;
    }
    void* pRight = *(void**)((uint8_t*)pNode + 0x10);                  // insn 12
    if (*(uint8_t*)((uint8_t*)pRight + 0x61) == 0) {                   // insn 13-14
        void* pChild = *(void**)pRight;                                // insn 15
        while (*(uint8_t*)((uint8_t*)pChild + 0x61) == 0) {             // insn 16,21-22
            pRight = pChild;                                           // insn 19
            pChild = *(void**)pChild;                                   // insn 20
        }
        *(void**)((uint8_t*)pThis + 0x8) = pRight;                     // insn 23
        return;
    }
    void* pUp = *(void**)((uint8_t*)pNode + 0x8);                     // insn 27
    while (*(uint8_t*)((uint8_t*)pUp + 0x61) == 0                    // insn 28-29,35-36
           && *(void**)((uint8_t*)pThis + 0x8) == *(void**)((uint8_t*)pUp + 0x10)) {  // insn 30-32
        *(void**)((uint8_t*)pThis + 0x8) = pUp;                        // insn 33
        pUp = *(void**)((uint8_t*)pUp + 0x8);                          // insn 34
    }
    *(void**)((uint8_t*)pThis + 0x8) = pUp;                           // insn 37
}
inline void SynIterNext_141792240(void* pThis) {   // 0x141792240
    if (*(void**)pThis == nullptr)                                     // insn 2-5
        g_fnIT_1418233c0(pThis);
    void* pNode = *(void**)((uint8_t*)pThis + 0x8);                   // insn 6
    if (*(uint8_t*)((uint8_t*)pNode + 0x29) != 0) {                    // insn 7-8
        g_fnIT_1418233c0(pNode);                                              // insn 11 (tail)
        return;
    }
    void* pRight = *(void**)((uint8_t*)pNode + 0x10);                  // insn 12
    if (*(uint8_t*)((uint8_t*)pRight + 0x29) == 0) {                   // insn 13-14
        void* pChild = *(void**)pRight;                                // insn 15
        while (*(uint8_t*)((uint8_t*)pChild + 0x29) == 0) {             // insn 16,21-22
            pRight = pChild;                                           // insn 19
            pChild = *(void**)pChild;                                   // insn 20
        }
        *(void**)((uint8_t*)pThis + 0x8) = pRight;                     // insn 23
        return;
    }
    void* pUp = *(void**)((uint8_t*)pNode + 0x8);                     // insn 27
    while (*(uint8_t*)((uint8_t*)pUp + 0x29) == 0                    // insn 28-29,35-36
           && *(void**)((uint8_t*)pThis + 0x8) == *(void**)((uint8_t*)pUp + 0x10)) {  // insn 30-32
        *(void**)((uint8_t*)pThis + 0x8) = pUp;                        // insn 33
        pUp = *(void**)((uint8_t*)pUp + 0x8);                          // insn 34
    }
    *(void**)((uint8_t*)pThis + 0x8) = pUp;                           // insn 37
}
inline void SynIterNext_1417a70b0(void* pThis) {   // 0x1417a70b0
    if (*(void**)pThis == nullptr)                                     // insn 2-5
        g_fnIT_1418233c0(pThis);
    void* pNode = *(void**)((uint8_t*)pThis + 0x8);                   // insn 6
    if (*(uint8_t*)((uint8_t*)pNode + 0x29) != 0) {                    // insn 7-8
        g_fnIT_1418233c0(pNode);                                              // insn 11 (tail)
        return;
    }
    void* pRight = *(void**)((uint8_t*)pNode + 0x10);                  // insn 12
    if (*(uint8_t*)((uint8_t*)pRight + 0x29) == 0) {                   // insn 13-14
        void* pChild = *(void**)pRight;                                // insn 15
        while (*(uint8_t*)((uint8_t*)pChild + 0x29) == 0) {             // insn 16,21-22
            pRight = pChild;                                           // insn 19
            pChild = *(void**)pChild;                                   // insn 20
        }
        *(void**)((uint8_t*)pThis + 0x8) = pRight;                     // insn 23
        return;
    }
    void* pUp = *(void**)((uint8_t*)pNode + 0x8);                     // insn 27
    while (*(uint8_t*)((uint8_t*)pUp + 0x29) == 0                    // insn 28-29,35-36
           && *(void**)((uint8_t*)pThis + 0x8) == *(void**)((uint8_t*)pUp + 0x10)) {  // insn 30-32
        *(void**)((uint8_t*)pThis + 0x8) = pUp;                        // insn 33
        pUp = *(void**)((uint8_t*)pUp + 0x8);                          // insn 34
    }
    *(void**)((uint8_t*)pThis + 0x8) = pUp;                           // insn 37
}

}  // namespace tq

#endif
