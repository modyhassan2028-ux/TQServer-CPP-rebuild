// synthunks_fd_family.h — generated: the ordered-tree lookup family.
// Every body is the transcription below with its own node marker offset; the shape, the key
// offset and the report seam are identical in all of them (verified per body).
#ifndef SYNDICATE_SYNTHUNKS_FD_FAMILY_H
#define SYNDICATE_SYNTHUNKS_FD_FAMILY_H
#include <cstdint>

namespace tq {
#define FD_Q(p, off) (*(void**)((uint8_t*)(p) + (off)))
#define FD_B(p, off) (*(uint8_t*)((uint8_t*)(p) + (off)))
extern void (*g_fnFD_1418233c0)(void*);

inline void* SynFind_14172b520(void* pThis, void* pOut, const uint32_t* pKey) {   // 0x14172b520
    void* rbx = FD_Q(pThis, 0x30);                             // insn 6   head
    void* r12 = (void*)(uintptr_t)pKey;                        // insn 7
    void* rbp = pOut;                                          // insn 8
    void* rax = FD_Q(rbx, 0x8);                                // insn 9   head->parent, the root
    void* rsi = pThis;                                         // insn 10
    if (FD_B(rax, 0x29) == 0) {                               // insn 11-12
        for (;;) {
            if (*(uint32_t*)((uint8_t*)rax + 0x18) >= *(const uint32_t*)r12) {   // insn 13-15
                rbx = rax;                                     // insn 18
                rax = FD_Q(rax, 0x00);                         // insn 19
            } else {
                rax = FD_Q(rax, 0x10);                         // insn 16
            }
            if (FD_B(rax, 0x29) != 0) break;                  // insn 20-21
        }
    }
    rax = FD_Q(rsi, 0x00);                                     // insn 22  this->f00
    void* rdi = FD_Q(rsi, 0x30);                               // insn 23  head
    void* aPair[2];
    aPair[1] = rbx;                                            // insn 24  the candidate
    aPair[0] = rax;                                            // insn 25  the container
    if (rax == nullptr)                                        // insn 26-27
        g_fnFD_1418233c0(pThis);                               // insn 30  (28-29 compare rax with itself)
    if (rbx != rdi && *(const uint32_t*)r12 >= *(uint32_t*)((uint8_t*)rbx + 0x18)) {   // insn 31-35
        /* the pair written at 24-25 is the answer */          // insn 36-37
    } else {
        aPair[1] = FD_Q(rsi, 0x30);                            // insn 38-40  end()
        aPair[0] = FD_Q(rsi, 0x00);                            // insn 41-42
    }
    FD_Q(rbp, 0x00) = aPair[0];                                // insn 43-47
    FD_Q(rbp, 0x08) = aPair[1];                                // insn 48-49
    return rbp;                                                // insn 50
}

inline void* SynFind_14172bc30(void* pThis, void* pOut, const uint32_t* pKey) {   // 0x14172bc30
    void* rbx = FD_Q(pThis, 0x30);                             // insn 6   head
    void* r12 = (void*)(uintptr_t)pKey;                        // insn 7
    void* rbp = pOut;                                          // insn 8
    void* rax = FD_Q(rbx, 0x8);                                // insn 9   head->parent, the root
    void* rsi = pThis;                                         // insn 10
    if (FD_B(rax, 0x49) == 0) {                               // insn 11-12
        for (;;) {
            if (*(uint32_t*)((uint8_t*)rax + 0x18) >= *(const uint32_t*)r12) {   // insn 13-15
                rbx = rax;                                     // insn 18
                rax = FD_Q(rax, 0x00);                         // insn 19
            } else {
                rax = FD_Q(rax, 0x10);                         // insn 16
            }
            if (FD_B(rax, 0x49) != 0) break;                  // insn 20-21
        }
    }
    rax = FD_Q(rsi, 0x00);                                     // insn 22  this->f00
    void* rdi = FD_Q(rsi, 0x30);                               // insn 23  head
    void* aPair[2];
    aPair[1] = rbx;                                            // insn 24  the candidate
    aPair[0] = rax;                                            // insn 25  the container
    if (rax == nullptr)                                        // insn 26-27
        g_fnFD_1418233c0(pThis);                               // insn 30  (28-29 compare rax with itself)
    if (rbx != rdi && *(const uint32_t*)r12 >= *(uint32_t*)((uint8_t*)rbx + 0x18)) {   // insn 31-35
        /* the pair written at 24-25 is the answer */          // insn 36-37
    } else {
        aPair[1] = FD_Q(rsi, 0x30);                            // insn 38-40  end()
        aPair[0] = FD_Q(rsi, 0x00);                            // insn 41-42
    }
    FD_Q(rbp, 0x00) = aPair[0];                                // insn 43-47
    FD_Q(rbp, 0x08) = aPair[1];                                // insn 48-49
    return rbp;                                                // insn 50
}

inline void* SynFind_14173d1e0(void* pThis, void* pOut, const uint32_t* pKey) {   // 0x14173d1e0
    void* rbx = FD_Q(pThis, 0x30);                             // insn 6   head
    void* r12 = (void*)(uintptr_t)pKey;                        // insn 7
    void* rbp = pOut;                                          // insn 8
    void* rax = FD_Q(rbx, 0x8);                                // insn 9   head->parent, the root
    void* rsi = pThis;                                         // insn 10
    if (FD_B(rax, 0x61) == 0) {                               // insn 11-12
        for (;;) {
            if (*(uint32_t*)((uint8_t*)rax + 0x18) >= *(const uint32_t*)r12) {   // insn 13-15
                rbx = rax;                                     // insn 18
                rax = FD_Q(rax, 0x00);                         // insn 19
            } else {
                rax = FD_Q(rax, 0x10);                         // insn 16
            }
            if (FD_B(rax, 0x61) != 0) break;                  // insn 20-21
        }
    }
    rax = FD_Q(rsi, 0x00);                                     // insn 22  this->f00
    void* rdi = FD_Q(rsi, 0x30);                               // insn 23  head
    void* aPair[2];
    aPair[1] = rbx;                                            // insn 24  the candidate
    aPair[0] = rax;                                            // insn 25  the container
    if (rax == nullptr)                                        // insn 26-27
        g_fnFD_1418233c0(pThis);                               // insn 30  (28-29 compare rax with itself)
    if (rbx != rdi && *(const uint32_t*)r12 >= *(uint32_t*)((uint8_t*)rbx + 0x18)) {   // insn 31-35
        /* the pair written at 24-25 is the answer */          // insn 36-37
    } else {
        aPair[1] = FD_Q(rsi, 0x30);                            // insn 38-40  end()
        aPair[0] = FD_Q(rsi, 0x00);                            // insn 41-42
    }
    FD_Q(rbp, 0x00) = aPair[0];                                // insn 43-47
    FD_Q(rbp, 0x08) = aPair[1];                                // insn 48-49
    return rbp;                                                // insn 50
}

inline void* SynFind_14173d330(void* pThis, void* pOut, const uint32_t* pKey) {   // 0x14173d330
    void* rbx = FD_Q(pThis, 0x30);                             // insn 6   head
    void* r12 = (void*)(uintptr_t)pKey;                        // insn 7
    void* rbp = pOut;                                          // insn 8
    void* rax = FD_Q(rbx, 0x8);                                // insn 9   head->parent, the root
    void* rsi = pThis;                                         // insn 10
    if (FD_B(rax, 0x21) == 0) {                               // insn 11-12
        for (;;) {
            if (*(uint32_t*)((uint8_t*)rax + 0x18) >= *(const uint32_t*)r12) {   // insn 13-15
                rbx = rax;                                     // insn 18
                rax = FD_Q(rax, 0x00);                         // insn 19
            } else {
                rax = FD_Q(rax, 0x10);                         // insn 16
            }
            if (FD_B(rax, 0x21) != 0) break;                  // insn 20-21
        }
    }
    rax = FD_Q(rsi, 0x00);                                     // insn 22  this->f00
    void* rdi = FD_Q(rsi, 0x30);                               // insn 23  head
    void* aPair[2];
    aPair[1] = rbx;                                            // insn 24  the candidate
    aPair[0] = rax;                                            // insn 25  the container
    if (rax == nullptr)                                        // insn 26-27
        g_fnFD_1418233c0(pThis);                               // insn 30  (28-29 compare rax with itself)
    if (rbx != rdi && *(const uint32_t*)r12 >= *(uint32_t*)((uint8_t*)rbx + 0x18)) {   // insn 31-35
        /* the pair written at 24-25 is the answer */          // insn 36-37
    } else {
        aPair[1] = FD_Q(rsi, 0x30);                            // insn 38-40  end()
        aPair[0] = FD_Q(rsi, 0x00);                            // insn 41-42
    }
    FD_Q(rbp, 0x00) = aPair[0];                                // insn 43-47
    FD_Q(rbp, 0x08) = aPair[1];                                // insn 48-49
    return rbp;                                                // insn 50
}

inline void* SynFind_141749980(void* pThis, void* pOut, const uint32_t* pKey) {   // 0x141749980
    void* rbx = FD_Q(pThis, 0x30);                             // insn 6   head
    void* r12 = (void*)(uintptr_t)pKey;                        // insn 7
    void* rbp = pOut;                                          // insn 8
    void* rax = FD_Q(rbx, 0x8);                                // insn 9   head->parent, the root
    void* rsi = pThis;                                         // insn 10
    if (FD_B(rax, 0x3d) == 0) {                               // insn 11-12
        for (;;) {
            if (*(uint32_t*)((uint8_t*)rax + 0x18) >= *(const uint32_t*)r12) {   // insn 13-15
                rbx = rax;                                     // insn 18
                rax = FD_Q(rax, 0x00);                         // insn 19
            } else {
                rax = FD_Q(rax, 0x10);                         // insn 16
            }
            if (FD_B(rax, 0x3d) != 0) break;                  // insn 20-21
        }
    }
    rax = FD_Q(rsi, 0x00);                                     // insn 22  this->f00
    void* rdi = FD_Q(rsi, 0x30);                               // insn 23  head
    void* aPair[2];
    aPair[1] = rbx;                                            // insn 24  the candidate
    aPair[0] = rax;                                            // insn 25  the container
    if (rax == nullptr)                                        // insn 26-27
        g_fnFD_1418233c0(pThis);                               // insn 30  (28-29 compare rax with itself)
    if (rbx != rdi && *(const uint32_t*)r12 >= *(uint32_t*)((uint8_t*)rbx + 0x18)) {   // insn 31-35
        /* the pair written at 24-25 is the answer */          // insn 36-37
    } else {
        aPair[1] = FD_Q(rsi, 0x30);                            // insn 38-40  end()
        aPair[0] = FD_Q(rsi, 0x00);                            // insn 41-42
    }
    FD_Q(rbp, 0x00) = aPair[0];                                // insn 43-47
    FD_Q(rbp, 0x08) = aPair[1];                                // insn 48-49
    return rbp;                                                // insn 50
}

inline void* SynFind_141749fc0(void* pThis, void* pOut, const uint32_t* pKey) {   // 0x141749fc0
    void* rbx = FD_Q(pThis, 0x30);                             // insn 6   head
    void* r12 = (void*)(uintptr_t)pKey;                        // insn 7
    void* rbp = pOut;                                          // insn 8
    void* rax = FD_Q(rbx, 0x8);                                // insn 9   head->parent, the root
    void* rsi = pThis;                                         // insn 10
    if (FD_B(rax, 0x29) == 0) {                               // insn 11-12
        for (;;) {
            if (*(uint32_t*)((uint8_t*)rax + 0x18) >= *(const uint32_t*)r12) {   // insn 13-15
                rbx = rax;                                     // insn 18
                rax = FD_Q(rax, 0x00);                         // insn 19
            } else {
                rax = FD_Q(rax, 0x10);                         // insn 16
            }
            if (FD_B(rax, 0x29) != 0) break;                  // insn 20-21
        }
    }
    rax = FD_Q(rsi, 0x00);                                     // insn 22  this->f00
    void* rdi = FD_Q(rsi, 0x30);                               // insn 23  head
    void* aPair[2];
    aPair[1] = rbx;                                            // insn 24  the candidate
    aPair[0] = rax;                                            // insn 25  the container
    if (rax == nullptr)                                        // insn 26-27
        g_fnFD_1418233c0(pThis);                               // insn 30  (28-29 compare rax with itself)
    if (rbx != rdi && *(const uint32_t*)r12 >= *(uint32_t*)((uint8_t*)rbx + 0x18)) {   // insn 31-35
        /* the pair written at 24-25 is the answer */          // insn 36-37
    } else {
        aPair[1] = FD_Q(rsi, 0x30);                            // insn 38-40  end()
        aPair[0] = FD_Q(rsi, 0x00);                            // insn 41-42
    }
    FD_Q(rbp, 0x00) = aPair[0];                                // insn 43-47
    FD_Q(rbp, 0x08) = aPair[1];                                // insn 48-49
    return rbp;                                                // insn 50
}

inline void* SynFind_1417600e0(void* pThis, void* pOut, const uint32_t* pKey) {   // 0x1417600e0
    void* rbx = FD_Q(pThis, 0x30);                             // insn 6   head
    void* r12 = (void*)(uintptr_t)pKey;                        // insn 7
    void* rbp = pOut;                                          // insn 8
    void* rax = FD_Q(rbx, 0x8);                                // insn 9   head->parent, the root
    void* rsi = pThis;                                         // insn 10
    if (FD_B(rax, 0x1d) == 0) {                               // insn 11-12
        for (;;) {
            if (*(uint32_t*)((uint8_t*)rax + 0x18) >= *(const uint32_t*)r12) {   // insn 13-15
                rbx = rax;                                     // insn 18
                rax = FD_Q(rax, 0x00);                         // insn 19
            } else {
                rax = FD_Q(rax, 0x10);                         // insn 16
            }
            if (FD_B(rax, 0x1d) != 0) break;                  // insn 20-21
        }
    }
    rax = FD_Q(rsi, 0x00);                                     // insn 22  this->f00
    void* rdi = FD_Q(rsi, 0x30);                               // insn 23  head
    void* aPair[2];
    aPair[1] = rbx;                                            // insn 24  the candidate
    aPair[0] = rax;                                            // insn 25  the container
    if (rax == nullptr)                                        // insn 26-27
        g_fnFD_1418233c0(pThis);                               // insn 30  (28-29 compare rax with itself)
    if (rbx != rdi && *(const uint32_t*)r12 >= *(uint32_t*)((uint8_t*)rbx + 0x18)) {   // insn 31-35
        /* the pair written at 24-25 is the answer */          // insn 36-37
    } else {
        aPair[1] = FD_Q(rsi, 0x30);                            // insn 38-40  end()
        aPair[0] = FD_Q(rsi, 0x00);                            // insn 41-42
    }
    FD_Q(rbp, 0x00) = aPair[0];                                // insn 43-47
    FD_Q(rbp, 0x08) = aPair[1];                                // insn 48-49
    return rbp;                                                // insn 50
}

inline void* SynFind_1417604a0(void* pThis, void* pOut, const uint32_t* pKey) {   // 0x1417604a0
    void* rbx = FD_Q(pThis, 0x30);                             // insn 6   head
    void* r12 = (void*)(uintptr_t)pKey;                        // insn 7
    void* rbp = pOut;                                          // insn 8
    void* rax = FD_Q(rbx, 0x8);                                // insn 9   head->parent, the root
    void* rsi = pThis;                                         // insn 10
    if (FD_B(rax, 0x29) == 0) {                               // insn 11-12
        for (;;) {
            if (*(uint32_t*)((uint8_t*)rax + 0x18) >= *(const uint32_t*)r12) {   // insn 13-15
                rbx = rax;                                     // insn 18
                rax = FD_Q(rax, 0x00);                         // insn 19
            } else {
                rax = FD_Q(rax, 0x10);                         // insn 16
            }
            if (FD_B(rax, 0x29) != 0) break;                  // insn 20-21
        }
    }
    rax = FD_Q(rsi, 0x00);                                     // insn 22  this->f00
    void* rdi = FD_Q(rsi, 0x30);                               // insn 23  head
    void* aPair[2];
    aPair[1] = rbx;                                            // insn 24  the candidate
    aPair[0] = rax;                                            // insn 25  the container
    if (rax == nullptr)                                        // insn 26-27
        g_fnFD_1418233c0(pThis);                               // insn 30  (28-29 compare rax with itself)
    if (rbx != rdi && *(const uint32_t*)r12 >= *(uint32_t*)((uint8_t*)rbx + 0x18)) {   // insn 31-35
        /* the pair written at 24-25 is the answer */          // insn 36-37
    } else {
        aPair[1] = FD_Q(rsi, 0x30);                            // insn 38-40  end()
        aPair[0] = FD_Q(rsi, 0x00);                            // insn 41-42
    }
    FD_Q(rbp, 0x00) = aPair[0];                                // insn 43-47
    FD_Q(rbp, 0x08) = aPair[1];                                // insn 48-49
    return rbp;                                                // insn 50
}

inline void* SynFind_141760950(void* pThis, void* pOut, const uint32_t* pKey) {   // 0x141760950
    void* rbx = FD_Q(pThis, 0x30);                             // insn 6   head
    void* r12 = (void*)(uintptr_t)pKey;                        // insn 7
    void* rbp = pOut;                                          // insn 8
    void* rax = FD_Q(rbx, 0x8);                                // insn 9   head->parent, the root
    void* rsi = pThis;                                         // insn 10
    if (FD_B(rax, 0x59) == 0) {                               // insn 11-12
        for (;;) {
            if (*(uint32_t*)((uint8_t*)rax + 0x18) >= *(const uint32_t*)r12) {   // insn 13-15
                rbx = rax;                                     // insn 18
                rax = FD_Q(rax, 0x00);                         // insn 19
            } else {
                rax = FD_Q(rax, 0x10);                         // insn 16
            }
            if (FD_B(rax, 0x59) != 0) break;                  // insn 20-21
        }
    }
    rax = FD_Q(rsi, 0x00);                                     // insn 22  this->f00
    void* rdi = FD_Q(rsi, 0x30);                               // insn 23  head
    void* aPair[2];
    aPair[1] = rbx;                                            // insn 24  the candidate
    aPair[0] = rax;                                            // insn 25  the container
    if (rax == nullptr)                                        // insn 26-27
        g_fnFD_1418233c0(pThis);                               // insn 30  (28-29 compare rax with itself)
    if (rbx != rdi && *(const uint32_t*)r12 >= *(uint32_t*)((uint8_t*)rbx + 0x18)) {   // insn 31-35
        /* the pair written at 24-25 is the answer */          // insn 36-37
    } else {
        aPair[1] = FD_Q(rsi, 0x30);                            // insn 38-40  end()
        aPair[0] = FD_Q(rsi, 0x00);                            // insn 41-42
    }
    FD_Q(rbp, 0x00) = aPair[0];                                // insn 43-47
    FD_Q(rbp, 0x08) = aPair[1];                                // insn 48-49
    return rbp;                                                // insn 50
}

inline void* SynFind_141760a20(void* pThis, void* pOut, const uint32_t* pKey) {   // 0x141760a20
    void* rbx = FD_Q(pThis, 0x30);                             // insn 6   head
    void* r12 = (void*)(uintptr_t)pKey;                        // insn 7
    void* rbp = pOut;                                          // insn 8
    void* rax = FD_Q(rbx, 0x8);                                // insn 9   head->parent, the root
    void* rsi = pThis;                                         // insn 10
    if (FD_B(rax, 0x29) == 0) {                               // insn 11-12
        for (;;) {
            if (*(uint32_t*)((uint8_t*)rax + 0x18) >= *(const uint32_t*)r12) {   // insn 13-15
                rbx = rax;                                     // insn 18
                rax = FD_Q(rax, 0x00);                         // insn 19
            } else {
                rax = FD_Q(rax, 0x10);                         // insn 16
            }
            if (FD_B(rax, 0x29) != 0) break;                  // insn 20-21
        }
    }
    rax = FD_Q(rsi, 0x00);                                     // insn 22  this->f00
    void* rdi = FD_Q(rsi, 0x30);                               // insn 23  head
    void* aPair[2];
    aPair[1] = rbx;                                            // insn 24  the candidate
    aPair[0] = rax;                                            // insn 25  the container
    if (rax == nullptr)                                        // insn 26-27
        g_fnFD_1418233c0(pThis);                               // insn 30  (28-29 compare rax with itself)
    if (rbx != rdi && *(const uint32_t*)r12 >= *(uint32_t*)((uint8_t*)rbx + 0x18)) {   // insn 31-35
        /* the pair written at 24-25 is the answer */          // insn 36-37
    } else {
        aPair[1] = FD_Q(rsi, 0x30);                            // insn 38-40  end()
        aPair[0] = FD_Q(rsi, 0x00);                            // insn 41-42
    }
    FD_Q(rbp, 0x00) = aPair[0];                                // insn 43-47
    FD_Q(rbp, 0x08) = aPair[1];                                // insn 48-49
    return rbp;                                                // insn 50
}

inline void* SynFind_141760af0(void* pThis, void* pOut, const uint32_t* pKey) {   // 0x141760af0
    void* rbx = FD_Q(pThis, 0x30);                             // insn 6   head
    void* r12 = (void*)(uintptr_t)pKey;                        // insn 7
    void* rbp = pOut;                                          // insn 8
    void* rax = FD_Q(rbx, 0x8);                                // insn 9   head->parent, the root
    void* rsi = pThis;                                         // insn 10
    if (FD_B(rax, 0x61) == 0) {                               // insn 11-12
        for (;;) {
            if (*(uint32_t*)((uint8_t*)rax + 0x18) >= *(const uint32_t*)r12) {   // insn 13-15
                rbx = rax;                                     // insn 18
                rax = FD_Q(rax, 0x00);                         // insn 19
            } else {
                rax = FD_Q(rax, 0x10);                         // insn 16
            }
            if (FD_B(rax, 0x61) != 0) break;                  // insn 20-21
        }
    }
    rax = FD_Q(rsi, 0x00);                                     // insn 22  this->f00
    void* rdi = FD_Q(rsi, 0x30);                               // insn 23  head
    void* aPair[2];
    aPair[1] = rbx;                                            // insn 24  the candidate
    aPair[0] = rax;                                            // insn 25  the container
    if (rax == nullptr)                                        // insn 26-27
        g_fnFD_1418233c0(pThis);                               // insn 30  (28-29 compare rax with itself)
    if (rbx != rdi && *(const uint32_t*)r12 >= *(uint32_t*)((uint8_t*)rbx + 0x18)) {   // insn 31-35
        /* the pair written at 24-25 is the answer */          // insn 36-37
    } else {
        aPair[1] = FD_Q(rsi, 0x30);                            // insn 38-40  end()
        aPair[0] = FD_Q(rsi, 0x00);                            // insn 41-42
    }
    FD_Q(rbp, 0x00) = aPair[0];                                // insn 43-47
    FD_Q(rbp, 0x08) = aPair[1];                                // insn 48-49
    return rbp;                                                // insn 50
}

inline void* SynFind_141760d70(void* pThis, void* pOut, const uint32_t* pKey) {   // 0x141760d70
    void* rbx = FD_Q(pThis, 0x30);                             // insn 6   head
    void* r12 = (void*)(uintptr_t)pKey;                        // insn 7
    void* rbp = pOut;                                          // insn 8
    void* rax = FD_Q(rbx, 0x8);                                // insn 9   head->parent, the root
    void* rsi = pThis;                                         // insn 10
    if (FD_B(rax, 0x29) == 0) {                               // insn 11-12
        for (;;) {
            if (*(uint32_t*)((uint8_t*)rax + 0x18) >= *(const uint32_t*)r12) {   // insn 13-15
                rbx = rax;                                     // insn 18
                rax = FD_Q(rax, 0x00);                         // insn 19
            } else {
                rax = FD_Q(rax, 0x10);                         // insn 16
            }
            if (FD_B(rax, 0x29) != 0) break;                  // insn 20-21
        }
    }
    rax = FD_Q(rsi, 0x00);                                     // insn 22  this->f00
    void* rdi = FD_Q(rsi, 0x30);                               // insn 23  head
    void* aPair[2];
    aPair[1] = rbx;                                            // insn 24  the candidate
    aPair[0] = rax;                                            // insn 25  the container
    if (rax == nullptr)                                        // insn 26-27
        g_fnFD_1418233c0(pThis);                               // insn 30  (28-29 compare rax with itself)
    if (rbx != rdi && *(const uint32_t*)r12 >= *(uint32_t*)((uint8_t*)rbx + 0x18)) {   // insn 31-35
        /* the pair written at 24-25 is the answer */          // insn 36-37
    } else {
        aPair[1] = FD_Q(rsi, 0x30);                            // insn 38-40  end()
        aPair[0] = FD_Q(rsi, 0x00);                            // insn 41-42
    }
    FD_Q(rbp, 0x00) = aPair[0];                                // insn 43-47
    FD_Q(rbp, 0x08) = aPair[1];                                // insn 48-49
    return rbp;                                                // insn 50
}

inline void* SynFind_141760e40(void* pThis, void* pOut, const uint32_t* pKey) {   // 0x141760e40
    void* rbx = FD_Q(pThis, 0x30);                             // insn 6   head
    void* r12 = (void*)(uintptr_t)pKey;                        // insn 7
    void* rbp = pOut;                                          // insn 8
    void* rax = FD_Q(rbx, 0x8);                                // insn 9   head->parent, the root
    void* rsi = pThis;                                         // insn 10
    if (FD_B(rax, 0x61) == 0) {                               // insn 11-12
        for (;;) {
            if (*(uint32_t*)((uint8_t*)rax + 0x18) >= *(const uint32_t*)r12) {   // insn 13-15
                rbx = rax;                                     // insn 18
                rax = FD_Q(rax, 0x00);                         // insn 19
            } else {
                rax = FD_Q(rax, 0x10);                         // insn 16
            }
            if (FD_B(rax, 0x61) != 0) break;                  // insn 20-21
        }
    }
    rax = FD_Q(rsi, 0x00);                                     // insn 22  this->f00
    void* rdi = FD_Q(rsi, 0x30);                               // insn 23  head
    void* aPair[2];
    aPair[1] = rbx;                                            // insn 24  the candidate
    aPair[0] = rax;                                            // insn 25  the container
    if (rax == nullptr)                                        // insn 26-27
        g_fnFD_1418233c0(pThis);                               // insn 30  (28-29 compare rax with itself)
    if (rbx != rdi && *(const uint32_t*)r12 >= *(uint32_t*)((uint8_t*)rbx + 0x18)) {   // insn 31-35
        /* the pair written at 24-25 is the answer */          // insn 36-37
    } else {
        aPair[1] = FD_Q(rsi, 0x30);                            // insn 38-40  end()
        aPair[0] = FD_Q(rsi, 0x00);                            // insn 41-42
    }
    FD_Q(rbp, 0x00) = aPair[0];                                // insn 43-47
    FD_Q(rbp, 0x08) = aPair[1];                                // insn 48-49
    return rbp;                                                // insn 50
}

inline void* SynFind_141760f10(void* pThis, void* pOut, const uint32_t* pKey) {   // 0x141760f10
    void* rbx = FD_Q(pThis, 0x30);                             // insn 6   head
    void* r12 = (void*)(uintptr_t)pKey;                        // insn 7
    void* rbp = pOut;                                          // insn 8
    void* rax = FD_Q(rbx, 0x8);                                // insn 9   head->parent, the root
    void* rsi = pThis;                                         // insn 10
    if (FD_B(rax, 0x29) == 0) {                               // insn 11-12
        for (;;) {
            if (*(uint32_t*)((uint8_t*)rax + 0x18) >= *(const uint32_t*)r12) {   // insn 13-15
                rbx = rax;                                     // insn 18
                rax = FD_Q(rax, 0x00);                         // insn 19
            } else {
                rax = FD_Q(rax, 0x10);                         // insn 16
            }
            if (FD_B(rax, 0x29) != 0) break;                  // insn 20-21
        }
    }
    rax = FD_Q(rsi, 0x00);                                     // insn 22  this->f00
    void* rdi = FD_Q(rsi, 0x30);                               // insn 23  head
    void* aPair[2];
    aPair[1] = rbx;                                            // insn 24  the candidate
    aPair[0] = rax;                                            // insn 25  the container
    if (rax == nullptr)                                        // insn 26-27
        g_fnFD_1418233c0(pThis);                               // insn 30  (28-29 compare rax with itself)
    if (rbx != rdi && *(const uint32_t*)r12 >= *(uint32_t*)((uint8_t*)rbx + 0x18)) {   // insn 31-35
        /* the pair written at 24-25 is the answer */          // insn 36-37
    } else {
        aPair[1] = FD_Q(rsi, 0x30);                            // insn 38-40  end()
        aPair[0] = FD_Q(rsi, 0x00);                            // insn 41-42
    }
    FD_Q(rbp, 0x00) = aPair[0];                                // insn 43-47
    FD_Q(rbp, 0x08) = aPair[1];                                // insn 48-49
    return rbp;                                                // insn 50
}

inline void* SynFind_1417618a0(void* pThis, void* pOut, const uint32_t* pKey) {   // 0x1417618a0
    void* rbx = FD_Q(pThis, 0x30);                             // insn 6   head
    void* r12 = (void*)(uintptr_t)pKey;                        // insn 7
    void* rbp = pOut;                                          // insn 8
    void* rax = FD_Q(rbx, 0x8);                                // insn 9   head->parent, the root
    void* rsi = pThis;                                         // insn 10
    if (FD_B(rax, 0x2d) == 0) {                               // insn 11-12
        for (;;) {
            if (*(uint32_t*)((uint8_t*)rax + 0x18) >= *(const uint32_t*)r12) {   // insn 13-15
                rbx = rax;                                     // insn 18
                rax = FD_Q(rax, 0x00);                         // insn 19
            } else {
                rax = FD_Q(rax, 0x10);                         // insn 16
            }
            if (FD_B(rax, 0x2d) != 0) break;                  // insn 20-21
        }
    }
    rax = FD_Q(rsi, 0x00);                                     // insn 22  this->f00
    void* rdi = FD_Q(rsi, 0x30);                               // insn 23  head
    void* aPair[2];
    aPair[1] = rbx;                                            // insn 24  the candidate
    aPair[0] = rax;                                            // insn 25  the container
    if (rax == nullptr)                                        // insn 26-27
        g_fnFD_1418233c0(pThis);                               // insn 30  (28-29 compare rax with itself)
    if (rbx != rdi && *(const uint32_t*)r12 >= *(uint32_t*)((uint8_t*)rbx + 0x18)) {   // insn 31-35
        /* the pair written at 24-25 is the answer */          // insn 36-37
    } else {
        aPair[1] = FD_Q(rsi, 0x30);                            // insn 38-40  end()
        aPair[0] = FD_Q(rsi, 0x00);                            // insn 41-42
    }
    FD_Q(rbp, 0x00) = aPair[0];                                // insn 43-47
    FD_Q(rbp, 0x08) = aPair[1];                                // insn 48-49
    return rbp;                                                // insn 50
}

inline void* SynFind_14177bbc0(void* pThis, void* pOut, const uint32_t* pKey) {   // 0x14177bbc0
    void* rbx = FD_Q(pThis, 0x30);                             // insn 6   head
    void* r12 = (void*)(uintptr_t)pKey;                        // insn 7
    void* rbp = pOut;                                          // insn 8
    void* rax = FD_Q(rbx, 0x8);                                // insn 9   head->parent, the root
    void* rsi = pThis;                                         // insn 10
    if (FD_B(rax, 0x29) == 0) {                               // insn 11-12
        for (;;) {
            if (*(uint32_t*)((uint8_t*)rax + 0x18) >= *(const uint32_t*)r12) {   // insn 13-15
                rbx = rax;                                     // insn 18
                rax = FD_Q(rax, 0x00);                         // insn 19
            } else {
                rax = FD_Q(rax, 0x10);                         // insn 16
            }
            if (FD_B(rax, 0x29) != 0) break;                  // insn 20-21
        }
    }
    rax = FD_Q(rsi, 0x00);                                     // insn 22  this->f00
    void* rdi = FD_Q(rsi, 0x30);                               // insn 23  head
    void* aPair[2];
    aPair[1] = rbx;                                            // insn 24  the candidate
    aPair[0] = rax;                                            // insn 25  the container
    if (rax == nullptr)                                        // insn 26-27
        g_fnFD_1418233c0(pThis);                               // insn 30  (28-29 compare rax with itself)
    if (rbx != rdi && *(const uint32_t*)r12 >= *(uint32_t*)((uint8_t*)rbx + 0x18)) {   // insn 31-35
        /* the pair written at 24-25 is the answer */          // insn 36-37
    } else {
        aPair[1] = FD_Q(rsi, 0x30);                            // insn 38-40  end()
        aPair[0] = FD_Q(rsi, 0x00);                            // insn 41-42
    }
    FD_Q(rbp, 0x00) = aPair[0];                                // insn 43-47
    FD_Q(rbp, 0x08) = aPair[1];                                // insn 48-49
    return rbp;                                                // insn 50
}

inline void* SynFind_14178b6c0(void* pThis, void* pOut, const uint32_t* pKey) {   // 0x14178b6c0
    void* rbx = FD_Q(pThis, 0x30);                             // insn 6   head
    void* r12 = (void*)(uintptr_t)pKey;                        // insn 7
    void* rbp = pOut;                                          // insn 8
    void* rax = FD_Q(rbx, 0x8);                                // insn 9   head->parent, the root
    void* rsi = pThis;                                         // insn 10
    if (FD_B(rax, 0x29) == 0) {                               // insn 11-12
        for (;;) {
            if (*(uint32_t*)((uint8_t*)rax + 0x18) >= *(const uint32_t*)r12) {   // insn 13-15
                rbx = rax;                                     // insn 18
                rax = FD_Q(rax, 0x00);                         // insn 19
            } else {
                rax = FD_Q(rax, 0x10);                         // insn 16
            }
            if (FD_B(rax, 0x29) != 0) break;                  // insn 20-21
        }
    }
    rax = FD_Q(rsi, 0x00);                                     // insn 22  this->f00
    void* rdi = FD_Q(rsi, 0x30);                               // insn 23  head
    void* aPair[2];
    aPair[1] = rbx;                                            // insn 24  the candidate
    aPair[0] = rax;                                            // insn 25  the container
    if (rax == nullptr)                                        // insn 26-27
        g_fnFD_1418233c0(pThis);                               // insn 30  (28-29 compare rax with itself)
    if (rbx != rdi && *(const uint32_t*)r12 >= *(uint32_t*)((uint8_t*)rbx + 0x18)) {   // insn 31-35
        /* the pair written at 24-25 is the answer */          // insn 36-37
    } else {
        aPair[1] = FD_Q(rsi, 0x30);                            // insn 38-40  end()
        aPair[0] = FD_Q(rsi, 0x00);                            // insn 41-42
    }
    FD_Q(rbp, 0x00) = aPair[0];                                // insn 43-47
    FD_Q(rbp, 0x08) = aPair[1];                                // insn 48-49
    return rbp;                                                // insn 50
}

inline void* SynFind_141796480(void* pThis, void* pOut, const uint32_t* pKey) {   // 0x141796480
    void* rbx = FD_Q(pThis, 0x30);                             // insn 6   head
    void* r12 = (void*)(uintptr_t)pKey;                        // insn 7
    void* rbp = pOut;                                          // insn 8
    void* rax = FD_Q(rbx, 0x8);                                // insn 9   head->parent, the root
    void* rsi = pThis;                                         // insn 10
    if (FD_B(rax, 0x1d) == 0) {                               // insn 11-12
        for (;;) {
            if (*(uint32_t*)((uint8_t*)rax + 0x18) >= *(const uint32_t*)r12) {   // insn 13-15
                rbx = rax;                                     // insn 18
                rax = FD_Q(rax, 0x00);                         // insn 19
            } else {
                rax = FD_Q(rax, 0x10);                         // insn 16
            }
            if (FD_B(rax, 0x1d) != 0) break;                  // insn 20-21
        }
    }
    rax = FD_Q(rsi, 0x00);                                     // insn 22  this->f00
    void* rdi = FD_Q(rsi, 0x30);                               // insn 23  head
    void* aPair[2];
    aPair[1] = rbx;                                            // insn 24  the candidate
    aPair[0] = rax;                                            // insn 25  the container
    if (rax == nullptr)                                        // insn 26-27
        g_fnFD_1418233c0(pThis);                               // insn 30  (28-29 compare rax with itself)
    if (rbx != rdi && *(const uint32_t*)r12 >= *(uint32_t*)((uint8_t*)rbx + 0x18)) {   // insn 31-35
        /* the pair written at 24-25 is the answer */          // insn 36-37
    } else {
        aPair[1] = FD_Q(rsi, 0x30);                            // insn 38-40  end()
        aPair[0] = FD_Q(rsi, 0x00);                            // insn 41-42
    }
    FD_Q(rbp, 0x00) = aPair[0];                                // insn 43-47
    FD_Q(rbp, 0x08) = aPair[1];                                // insn 48-49
    return rbp;                                                // insn 50
}

inline void* SynFind_141796550(void* pThis, void* pOut, const uint32_t* pKey) {   // 0x141796550
    void* rbx = FD_Q(pThis, 0x30);                             // insn 6   head
    void* r12 = (void*)(uintptr_t)pKey;                        // insn 7
    void* rbp = pOut;                                          // insn 8
    void* rax = FD_Q(rbx, 0x8);                                // insn 9   head->parent, the root
    void* rsi = pThis;                                         // insn 10
    if (FD_B(rax, 0x29) == 0) {                               // insn 11-12
        for (;;) {
            if (*(uint32_t*)((uint8_t*)rax + 0x18) >= *(const uint32_t*)r12) {   // insn 13-15
                rbx = rax;                                     // insn 18
                rax = FD_Q(rax, 0x00);                         // insn 19
            } else {
                rax = FD_Q(rax, 0x10);                         // insn 16
            }
            if (FD_B(rax, 0x29) != 0) break;                  // insn 20-21
        }
    }
    rax = FD_Q(rsi, 0x00);                                     // insn 22  this->f00
    void* rdi = FD_Q(rsi, 0x30);                               // insn 23  head
    void* aPair[2];
    aPair[1] = rbx;                                            // insn 24  the candidate
    aPair[0] = rax;                                            // insn 25  the container
    if (rax == nullptr)                                        // insn 26-27
        g_fnFD_1418233c0(pThis);                               // insn 30  (28-29 compare rax with itself)
    if (rbx != rdi && *(const uint32_t*)r12 >= *(uint32_t*)((uint8_t*)rbx + 0x18)) {   // insn 31-35
        /* the pair written at 24-25 is the answer */          // insn 36-37
    } else {
        aPair[1] = FD_Q(rsi, 0x30);                            // insn 38-40  end()
        aPair[0] = FD_Q(rsi, 0x00);                            // insn 41-42
    }
    FD_Q(rbp, 0x00) = aPair[0];                                // insn 43-47
    FD_Q(rbp, 0x08) = aPair[1];                                // insn 48-49
    return rbp;                                                // insn 50
}

inline void* SynFind_141796740(void* pThis, void* pOut, const uint32_t* pKey) {   // 0x141796740
    void* rbx = FD_Q(pThis, 0x30);                             // insn 6   head
    void* r12 = (void*)(uintptr_t)pKey;                        // insn 7
    void* rbp = pOut;                                          // insn 8
    void* rax = FD_Q(rbx, 0x8);                                // insn 9   head->parent, the root
    void* rsi = pThis;                                         // insn 10
    if (FD_B(rax, 0x61) == 0) {                               // insn 11-12
        for (;;) {
            if (*(uint32_t*)((uint8_t*)rax + 0x18) >= *(const uint32_t*)r12) {   // insn 13-15
                rbx = rax;                                     // insn 18
                rax = FD_Q(rax, 0x00);                         // insn 19
            } else {
                rax = FD_Q(rax, 0x10);                         // insn 16
            }
            if (FD_B(rax, 0x61) != 0) break;                  // insn 20-21
        }
    }
    rax = FD_Q(rsi, 0x00);                                     // insn 22  this->f00
    void* rdi = FD_Q(rsi, 0x30);                               // insn 23  head
    void* aPair[2];
    aPair[1] = rbx;                                            // insn 24  the candidate
    aPair[0] = rax;                                            // insn 25  the container
    if (rax == nullptr)                                        // insn 26-27
        g_fnFD_1418233c0(pThis);                               // insn 30  (28-29 compare rax with itself)
    if (rbx != rdi && *(const uint32_t*)r12 >= *(uint32_t*)((uint8_t*)rbx + 0x18)) {   // insn 31-35
        /* the pair written at 24-25 is the answer */          // insn 36-37
    } else {
        aPair[1] = FD_Q(rsi, 0x30);                            // insn 38-40  end()
        aPair[0] = FD_Q(rsi, 0x00);                            // insn 41-42
    }
    FD_Q(rbp, 0x00) = aPair[0];                                // insn 43-47
    FD_Q(rbp, 0x08) = aPair[1];                                // insn 48-49
    return rbp;                                                // insn 50
}

inline void* SynFind_141796810(void* pThis, void* pOut, const uint32_t* pKey) {   // 0x141796810
    void* rbx = FD_Q(pThis, 0x30);                             // insn 6   head
    void* r12 = (void*)(uintptr_t)pKey;                        // insn 7
    void* rbp = pOut;                                          // insn 8
    void* rax = FD_Q(rbx, 0x8);                                // insn 9   head->parent, the root
    void* rsi = pThis;                                         // insn 10
    if (FD_B(rax, 0x21) == 0) {                               // insn 11-12
        for (;;) {
            if (*(uint32_t*)((uint8_t*)rax + 0x18) >= *(const uint32_t*)r12) {   // insn 13-15
                rbx = rax;                                     // insn 18
                rax = FD_Q(rax, 0x00);                         // insn 19
            } else {
                rax = FD_Q(rax, 0x10);                         // insn 16
            }
            if (FD_B(rax, 0x21) != 0) break;                  // insn 20-21
        }
    }
    rax = FD_Q(rsi, 0x00);                                     // insn 22  this->f00
    void* rdi = FD_Q(rsi, 0x30);                               // insn 23  head
    void* aPair[2];
    aPair[1] = rbx;                                            // insn 24  the candidate
    aPair[0] = rax;                                            // insn 25  the container
    if (rax == nullptr)                                        // insn 26-27
        g_fnFD_1418233c0(pThis);                               // insn 30  (28-29 compare rax with itself)
    if (rbx != rdi && *(const uint32_t*)r12 >= *(uint32_t*)((uint8_t*)rbx + 0x18)) {   // insn 31-35
        /* the pair written at 24-25 is the answer */          // insn 36-37
    } else {
        aPair[1] = FD_Q(rsi, 0x30);                            // insn 38-40  end()
        aPair[0] = FD_Q(rsi, 0x00);                            // insn 41-42
    }
    FD_Q(rbp, 0x00) = aPair[0];                                // insn 43-47
    FD_Q(rbp, 0x08) = aPair[1];                                // insn 48-49
    return rbp;                                                // insn 50
}

inline void* SynFind_1417993b0(void* pThis, void* pOut, const uint32_t* pKey) {   // 0x1417993b0
    void* rbx = FD_Q(pThis, 0x30);                             // insn 6   head
    void* r12 = (void*)(uintptr_t)pKey;                        // insn 7
    void* rbp = pOut;                                          // insn 8
    void* rax = FD_Q(rbx, 0x8);                                // insn 9   head->parent, the root
    void* rsi = pThis;                                         // insn 10
    if (FD_B(rax, 0x61) == 0) {                               // insn 11-12
        for (;;) {
            if (*(uint32_t*)((uint8_t*)rax + 0x18) >= *(const uint32_t*)r12) {   // insn 13-15
                rbx = rax;                                     // insn 18
                rax = FD_Q(rax, 0x00);                         // insn 19
            } else {
                rax = FD_Q(rax, 0x10);                         // insn 16
            }
            if (FD_B(rax, 0x61) != 0) break;                  // insn 20-21
        }
    }
    rax = FD_Q(rsi, 0x00);                                     // insn 22  this->f00
    void* rdi = FD_Q(rsi, 0x30);                               // insn 23  head
    void* aPair[2];
    aPair[1] = rbx;                                            // insn 24  the candidate
    aPair[0] = rax;                                            // insn 25  the container
    if (rax == nullptr)                                        // insn 26-27
        g_fnFD_1418233c0(pThis);                               // insn 30  (28-29 compare rax with itself)
    if (rbx != rdi && *(const uint32_t*)r12 >= *(uint32_t*)((uint8_t*)rbx + 0x18)) {   // insn 31-35
        /* the pair written at 24-25 is the answer */          // insn 36-37
    } else {
        aPair[1] = FD_Q(rsi, 0x30);                            // insn 38-40  end()
        aPair[0] = FD_Q(rsi, 0x00);                            // insn 41-42
    }
    FD_Q(rbp, 0x00) = aPair[0];                                // insn 43-47
    FD_Q(rbp, 0x08) = aPair[1];                                // insn 48-49
    return rbp;                                                // insn 50
}

inline void* SynFind_141799770(void* pThis, void* pOut, const uint32_t* pKey) {   // 0x141799770
    void* rbx = FD_Q(pThis, 0x30);                             // insn 6   head
    void* r12 = (void*)(uintptr_t)pKey;                        // insn 7
    void* rbp = pOut;                                          // insn 8
    void* rax = FD_Q(rbx, 0x8);                                // insn 9   head->parent, the root
    void* rsi = pThis;                                         // insn 10
    if (FD_B(rax, 0x29) == 0) {                               // insn 11-12
        for (;;) {
            if (*(uint32_t*)((uint8_t*)rax + 0x18) >= *(const uint32_t*)r12) {   // insn 13-15
                rbx = rax;                                     // insn 18
                rax = FD_Q(rax, 0x00);                         // insn 19
            } else {
                rax = FD_Q(rax, 0x10);                         // insn 16
            }
            if (FD_B(rax, 0x29) != 0) break;                  // insn 20-21
        }
    }
    rax = FD_Q(rsi, 0x00);                                     // insn 22  this->f00
    void* rdi = FD_Q(rsi, 0x30);                               // insn 23  head
    void* aPair[2];
    aPair[1] = rbx;                                            // insn 24  the candidate
    aPair[0] = rax;                                            // insn 25  the container
    if (rax == nullptr)                                        // insn 26-27
        g_fnFD_1418233c0(pThis);                               // insn 30  (28-29 compare rax with itself)
    if (rbx != rdi && *(const uint32_t*)r12 >= *(uint32_t*)((uint8_t*)rbx + 0x18)) {   // insn 31-35
        /* the pair written at 24-25 is the answer */          // insn 36-37
    } else {
        aPair[1] = FD_Q(rsi, 0x30);                            // insn 38-40  end()
        aPair[0] = FD_Q(rsi, 0x00);                            // insn 41-42
    }
    FD_Q(rbp, 0x00) = aPair[0];                                // insn 43-47
    FD_Q(rbp, 0x08) = aPair[1];                                // insn 48-49
    return rbp;                                                // insn 50
}

inline void* SynFind_1417a8520(void* pThis, void* pOut, const uint32_t* pKey) {   // 0x1417a8520
    void* rbx = FD_Q(pThis, 0x30);                             // insn 6   head
    void* r12 = (void*)(uintptr_t)pKey;                        // insn 7
    void* rbp = pOut;                                          // insn 8
    void* rax = FD_Q(rbx, 0x8);                                // insn 9   head->parent, the root
    void* rsi = pThis;                                         // insn 10
    if (FD_B(rax, 0x29) == 0) {                               // insn 11-12
        for (;;) {
            if (*(uint32_t*)((uint8_t*)rax + 0x18) >= *(const uint32_t*)r12) {   // insn 13-15
                rbx = rax;                                     // insn 18
                rax = FD_Q(rax, 0x00);                         // insn 19
            } else {
                rax = FD_Q(rax, 0x10);                         // insn 16
            }
            if (FD_B(rax, 0x29) != 0) break;                  // insn 20-21
        }
    }
    rax = FD_Q(rsi, 0x00);                                     // insn 22  this->f00
    void* rdi = FD_Q(rsi, 0x30);                               // insn 23  head
    void* aPair[2];
    aPair[1] = rbx;                                            // insn 24  the candidate
    aPair[0] = rax;                                            // insn 25  the container
    if (rax == nullptr)                                        // insn 26-27
        g_fnFD_1418233c0(pThis);                               // insn 30  (28-29 compare rax with itself)
    if (rbx != rdi && *(const uint32_t*)r12 >= *(uint32_t*)((uint8_t*)rbx + 0x18)) {   // insn 31-35
        /* the pair written at 24-25 is the answer */          // insn 36-37
    } else {
        aPair[1] = FD_Q(rsi, 0x30);                            // insn 38-40  end()
        aPair[0] = FD_Q(rsi, 0x00);                            // insn 41-42
    }
    FD_Q(rbp, 0x00) = aPair[0];                                // insn 43-47
    FD_Q(rbp, 0x08) = aPair[1];                                // insn 48-49
    return rbp;                                                // insn 50
}

inline void* SynFind_1417cd6d0(void* pThis, void* pOut, const uint32_t* pKey) {   // 0x1417cd6d0
    void* rbx = FD_Q(pThis, 0x30);                             // insn 6   head
    void* r12 = (void*)(uintptr_t)pKey;                        // insn 7
    void* rbp = pOut;                                          // insn 8
    void* rax = FD_Q(rbx, 0x8);                                // insn 9   head->parent, the root
    void* rsi = pThis;                                         // insn 10
    if (FD_B(rax, 0x21) == 0) {                               // insn 11-12
        for (;;) {
            if (*(uint32_t*)((uint8_t*)rax + 0x18) >= *(const uint32_t*)r12) {   // insn 13-15
                rbx = rax;                                     // insn 18
                rax = FD_Q(rax, 0x00);                         // insn 19
            } else {
                rax = FD_Q(rax, 0x10);                         // insn 16
            }
            if (FD_B(rax, 0x21) != 0) break;                  // insn 20-21
        }
    }
    rax = FD_Q(rsi, 0x00);                                     // insn 22  this->f00
    void* rdi = FD_Q(rsi, 0x30);                               // insn 23  head
    void* aPair[2];
    aPair[1] = rbx;                                            // insn 24  the candidate
    aPair[0] = rax;                                            // insn 25  the container
    if (rax == nullptr)                                        // insn 26-27
        g_fnFD_1418233c0(pThis);                               // insn 30  (28-29 compare rax with itself)
    if (rbx != rdi && *(const uint32_t*)r12 >= *(uint32_t*)((uint8_t*)rbx + 0x18)) {   // insn 31-35
        /* the pair written at 24-25 is the answer */          // insn 36-37
    } else {
        aPair[1] = FD_Q(rsi, 0x30);                            // insn 38-40  end()
        aPair[0] = FD_Q(rsi, 0x00);                            // insn 41-42
    }
    FD_Q(rbp, 0x00) = aPair[0];                                // insn 43-47
    FD_Q(rbp, 0x08) = aPair[1];                                // insn 48-49
    return rbp;                                                // insn 50
}

#undef FD_Q
#undef FD_B
}  // namespace tq

#endif