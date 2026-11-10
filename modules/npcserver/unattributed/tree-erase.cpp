// Transcribed from NpcServer.exe; see tree-erase.h.
#include <stdexcept>
#include "modules/npcserver/unattributed/tree-erase.h"
#include "modules/npcserver/unattributed/tree-links.h"

namespace tq {

static void ThrowOutOfRange(const char* pszMessage) { throw std::out_of_range(pszMessage); }
void (*g_pfnNpcThrowOutOfRange)(const char* pszMessage) = &ThrowOutOfRange;

// 0x140021fe0 - the successor step of the second tree flavour
void FUN_140021fe0(long long* pIter) {
    if (pIter[0] == 0) {
        return;                                     // reported through _invalid_parameter_noinfo in the image
    }
    long long nNode = pIter[1];
    if (*(char*)(nNode + 0x29) == '\0') {
        long long nRight = *(long long*)(nNode + 0x10);
        if (*(char*)(nRight + 0x29) != '\0') {
            nNode = *(long long*)(nNode + 8);
            char nFlag = *(char*)(nNode + 0x29);
            while ((nFlag == '\0') && (pIter[1] == *(long long*)(nNode + 0x10))) {
                pIter[1] = nNode;
                nNode = *(long long*)(nNode + 8);
                nFlag = *(char*)(nNode + 0x29);
            }
            pIter[1] = nNode;
            return;
        }
        char nFlag = *(char*)(*(long long*)(nRight + 0x00) + 0x29);
        long long nWalk = *(long long*)(nRight + 0x00);
        while (nFlag == '\0') {
            nFlag = *(char*)(*(long long*)(nWalk + 0x00) + 0x29);
            nRight = nWalk;
            nWalk = *(long long*)(nWalk + 0x00);
        }
        pIter[1] = nRight;
        return;
    }
    return;
}

// 0x140021d50 - rotate left over pNode
void FUN_140021d50(long long pTree, long long pNode) {
    long long nRight = *(long long*)(pNode + 0x10);
    *(long long*)(pNode + 0x10) = *(long long*)(nRight + 0x00);
    if (*(char*)(*(long long*)(nRight + 0x00) + 0x29) == '\0') {
        *(long long*)(*(long long*)(nRight + 0x00) + 8) = pNode;
    }
    *(long long*)(nRight + 8) = *(long long*)(pNode + 8);
    if (pNode == *(long long*)(*(long long*)(pTree + 0x30) + 8)) {
        *(long long*)(*(long long*)(pTree + 0x30) + 8) = nRight;
        *(long long*)(nRight + 0x00) = pNode;
        *(long long*)(pNode + 8) = nRight;
        return;
    }
    long long nParent = *(long long*)(pNode + 8);
    if (pNode == *(long long*)(nParent + 0x00)) {
        *(long long*)(nParent + 0x00) = nRight;
        *(long long*)(nRight + 0x00) = pNode;
        *(long long*)(pNode + 8) = nRight;
        return;
    }
    *(long long*)(nParent + 0x10) = nRight;
    *(long long*)(nRight + 0x00) = pNode;
    *(long long*)(pNode + 8) = nRight;
    return;
}

// 0x140021db0 - rotate right over pNode
void FUN_140021db0(long long pTree, long long* pNode) {
    long long nLeft = *(long long*)((long long)pNode + 0x00);
    *(long long*)((long long)pNode + 0x00) = *(long long*)(nLeft + 0x10);
    if (*(char*)(*(long long*)(nLeft + 0x10) + 0x29) == '\0') {
        *(long long*)(*(long long*)(nLeft + 0x10) + 8) = (long long)pNode;
    }
    *(long long*)(nLeft + 8) = *(long long*)((long long)pNode + 8);
    if (pNode == *(long long**)(*(long long*)(pTree + 0x30) + 8)) {
        *(long long*)(*(long long*)(pTree + 0x30) + 8) = nLeft;
        *(long long*)(nLeft + 0x10) = (long long)pNode;
        *(long long*)((long long)pNode + 8) = nLeft;
        return;
    }
    long long nParent = *(long long*)((long long)pNode + 8);
    if (pNode == (long long*)*(long long*)(nParent + 0x10)) {
        *(long long*)(nParent + 0x10) = nLeft;
        *(long long*)(nLeft + 0x10) = (long long)pNode;
        *(long long*)((long long)pNode + 8) = nLeft;
        return;
    }
    *(long long*)(nParent + 0x00) = nLeft;
    *(long long*)(nLeft + 0x10) = (long long)pNode;
    *(long long*)((long long)pNode + 8) = nLeft;
    return;
}

// 0x140022e50 - erase the node the iterator names, then answer the iterator that follows it
long long* FUN_140022e50(long long* pTree, long long* pOut, long long* pIter) {
    long long* n2 = (long long*)pIter[1];
    if (*(char*)((long long)n2 + 0x29) != '\0') {
        g_pfnNpcThrowOutOfRange("invalid map/set<T> iterator");
    }
    FUN_140021f50(pIter);
    long long* v8 = (long long*)n2[0];
    long long* v9 = 0;
    long long* v7 = 0;
    if (*(char*)((long long)v8 + 0x29) == '\0') {
        v9 = v8;
        if (*(char*)(n2[2] + 0x29) == '\0') {
            v7 = (long long*)pIter[1];
            v9 = (long long*)v7[2];
            if (v7 != n2) {
                v8[1] = (long long)v7;
                *v7 = n2[0];
                v8 = v7;
                if (v7 != (long long*)n2[2]) {
                    v8 = (long long*)v7[1];
                    if (*(char*)((long long)v9 + 0x29) == '\0') {
                        v9[1] = (long long)v8;
                    }
                    *v8 = (long long)v9;
                    v7[2] = n2[2];
                    *(long long**)(n2[2] + 8) = v7;
                }
                if (*(long long**)(pTree[6] + 8) == n2) {
                    *(long long**)(pTree[6] + 8) = v7;
                } else {
                    long long* u4 = (long long*)n2[1];
                    if ((long long*)*u4 == n2) {
                        *u4 = (long long)v7;
                    } else {
                        u4[2] = (long long)v7;
                    }
                }
                v7[1] = n2[1];
                long long* v3 = n2 + 5;
                long long* pColour = v7 + 5;
                if (pColour != v3) {
                    long long l5 = *pColour;
                    *(char*)pColour = (char)*v3;
                    *(char*)v3 = (char)l5;
                }
                goto LAB_14002303c;
            }
        }
    } else {
        v9 = (long long*)n2[2];
    }
    v8 = (long long*)n2[1];
    if (*(char*)((long long)v9 + 0x29) == '\0') {
        v9[1] = (long long)v8;
    }
    if (*(long long**)(pTree[6] + 8) == n2) {
        *(long long**)(pTree[6] + 8) = v9;
    } else if ((long long*)*v8 == n2) {
        *v8 = (long long)v9;
    } else {
        v8[2] = (long long)v9;
    }
    if (*(long long**)pTree[6] == n2) {
        v7 = v8;
        if (*(char*)((long long)v9 + 0x29) == '\0') {
            char c1 = *(char*)(*v9 + 0x29);
            long long* v3 = (long long*)*v9;
            v7 = v9;
            for (;;) {
                long long* v6 = v3;
                if (c1 != '\0') break;
                v3 = (long long*)*v6;
                c1 = *(char*)((long long)v3 + 0x29);
                v7 = v6;
            }
        }
        *(long long**)pTree[6] = v7;
    }
    if (*(long long**)(pTree[6] + 0x10) == n2) {
        v7 = v8;
        if (*(char*)((long long)v9 + 0x29) == '\0') {
            char c1 = *(char*)(v9[2] + 0x29);
            long long* v3 = (long long*)v9[2];
            v7 = v9;
            for (;;) {
                long long* v6 = v3;
                if (c1 != '\0') break;
                v3 = (long long*)v6[2];
                c1 = *(char*)((long long)v3 + 0x29);
                v7 = v6;
            }
        }
        *(long long**)(pTree[6] + 0x10) = v7;
    }
LAB_14002303c:
    if ((char)n2[5] == '\x01') {
        if (v9 != *(long long**)(pTree[6] + 8)) {
            do {
                v7 = v8;
                if ((char)v9[5] != '\x01') break;
                v8 = (long long*)*v7;
                if (v9 == v8) {
                    v8 = (long long*)v7[2];
                    if ((char)v8[5] == '\0') {
                        *(char*)(v8 + 5) = 1;
                        *(char*)(v7 + 5) = 0;
                        FUN_140021e60((long long)pTree, (long long)v7);
                        v8 = (long long*)v7[2];
                    }
                    if (*(char*)((long long)v8 + 0x29) == '\0') {
                        if ((*(char*)(*v8 + 0x28) != '\x01') || (*(char*)(v8[2] + 0x28) != '\x01')) {
                            if (*(char*)(v8[2] + 0x28) == '\x01') {
                                *(char*)(*v8 + 0x28) = 1;
                                *(char*)(v8 + 5) = 0;
                                FUN_140021ec0((long long)pTree, v8);
                                v8 = (long long*)v7[2];
                            }
                            *(char*)(v8 + 5) = (char)v7[5];
                            *(char*)(v7 + 5) = 1;
                            *(char*)(v8[2] + 0x28) = 1;
                            FUN_140021e60((long long)pTree, (long long)v7);
                            break;
                        }
                        *(char*)(v8 + 5) = 0;
                    }
                } else {
                    if ((char)v8[5] == '\0') {
                        *(char*)(v8 + 5) = 1;
                        *(char*)(v7 + 5) = 0;
                        FUN_140021ec0((long long)pTree, v7);
                        v8 = (long long*)*v7;
                    }
                    if (*(char*)((long long)v8 + 0x29) == '\0') {
                        if ((*(char*)(v8[2] + 0x28) != '\x01') || (*(char*)(*v8 + 0x28) != '\x01')) {
                            if (*(char*)(*v8 + 0x28) == '\x01') {
                                *(char*)(v8[2] + 0x28) = 1;
                                *(char*)(v8 + 5) = 0;
                                FUN_140021e60((long long)pTree, (long long)v8);
                                v8 = (long long*)*v7;
                            }
                            *(char*)(v8 + 5) = (char)v7[5];
                            *(char*)(v7 + 5) = 1;
                            *(char*)(*v8 + 0x28) = 1;
                            FUN_140021ec0((long long)pTree, v7);
                            break;
                        }
                        *(char*)(v8 + 5) = 0;
                    }
                }
                v8 = (long long*)v7[1];
                v9 = v7;
            } while (v7 != *(long long**)(pTree[6] + 8));
        }
        *(char*)(v9 + 5) = 1;
    }
    g_pfnNpcOperatorDelete(n2);
    if (pTree[7] != 0) {
        pTree[7] = pTree[7] + -1;
    }
    long long l5 = pIter[1];
    *pOut = *pTree;
    pOut[1] = l5;
    return pOut;
}

// 0x140023400 - the same body with its own successor and rotations behind it
long long* FUN_140023400(long long* pTree, long long* pOut, long long* pIter) {
    long long* n2 = (long long*)pIter[1];
    if (*(char*)((long long)n2 + 0x29) != '\0') {
        g_pfnNpcThrowOutOfRange("invalid map/set<T> iterator");
    }
    FUN_140021fe0(pIter);
    long long* v8 = (long long*)n2[0];
    long long* v9 = 0;
    long long* v7 = 0;
    if (*(char*)((long long)v8 + 0x29) == '\0') {
        v9 = v8;
        if (*(char*)(n2[2] + 0x29) == '\0') {
            v7 = (long long*)pIter[1];
            v9 = (long long*)v7[2];
            if (v7 != n2) {
                v8[1] = (long long)v7;
                *v7 = n2[0];
                v8 = v7;
                if (v7 != (long long*)n2[2]) {
                    v8 = (long long*)v7[1];
                    if (*(char*)((long long)v9 + 0x29) == '\0') {
                        v9[1] = (long long)v8;
                    }
                    *v8 = (long long)v9;
                    v7[2] = n2[2];
                    *(long long**)(n2[2] + 8) = v7;
                }
                if (*(long long**)(pTree[6] + 8) == n2) {
                    *(long long**)(pTree[6] + 8) = v7;
                } else {
                    long long* u4 = (long long*)n2[1];
                    if ((long long*)*u4 == n2) {
                        *u4 = (long long)v7;
                    } else {
                        u4[2] = (long long)v7;
                    }
                }
                v7[1] = n2[1];
                long long* v3 = n2 + 5;
                long long* pColour = v7 + 5;
                if (pColour != v3) {
                    long long l5 = *pColour;
                    *(char*)pColour = (char)*v3;
                    *(char*)v3 = (char)l5;
                }
                goto LAB_1400235ec;
            }
        }
    } else {
        v9 = (long long*)n2[2];
    }
    v8 = (long long*)n2[1];
    if (*(char*)((long long)v9 + 0x29) == '\0') {
        v9[1] = (long long)v8;
    }
    if (*(long long**)(pTree[6] + 8) == n2) {
        *(long long**)(pTree[6] + 8) = v9;
    } else if ((long long*)*v8 == n2) {
        *v8 = (long long)v9;
    } else {
        v8[2] = (long long)v9;
    }
    if (*(long long**)pTree[6] == n2) {
        v7 = v8;
        if (*(char*)((long long)v9 + 0x29) == '\0') {
            char c1 = *(char*)(*v9 + 0x29);
            long long* v3 = (long long*)*v9;
            v7 = v9;
            for (;;) {
                long long* v6 = v3;
                if (c1 != '\0') break;
                v3 = (long long*)*v6;
                c1 = *(char*)((long long)v3 + 0x29);
                v7 = v6;
            }
        }
        *(long long**)pTree[6] = v7;
    }
    if (*(long long**)(pTree[6] + 0x10) == n2) {
        v7 = v8;
        if (*(char*)((long long)v9 + 0x29) == '\0') {
            char c1 = *(char*)(v9[2] + 0x29);
            long long* v3 = (long long*)v9[2];
            v7 = v9;
            for (;;) {
                long long* v6 = v3;
                if (c1 != '\0') break;
                v3 = (long long*)v6[2];
                c1 = *(char*)((long long)v3 + 0x29);
                v7 = v6;
            }
        }
        *(long long**)(pTree[6] + 0x10) = v7;
    }
LAB_1400235ec:
    if ((char)n2[5] == '\x01') {
        if (v9 != *(long long**)(pTree[6] + 8)) {
            do {
                v7 = v8;
                if ((char)v9[5] != '\x01') break;
                v8 = (long long*)*v7;
                if (v9 == v8) {
                    v8 = (long long*)v7[2];
                    if ((char)v8[5] == '\0') {
                        *(char*)(v8 + 5) = 1;
                        *(char*)(v7 + 5) = 0;
                        FUN_140021d50((long long)pTree, (long long)v7);
                        v8 = (long long*)v7[2];
                    }
                    if (*(char*)((long long)v8 + 0x29) == '\0') {
                        if ((*(char*)(*v8 + 0x28) != '\x01') || (*(char*)(v8[2] + 0x28) != '\x01')) {
                            if (*(char*)(v8[2] + 0x28) == '\x01') {
                                *(char*)(*v8 + 0x28) = 1;
                                *(char*)(v8 + 5) = 0;
                                FUN_140021db0((long long)pTree, v8);
                                v8 = (long long*)v7[2];
                            }
                            *(char*)(v8 + 5) = (char)v7[5];
                            *(char*)(v7 + 5) = 1;
                            *(char*)(v8[2] + 0x28) = 1;
                            FUN_140021d50((long long)pTree, (long long)v7);
                            break;
                        }
                        *(char*)(v8 + 5) = 0;
                    }
                } else {
                    if ((char)v8[5] == '\0') {
                        *(char*)(v8 + 5) = 1;
                        *(char*)(v7 + 5) = 0;
                        FUN_140021db0((long long)pTree, v7);
                        v8 = (long long*)*v7;
                    }
                    if (*(char*)((long long)v8 + 0x29) == '\0') {
                        if ((*(char*)(v8[2] + 0x28) != '\x01') || (*(char*)(*v8 + 0x28) != '\x01')) {
                            if (*(char*)(*v8 + 0x28) == '\x01') {
                                *(char*)(v8[2] + 0x28) = 1;
                                *(char*)(v8 + 5) = 0;
                                FUN_140021d50((long long)pTree, (long long)v8);
                                v8 = (long long*)*v7;
                            }
                            *(char*)(v8 + 5) = (char)v7[5];
                            *(char*)(v7 + 5) = 1;
                            *(char*)(*v8 + 0x28) = 1;
                            FUN_140021db0((long long)pTree, v7);
                            break;
                        }
                        *(char*)(v8 + 5) = 0;
                    }
                }
                v8 = (long long*)v7[1];
                v9 = v7;
            } while (v7 != *(long long**)(pTree[6] + 8));
        }
        *(char*)(v9 + 5) = 1;
    }
    g_pfnNpcOperatorDelete(n2);
    if (pTree[7] != 0) {
        pTree[7] = pTree[7] + -1;
    }
    long long l5 = pIter[1];
    *pOut = *pTree;
    pOut[1] = l5;
    return pOut;
}

const NpcTreeEraseEntry g_aNpcTreeErase[] = {
    { "140022e50", "erase",       (void*)&FUN_140022e50 },
    { "140023400", "erase",       (void*)&FUN_140023400 },
    { "140021fe0", "successor",   (void*)&FUN_140021fe0 },
    { "140021d50", "rotate-left", (void*)&FUN_140021d50 },
    { "140021db0", "rotate-right",(void*)&FUN_140021db0 },
};

const int g_nNpcTreeErase = 5;

}  // namespace tq
