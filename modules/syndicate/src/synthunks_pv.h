// synthunks_pv.h — RAW Syndicate.dll v6159 · 29 ordered-tree iterator predecessor steps
// (family PV, the `--` sibling of family IT). The whole body is 47 instructions; each instance
// below is transcribed instruction by instruction, never inferred from the IT sibling.
//
// The marker byte sits at a per-class offset (+0x1b, +0x1d, +0x21, +0x29, +0x2d, +0x39, +0x3d, +0x49, +0x51, +0x59, +0x61, +0x69) and is always compared
// against zero. The links do not vary: left +0x0 (a bare [reg] load), parent +0x8, right +0x10,
// iterator node slot +0x8, frame 0x20. Three quirks are preserved verbatim:
//   * the null-container guard (insn 2-5) hands the *holder* pThis to the report seam, not null;
//   * the sentinel path (insn 9-15) stores head->f10 before deciding, so the store survives even
//     when the tail call follows, and that tail call still carries the sentinel in rcx;
//   * insn 40-42 re-reads the slot it just wrote and, if that node is marked, tail-calls the seam
//     with the parent that ended the climb. Given the invariant tested at insn 31 the slot can
//     never be marked there for a well-formed tree, so the path is unreachable — kept as in the
//     raw rather than "fixed".
#ifndef TQ_SYN_THUNKS_PV_H
#define TQ_SYN_THUNKS_PV_H

#include <cstdint>

namespace tq {

extern void (*g_fnPV_1418233c0)(void* pArg);

inline void SynIterPrev_141723420(void* pThis) {   // 0x141723420
    if (*(void**)pThis == nullptr)                                     // insn 2-5
        g_fnPV_1418233c0(pThis);                                            // insn 5 (rcx = the holder)
    void* pNode = *(void**)((uint8_t*)pThis + 0x8);                    // insn 6
    if (*(uint8_t*)((uint8_t*)pNode + 0x29) != 0) {                  // insn 7-8 (je 16)
        void* pRight = *(void**)((uint8_t*)pNode + 0x10);              // insn 9
        *(void**)((uint8_t*)pThis + 0x8) = pRight;                     // insn 10
        if (*(uint8_t*)((uint8_t*)pRight + 0x29) == 0)                 // insn 11-12 (je 44)
            return;                                                     // insn 44-46
        g_fnPV_1418233c0(pNode);                                            // insn 13-15 (rcx = the sentinel)
        return;
    }
    void* pLeft = *(void**)pNode;                                      // insn 16
    if (*(uint8_t*)((uint8_t*)pLeft + 0x29) == 0) {                  // insn 17-18 (jne 30 -> climb)
        void* pRight = *(void**)((uint8_t*)pLeft + 0x10);              // insn 19
        while (*(uint8_t*)((uint8_t*)pRight + 0x29) == 0) {            // insn 20-21 (jne 26), 24-25 (je 22)
            pLeft = pRight;                                             // insn 22
            pRight = *(void**)((uint8_t*)pRight + 0x10);                // insn 23
        }
        *(void**)((uint8_t*)pThis + 0x8) = pLeft;                       // insn 26
        return;                                                        // insn 27-29
    }
    void* pUp = *(void**)((uint8_t*)pNode + 0x8);                      // insn 30
    while (*(uint8_t*)((uint8_t*)pUp + 0x29) == 0                       // insn 31-32 (jne 40), 38-39 (je 33)
           && *(void**)((uint8_t*)pThis + 0x8) == *(void**)pUp) {      // insn 33-35 (jne 40)
        *(void**)((uint8_t*)pThis + 0x8) = pUp;                         // insn 36
        pUp = *(void**)((uint8_t*)pUp + 0x8);                           // insn 37
    }
    void* pMarked = *(void**)((uint8_t*)pThis + 0x8);                  // insn 40
    if (*(uint8_t*)((uint8_t*)pMarked + 0x29) != 0) {                 // insn 41-42 (jne 13)
        g_fnPV_1418233c0(pUp);                                              // insn 13-15 (rcx = the parent)
        return;
    }
    *(void**)((uint8_t*)pThis + 0x8) = pUp;                            // insn 43
}
inline void SynIterPrev_1417234c0(void* pThis) {   // 0x1417234c0
    if (*(void**)pThis == nullptr)                                     // insn 2-5
        g_fnPV_1418233c0(pThis);                                            // insn 5 (rcx = the holder)
    void* pNode = *(void**)((uint8_t*)pThis + 0x8);                    // insn 6
    if (*(uint8_t*)((uint8_t*)pNode + 0x1d) != 0) {                  // insn 7-8 (je 16)
        void* pRight = *(void**)((uint8_t*)pNode + 0x10);              // insn 9
        *(void**)((uint8_t*)pThis + 0x8) = pRight;                     // insn 10
        if (*(uint8_t*)((uint8_t*)pRight + 0x1d) == 0)                 // insn 11-12 (je 44)
            return;                                                     // insn 44-46
        g_fnPV_1418233c0(pNode);                                            // insn 13-15 (rcx = the sentinel)
        return;
    }
    void* pLeft = *(void**)pNode;                                      // insn 16
    if (*(uint8_t*)((uint8_t*)pLeft + 0x1d) == 0) {                  // insn 17-18 (jne 30 -> climb)
        void* pRight = *(void**)((uint8_t*)pLeft + 0x10);              // insn 19
        while (*(uint8_t*)((uint8_t*)pRight + 0x1d) == 0) {            // insn 20-21 (jne 26), 24-25 (je 22)
            pLeft = pRight;                                             // insn 22
            pRight = *(void**)((uint8_t*)pRight + 0x10);                // insn 23
        }
        *(void**)((uint8_t*)pThis + 0x8) = pLeft;                       // insn 26
        return;                                                        // insn 27-29
    }
    void* pUp = *(void**)((uint8_t*)pNode + 0x8);                      // insn 30
    while (*(uint8_t*)((uint8_t*)pUp + 0x1d) == 0                       // insn 31-32 (jne 40), 38-39 (je 33)
           && *(void**)((uint8_t*)pThis + 0x8) == *(void**)pUp) {      // insn 33-35 (jne 40)
        *(void**)((uint8_t*)pThis + 0x8) = pUp;                         // insn 36
        pUp = *(void**)((uint8_t*)pUp + 0x8);                           // insn 37
    }
    void* pMarked = *(void**)((uint8_t*)pThis + 0x8);                  // insn 40
    if (*(uint8_t*)((uint8_t*)pMarked + 0x1d) != 0) {                 // insn 41-42 (jne 13)
        g_fnPV_1418233c0(pUp);                                              // insn 13-15 (rcx = the parent)
        return;
    }
    *(void**)((uint8_t*)pThis + 0x8) = pUp;                            // insn 43
}
inline void SynIterPrev_141723560(void* pThis) {   // 0x141723560
    if (*(void**)pThis == nullptr)                                     // insn 2-5
        g_fnPV_1418233c0(pThis);                                            // insn 5 (rcx = the holder)
    void* pNode = *(void**)((uint8_t*)pThis + 0x8);                    // insn 6
    if (*(uint8_t*)((uint8_t*)pNode + 0x49) != 0) {                  // insn 7-8 (je 16)
        void* pRight = *(void**)((uint8_t*)pNode + 0x10);              // insn 9
        *(void**)((uint8_t*)pThis + 0x8) = pRight;                     // insn 10
        if (*(uint8_t*)((uint8_t*)pRight + 0x49) == 0)                 // insn 11-12 (je 44)
            return;                                                     // insn 44-46
        g_fnPV_1418233c0(pNode);                                            // insn 13-15 (rcx = the sentinel)
        return;
    }
    void* pLeft = *(void**)pNode;                                      // insn 16
    if (*(uint8_t*)((uint8_t*)pLeft + 0x49) == 0) {                  // insn 17-18 (jne 30 -> climb)
        void* pRight = *(void**)((uint8_t*)pLeft + 0x10);              // insn 19
        while (*(uint8_t*)((uint8_t*)pRight + 0x49) == 0) {            // insn 20-21 (jne 26), 24-25 (je 22)
            pLeft = pRight;                                             // insn 22
            pRight = *(void**)((uint8_t*)pRight + 0x10);                // insn 23
        }
        *(void**)((uint8_t*)pThis + 0x8) = pLeft;                       // insn 26
        return;                                                        // insn 27-29
    }
    void* pUp = *(void**)((uint8_t*)pNode + 0x8);                      // insn 30
    while (*(uint8_t*)((uint8_t*)pUp + 0x49) == 0                       // insn 31-32 (jne 40), 38-39 (je 33)
           && *(void**)((uint8_t*)pThis + 0x8) == *(void**)pUp) {      // insn 33-35 (jne 40)
        *(void**)((uint8_t*)pThis + 0x8) = pUp;                         // insn 36
        pUp = *(void**)((uint8_t*)pUp + 0x8);                           // insn 37
    }
    void* pMarked = *(void**)((uint8_t*)pThis + 0x8);                  // insn 40
    if (*(uint8_t*)((uint8_t*)pMarked + 0x49) != 0) {                 // insn 41-42 (jne 13)
        g_fnPV_1418233c0(pUp);                                              // insn 13-15 (rcx = the parent)
        return;
    }
    *(void**)((uint8_t*)pThis + 0x8) = pUp;                            // insn 43
}
inline void SynIterPrev_141725500(void* pThis) {   // 0x141725500
    if (*(void**)pThis == nullptr)                                     // insn 2-5
        g_fnPV_1418233c0(pThis);                                            // insn 5 (rcx = the holder)
    void* pNode = *(void**)((uint8_t*)pThis + 0x8);                    // insn 6
    if (*(uint8_t*)((uint8_t*)pNode + 0x1d) != 0) {                  // insn 7-8 (je 16)
        void* pRight = *(void**)((uint8_t*)pNode + 0x10);              // insn 9
        *(void**)((uint8_t*)pThis + 0x8) = pRight;                     // insn 10
        if (*(uint8_t*)((uint8_t*)pRight + 0x1d) == 0)                 // insn 11-12 (je 44)
            return;                                                     // insn 44-46
        g_fnPV_1418233c0(pNode);                                            // insn 13-15 (rcx = the sentinel)
        return;
    }
    void* pLeft = *(void**)pNode;                                      // insn 16
    if (*(uint8_t*)((uint8_t*)pLeft + 0x1d) == 0) {                  // insn 17-18 (jne 30 -> climb)
        void* pRight = *(void**)((uint8_t*)pLeft + 0x10);              // insn 19
        while (*(uint8_t*)((uint8_t*)pRight + 0x1d) == 0) {            // insn 20-21 (jne 26), 24-25 (je 22)
            pLeft = pRight;                                             // insn 22
            pRight = *(void**)((uint8_t*)pRight + 0x10);                // insn 23
        }
        *(void**)((uint8_t*)pThis + 0x8) = pLeft;                       // insn 26
        return;                                                        // insn 27-29
    }
    void* pUp = *(void**)((uint8_t*)pNode + 0x8);                      // insn 30
    while (*(uint8_t*)((uint8_t*)pUp + 0x1d) == 0                       // insn 31-32 (jne 40), 38-39 (je 33)
           && *(void**)((uint8_t*)pThis + 0x8) == *(void**)pUp) {      // insn 33-35 (jne 40)
        *(void**)((uint8_t*)pThis + 0x8) = pUp;                         // insn 36
        pUp = *(void**)((uint8_t*)pUp + 0x8);                           // insn 37
    }
    void* pMarked = *(void**)((uint8_t*)pThis + 0x8);                  // insn 40
    if (*(uint8_t*)((uint8_t*)pMarked + 0x1d) != 0) {                 // insn 41-42 (jne 13)
        g_fnPV_1418233c0(pUp);                                              // insn 13-15 (rcx = the parent)
        return;
    }
    *(void**)((uint8_t*)pThis + 0x8) = pUp;                            // insn 43
}
inline void SynIterPrev_141725740(void* pThis) {   // 0x141725740
    if (*(void**)pThis == nullptr)                                     // insn 2-5
        g_fnPV_1418233c0(pThis);                                            // insn 5 (rcx = the holder)
    void* pNode = *(void**)((uint8_t*)pThis + 0x8);                    // insn 6
    if (*(uint8_t*)((uint8_t*)pNode + 0x1b) != 0) {                  // insn 7-8 (je 16)
        void* pRight = *(void**)((uint8_t*)pNode + 0x10);              // insn 9
        *(void**)((uint8_t*)pThis + 0x8) = pRight;                     // insn 10
        if (*(uint8_t*)((uint8_t*)pRight + 0x1b) == 0)                 // insn 11-12 (je 44)
            return;                                                     // insn 44-46
        g_fnPV_1418233c0(pNode);                                            // insn 13-15 (rcx = the sentinel)
        return;
    }
    void* pLeft = *(void**)pNode;                                      // insn 16
    if (*(uint8_t*)((uint8_t*)pLeft + 0x1b) == 0) {                  // insn 17-18 (jne 30 -> climb)
        void* pRight = *(void**)((uint8_t*)pLeft + 0x10);              // insn 19
        while (*(uint8_t*)((uint8_t*)pRight + 0x1b) == 0) {            // insn 20-21 (jne 26), 24-25 (je 22)
            pLeft = pRight;                                             // insn 22
            pRight = *(void**)((uint8_t*)pRight + 0x10);                // insn 23
        }
        *(void**)((uint8_t*)pThis + 0x8) = pLeft;                       // insn 26
        return;                                                        // insn 27-29
    }
    void* pUp = *(void**)((uint8_t*)pNode + 0x8);                      // insn 30
    while (*(uint8_t*)((uint8_t*)pUp + 0x1b) == 0                       // insn 31-32 (jne 40), 38-39 (je 33)
           && *(void**)((uint8_t*)pThis + 0x8) == *(void**)pUp) {      // insn 33-35 (jne 40)
        *(void**)((uint8_t*)pThis + 0x8) = pUp;                         // insn 36
        pUp = *(void**)((uint8_t*)pUp + 0x8);                           // insn 37
    }
    void* pMarked = *(void**)((uint8_t*)pThis + 0x8);                  // insn 40
    if (*(uint8_t*)((uint8_t*)pMarked + 0x1b) != 0) {                 // insn 41-42 (jne 13)
        g_fnPV_1418233c0(pUp);                                              // insn 13-15 (rcx = the parent)
        return;
    }
    *(void**)((uint8_t*)pThis + 0x8) = pUp;                            // insn 43
}
inline void SynIterPrev_141725800(void* pThis) {   // 0x141725800
    if (*(void**)pThis == nullptr)                                     // insn 2-5
        g_fnPV_1418233c0(pThis);                                            // insn 5 (rcx = the holder)
    void* pNode = *(void**)((uint8_t*)pThis + 0x8);                    // insn 6
    if (*(uint8_t*)((uint8_t*)pNode + 0x51) != 0) {                  // insn 7-8 (je 16)
        void* pRight = *(void**)((uint8_t*)pNode + 0x10);              // insn 9
        *(void**)((uint8_t*)pThis + 0x8) = pRight;                     // insn 10
        if (*(uint8_t*)((uint8_t*)pRight + 0x51) == 0)                 // insn 11-12 (je 44)
            return;                                                     // insn 44-46
        g_fnPV_1418233c0(pNode);                                            // insn 13-15 (rcx = the sentinel)
        return;
    }
    void* pLeft = *(void**)pNode;                                      // insn 16
    if (*(uint8_t*)((uint8_t*)pLeft + 0x51) == 0) {                  // insn 17-18 (jne 30 -> climb)
        void* pRight = *(void**)((uint8_t*)pLeft + 0x10);              // insn 19
        while (*(uint8_t*)((uint8_t*)pRight + 0x51) == 0) {            // insn 20-21 (jne 26), 24-25 (je 22)
            pLeft = pRight;                                             // insn 22
            pRight = *(void**)((uint8_t*)pRight + 0x10);                // insn 23
        }
        *(void**)((uint8_t*)pThis + 0x8) = pLeft;                       // insn 26
        return;                                                        // insn 27-29
    }
    void* pUp = *(void**)((uint8_t*)pNode + 0x8);                      // insn 30
    while (*(uint8_t*)((uint8_t*)pUp + 0x51) == 0                       // insn 31-32 (jne 40), 38-39 (je 33)
           && *(void**)((uint8_t*)pThis + 0x8) == *(void**)pUp) {      // insn 33-35 (jne 40)
        *(void**)((uint8_t*)pThis + 0x8) = pUp;                         // insn 36
        pUp = *(void**)((uint8_t*)pUp + 0x8);                           // insn 37
    }
    void* pMarked = *(void**)((uint8_t*)pThis + 0x8);                  // insn 40
    if (*(uint8_t*)((uint8_t*)pMarked + 0x51) != 0) {                 // insn 41-42 (jne 13)
        g_fnPV_1418233c0(pUp);                                              // insn 13-15 (rcx = the parent)
        return;
    }
    *(void**)((uint8_t*)pThis + 0x8) = pUp;                            // insn 43
}
inline void SynIterPrev_14173b010(void* pThis) {   // 0x14173b010
    if (*(void**)pThis == nullptr)                                     // insn 2-5
        g_fnPV_1418233c0(pThis);                                            // insn 5 (rcx = the holder)
    void* pNode = *(void**)((uint8_t*)pThis + 0x8);                    // insn 6
    if (*(uint8_t*)((uint8_t*)pNode + 0x61) != 0) {                  // insn 7-8 (je 16)
        void* pRight = *(void**)((uint8_t*)pNode + 0x10);              // insn 9
        *(void**)((uint8_t*)pThis + 0x8) = pRight;                     // insn 10
        if (*(uint8_t*)((uint8_t*)pRight + 0x61) == 0)                 // insn 11-12 (je 44)
            return;                                                     // insn 44-46
        g_fnPV_1418233c0(pNode);                                            // insn 13-15 (rcx = the sentinel)
        return;
    }
    void* pLeft = *(void**)pNode;                                      // insn 16
    if (*(uint8_t*)((uint8_t*)pLeft + 0x61) == 0) {                  // insn 17-18 (jne 30 -> climb)
        void* pRight = *(void**)((uint8_t*)pLeft + 0x10);              // insn 19
        while (*(uint8_t*)((uint8_t*)pRight + 0x61) == 0) {            // insn 20-21 (jne 26), 24-25 (je 22)
            pLeft = pRight;                                             // insn 22
            pRight = *(void**)((uint8_t*)pRight + 0x10);                // insn 23
        }
        *(void**)((uint8_t*)pThis + 0x8) = pLeft;                       // insn 26
        return;                                                        // insn 27-29
    }
    void* pUp = *(void**)((uint8_t*)pNode + 0x8);                      // insn 30
    while (*(uint8_t*)((uint8_t*)pUp + 0x61) == 0                       // insn 31-32 (jne 40), 38-39 (je 33)
           && *(void**)((uint8_t*)pThis + 0x8) == *(void**)pUp) {      // insn 33-35 (jne 40)
        *(void**)((uint8_t*)pThis + 0x8) = pUp;                         // insn 36
        pUp = *(void**)((uint8_t*)pUp + 0x8);                           // insn 37
    }
    void* pMarked = *(void**)((uint8_t*)pThis + 0x8);                  // insn 40
    if (*(uint8_t*)((uint8_t*)pMarked + 0x61) != 0) {                 // insn 41-42 (jne 13)
        g_fnPV_1418233c0(pUp);                                              // insn 13-15 (rcx = the parent)
        return;
    }
    *(void**)((uint8_t*)pThis + 0x8) = pUp;                            // insn 43
}
inline void SynIterPrev_14173b1a0(void* pThis) {   // 0x14173b1a0
    if (*(void**)pThis == nullptr)                                     // insn 2-5
        g_fnPV_1418233c0(pThis);                                            // insn 5 (rcx = the holder)
    void* pNode = *(void**)((uint8_t*)pThis + 0x8);                    // insn 6
    if (*(uint8_t*)((uint8_t*)pNode + 0x21) != 0) {                  // insn 7-8 (je 16)
        void* pRight = *(void**)((uint8_t*)pNode + 0x10);              // insn 9
        *(void**)((uint8_t*)pThis + 0x8) = pRight;                     // insn 10
        if (*(uint8_t*)((uint8_t*)pRight + 0x21) == 0)                 // insn 11-12 (je 44)
            return;                                                     // insn 44-46
        g_fnPV_1418233c0(pNode);                                            // insn 13-15 (rcx = the sentinel)
        return;
    }
    void* pLeft = *(void**)pNode;                                      // insn 16
    if (*(uint8_t*)((uint8_t*)pLeft + 0x21) == 0) {                  // insn 17-18 (jne 30 -> climb)
        void* pRight = *(void**)((uint8_t*)pLeft + 0x10);              // insn 19
        while (*(uint8_t*)((uint8_t*)pRight + 0x21) == 0) {            // insn 20-21 (jne 26), 24-25 (je 22)
            pLeft = pRight;                                             // insn 22
            pRight = *(void**)((uint8_t*)pRight + 0x10);                // insn 23
        }
        *(void**)((uint8_t*)pThis + 0x8) = pLeft;                       // insn 26
        return;                                                        // insn 27-29
    }
    void* pUp = *(void**)((uint8_t*)pNode + 0x8);                      // insn 30
    while (*(uint8_t*)((uint8_t*)pUp + 0x21) == 0                       // insn 31-32 (jne 40), 38-39 (je 33)
           && *(void**)((uint8_t*)pThis + 0x8) == *(void**)pUp) {      // insn 33-35 (jne 40)
        *(void**)((uint8_t*)pThis + 0x8) = pUp;                         // insn 36
        pUp = *(void**)((uint8_t*)pUp + 0x8);                           // insn 37
    }
    void* pMarked = *(void**)((uint8_t*)pThis + 0x8);                  // insn 40
    if (*(uint8_t*)((uint8_t*)pMarked + 0x21) != 0) {                 // insn 41-42 (jne 13)
        g_fnPV_1418233c0(pUp);                                              // insn 13-15 (rcx = the parent)
        return;
    }
    *(void**)((uint8_t*)pThis + 0x8) = pUp;                            // insn 43
}
inline void SynIterPrev_141744990(void* pThis) {   // 0x141744990
    if (*(void**)pThis == nullptr)                                     // insn 2-5
        g_fnPV_1418233c0(pThis);                                            // insn 5 (rcx = the holder)
    void* pNode = *(void**)((uint8_t*)pThis + 0x8);                    // insn 6
    if (*(uint8_t*)((uint8_t*)pNode + 0x3d) != 0) {                  // insn 7-8 (je 16)
        void* pRight = *(void**)((uint8_t*)pNode + 0x10);              // insn 9
        *(void**)((uint8_t*)pThis + 0x8) = pRight;                     // insn 10
        if (*(uint8_t*)((uint8_t*)pRight + 0x3d) == 0)                 // insn 11-12 (je 44)
            return;                                                     // insn 44-46
        g_fnPV_1418233c0(pNode);                                            // insn 13-15 (rcx = the sentinel)
        return;
    }
    void* pLeft = *(void**)pNode;                                      // insn 16
    if (*(uint8_t*)((uint8_t*)pLeft + 0x3d) == 0) {                  // insn 17-18 (jne 30 -> climb)
        void* pRight = *(void**)((uint8_t*)pLeft + 0x10);              // insn 19
        while (*(uint8_t*)((uint8_t*)pRight + 0x3d) == 0) {            // insn 20-21 (jne 26), 24-25 (je 22)
            pLeft = pRight;                                             // insn 22
            pRight = *(void**)((uint8_t*)pRight + 0x10);                // insn 23
        }
        *(void**)((uint8_t*)pThis + 0x8) = pLeft;                       // insn 26
        return;                                                        // insn 27-29
    }
    void* pUp = *(void**)((uint8_t*)pNode + 0x8);                      // insn 30
    while (*(uint8_t*)((uint8_t*)pUp + 0x3d) == 0                       // insn 31-32 (jne 40), 38-39 (je 33)
           && *(void**)((uint8_t*)pThis + 0x8) == *(void**)pUp) {      // insn 33-35 (jne 40)
        *(void**)((uint8_t*)pThis + 0x8) = pUp;                         // insn 36
        pUp = *(void**)((uint8_t*)pUp + 0x8);                           // insn 37
    }
    void* pMarked = *(void**)((uint8_t*)pThis + 0x8);                  // insn 40
    if (*(uint8_t*)((uint8_t*)pMarked + 0x3d) != 0) {                 // insn 41-42 (jne 13)
        g_fnPV_1418233c0(pUp);                                              // insn 13-15 (rcx = the parent)
        return;
    }
    *(void**)((uint8_t*)pThis + 0x8) = pUp;                            // insn 43
}
inline void SynIterPrev_141744a30(void* pThis) {   // 0x141744a30
    if (*(void**)pThis == nullptr)                                     // insn 2-5
        g_fnPV_1418233c0(pThis);                                            // insn 5 (rcx = the holder)
    void* pNode = *(void**)((uint8_t*)pThis + 0x8);                    // insn 6
    if (*(uint8_t*)((uint8_t*)pNode + 0x29) != 0) {                  // insn 7-8 (je 16)
        void* pRight = *(void**)((uint8_t*)pNode + 0x10);              // insn 9
        *(void**)((uint8_t*)pThis + 0x8) = pRight;                     // insn 10
        if (*(uint8_t*)((uint8_t*)pRight + 0x29) == 0)                 // insn 11-12 (je 44)
            return;                                                     // insn 44-46
        g_fnPV_1418233c0(pNode);                                            // insn 13-15 (rcx = the sentinel)
        return;
    }
    void* pLeft = *(void**)pNode;                                      // insn 16
    if (*(uint8_t*)((uint8_t*)pLeft + 0x29) == 0) {                  // insn 17-18 (jne 30 -> climb)
        void* pRight = *(void**)((uint8_t*)pLeft + 0x10);              // insn 19
        while (*(uint8_t*)((uint8_t*)pRight + 0x29) == 0) {            // insn 20-21 (jne 26), 24-25 (je 22)
            pLeft = pRight;                                             // insn 22
            pRight = *(void**)((uint8_t*)pRight + 0x10);                // insn 23
        }
        *(void**)((uint8_t*)pThis + 0x8) = pLeft;                       // insn 26
        return;                                                        // insn 27-29
    }
    void* pUp = *(void**)((uint8_t*)pNode + 0x8);                      // insn 30
    while (*(uint8_t*)((uint8_t*)pUp + 0x29) == 0                       // insn 31-32 (jne 40), 38-39 (je 33)
           && *(void**)((uint8_t*)pThis + 0x8) == *(void**)pUp) {      // insn 33-35 (jne 40)
        *(void**)((uint8_t*)pThis + 0x8) = pUp;                         // insn 36
        pUp = *(void**)((uint8_t*)pUp + 0x8);                           // insn 37
    }
    void* pMarked = *(void**)((uint8_t*)pThis + 0x8);                  // insn 40
    if (*(uint8_t*)((uint8_t*)pMarked + 0x29) != 0) {                 // insn 41-42 (jne 13)
        g_fnPV_1418233c0(pUp);                                              // insn 13-15 (rcx = the parent)
        return;
    }
    *(void**)((uint8_t*)pThis + 0x8) = pUp;                            // insn 43
}
inline void SynIterPrev_141750b50(void* pThis) {   // 0x141750b50
    if (*(void**)pThis == nullptr)                                     // insn 2-5
        g_fnPV_1418233c0(pThis);                                            // insn 5 (rcx = the holder)
    void* pNode = *(void**)((uint8_t*)pThis + 0x8);                    // insn 6
    if (*(uint8_t*)((uint8_t*)pNode + 0x29) != 0) {                  // insn 7-8 (je 16)
        void* pRight = *(void**)((uint8_t*)pNode + 0x10);              // insn 9
        *(void**)((uint8_t*)pThis + 0x8) = pRight;                     // insn 10
        if (*(uint8_t*)((uint8_t*)pRight + 0x29) == 0)                 // insn 11-12 (je 44)
            return;                                                     // insn 44-46
        g_fnPV_1418233c0(pNode);                                            // insn 13-15 (rcx = the sentinel)
        return;
    }
    void* pLeft = *(void**)pNode;                                      // insn 16
    if (*(uint8_t*)((uint8_t*)pLeft + 0x29) == 0) {                  // insn 17-18 (jne 30 -> climb)
        void* pRight = *(void**)((uint8_t*)pLeft + 0x10);              // insn 19
        while (*(uint8_t*)((uint8_t*)pRight + 0x29) == 0) {            // insn 20-21 (jne 26), 24-25 (je 22)
            pLeft = pRight;                                             // insn 22
            pRight = *(void**)((uint8_t*)pRight + 0x10);                // insn 23
        }
        *(void**)((uint8_t*)pThis + 0x8) = pLeft;                       // insn 26
        return;                                                        // insn 27-29
    }
    void* pUp = *(void**)((uint8_t*)pNode + 0x8);                      // insn 30
    while (*(uint8_t*)((uint8_t*)pUp + 0x29) == 0                       // insn 31-32 (jne 40), 38-39 (je 33)
           && *(void**)((uint8_t*)pThis + 0x8) == *(void**)pUp) {      // insn 33-35 (jne 40)
        *(void**)((uint8_t*)pThis + 0x8) = pUp;                         // insn 36
        pUp = *(void**)((uint8_t*)pUp + 0x8);                           // insn 37
    }
    void* pMarked = *(void**)((uint8_t*)pThis + 0x8);                  // insn 40
    if (*(uint8_t*)((uint8_t*)pMarked + 0x29) != 0) {                 // insn 41-42 (jne 13)
        g_fnPV_1418233c0(pUp);                                              // insn 13-15 (rcx = the parent)
        return;
    }
    *(void**)((uint8_t*)pThis + 0x8) = pUp;                            // insn 43
}
inline void SynIterPrev_141750c30(void* pThis) {   // 0x141750c30
    if (*(void**)pThis == nullptr)                                     // insn 2-5
        g_fnPV_1418233c0(pThis);                                            // insn 5 (rcx = the holder)
    void* pNode = *(void**)((uint8_t*)pThis + 0x8);                    // insn 6
    if (*(uint8_t*)((uint8_t*)pNode + 0x61) != 0) {                  // insn 7-8 (je 16)
        void* pRight = *(void**)((uint8_t*)pNode + 0x10);              // insn 9
        *(void**)((uint8_t*)pThis + 0x8) = pRight;                     // insn 10
        if (*(uint8_t*)((uint8_t*)pRight + 0x61) == 0)                 // insn 11-12 (je 44)
            return;                                                     // insn 44-46
        g_fnPV_1418233c0(pNode);                                            // insn 13-15 (rcx = the sentinel)
        return;
    }
    void* pLeft = *(void**)pNode;                                      // insn 16
    if (*(uint8_t*)((uint8_t*)pLeft + 0x61) == 0) {                  // insn 17-18 (jne 30 -> climb)
        void* pRight = *(void**)((uint8_t*)pLeft + 0x10);              // insn 19
        while (*(uint8_t*)((uint8_t*)pRight + 0x61) == 0) {            // insn 20-21 (jne 26), 24-25 (je 22)
            pLeft = pRight;                                             // insn 22
            pRight = *(void**)((uint8_t*)pRight + 0x10);                // insn 23
        }
        *(void**)((uint8_t*)pThis + 0x8) = pLeft;                       // insn 26
        return;                                                        // insn 27-29
    }
    void* pUp = *(void**)((uint8_t*)pNode + 0x8);                      // insn 30
    while (*(uint8_t*)((uint8_t*)pUp + 0x61) == 0                       // insn 31-32 (jne 40), 38-39 (je 33)
           && *(void**)((uint8_t*)pThis + 0x8) == *(void**)pUp) {      // insn 33-35 (jne 40)
        *(void**)((uint8_t*)pThis + 0x8) = pUp;                         // insn 36
        pUp = *(void**)((uint8_t*)pUp + 0x8);                           // insn 37
    }
    void* pMarked = *(void**)((uint8_t*)pThis + 0x8);                  // insn 40
    if (*(uint8_t*)((uint8_t*)pMarked + 0x61) != 0) {                 // insn 41-42 (jne 13)
        g_fnPV_1418233c0(pUp);                                              // insn 13-15 (rcx = the parent)
        return;
    }
    *(void**)((uint8_t*)pThis + 0x8) = pUp;                            // insn 43
}
inline void SynIterPrev_141750ce0(void* pThis) {   // 0x141750ce0
    if (*(void**)pThis == nullptr)                                     // insn 2-5
        g_fnPV_1418233c0(pThis);                                            // insn 5 (rcx = the holder)
    void* pNode = *(void**)((uint8_t*)pThis + 0x8);                    // insn 6
    if (*(uint8_t*)((uint8_t*)pNode + 0x2d) != 0) {                  // insn 7-8 (je 16)
        void* pRight = *(void**)((uint8_t*)pNode + 0x10);              // insn 9
        *(void**)((uint8_t*)pThis + 0x8) = pRight;                     // insn 10
        if (*(uint8_t*)((uint8_t*)pRight + 0x2d) == 0)                 // insn 11-12 (je 44)
            return;                                                     // insn 44-46
        g_fnPV_1418233c0(pNode);                                            // insn 13-15 (rcx = the sentinel)
        return;
    }
    void* pLeft = *(void**)pNode;                                      // insn 16
    if (*(uint8_t*)((uint8_t*)pLeft + 0x2d) == 0) {                  // insn 17-18 (jne 30 -> climb)
        void* pRight = *(void**)((uint8_t*)pLeft + 0x10);              // insn 19
        while (*(uint8_t*)((uint8_t*)pRight + 0x2d) == 0) {            // insn 20-21 (jne 26), 24-25 (je 22)
            pLeft = pRight;                                             // insn 22
            pRight = *(void**)((uint8_t*)pRight + 0x10);                // insn 23
        }
        *(void**)((uint8_t*)pThis + 0x8) = pLeft;                       // insn 26
        return;                                                        // insn 27-29
    }
    void* pUp = *(void**)((uint8_t*)pNode + 0x8);                      // insn 30
    while (*(uint8_t*)((uint8_t*)pUp + 0x2d) == 0                       // insn 31-32 (jne 40), 38-39 (je 33)
           && *(void**)((uint8_t*)pThis + 0x8) == *(void**)pUp) {      // insn 33-35 (jne 40)
        *(void**)((uint8_t*)pThis + 0x8) = pUp;                         // insn 36
        pUp = *(void**)((uint8_t*)pUp + 0x8);                           // insn 37
    }
    void* pMarked = *(void**)((uint8_t*)pThis + 0x8);                  // insn 40
    if (*(uint8_t*)((uint8_t*)pMarked + 0x2d) != 0) {                 // insn 41-42 (jne 13)
        g_fnPV_1418233c0(pUp);                                              // insn 13-15 (rcx = the parent)
        return;
    }
    *(void**)((uint8_t*)pThis + 0x8) = pUp;                            // insn 43
}
inline void SynIterPrev_141753cd0(void* pThis) {   // 0x141753cd0
    if (*(void**)pThis == nullptr)                                     // insn 2-5
        g_fnPV_1418233c0(pThis);                                            // insn 5 (rcx = the holder)
    void* pNode = *(void**)((uint8_t*)pThis + 0x8);                    // insn 6
    if (*(uint8_t*)((uint8_t*)pNode + 0x29) != 0) {                  // insn 7-8 (je 16)
        void* pRight = *(void**)((uint8_t*)pNode + 0x10);              // insn 9
        *(void**)((uint8_t*)pThis + 0x8) = pRight;                     // insn 10
        if (*(uint8_t*)((uint8_t*)pRight + 0x29) == 0)                 // insn 11-12 (je 44)
            return;                                                     // insn 44-46
        g_fnPV_1418233c0(pNode);                                            // insn 13-15 (rcx = the sentinel)
        return;
    }
    void* pLeft = *(void**)pNode;                                      // insn 16
    if (*(uint8_t*)((uint8_t*)pLeft + 0x29) == 0) {                  // insn 17-18 (jne 30 -> climb)
        void* pRight = *(void**)((uint8_t*)pLeft + 0x10);              // insn 19
        while (*(uint8_t*)((uint8_t*)pRight + 0x29) == 0) {            // insn 20-21 (jne 26), 24-25 (je 22)
            pLeft = pRight;                                             // insn 22
            pRight = *(void**)((uint8_t*)pRight + 0x10);                // insn 23
        }
        *(void**)((uint8_t*)pThis + 0x8) = pLeft;                       // insn 26
        return;                                                        // insn 27-29
    }
    void* pUp = *(void**)((uint8_t*)pNode + 0x8);                      // insn 30
    while (*(uint8_t*)((uint8_t*)pUp + 0x29) == 0                       // insn 31-32 (jne 40), 38-39 (je 33)
           && *(void**)((uint8_t*)pThis + 0x8) == *(void**)pUp) {      // insn 33-35 (jne 40)
        *(void**)((uint8_t*)pThis + 0x8) = pUp;                         // insn 36
        pUp = *(void**)((uint8_t*)pUp + 0x8);                           // insn 37
    }
    void* pMarked = *(void**)((uint8_t*)pThis + 0x8);                  // insn 40
    if (*(uint8_t*)((uint8_t*)pMarked + 0x29) != 0) {                 // insn 41-42 (jne 13)
        g_fnPV_1418233c0(pUp);                                              // insn 13-15 (rcx = the parent)
        return;
    }
    *(void**)((uint8_t*)pThis + 0x8) = pUp;                            // insn 43
}
inline void SynIterPrev_141753e20(void* pThis) {   // 0x141753e20
    if (*(void**)pThis == nullptr)                                     // insn 2-5
        g_fnPV_1418233c0(pThis);                                            // insn 5 (rcx = the holder)
    void* pNode = *(void**)((uint8_t*)pThis + 0x8);                    // insn 6
    if (*(uint8_t*)((uint8_t*)pNode + 0x59) != 0) {                  // insn 7-8 (je 16)
        void* pRight = *(void**)((uint8_t*)pNode + 0x10);              // insn 9
        *(void**)((uint8_t*)pThis + 0x8) = pRight;                     // insn 10
        if (*(uint8_t*)((uint8_t*)pRight + 0x59) == 0)                 // insn 11-12 (je 44)
            return;                                                     // insn 44-46
        g_fnPV_1418233c0(pNode);                                            // insn 13-15 (rcx = the sentinel)
        return;
    }
    void* pLeft = *(void**)pNode;                                      // insn 16
    if (*(uint8_t*)((uint8_t*)pLeft + 0x59) == 0) {                  // insn 17-18 (jne 30 -> climb)
        void* pRight = *(void**)((uint8_t*)pLeft + 0x10);              // insn 19
        while (*(uint8_t*)((uint8_t*)pRight + 0x59) == 0) {            // insn 20-21 (jne 26), 24-25 (je 22)
            pLeft = pRight;                                             // insn 22
            pRight = *(void**)((uint8_t*)pRight + 0x10);                // insn 23
        }
        *(void**)((uint8_t*)pThis + 0x8) = pLeft;                       // insn 26
        return;                                                        // insn 27-29
    }
    void* pUp = *(void**)((uint8_t*)pNode + 0x8);                      // insn 30
    while (*(uint8_t*)((uint8_t*)pUp + 0x59) == 0                       // insn 31-32 (jne 40), 38-39 (je 33)
           && *(void**)((uint8_t*)pThis + 0x8) == *(void**)pUp) {      // insn 33-35 (jne 40)
        *(void**)((uint8_t*)pThis + 0x8) = pUp;                         // insn 36
        pUp = *(void**)((uint8_t*)pUp + 0x8);                           // insn 37
    }
    void* pMarked = *(void**)((uint8_t*)pThis + 0x8);                  // insn 40
    if (*(uint8_t*)((uint8_t*)pMarked + 0x59) != 0) {                 // insn 41-42 (jne 13)
        g_fnPV_1418233c0(pUp);                                              // insn 13-15 (rcx = the parent)
        return;
    }
    *(void**)((uint8_t*)pThis + 0x8) = pUp;                            // insn 43
}
inline void SynIterPrev_141753ec0(void* pThis) {   // 0x141753ec0
    if (*(void**)pThis == nullptr)                                     // insn 2-5
        g_fnPV_1418233c0(pThis);                                            // insn 5 (rcx = the holder)
    void* pNode = *(void**)((uint8_t*)pThis + 0x8);                    // insn 6
    if (*(uint8_t*)((uint8_t*)pNode + 0x61) != 0) {                  // insn 7-8 (je 16)
        void* pRight = *(void**)((uint8_t*)pNode + 0x10);              // insn 9
        *(void**)((uint8_t*)pThis + 0x8) = pRight;                     // insn 10
        if (*(uint8_t*)((uint8_t*)pRight + 0x61) == 0)                 // insn 11-12 (je 44)
            return;                                                     // insn 44-46
        g_fnPV_1418233c0(pNode);                                            // insn 13-15 (rcx = the sentinel)
        return;
    }
    void* pLeft = *(void**)pNode;                                      // insn 16
    if (*(uint8_t*)((uint8_t*)pLeft + 0x61) == 0) {                  // insn 17-18 (jne 30 -> climb)
        void* pRight = *(void**)((uint8_t*)pLeft + 0x10);              // insn 19
        while (*(uint8_t*)((uint8_t*)pRight + 0x61) == 0) {            // insn 20-21 (jne 26), 24-25 (je 22)
            pLeft = pRight;                                             // insn 22
            pRight = *(void**)((uint8_t*)pRight + 0x10);                // insn 23
        }
        *(void**)((uint8_t*)pThis + 0x8) = pLeft;                       // insn 26
        return;                                                        // insn 27-29
    }
    void* pUp = *(void**)((uint8_t*)pNode + 0x8);                      // insn 30
    while (*(uint8_t*)((uint8_t*)pUp + 0x61) == 0                       // insn 31-32 (jne 40), 38-39 (je 33)
           && *(void**)((uint8_t*)pThis + 0x8) == *(void**)pUp) {      // insn 33-35 (jne 40)
        *(void**)((uint8_t*)pThis + 0x8) = pUp;                         // insn 36
        pUp = *(void**)((uint8_t*)pUp + 0x8);                           // insn 37
    }
    void* pMarked = *(void**)((uint8_t*)pThis + 0x8);                  // insn 40
    if (*(uint8_t*)((uint8_t*)pMarked + 0x61) != 0) {                 // insn 41-42 (jne 13)
        g_fnPV_1418233c0(pUp);                                              // insn 13-15 (rcx = the parent)
        return;
    }
    *(void**)((uint8_t*)pThis + 0x8) = pUp;                            // insn 43
}
inline void SynIterPrev_141753f60(void* pThis) {   // 0x141753f60
    if (*(void**)pThis == nullptr)                                     // insn 2-5
        g_fnPV_1418233c0(pThis);                                            // insn 5 (rcx = the holder)
    void* pNode = *(void**)((uint8_t*)pThis + 0x8);                    // insn 6
    if (*(uint8_t*)((uint8_t*)pNode + 0x29) != 0) {                  // insn 7-8 (je 16)
        void* pRight = *(void**)((uint8_t*)pNode + 0x10);              // insn 9
        *(void**)((uint8_t*)pThis + 0x8) = pRight;                     // insn 10
        if (*(uint8_t*)((uint8_t*)pRight + 0x29) == 0)                 // insn 11-12 (je 44)
            return;                                                     // insn 44-46
        g_fnPV_1418233c0(pNode);                                            // insn 13-15 (rcx = the sentinel)
        return;
    }
    void* pLeft = *(void**)pNode;                                      // insn 16
    if (*(uint8_t*)((uint8_t*)pLeft + 0x29) == 0) {                  // insn 17-18 (jne 30 -> climb)
        void* pRight = *(void**)((uint8_t*)pLeft + 0x10);              // insn 19
        while (*(uint8_t*)((uint8_t*)pRight + 0x29) == 0) {            // insn 20-21 (jne 26), 24-25 (je 22)
            pLeft = pRight;                                             // insn 22
            pRight = *(void**)((uint8_t*)pRight + 0x10);                // insn 23
        }
        *(void**)((uint8_t*)pThis + 0x8) = pLeft;                       // insn 26
        return;                                                        // insn 27-29
    }
    void* pUp = *(void**)((uint8_t*)pNode + 0x8);                      // insn 30
    while (*(uint8_t*)((uint8_t*)pUp + 0x29) == 0                       // insn 31-32 (jne 40), 38-39 (je 33)
           && *(void**)((uint8_t*)pThis + 0x8) == *(void**)pUp) {      // insn 33-35 (jne 40)
        *(void**)((uint8_t*)pThis + 0x8) = pUp;                         // insn 36
        pUp = *(void**)((uint8_t*)pUp + 0x8);                           // insn 37
    }
    void* pMarked = *(void**)((uint8_t*)pThis + 0x8);                  // insn 40
    if (*(uint8_t*)((uint8_t*)pMarked + 0x29) != 0) {                 // insn 41-42 (jne 13)
        g_fnPV_1418233c0(pUp);                                              // insn 13-15 (rcx = the parent)
        return;
    }
    *(void**)((uint8_t*)pThis + 0x8) = pUp;                            // insn 43
}
inline void SynIterPrev_1417541c0(void* pThis) {   // 0x1417541c0
    if (*(void**)pThis == nullptr)                                     // insn 2-5
        g_fnPV_1418233c0(pThis);                                            // insn 5 (rcx = the holder)
    void* pNode = *(void**)((uint8_t*)pThis + 0x8);                    // insn 6
    if (*(uint8_t*)((uint8_t*)pNode + 0x29) != 0) {                  // insn 7-8 (je 16)
        void* pRight = *(void**)((uint8_t*)pNode + 0x10);              // insn 9
        *(void**)((uint8_t*)pThis + 0x8) = pRight;                     // insn 10
        if (*(uint8_t*)((uint8_t*)pRight + 0x29) == 0)                 // insn 11-12 (je 44)
            return;                                                     // insn 44-46
        g_fnPV_1418233c0(pNode);                                            // insn 13-15 (rcx = the sentinel)
        return;
    }
    void* pLeft = *(void**)pNode;                                      // insn 16
    if (*(uint8_t*)((uint8_t*)pLeft + 0x29) == 0) {                  // insn 17-18 (jne 30 -> climb)
        void* pRight = *(void**)((uint8_t*)pLeft + 0x10);              // insn 19
        while (*(uint8_t*)((uint8_t*)pRight + 0x29) == 0) {            // insn 20-21 (jne 26), 24-25 (je 22)
            pLeft = pRight;                                             // insn 22
            pRight = *(void**)((uint8_t*)pRight + 0x10);                // insn 23
        }
        *(void**)((uint8_t*)pThis + 0x8) = pLeft;                       // insn 26
        return;                                                        // insn 27-29
    }
    void* pUp = *(void**)((uint8_t*)pNode + 0x8);                      // insn 30
    while (*(uint8_t*)((uint8_t*)pUp + 0x29) == 0                       // insn 31-32 (jne 40), 38-39 (je 33)
           && *(void**)((uint8_t*)pThis + 0x8) == *(void**)pUp) {      // insn 33-35 (jne 40)
        *(void**)((uint8_t*)pThis + 0x8) = pUp;                         // insn 36
        pUp = *(void**)((uint8_t*)pUp + 0x8);                           // insn 37
    }
    void* pMarked = *(void**)((uint8_t*)pThis + 0x8);                  // insn 40
    if (*(uint8_t*)((uint8_t*)pMarked + 0x29) != 0) {                 // insn 41-42 (jne 13)
        g_fnPV_1418233c0(pUp);                                              // insn 13-15 (rcx = the parent)
        return;
    }
    *(void**)((uint8_t*)pThis + 0x8) = pUp;                            // insn 43
}
inline void SynIterPrev_141754260(void* pThis) {   // 0x141754260
    if (*(void**)pThis == nullptr)                                     // insn 2-5
        g_fnPV_1418233c0(pThis);                                            // insn 5 (rcx = the holder)
    void* pNode = *(void**)((uint8_t*)pThis + 0x8);                    // insn 6
    if (*(uint8_t*)((uint8_t*)pNode + 0x69) != 0) {                  // insn 7-8 (je 16)
        void* pRight = *(void**)((uint8_t*)pNode + 0x10);              // insn 9
        *(void**)((uint8_t*)pThis + 0x8) = pRight;                     // insn 10
        if (*(uint8_t*)((uint8_t*)pRight + 0x69) == 0)                 // insn 11-12 (je 44)
            return;                                                     // insn 44-46
        g_fnPV_1418233c0(pNode);                                            // insn 13-15 (rcx = the sentinel)
        return;
    }
    void* pLeft = *(void**)pNode;                                      // insn 16
    if (*(uint8_t*)((uint8_t*)pLeft + 0x69) == 0) {                  // insn 17-18 (jne 30 -> climb)
        void* pRight = *(void**)((uint8_t*)pLeft + 0x10);              // insn 19
        while (*(uint8_t*)((uint8_t*)pRight + 0x69) == 0) {            // insn 20-21 (jne 26), 24-25 (je 22)
            pLeft = pRight;                                             // insn 22
            pRight = *(void**)((uint8_t*)pRight + 0x10);                // insn 23
        }
        *(void**)((uint8_t*)pThis + 0x8) = pLeft;                       // insn 26
        return;                                                        // insn 27-29
    }
    void* pUp = *(void**)((uint8_t*)pNode + 0x8);                      // insn 30
    while (*(uint8_t*)((uint8_t*)pUp + 0x69) == 0                       // insn 31-32 (jne 40), 38-39 (je 33)
           && *(void**)((uint8_t*)pThis + 0x8) == *(void**)pUp) {      // insn 33-35 (jne 40)
        *(void**)((uint8_t*)pThis + 0x8) = pUp;                         // insn 36
        pUp = *(void**)((uint8_t*)pUp + 0x8);                           // insn 37
    }
    void* pMarked = *(void**)((uint8_t*)pThis + 0x8);                  // insn 40
    if (*(uint8_t*)((uint8_t*)pMarked + 0x69) != 0) {                 // insn 41-42 (jne 13)
        g_fnPV_1418233c0(pUp);                                              // insn 13-15 (rcx = the parent)
        return;
    }
    *(void**)((uint8_t*)pThis + 0x8) = pUp;                            // insn 43
}
inline void SynIterPrev_141754300(void* pThis) {   // 0x141754300
    if (*(void**)pThis == nullptr)                                     // insn 2-5
        g_fnPV_1418233c0(pThis);                                            // insn 5 (rcx = the holder)
    void* pNode = *(void**)((uint8_t*)pThis + 0x8);                    // insn 6
    if (*(uint8_t*)((uint8_t*)pNode + 0x29) != 0) {                  // insn 7-8 (je 16)
        void* pRight = *(void**)((uint8_t*)pNode + 0x10);              // insn 9
        *(void**)((uint8_t*)pThis + 0x8) = pRight;                     // insn 10
        if (*(uint8_t*)((uint8_t*)pRight + 0x29) == 0)                 // insn 11-12 (je 44)
            return;                                                     // insn 44-46
        g_fnPV_1418233c0(pNode);                                            // insn 13-15 (rcx = the sentinel)
        return;
    }
    void* pLeft = *(void**)pNode;                                      // insn 16
    if (*(uint8_t*)((uint8_t*)pLeft + 0x29) == 0) {                  // insn 17-18 (jne 30 -> climb)
        void* pRight = *(void**)((uint8_t*)pLeft + 0x10);              // insn 19
        while (*(uint8_t*)((uint8_t*)pRight + 0x29) == 0) {            // insn 20-21 (jne 26), 24-25 (je 22)
            pLeft = pRight;                                             // insn 22
            pRight = *(void**)((uint8_t*)pRight + 0x10);                // insn 23
        }
        *(void**)((uint8_t*)pThis + 0x8) = pLeft;                       // insn 26
        return;                                                        // insn 27-29
    }
    void* pUp = *(void**)((uint8_t*)pNode + 0x8);                      // insn 30
    while (*(uint8_t*)((uint8_t*)pUp + 0x29) == 0                       // insn 31-32 (jne 40), 38-39 (je 33)
           && *(void**)((uint8_t*)pThis + 0x8) == *(void**)pUp) {      // insn 33-35 (jne 40)
        *(void**)((uint8_t*)pThis + 0x8) = pUp;                         // insn 36
        pUp = *(void**)((uint8_t*)pUp + 0x8);                           // insn 37
    }
    void* pMarked = *(void**)((uint8_t*)pThis + 0x8);                  // insn 40
    if (*(uint8_t*)((uint8_t*)pMarked + 0x29) != 0) {                 // insn 41-42 (jne 13)
        g_fnPV_1418233c0(pUp);                                              // insn 13-15 (rcx = the parent)
        return;
    }
    *(void**)((uint8_t*)pThis + 0x8) = pUp;                            // insn 43
}
inline void SynIterPrev_1417763c0(void* pThis) {   // 0x1417763c0
    if (*(void**)pThis == nullptr)                                     // insn 2-5
        g_fnPV_1418233c0(pThis);                                            // insn 5 (rcx = the holder)
    void* pNode = *(void**)((uint8_t*)pThis + 0x8);                    // insn 6
    if (*(uint8_t*)((uint8_t*)pNode + 0x39) != 0) {                  // insn 7-8 (je 16)
        void* pRight = *(void**)((uint8_t*)pNode + 0x10);              // insn 9
        *(void**)((uint8_t*)pThis + 0x8) = pRight;                     // insn 10
        if (*(uint8_t*)((uint8_t*)pRight + 0x39) == 0)                 // insn 11-12 (je 44)
            return;                                                     // insn 44-46
        g_fnPV_1418233c0(pNode);                                            // insn 13-15 (rcx = the sentinel)
        return;
    }
    void* pLeft = *(void**)pNode;                                      // insn 16
    if (*(uint8_t*)((uint8_t*)pLeft + 0x39) == 0) {                  // insn 17-18 (jne 30 -> climb)
        void* pRight = *(void**)((uint8_t*)pLeft + 0x10);              // insn 19
        while (*(uint8_t*)((uint8_t*)pRight + 0x39) == 0) {            // insn 20-21 (jne 26), 24-25 (je 22)
            pLeft = pRight;                                             // insn 22
            pRight = *(void**)((uint8_t*)pRight + 0x10);                // insn 23
        }
        *(void**)((uint8_t*)pThis + 0x8) = pLeft;                       // insn 26
        return;                                                        // insn 27-29
    }
    void* pUp = *(void**)((uint8_t*)pNode + 0x8);                      // insn 30
    while (*(uint8_t*)((uint8_t*)pUp + 0x39) == 0                       // insn 31-32 (jne 40), 38-39 (je 33)
           && *(void**)((uint8_t*)pThis + 0x8) == *(void**)pUp) {      // insn 33-35 (jne 40)
        *(void**)((uint8_t*)pThis + 0x8) = pUp;                         // insn 36
        pUp = *(void**)((uint8_t*)pUp + 0x8);                           // insn 37
    }
    void* pMarked = *(void**)((uint8_t*)pThis + 0x8);                  // insn 40
    if (*(uint8_t*)((uint8_t*)pMarked + 0x39) != 0) {                 // insn 41-42 (jne 13)
        g_fnPV_1418233c0(pUp);                                              // insn 13-15 (rcx = the parent)
        return;
    }
    *(void**)((uint8_t*)pThis + 0x8) = pUp;                            // insn 43
}
inline void SynIterPrev_14177a670(void* pThis) {   // 0x14177a670
    if (*(void**)pThis == nullptr)                                     // insn 2-5
        g_fnPV_1418233c0(pThis);                                            // insn 5 (rcx = the holder)
    void* pNode = *(void**)((uint8_t*)pThis + 0x8);                    // insn 6
    if (*(uint8_t*)((uint8_t*)pNode + 0x29) != 0) {                  // insn 7-8 (je 16)
        void* pRight = *(void**)((uint8_t*)pNode + 0x10);              // insn 9
        *(void**)((uint8_t*)pThis + 0x8) = pRight;                     // insn 10
        if (*(uint8_t*)((uint8_t*)pRight + 0x29) == 0)                 // insn 11-12 (je 44)
            return;                                                     // insn 44-46
        g_fnPV_1418233c0(pNode);                                            // insn 13-15 (rcx = the sentinel)
        return;
    }
    void* pLeft = *(void**)pNode;                                      // insn 16
    if (*(uint8_t*)((uint8_t*)pLeft + 0x29) == 0) {                  // insn 17-18 (jne 30 -> climb)
        void* pRight = *(void**)((uint8_t*)pLeft + 0x10);              // insn 19
        while (*(uint8_t*)((uint8_t*)pRight + 0x29) == 0) {            // insn 20-21 (jne 26), 24-25 (je 22)
            pLeft = pRight;                                             // insn 22
            pRight = *(void**)((uint8_t*)pRight + 0x10);                // insn 23
        }
        *(void**)((uint8_t*)pThis + 0x8) = pLeft;                       // insn 26
        return;                                                        // insn 27-29
    }
    void* pUp = *(void**)((uint8_t*)pNode + 0x8);                      // insn 30
    while (*(uint8_t*)((uint8_t*)pUp + 0x29) == 0                       // insn 31-32 (jne 40), 38-39 (je 33)
           && *(void**)((uint8_t*)pThis + 0x8) == *(void**)pUp) {      // insn 33-35 (jne 40)
        *(void**)((uint8_t*)pThis + 0x8) = pUp;                         // insn 36
        pUp = *(void**)((uint8_t*)pUp + 0x8);                           // insn 37
    }
    void* pMarked = *(void**)((uint8_t*)pThis + 0x8);                  // insn 40
    if (*(uint8_t*)((uint8_t*)pMarked + 0x29) != 0) {                 // insn 41-42 (jne 13)
        g_fnPV_1418233c0(pUp);                                              // insn 13-15 (rcx = the parent)
        return;
    }
    *(void**)((uint8_t*)pThis + 0x8) = pUp;                            // insn 43
}
inline void SynIterPrev_1417897d0(void* pThis) {   // 0x1417897d0
    if (*(void**)pThis == nullptr)                                     // insn 2-5
        g_fnPV_1418233c0(pThis);                                            // insn 5 (rcx = the holder)
    void* pNode = *(void**)((uint8_t*)pThis + 0x8);                    // insn 6
    if (*(uint8_t*)((uint8_t*)pNode + 0x29) != 0) {                  // insn 7-8 (je 16)
        void* pRight = *(void**)((uint8_t*)pNode + 0x10);              // insn 9
        *(void**)((uint8_t*)pThis + 0x8) = pRight;                     // insn 10
        if (*(uint8_t*)((uint8_t*)pRight + 0x29) == 0)                 // insn 11-12 (je 44)
            return;                                                     // insn 44-46
        g_fnPV_1418233c0(pNode);                                            // insn 13-15 (rcx = the sentinel)
        return;
    }
    void* pLeft = *(void**)pNode;                                      // insn 16
    if (*(uint8_t*)((uint8_t*)pLeft + 0x29) == 0) {                  // insn 17-18 (jne 30 -> climb)
        void* pRight = *(void**)((uint8_t*)pLeft + 0x10);              // insn 19
        while (*(uint8_t*)((uint8_t*)pRight + 0x29) == 0) {            // insn 20-21 (jne 26), 24-25 (je 22)
            pLeft = pRight;                                             // insn 22
            pRight = *(void**)((uint8_t*)pRight + 0x10);                // insn 23
        }
        *(void**)((uint8_t*)pThis + 0x8) = pLeft;                       // insn 26
        return;                                                        // insn 27-29
    }
    void* pUp = *(void**)((uint8_t*)pNode + 0x8);                      // insn 30
    while (*(uint8_t*)((uint8_t*)pUp + 0x29) == 0                       // insn 31-32 (jne 40), 38-39 (je 33)
           && *(void**)((uint8_t*)pThis + 0x8) == *(void**)pUp) {      // insn 33-35 (jne 40)
        *(void**)((uint8_t*)pThis + 0x8) = pUp;                         // insn 36
        pUp = *(void**)((uint8_t*)pUp + 0x8);                           // insn 37
    }
    void* pMarked = *(void**)((uint8_t*)pThis + 0x8);                  // insn 40
    if (*(uint8_t*)((uint8_t*)pMarked + 0x29) != 0) {                 // insn 41-42 (jne 13)
        g_fnPV_1418233c0(pUp);                                              // insn 13-15 (rcx = the parent)
        return;
    }
    *(void**)((uint8_t*)pThis + 0x8) = pUp;                            // insn 43
}
inline void SynIterPrev_141789870(void* pThis) {   // 0x141789870
    if (*(void**)pThis == nullptr)                                     // insn 2-5
        g_fnPV_1418233c0(pThis);                                            // insn 5 (rcx = the holder)
    void* pNode = *(void**)((uint8_t*)pThis + 0x8);                    // insn 6
    if (*(uint8_t*)((uint8_t*)pNode + 0x49) != 0) {                  // insn 7-8 (je 16)
        void* pRight = *(void**)((uint8_t*)pNode + 0x10);              // insn 9
        *(void**)((uint8_t*)pThis + 0x8) = pRight;                     // insn 10
        if (*(uint8_t*)((uint8_t*)pRight + 0x49) == 0)                 // insn 11-12 (je 44)
            return;                                                     // insn 44-46
        g_fnPV_1418233c0(pNode);                                            // insn 13-15 (rcx = the sentinel)
        return;
    }
    void* pLeft = *(void**)pNode;                                      // insn 16
    if (*(uint8_t*)((uint8_t*)pLeft + 0x49) == 0) {                  // insn 17-18 (jne 30 -> climb)
        void* pRight = *(void**)((uint8_t*)pLeft + 0x10);              // insn 19
        while (*(uint8_t*)((uint8_t*)pRight + 0x49) == 0) {            // insn 20-21 (jne 26), 24-25 (je 22)
            pLeft = pRight;                                             // insn 22
            pRight = *(void**)((uint8_t*)pRight + 0x10);                // insn 23
        }
        *(void**)((uint8_t*)pThis + 0x8) = pLeft;                       // insn 26
        return;                                                        // insn 27-29
    }
    void* pUp = *(void**)((uint8_t*)pNode + 0x8);                      // insn 30
    while (*(uint8_t*)((uint8_t*)pUp + 0x49) == 0                       // insn 31-32 (jne 40), 38-39 (je 33)
           && *(void**)((uint8_t*)pThis + 0x8) == *(void**)pUp) {      // insn 33-35 (jne 40)
        *(void**)((uint8_t*)pThis + 0x8) = pUp;                         // insn 36
        pUp = *(void**)((uint8_t*)pUp + 0x8);                           // insn 37
    }
    void* pMarked = *(void**)((uint8_t*)pThis + 0x8);                  // insn 40
    if (*(uint8_t*)((uint8_t*)pMarked + 0x49) != 0) {                 // insn 41-42 (jne 13)
        g_fnPV_1418233c0(pUp);                                              // insn 13-15 (rcx = the parent)
        return;
    }
    *(void**)((uint8_t*)pThis + 0x8) = pUp;                            // insn 43
}
inline void SynIterPrev_141790d70(void* pThis) {   // 0x141790d70
    if (*(void**)pThis == nullptr)                                     // insn 2-5
        g_fnPV_1418233c0(pThis);                                            // insn 5 (rcx = the holder)
    void* pNode = *(void**)((uint8_t*)pThis + 0x8);                    // insn 6
    if (*(uint8_t*)((uint8_t*)pNode + 0x21) != 0) {                  // insn 7-8 (je 16)
        void* pRight = *(void**)((uint8_t*)pNode + 0x10);              // insn 9
        *(void**)((uint8_t*)pThis + 0x8) = pRight;                     // insn 10
        if (*(uint8_t*)((uint8_t*)pRight + 0x21) == 0)                 // insn 11-12 (je 44)
            return;                                                     // insn 44-46
        g_fnPV_1418233c0(pNode);                                            // insn 13-15 (rcx = the sentinel)
        return;
    }
    void* pLeft = *(void**)pNode;                                      // insn 16
    if (*(uint8_t*)((uint8_t*)pLeft + 0x21) == 0) {                  // insn 17-18 (jne 30 -> climb)
        void* pRight = *(void**)((uint8_t*)pLeft + 0x10);              // insn 19
        while (*(uint8_t*)((uint8_t*)pRight + 0x21) == 0) {            // insn 20-21 (jne 26), 24-25 (je 22)
            pLeft = pRight;                                             // insn 22
            pRight = *(void**)((uint8_t*)pRight + 0x10);                // insn 23
        }
        *(void**)((uint8_t*)pThis + 0x8) = pLeft;                       // insn 26
        return;                                                        // insn 27-29
    }
    void* pUp = *(void**)((uint8_t*)pNode + 0x8);                      // insn 30
    while (*(uint8_t*)((uint8_t*)pUp + 0x21) == 0                       // insn 31-32 (jne 40), 38-39 (je 33)
           && *(void**)((uint8_t*)pThis + 0x8) == *(void**)pUp) {      // insn 33-35 (jne 40)
        *(void**)((uint8_t*)pThis + 0x8) = pUp;                         // insn 36
        pUp = *(void**)((uint8_t*)pUp + 0x8);                           // insn 37
    }
    void* pMarked = *(void**)((uint8_t*)pThis + 0x8);                  // insn 40
    if (*(uint8_t*)((uint8_t*)pMarked + 0x21) != 0) {                 // insn 41-42 (jne 13)
        g_fnPV_1418233c0(pUp);                                              // insn 13-15 (rcx = the parent)
        return;
    }
    *(void**)((uint8_t*)pThis + 0x8) = pUp;                            // insn 43
}
inline void SynIterPrev_1417924e0(void* pThis) {   // 0x1417924e0
    if (*(void**)pThis == nullptr)                                     // insn 2-5
        g_fnPV_1418233c0(pThis);                                            // insn 5 (rcx = the holder)
    void* pNode = *(void**)((uint8_t*)pThis + 0x8);                    // insn 6
    if (*(uint8_t*)((uint8_t*)pNode + 0x29) != 0) {                  // insn 7-8 (je 16)
        void* pRight = *(void**)((uint8_t*)pNode + 0x10);              // insn 9
        *(void**)((uint8_t*)pThis + 0x8) = pRight;                     // insn 10
        if (*(uint8_t*)((uint8_t*)pRight + 0x29) == 0)                 // insn 11-12 (je 44)
            return;                                                     // insn 44-46
        g_fnPV_1418233c0(pNode);                                            // insn 13-15 (rcx = the sentinel)
        return;
    }
    void* pLeft = *(void**)pNode;                                      // insn 16
    if (*(uint8_t*)((uint8_t*)pLeft + 0x29) == 0) {                  // insn 17-18 (jne 30 -> climb)
        void* pRight = *(void**)((uint8_t*)pLeft + 0x10);              // insn 19
        while (*(uint8_t*)((uint8_t*)pRight + 0x29) == 0) {            // insn 20-21 (jne 26), 24-25 (je 22)
            pLeft = pRight;                                             // insn 22
            pRight = *(void**)((uint8_t*)pRight + 0x10);                // insn 23
        }
        *(void**)((uint8_t*)pThis + 0x8) = pLeft;                       // insn 26
        return;                                                        // insn 27-29
    }
    void* pUp = *(void**)((uint8_t*)pNode + 0x8);                      // insn 30
    while (*(uint8_t*)((uint8_t*)pUp + 0x29) == 0                       // insn 31-32 (jne 40), 38-39 (je 33)
           && *(void**)((uint8_t*)pThis + 0x8) == *(void**)pUp) {      // insn 33-35 (jne 40)
        *(void**)((uint8_t*)pThis + 0x8) = pUp;                         // insn 36
        pUp = *(void**)((uint8_t*)pUp + 0x8);                           // insn 37
    }
    void* pMarked = *(void**)((uint8_t*)pThis + 0x8);                  // insn 40
    if (*(uint8_t*)((uint8_t*)pMarked + 0x29) != 0) {                 // insn 41-42 (jne 13)
        g_fnPV_1418233c0(pUp);                                              // insn 13-15 (rcx = the parent)
        return;
    }
    *(void**)((uint8_t*)pThis + 0x8) = pUp;                            // insn 43
}
inline void SynIterPrev_141792580(void* pThis) {   // 0x141792580
    if (*(void**)pThis == nullptr)                                     // insn 2-5
        g_fnPV_1418233c0(pThis);                                            // insn 5 (rcx = the holder)
    void* pNode = *(void**)((uint8_t*)pThis + 0x8);                    // insn 6
    if (*(uint8_t*)((uint8_t*)pNode + 0x61) != 0) {                  // insn 7-8 (je 16)
        void* pRight = *(void**)((uint8_t*)pNode + 0x10);              // insn 9
        *(void**)((uint8_t*)pThis + 0x8) = pRight;                     // insn 10
        if (*(uint8_t*)((uint8_t*)pRight + 0x61) == 0)                 // insn 11-12 (je 44)
            return;                                                     // insn 44-46
        g_fnPV_1418233c0(pNode);                                            // insn 13-15 (rcx = the sentinel)
        return;
    }
    void* pLeft = *(void**)pNode;                                      // insn 16
    if (*(uint8_t*)((uint8_t*)pLeft + 0x61) == 0) {                  // insn 17-18 (jne 30 -> climb)
        void* pRight = *(void**)((uint8_t*)pLeft + 0x10);              // insn 19
        while (*(uint8_t*)((uint8_t*)pRight + 0x61) == 0) {            // insn 20-21 (jne 26), 24-25 (je 22)
            pLeft = pRight;                                             // insn 22
            pRight = *(void**)((uint8_t*)pRight + 0x10);                // insn 23
        }
        *(void**)((uint8_t*)pThis + 0x8) = pLeft;                       // insn 26
        return;                                                        // insn 27-29
    }
    void* pUp = *(void**)((uint8_t*)pNode + 0x8);                      // insn 30
    while (*(uint8_t*)((uint8_t*)pUp + 0x61) == 0                       // insn 31-32 (jne 40), 38-39 (je 33)
           && *(void**)((uint8_t*)pThis + 0x8) == *(void**)pUp) {      // insn 33-35 (jne 40)
        *(void**)((uint8_t*)pThis + 0x8) = pUp;                         // insn 36
        pUp = *(void**)((uint8_t*)pUp + 0x8);                           // insn 37
    }
    void* pMarked = *(void**)((uint8_t*)pThis + 0x8);                  // insn 40
    if (*(uint8_t*)((uint8_t*)pMarked + 0x61) != 0) {                 // insn 41-42 (jne 13)
        g_fnPV_1418233c0(pUp);                                              // insn 13-15 (rcx = the parent)
        return;
    }
    *(void**)((uint8_t*)pThis + 0x8) = pUp;                            // insn 43
}
inline void SynIterPrev_1417a7160(void* pThis) {   // 0x1417a7160
    if (*(void**)pThis == nullptr)                                     // insn 2-5
        g_fnPV_1418233c0(pThis);                                            // insn 5 (rcx = the holder)
    void* pNode = *(void**)((uint8_t*)pThis + 0x8);                    // insn 6
    if (*(uint8_t*)((uint8_t*)pNode + 0x29) != 0) {                  // insn 7-8 (je 16)
        void* pRight = *(void**)((uint8_t*)pNode + 0x10);              // insn 9
        *(void**)((uint8_t*)pThis + 0x8) = pRight;                     // insn 10
        if (*(uint8_t*)((uint8_t*)pRight + 0x29) == 0)                 // insn 11-12 (je 44)
            return;                                                     // insn 44-46
        g_fnPV_1418233c0(pNode);                                            // insn 13-15 (rcx = the sentinel)
        return;
    }
    void* pLeft = *(void**)pNode;                                      // insn 16
    if (*(uint8_t*)((uint8_t*)pLeft + 0x29) == 0) {                  // insn 17-18 (jne 30 -> climb)
        void* pRight = *(void**)((uint8_t*)pLeft + 0x10);              // insn 19
        while (*(uint8_t*)((uint8_t*)pRight + 0x29) == 0) {            // insn 20-21 (jne 26), 24-25 (je 22)
            pLeft = pRight;                                             // insn 22
            pRight = *(void**)((uint8_t*)pRight + 0x10);                // insn 23
        }
        *(void**)((uint8_t*)pThis + 0x8) = pLeft;                       // insn 26
        return;                                                        // insn 27-29
    }
    void* pUp = *(void**)((uint8_t*)pNode + 0x8);                      // insn 30
    while (*(uint8_t*)((uint8_t*)pUp + 0x29) == 0                       // insn 31-32 (jne 40), 38-39 (je 33)
           && *(void**)((uint8_t*)pThis + 0x8) == *(void**)pUp) {      // insn 33-35 (jne 40)
        *(void**)((uint8_t*)pThis + 0x8) = pUp;                         // insn 36
        pUp = *(void**)((uint8_t*)pUp + 0x8);                           // insn 37
    }
    void* pMarked = *(void**)((uint8_t*)pThis + 0x8);                  // insn 40
    if (*(uint8_t*)((uint8_t*)pMarked + 0x29) != 0) {                 // insn 41-42 (jne 13)
        g_fnPV_1418233c0(pUp);                                              // insn 13-15 (rcx = the parent)
        return;
    }
    *(void**)((uint8_t*)pThis + 0x8) = pUp;                            // insn 43
}
inline void SynIterPrev_1417c74c0(void* pThis) {   // 0x1417c74c0
    if (*(void**)pThis == nullptr)                                     // insn 2-5
        g_fnPV_1418233c0(pThis);                                            // insn 5 (rcx = the holder)
    void* pNode = *(void**)((uint8_t*)pThis + 0x8);                    // insn 6
    if (*(uint8_t*)((uint8_t*)pNode + 0x21) != 0) {                  // insn 7-8 (je 16)
        void* pRight = *(void**)((uint8_t*)pNode + 0x10);              // insn 9
        *(void**)((uint8_t*)pThis + 0x8) = pRight;                     // insn 10
        if (*(uint8_t*)((uint8_t*)pRight + 0x21) == 0)                 // insn 11-12 (je 44)
            return;                                                     // insn 44-46
        g_fnPV_1418233c0(pNode);                                            // insn 13-15 (rcx = the sentinel)
        return;
    }
    void* pLeft = *(void**)pNode;                                      // insn 16
    if (*(uint8_t*)((uint8_t*)pLeft + 0x21) == 0) {                  // insn 17-18 (jne 30 -> climb)
        void* pRight = *(void**)((uint8_t*)pLeft + 0x10);              // insn 19
        while (*(uint8_t*)((uint8_t*)pRight + 0x21) == 0) {            // insn 20-21 (jne 26), 24-25 (je 22)
            pLeft = pRight;                                             // insn 22
            pRight = *(void**)((uint8_t*)pRight + 0x10);                // insn 23
        }
        *(void**)((uint8_t*)pThis + 0x8) = pLeft;                       // insn 26
        return;                                                        // insn 27-29
    }
    void* pUp = *(void**)((uint8_t*)pNode + 0x8);                      // insn 30
    while (*(uint8_t*)((uint8_t*)pUp + 0x21) == 0                       // insn 31-32 (jne 40), 38-39 (je 33)
           && *(void**)((uint8_t*)pThis + 0x8) == *(void**)pUp) {      // insn 33-35 (jne 40)
        *(void**)((uint8_t*)pThis + 0x8) = pUp;                         // insn 36
        pUp = *(void**)((uint8_t*)pUp + 0x8);                           // insn 37
    }
    void* pMarked = *(void**)((uint8_t*)pThis + 0x8);                  // insn 40
    if (*(uint8_t*)((uint8_t*)pMarked + 0x21) != 0) {                 // insn 41-42 (jne 13)
        g_fnPV_1418233c0(pUp);                                              // insn 13-15 (rcx = the parent)
        return;
    }
    *(void**)((uint8_t*)pThis + 0x8) = pUp;                            // insn 43
}

}  // namespace tq

#endif
