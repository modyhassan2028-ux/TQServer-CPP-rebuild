// D206 — NpcServer.exe 0x140076f80, 0x140077120, 0x1400771d0, 0x140077280, 0x140077330.
#include <cassert>
#include <cstdio>
#include <cstring>
#include <cstdint>
#include <string>
#include "modules/npcserver/unattributed/front-of-image.h"

using namespace tq;

static int g_byteSize = 4;
static int g_seqN = 0, g_seq[16];
static void Note(int c) { if (g_seqN < 16) g_seq[g_seqN] = c; ++g_seqN; }
static int SizeSlot(long long* p) { (void)p; Note(1); return g_byteSize; }
static long long g_delta = 0;
static long long ArraySlot(long long* p, long long b) {
    (void)p; Note(2);
    return b + (g_delta ? g_delta : g_byteSize);
}
// the real resize and data functions drive a real string
static void ResizeSeam(std::string* p, long long n) { FUN_140077900(p, (unsigned long long)n); }
static long long DataSeam(std::string* p) { return (long long)p->data(); }
static int g_freed = 0; static void* g_freedPtr = nullptr;
static void* FreeSeam(void* p) { ++g_freed; g_freedPtr = p; return nullptr; }

int main() {
    long long vt[12];
    std::memset(vt, 0, sizeof vt);
    vt[8] = (long long)&SizeSlot;     // +0x40
    vt[10] = (long long)&ArraySlot;   // +0x50
    long long aMsg[1] = { (long long)vt };
    g_pfnNpcOperatorDelete = &FreeSeam;
    static unsigned char aBuf[0x40];

    // room too small: nothing is written and the answer carries the size with its low byte cleared
    {
        g_byteSize = 4; g_delta = 0; g_seqN = 0;
        long long l = FUN_140077120(aMsg, (long long)aBuf, 3);
        assert(l == 0);                                  // 4 with the low byte cleared
        assert(g_seqN == 1);                             // only the size was asked for
        g_byteSize = 0x108;
        l = FUN_140077120(aMsg, (long long)aBuf, 0x100);
        assert(l == 0x100);                              // the upper bytes survive, the low byte is zero
        g_byteSize = 4;
        // enough room: the array writer runs and the answer is one
        g_seqN = 0;
        l = FUN_140076f80(aMsg, (long long)aBuf, 4);     // through the forwarder
        assert(l == 1);
        assert(g_seq[0] == 1 && g_seq[1] == 2);
        // a short write reports through the consistency check and still answers one
        g_delta = 2;
        static int g_marker = 0;
        (void)g_marker;
        l = FUN_140077120(aMsg, (long long)aBuf, 8);
        assert(l == 1);
        g_delta = 0;
    }

    // serializing into a string
    {
        g_byteSize = 4; g_delta = 0;
        unsigned char aStorage[sizeof(std::string)];
        std::string* p = FUN_1400771d0(aMsg, (std::string*)aStorage);
        assert(p == (std::string*)aStorage);
        assert(p->size() == 4);                          // grown by the byte size
        for (int i = 0; i < 4; ++i) assert((*p)[i] == 0);
        p->~basic_string();
        // the same through the other producer
        p = FUN_140077280(aMsg, (std::string*)aStorage);
        assert(p->size() == 4);
        p->~basic_string();
        // an empty message body leaves an empty string
        g_byteSize = 0;
        p = FUN_140077280(aMsg, (std::string*)aStorage);
        assert(p->size() == 0);
        p->~basic_string();
        g_byteSize = 4;
    }

    // the deleting destructor: the vtable is installed, and the object is released only with bit 0 set
    {
        static const void* g_dummyVt[2] = { nullptr, nullptr };
        g_pNpcVtblMessageLite = (const void*)g_dummyVt;
        static unsigned char aObj[0x20];
        std::memset(aObj, 0xCC, sizeof aObj);
        g_freed = 0; g_freedPtr = nullptr;
        void* p = FUN_140077330((void**)aObj, 0);
        assert(p == (void*)aObj);
        assert(*(void**)aObj == (void*)g_dummyVt);       // the vtable is installed in both cases
        assert(g_freed == 0);
        p = FUN_140077330((void**)aObj, 1);
        assert(p == (void*)aObj && g_freed == 1 && g_freedPtr == (void*)aObj);
        g_freed = 0;
        p = FUN_140077330((void**)aObj, 0x10);           // other flag bits do not free
        assert(g_freed == 0);
    }

    std::printf("NPCSERVER_D206_OK: 0x140076f80/120/1d0/280/330\n");
    return 0;
}
