// D205 — NpcServer.exe 0x140076f00, 0x140076f40, 0x140077520, 0x140077840, 0x1400778a0, 0x140077900,
// 0x140077850, 0x1400774a0, 0x1400774e0.
#include <cassert>
#include <cstdio>
#include <cstring>
#include <cstdint>
#include <string>
#include "modules/npcserver/unattributed/front-of-image.h"

using namespace tq;

static int g_seqN = 0, g_seq[16];
static void Note(int c) { if (g_seqN < 16) g_seq[g_seqN] = c; ++g_seqN; }
static long long g_resizeTo = -1;
static void Resize(std::string* p, long long n) { (void)p; g_resizeTo = n; Note(1); }
static unsigned char g_buf[0x100];
static long long DataOf(std::string* p) { (void)p; Note(2); return (long long)g_buf; }
static int g_byteSize = 3;
static int SizeSlot(long long* p) { (void)p; Note(3); return g_byteSize; }
static long long g_arrayDelta = 0;
static long long ArraySlot(long long* p, long long b) { (void)p; Note(4); return b + (g_arrayDelta ? g_arrayDelta : g_byteSize); }
static int g_c800 = 0, g_c800Arg = -1;
static void C800(long long t, int n) { (void)t; g_c800Arg = n; ++g_c800; Note(5); }
static int g_slot18 = 0, g_slot38 = 0;
static void Slot18(long long* p) { (void)p; ++g_slot18; Note(6); }
static unsigned char Slot38(long long* p, void* a) { (void)p; (void)a; ++g_slot38; Note(7); return 1; }
static int g_t370 = 0; static void* g_t370a1 = nullptr;
static unsigned char T370(void* a1, long long* p) { (void)p; g_t370a1 = a1; ++g_t370; Note(8); return 1; }

int main() {
    long long vt[12];
    std::memset(vt, 0, sizeof vt);
    vt[8] = (long long)&SizeSlot;
    vt[10] = (long long)&ArraySlot;
    long long aMsg[1] = { (long long)vt };
    g_pfnNpc_140077900 = &Resize;
    g_pfnNpc_140077930 = &DataOf;
    g_pfnNpc_1400778c0 = &C800;
    g_pfnNpc_140077370 = &T370;

    // the field readers
    {
        static unsigned char t[0x40];
        std::memset(t, 0, sizeof t);
        *(unsigned char*)(t + 0x24) = 1;
        *(unsigned char*)(t + 0x18) = 0;
        *(int*)(t + 0x10) = 10;
        *(int*)(t + 0x14) = 7;
        assert(FUN_140077520((long long)t) == 1);
        assert(FUN_140077840((long long)t) == 0);
        assert(FUN_1400778a0((long long)t) == -3);       // the cursor is behind the start, as it stands
        *(int*)(t + 0x14) = 14;
        assert(FUN_1400778a0((long long)t) == 4);
        *(unsigned char*)(t + 0x18) = 0xFF;
        assert(FUN_140077840((long long)t) == 0xFF);
    }

    // resizing a string
    {
        std::string s("ab");
        FUN_140077900(&s, 6);
        assert(s.size() == 6);
        FUN_140077900(&s, 1);
        assert(s.size() == 1);
    }

    // handing out the target's buffer: refused when there is not enough room, and the cursor advanced when
    // there is
    {
        static unsigned char t[0x40];
        std::memset(t, 0, sizeof t);
        *(int*)(t + 0x10) = 4;
        *(void**)(t + 8) = (void*)0x1234;
        g_c800 = 0;
        assert(FUN_140077850((long long)t, 8) == nullptr);
        assert(g_c800 == 0);
        void* p = FUN_140077850((long long)t, 4);
        assert(p == (void*)0x1234 && g_c800 == 1 && g_c800Arg == 4);
    }

    // emptying then appending: the string is cleared first, so the append sees a zero length
    {
        std::string s("hello");
        g_seqN = 0; g_resizeTo = -1; g_arrayDelta = 0; g_byteSize = 3;
        FUN_140076f00(aMsg, &s);
        assert(g_resizeTo == 3);                          // zero plus the byte size, not five plus it
        g_seqN = 0; g_resizeTo = -1;
        FUN_140076f40(aMsg, &s);
        assert(g_resizeTo == 3);
        s = "hello";
        g_resizeTo = -1;
        FUN_140076f40(aMsg, &s);
        assert(g_resizeTo == 3);
    }

    // the two wrapper closers: slot 3 first, then the work, with the answer carried back
    {
        long long aVt[8];
        std::memset(aVt, 0, sizeof aVt);
        aVt[3] = (long long)&Slot18;                      // +0x18
        aVt[7] = (long long)&Slot38;                      // +0x38
        long long aThis[1] = { (long long)aVt };
        g_seqN = 0; g_slot18 = 0; g_slot38 = 0; g_t370 = 0; g_t370a1 = nullptr;
        unsigned char b = FUN_1400774a0((void*)0x4321, aThis);
        assert(b == 1);
        assert(g_seq[0] == 6 && g_seq[1] == 8);           // the wrapper closes before the work
        assert(g_t370 == 1 && g_t370a1 == (void*)0x4321);
        assert(g_slot38 == 0);
        g_seqN = 0; g_slot18 = 0; g_slot38 = 0;
        b = FUN_1400774e0((void*)0x4321, aThis);
        assert(b == 1);
        assert(g_seq[0] == 6 && g_seq[1] == 7);
        assert(g_slot18 == 1 && g_slot38 == 1 && g_t370 == 1);
    }

    std::printf("NPCSERVER_D205_OK: nine small bodies\n");
    return 0;
}
