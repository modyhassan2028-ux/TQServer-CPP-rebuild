#include "SyndicateMeedSort.h"
#include "SyndicateMeedFlow.h"
#include "SyndicateSynMeed.h"
#include <cstring>

namespace syndicate {

// ---- FUN_1417781b0: the comparator (verbatim) --
bool MeedSortCmp(void* a, void* b) {
    if (a == nullptr) {
        return false;
    }
    if (b == nullptr) {
        return true;
    }
    // sub(4)/sub(3)@+0x48, sub(0)@+0x40
    void* s = g_fnMeedMemSub(a, 4);
    int g4a = g_fnMeedSubNType(s);
    s = g_fnMeedMemSub(b, 4);
    int g4b = g_fnMeedSubNType(s);
    s = g_fnMeedMemSub(a, 3);
    int t3a = g_fnMeedSubNType(s);
    s = g_fnMeedMemSub(b, 3);
    int t3b = g_fnMeedSubNType(s);
    s = g_fnMeedMemSub(a, 0);
    uint32_t v0a =
        (uint32_t)g_fnMeedSubNId(s);
    s = g_fnMeedMemSub(b, 0);
    uint32_t v0b =
        (uint32_t)g_fnMeedSubNId(s);
    if (t3a == t3b) {
        if (g4a == g4b) {
            if (v0a == v0b) {
                return true;   // verbatim!
            }
            return v0b <= v0a;
        }
        return g4b <= g4a;
    }
    return t3b <= t3a;
}

// ---- FUN_1417786d0: the median-of-3 order ----
void MeedMedian3(void** p1, void** p2,
                 void** p3,
                 MeedSortCmpFn cmp) {
    if (cmp(*p2, *p1) && p2 != p1) {
        void* t = *p2;
        *p2 = *p1;
        *p1 = t;
    }
    if (cmp(*p3, *p2) && p3 != p2) {
        void* t = *p3;
        *p3 = *p2;
        *p2 = t;
    }
    if (cmp(*p2, *p1) && p2 != p1) {
        void* t = *p2;
        *p2 = *p1;
        *p1 = t;
    }
}

// ---- FUN_1417788c0: the median guess ---------
void MeedGuessMedian(void** p1, void** p2,
                     void** p3,
                     MeedSortCmpFn cmp) {
    int64_t n =
        ((int64_t)p3 - (int64_t)p1) >> 3;
    if (0x28 < n) {
        n = n + 1;
        int64_t m =
            (n + (((n >> 63)) & 7)) >> 3;
        MeedMedian3(p1, p1 + m, p1 + 2 * m, cmp);
        MeedMedian3(p2 - m, p2, p2 + m, cmp);
        MeedMedian3(p3 - 2 * m, p3 - m, p3, cmp);
        MeedMedian3(p1 + m, p2, p3 - m, cmp);
        return;
    }
    MeedMedian3(p1, p2, p3, cmp);
}

// ---- FUN_141778760: the heap sift-down ------
void MeedSiftDown(void** base, int64_t nHole,
                  int64_t nLen, void* pVal,
                  MeedSortCmpFn cmp) {
    int64_t hole = nHole;
    int64_t child;
    while (true) {
        child = hole * 2 + 2;
        if (nLen <= child) {
            break;
        }
        // the larger child (per cmp) up
        if (cmp(base[child], base[child - 1])) {
            child = hole * 2 + 1;
        }
        base[hole] = base[child];
        hole = child;
    }
    if (child == nLen) {
        base[hole] = base[nLen - 1];
        hole = nLen - 1;
    }
    while (nHole < hole) {
        int64_t parent = (hole - 1) / 2;
        if (!cmp(base[parent], pVal)) {
            break;
        }
        base[hole] = base[parent];
        hole = parent;
    }
    base[hole] = pVal;
}

// ---- FUN_141778d90: the bottom-up heapify ----
void MeedMakeHeap(void** begin, void** end,
                 MeedSortCmpFn cmp) {
    int64_t n =
        ((int64_t)end - (int64_t)begin) >> 3;
    if (1 < n) {
        int64_t i = (n - (n >> 63)) >> 1;
        while (0 < i) {
            int64_t off = i * 8;
            i = i - 1;
            MeedSiftDown(begin, i, n,
                *(void**)((char*)begin - 8 + off),
                cmp);
        }
    }
}

// ---- FUN_141778f80: the sort-heap -------------
void MeedSortHeap(void** begin, void** end,
                 MeedSortCmpFn cmp) {
    for (int64_t len = (int64_t)end
                       - (int64_t)begin;
         1 < (len >> 3); len = len - 8) {
        void* val =
            *(void**)((char*)begin + len - 8);
        *(void**)((char*)begin + len - 8) =
            *begin;
        MeedSiftDown(begin, 0, (len - 8) >> 3,
                     val, cmp);
    }
}

// ---- FUN_141778a20: the insertion sort --------
void MeedInsertionSort(void** begin,
                       void** end,
                       MeedSortCmpFn cmp) {
    if (begin == end || begin + 1 == end) {
        return;
    }
    void** p = begin + 1;
    do {
        void* val = *p;
        if (!cmp(val, *begin)) {
            void** q = p;
            char c = cmp(val, q[-1]);
            while (c != 0) {
                *q = q[-1];
                c = cmp(val, q[-2]);
                q = q - 1;
            }
            *q = val;
        } else {
            int64_t n =
                ((int64_t)p - (int64_t)begin)
                >> 3;
            if (0 < n) {
                memmove(begin + 1, begin,
                        (size_t)(n * 8));
            }
            *begin = val;
        }
        p = p + 1;
    } while (p != end);
}

// ---- FUN_141778b60: the partition -------------
// (transliterated 1:1 from the original
//  disassembly — goto-faithful)
void MeedPartitionImpl(void*** out,
                       void** first,
                       void** last,
                       MeedSortCmpFn cmp) {
    int64_t n = ((int64_t)last - (int64_t)first)
                >> 3;
    void** mid = first
        + ((n - (n >> 63)) >> 1);
    MeedGuessMedian(first, mid, last - 1, cmp);
    void** up = mid + 1;
    // the down-scan: skip the equal run
    if (first < mid) {
L_bc0:
        void** prev = mid - 1;
        if (cmp(mid[-1], *mid)) {
            goto L_be7;
        }
        if (cmp(*mid, mid[-1])) {
            goto L_be7;
        }
        mid = prev;
        if (first < prev) {
            goto L_bc0;
        }
    }
L_be7:
    // the up-scan: skip the equal run
    if (up < last) {
L_bf0:
        if (cmp(*up, *mid)) {
            goto L_c15;
        }
        if (cmp(*mid, *up)) {
            goto L_c15;
        }
        up = up + 1;
        if (up < last) {
            goto L_bf0;
        }
    }
L_c15:
    {
        void** urun = up;   // rdi
        void** low = mid;   // r12
L_c20:
        if (urun >= last) {
            goto L_c60;
        }
L_c25:
        if (cmp(*mid, *urun)) {
            goto L_c57;
        }
        if (cmp(*urun, *mid)) {
            goto L_c60;
        }
        // equal: collect at the run head
        {
            void** t = up;
            up = up + 1;
            if (t != urun) {
                void* v = *urun;
                *urun = *t;
                *t = v;
            }
        }
L_c57:
        urun = urun + 1;
        if (urun < last) {
            goto L_c25;
        }
        // fallthrough
L_c60:
        if (low > first) {
            void** scan = low - 1;   // rsi
L_c70:
            if (cmp(*scan, *mid)) {
                goto L_c9f;
            }
            if (cmp(*mid, *scan)) {
                goto L_cac;
            }
            // equal: the pivot cell migrates
            mid = mid - 1;
            if (mid != scan) {
                void* v = *scan;
                *scan = *mid;
                *mid = v;
            }
L_c9f:
            low = low - 1;
            scan = scan - 1;
            if (first < low) {
                goto L_c70;
            }
        }
L_cac:
        if (low == first) {
L_cb1:
            if (urun == last) {
                goto L_exit;
            }
            if (up != urun && mid != up) {
                void* v = *up;
                *up = *mid;
                *mid = v;
            }
            {
                void** t1 = urun;
                void** t2 = mid;
                up = up + 1;
                mid = mid + 1;
                urun = urun + 1;
                if (t2 != t1) {
                    void* v = *t1;
                    *t1 = *t2;
                    *t2 = v;
                }
            }
            goto L_c20;
        }
        // cfe: the mover merge
        low = low - 1;
        if (urun != last) {
            if (urun != low) {
                void* v = *urun;
                *urun = *low;
                *low = v;
            }
            urun = urun + 1;
        } else {
            mid = mid - 1;
            if (low != mid) {
                void* v = *low;
                *low = *mid;
                *mid = v;
            }
            up = up - 1;
            if (mid != up) {
                void* v = *up;
                *up = *mid;
                *mid = v;
            }
        }
        goto L_c20;
    }
L_exit:
    out[0] = mid;
    out[1] = up;
}

// ---- FUN_141779790: the introsort driver -----
void MeedSortDriver(void** begin, void** end,
                    int64_t nDepth,
                    MeedSortCmpFn cmp) {
    int64_t span = (int64_t)end
                   - (int64_t)begin;
    while (true) {
        int64_t n = span >> 3;
        if (n < 0x21) {
            if (1 < n) {
                MeedInsertionSort(begin, end,
                                  cmp);
            }
            return;
        }
        if (nDepth < 1) {
            if (0x20 < n) {
                MeedMakeHeap(begin, end, cmp);
                MeedSortHeap(begin, end, cmp);
                return;
            }
            if (1 < n) {
                MeedInsertionSort(begin, end,
                                  cmp);
            }
            return;
        }
        void** midOut[2];
        MeedPartitionImpl(midOut, begin, end,
                          cmp);
        nDepth = nDepth / 2 + (nDepth / 2) / 2;
        if (((int64_t)midOut[0]
             - (int64_t)begin & ~7)
            < ((int64_t)end
               - (int64_t)midOut[1] & ~7)) {
            MeedSortDriver(begin, midOut[0],
                           nDepth, cmp);
            begin = (void**)midOut[1];
        } else {
            MeedSortDriver(midOut[1], end,
                           nDepth, cmp);
            end = (void**)midOut[0];
        }
        span = (int64_t)end - (int64_t)begin;
    }
}

// ---- the seam target (141779eb0's backend) ---
void MeedSortRaw(void** ppBegin, void** ppEnd,
                 int nCount) {
    MeedSortDriver(ppBegin, ppEnd, nCount,
                   MeedSortCmp);
}

} // namespace syndicate
