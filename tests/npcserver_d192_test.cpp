// D192 — NpcServer.exe 0x140074e80, 0x140074eb0, 0x140074ec0, 0x140074f40, 0x140075040.
#include <cassert>
#include <cstdio>
#include <cstring>
#include <cstdint>
#include "modules/npcserver/unattributed/front-of-image.h"

using namespace tq;

static unsigned char g_ctl[0x10];
static int g_postOk = 1; static unsigned int g_postBytes = 0; static unsigned long long g_postKey = 0;
static void* g_postOv = nullptr; static void* g_postPort = nullptr;
static int Post(void* h, unsigned int n, unsigned long long k, void* o) {
    g_postPort = h; g_postBytes = n; g_postKey = k; g_postOv = o; return g_postOk;
}
static unsigned char g_blockA[0x200], g_blockB[0x200];
static int g_reallocFailAt = 0;
static int g_reallocCalls = 0;
static void* g_reallocIn[4]; static unsigned long long g_reallocSize[4];
static void* Realloc(void* p, unsigned long long n) {
    int i = g_reallocCalls < 4 ? g_reallocCalls : 3;
    g_reallocIn[i] = p; g_reallocSize[i] = n;
    ++g_reallocCalls;
    if (g_reallocFailAt && g_reallocCalls == g_reallocFailAt) return nullptr;
    return p == nullptr ? (void*)g_blockA : p;
}
static long long g_treeQuery = 0; static int* g_nodeRet = nullptr; static int g_nodeCalls = 0;
static void* TreeFind(long long* pTree, long long uKey) {
    (void)pTree; g_treeQuery = uKey; ++g_nodeCalls; return g_nodeRet;
}

int main() {
    g_pfnNpcPostQueuedCompletionStatus = &Post;
    g_pfnNpcRealloc_1400119a0 = &Realloc;
    g_pfnNpc_14001a880 = &TreeFind;

    // posting a completion
    {
        *(void**)g_ctl = (void*)0x7000;
        unsigned char ov[0x20]; std::memset(ov, 0, sizeof ov);
        g_postOk = 1;
        assert(FUN_140074e80(g_ctl, ov, 0x1122334455ull, 99) == 0);
        assert(g_postPort == (void*)0x7000 && g_postKey == 0x1122334455ull);
        assert(g_postBytes == 99 && g_postOv == (void*)ov);
        g_postOk = 0;
        assert(FUN_140074e80(g_ctl, ov, 1, 2) == -1);
    }

    // the port handle out of the base
    {
        unsigned char base[0x200]; std::memset(base, 0, sizeof base);
        *(void**)(base + 0x1f0) = (void*)0x8800;
        assert(FUN_140074eb0((long long)base) == (void*)0x8800);
    }

    // sizing both queues: the entry area is (n-1)*8 + 0x10 for each, and nothing is committed on failure
    {
        int queue[8]; std::memset(queue, 0, sizeof queue);
        *(void**)(queue + 2) = (void*)0x1000;
        *(void**)(queue + 4) = (void*)0x2000;
        g_reallocCalls = 0; g_reallocFailAt = 0;
        assert(FUN_140074ec0(queue, 0x20) == 0);
        assert(g_reallocCalls == 2);
        assert(g_reallocSize[0] == (0x20u - 1) * 8 + 0x10 && g_reallocSize[1] == g_reallocSize[0]);
        assert(g_reallocIn[0] == (void*)0x1000 && g_reallocIn[1] == (void*)0x2000);
        assert(queue[0] == 0x20 && queue[1] == 1);
        // the second allocation failing leaves the size untouched
        int queue2[8]; std::memset(queue2, 0, sizeof queue2);
        *(void**)(queue2 + 4) = (void*)0x2000;
        g_reallocCalls = 0; g_reallocFailAt = 2;
        assert(FUN_140074ec0(queue2, 8) == 0xffffffffull);
        assert(queue2[0] == 0 && queue2[1] == 0);
        g_reallocFailAt = 0;
    }

    // appending into a queue with room: the key lands after the count, and the cursor of that side moves
    {
        unsigned char arrA[0x100], arrB[0x100];
        std::memset(arrA, 0, sizeof arrA); std::memset(arrB, 0, sizeof arrB);
        int queue[8]; std::memset(queue, 0, sizeof queue);
        queue[0] = 4;                                        // capacity
        *(void**)(queue + 2) = arrA;
        *(void**)(queue + 4) = arrB;
        int active[2] = { 0, 0 };
        *(unsigned int*)arrA = 0;                            // one entry already there
        *(unsigned int*)arrB = 0;
        g_reallocCalls = 0;
        assert(FUN_140074f40((unsigned int*)queue, active, 0xABCD, 1) == 0);
        assert(*(unsigned long long*)(arrA + 8) == 0xABCD);
        assert(*(unsigned int*)arrA == 1 && active[0] == 1);
        assert(g_reallocCalls == 0);                         // no growth needed
        // the same side refuses a second append while it still holds its entry
        assert(FUN_140074f40((unsigned int*)queue, active, 0xEE, 1) == 0);
        assert(*(unsigned int*)arrA == 1 && active[0] == 1);
        // once it is withdrawn the side is free again
        assert(FUN_140075040(0x9000, (long long)queue, active, 1) == 0);
        assert(*(unsigned int*)arrA == 0 && active[0] == 0);
        // and the other side, which was empty, accepts its own entry
        assert(FUN_140074f40((unsigned int*)queue, active, 0xEE, 0) == 0);
        assert(*(unsigned long long*)(arrB + 8) == 0xEE && active[1] == 1);
        assert(*(unsigned int*)arrB == 1);
    }

    // a full queue doubles, reallocating both, and the entry goes into the side that asked
    {
        unsigned char arrA[0x100], arrB[0x100];
        std::memset(arrA, 0, sizeof arrA); std::memset(arrB, 0, sizeof arrB);
        int queue[8]; std::memset(queue, 0, sizeof queue);
        queue[0] = 2;
        *(void**)(queue + 2) = arrA;
        *(void**)(queue + 4) = arrB;
        int active[2] = { 0, 0 };
        *(unsigned int*)arrB = 2;                            // the second queue is exactly full
        g_reallocCalls = 0;
        unsigned int uIndex = FUN_140074f40((unsigned int*)queue, active, 0x1234, 0);
        assert(uIndex == 2);
        assert(queue[0] == 4);                               // the capacity doubled
        assert(g_reallocCalls == 2 && g_reallocSize[0] == (4u - 1) * 8 + 0x10);
        assert(*(unsigned long long*)(arrB + 8 + 2 * 8) == 0x1234);
        assert(*(unsigned int*)arrB == 3 && active[1] == 3);
    }

    // withdrawing: the last entry is moved into the hole and its tree node is corrected
    {
        unsigned char arr[0x100];
        std::memset(arr, 0, sizeof arr);
        long long queue[8]; std::memset(queue, 0, sizeof queue);
        *(void**)(queue + 1) = arr;                           // +8: the first queue
        *(unsigned int*)arr = 4;                              // four entries in the array
        *(unsigned long long*)(arr + 8) = 0x11;
        *(unsigned long long*)(arr + 0x10) = 0x22;
        *(unsigned long long*)(arr + 0x18) = 0x33;
        *(unsigned long long*)(arr + 0x20) = 0x44;
        int active[2] = { 2, 0 };                             // but the cursor says two were handed out
        int node[2] = { 0, 0 };
        g_nodeRet = node; g_nodeCalls = 0; g_treeQuery = 0;
        assert(FUN_140075040(0x9000, (long long)queue, active, 1) == 0);
        assert(active[0] == 0);                               // the cursor is cleared
        assert(*(unsigned int*)arr == 3);                     // one entry fewer
        assert(*(unsigned long long*)(arr + 0x10) == 0x44);   // the last entry took the hole at index 1
        assert(g_nodeCalls == 1 && g_treeQuery == 0x44);
        assert(node[0] == 2);                                 // corrected on the side that withdrew
        // an empty queue changes nothing
        g_nodeCalls = 0; active[0] = 0;
        assert(FUN_140075040(0x9000, (long long)queue, active, 1) == 0);
        assert(*(unsigned int*)arr == 3 && g_nodeCalls == 0);
    }

    std::printf("NPCSERVER_D192_OK: 0x140074e80/e0/ec0/f40/140075040\n");
    return 0;
}
