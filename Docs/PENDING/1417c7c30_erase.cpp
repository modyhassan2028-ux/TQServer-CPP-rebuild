// PENDING — 0x1417c7c30, the subtree erase with the full fix-up.
//
// The body is translated line for line from the bytes captured in
// Docs/ASM/1417c7c30.txt (0x1417c7c30..0x1417c7fe1), but it is NOT verified: with the
// arrangement the test builds for the first path it does not return, so something in the
// link/colour walk still differs from the original and no claim is made about it.
//
// What is settled: the 0x29-sentinel path builds its throw through 0x141823270,
// 0x1418233f8, 0x141823288 and 0x1417f3154 with the two vtable pointers 0x141824a60 and
// 0x141824ba0, and the body steps the iterator with 0x1417c6e80 before it touches a link.
//
// Nothing below is compiled: it stays here until the walk can be shown to terminate and
// the 19 checks around it pass six times.
// 0x1417c7c30 - the subtree erase with the full fix-up.
//   rcx = tree, rdx = the pair it answers with, r8 = the iterator that names the node.
// The neighbours it leans on live in CsyndicateLogicTailSlots.cpp.
extern void SynAccDec29_1417c6e80(void* pIter);             // 0x1417c6e80
extern void (*g_pfnLogic_1417f2fdc)(void* p);               // 0x1417f2fdc

void* SynTreeErase_1417c7c30(void* pTree, void* pOut, void* pIter) {
    int64_t frame = -2; (void)frame;
    unsigned char* tree = (unsigned char*)pTree;              // rbp
    unsigned char* out  = (unsigned char*)pOut;               // r13
    unsigned char* it   = (unsigned char*)pIter;              // r12
    unsigned char* n    = *(unsigned char**)(it + 8);         // rsi

    if (*(unsigned char*)(n + 0x29) != 0) {                   // the sentinel path throws
        unsigned char buf[0xa0] = {};
        unsigned char* obj = buf + 0x38;
        if (g_pfnSynTmp_141823270 != nullptr)
            g_pfnSynTmp_141823270(buf, (void*)(uintptr_t)0x141825ca8);
        if (g_pfnSyn_1418233f8 != nullptr) g_pfnSyn_1418233f8(obj);
        *(const void**)obj = (const void*)(uintptr_t)0x141824a60;
        if (g_pfnSyn_141823288 != nullptr) g_pfnSyn_141823288(buf + 0x50, buf + 0x78);
        *(const void**)obj = (const void*)(uintptr_t)0x141824ba0;
        if (g_pfnSynThrow_1417f3154 != nullptr)
            g_pfnSynThrow_1417f3154(obj, (const void*)(uintptr_t)0x141881e50);
    }

    SynAccDec29_1417c6e80(it);                                // the iterator is stepped first
    unsigned char* l = *(unsigned char**)(n);                  // r11
    unsigned char* rep = nullptr;                              // rdi
    bool doSwap = false;

    if (*(unsigned char*)(l + 0x29) == 0) {                    // the 0x0 side is real
        unsigned char* rr = *(unsigned char**)(n + 0x10);
        if (*(unsigned char*)(rr + 0x29) != 0) {
            rep = l;
        } else {
            unsigned char* pred = *(unsigned char**)(it + 8);
            rep = *(unsigned char**)(pred + 0x10);
            if (pred != n) doSwap = true;
        }
    } else {
        rep = *(unsigned char**)(n + 0x10);
    }

    if (!doSwap) {
        unsigned char* parent = *(unsigned char**)(n + 8);      // rbx
        if (*(unsigned char*)(rep + 0x29) == 0) *(void**)(rep + 8) = parent;
        {
            unsigned char* head = *(unsigned char**)(tree + 0x30);
            if (n == *(unsigned char**)(head + 8)) *(void**)(head + 8) = rep;
            else if (n == *(unsigned char**)parent) *(void**)parent = rep;
            else *(void**)(parent + 0x10) = rep;
        }
        {
            unsigned char* head = *(unsigned char**)(tree + 0x30);
            if (n == *(unsigned char**)head) {
                unsigned char* cc;
                if (*(unsigned char*)(rep + 0x29) != 0) cc = parent;
                else {
                    cc = rep;
                    unsigned char* a = *(unsigned char**)rep;
                    while (*(unsigned char*)(a + 0x29) == 0) { cc = a; a = *(unsigned char**)a; }
                }
                *(void**)head = cc;
            }
        }
        {
            unsigned char* head = *(unsigned char**)(tree + 0x30);
            if (n == *(unsigned char**)(head + 0x10)) {
                unsigned char* cc;
                if (*(unsigned char*)(rep + 0x29) != 0) cc = parent;
                else {
                    cc = rep;
                    unsigned char* a = *(unsigned char**)(rep + 0x10);
                    while (*(unsigned char*)(a + 0x29) == 0) { cc = a; a = *(unsigned char**)(a + 0x10); }
                }
                *(void**)(head + 0x10) = cc;
            }
        }
    } else {
        unsigned char* pred = *(unsigned char**)(it + 8);
        *(void**)(l + 8) = pred;
        *(void**)pred = *(void**)n;
        if (pred == *(unsigned char**)(n + 0x10)) {
            ;                                                      // the direct case only fixes the links below
        } else {
            unsigned char* parent = *(unsigned char**)(pred + 8);
            if (*(unsigned char*)(rep + 0x29) == 0) *(void**)(rep + 8) = parent;
            *(void**)parent = rep;
            *(void**)(pred + 0x10) = *(unsigned char**)(n + 0x10);
            *(void**)(*(unsigned char**)(n + 0x10) + 8) = pred;
        }
        {
            unsigned char* head = *(unsigned char**)(tree + 0x30);
            if (n == *(unsigned char**)(head + 8)) *(void**)(head + 8) = pred;
            else {
                unsigned char* p2 = *(unsigned char**)(n + 8);
                if (n == *(unsigned char**)p2) *(void**)p2 = pred;
                else *(void**)(p2 + 0x10) = pred;
            }
        }
        *(void**)(pred + 8) = *(unsigned char**)(n + 8);
        {
            unsigned char* a = n + 0x28;
            unsigned char* b = pred + 0x28;
            if (a != b) { unsigned char t = *b; unsigned char u = *a; *b = u; *a = t; }
        }
    }

    unsigned char* colTarget = rep;                            // rdi at 0x1417c7f6a
    if (*(unsigned char*)(n + 0x28) == 1) {
        unsigned char* head = *(unsigned char**)(tree + 0x30);
        if (rep != *(unsigned char**)(head + 8) && *(unsigned char*)(rep + 0x28) == 1) {
            unsigned char* cur = rep;
            unsigned char* node = *(unsigned char**)(n + 8);
            for (;;) {
                bool stop = false;
                if (cur == *(unsigned char**)node) {
                    unsigned char* sib = *(unsigned char**)(node + 0x10);
                    if (*(unsigned char*)(sib + 0x28) == 0) {
                        *(unsigned char*)(sib + 0x28) = 1;
                        *(unsigned char*)(node + 0x28) = 0;
                        SynAccRotRight_1417c6f90(tree, node);
                        sib = *(unsigned char**)(node + 0x10);
                    }
                    if (*(unsigned char*)(sib + 0x29) != 0) {
                        cur = node; stop = true;
                    } else if (*(unsigned char*)(*(unsigned char**)sib + 0x28) != 1 ||
                               *(unsigned char*)(*(unsigned char**)(sib + 0x10) + 0x28) != 1) {
                        if (*(unsigned char*)(*(unsigned char**)(sib + 0x10) + 0x28) == 1) {
                            *(unsigned char*)(*(unsigned char**)sib + 0x28) = 1;
                            *(unsigned char*)(sib + 0x28) = 0;
                            SynAccRotLeft_1417c6ff0(tree, sib);
                            sib = *(unsigned char**)(node + 0x10);
                        }
                        *(unsigned char*)(sib + 0x28) = *(unsigned char*)(node + 0x28);
                        *(unsigned char*)(node + 0x28) = 1;
                        *(unsigned char*)(*(unsigned char**)(sib + 0x10) + 0x28) = 1;
                        SynAccRotRight_1417c6f90(tree, node);
                        stop = true;
                    } else {
                        *(unsigned char*)(sib + 0x28) = 0;
                        cur = node;
                    }
                } else {
                    unsigned char* sib = *(unsigned char**)node;
                    if (*(unsigned char*)(sib + 0x28) == 0) {
                        *(unsigned char*)(sib + 0x28) = 1;
                        *(unsigned char*)(node + 0x28) = 0;
                        SynAccRotLeft_1417c6ff0(tree, node);
                        sib = *(unsigned char**)node;
                    }
                    if (*(unsigned char*)(sib + 0x29) != 0) {
                        cur = node; stop = true;
                    } else if (*(unsigned char*)(*(unsigned char**)(sib + 0x10) + 0x28) != 1 ||
                               *(unsigned char*)(*(unsigned char**)sib + 0x28) != 1) {
                        if (*(unsigned char*)(*(unsigned char**)sib + 0x28) == 1) {
                            *(unsigned char*)(*(unsigned char**)(sib + 0x10) + 0x28) = 1;
                            *(unsigned char*)(sib + 0x28) = 0;
                            SynAccRotRight_1417c6f90(tree, sib);
                            sib = *(unsigned char**)node;
                        }
                        *(unsigned char*)(sib + 0x28) = *(unsigned char*)(node + 0x28);
                        *(unsigned char*)(node + 0x28) = 1;
                        *(unsigned char*)(*(unsigned char**)sib + 0x28) = 1;
                        SynAccRotLeft_1417c6ff0(tree, node);
                        stop = true;
                    } else {
                        *(unsigned char*)(sib + 0x28) = 0;
                        cur = node;
                    }
                }
                if (stop) break;
                node = *(unsigned char**)(node + 8);
                head = *(unsigned char**)(tree + 0x30);
                if (cur == *(unsigned char**)(head + 8)) break;
            }
            colTarget = cur;
        }
    }
    *(unsigned char*)(colTarget + 0x28) = 1;                    // 0x1417c7f6a

    if (g_pfnLogic_1417f2fdc != nullptr) g_pfnLogic_1417f2fdc(n);
    {
        unsigned char* cnt = tree + 0x38;
        uint64_t v = *(uint64_t*)cnt;
        if (v != 0) *(uint64_t*)cnt = v - 1;
    }
    {
        unsigned char tmp[0x10];
        *(void**)tmp = *(void**)it;
        *(void**)(tmp + 8) = *(void**)(it + 8);
        *(void**)tmp = *(void**)tree;
        *(void**)out = *(void**)tmp;
        *(void**)(out + 8) = *(void**)(tmp + 8);
    }
    return out;
}
