// D226 — NpcServer.exe coded-input bounds: 0x14007c650 (byte count), 0x14007c670 (position), 0x14007d140 (the
// smaller of two ints) and 0x14007c6a0 (settle the overrun after the limit moved).
#include <cassert>
#include <cstdio>
#include <cstring>
#include <cstdint>
#include <cstddef>
#include "modules/npcserver/unattributed/front-of-image.h"

using namespace tq;

struct Coded {
    void* pSink;          // +0x00, the first word the flush indirection reads
    long long nStart;     // +0x08, the buffer start (buffer_)
    long long nEnd;       // +0x10, the buffer end (buffer_end_)
    int nConsumed;        // +0x18
    int nOverrun1;        // +0x1c
    int nPad1, nPad2;     // +0x20, +0x24 - the image leaves these alone
    int nLimitWord;       // +0x28
    int nOverrun2;        // +0x2c
    int nOtherWord;       // +0x30
};

int main() {
    // the byte count is the limit minus the current pointer, and it is a full 64-bit difference
    {
        Coded c;
        std::memset(&c, 0, sizeof c);
        c.nStart = 1000; c.nEnd = 1003;
        assert(FUN_14007c650((long long)&c) == 3);
        c.nEnd = c.nStart;
        assert(FUN_14007c650((long long)&c) == 0);
        c.nStart = 4242; c.nEnd = 1000;
        assert(FUN_14007c650((long long)&c) == 1000 - 4242);   // a negative count really is negative
    }

    // the position is the consumed count less both the byte count and the overrun at +0x2c
    {
        Coded c;
        std::memset(&c, 0, sizeof c);
        c.nStart = 1000; c.nEnd = 1003; c.nConsumed = 10; c.nOverrun2 = 2;
        assert(FUN_14007c670((long long)&c) == 10 - (3 + 2));
        c.nOverrun2 = 0;
        assert(FUN_14007c670((long long)&c) == 10 - 3);
    }

    // the settle answers the address of the smaller int, and keeps the first one on a tie
    {
        int a = 5, b = 9;
        assert(FUN_14007d140(&a, &b) == &a);
        a = 9;
        assert(FUN_14007d140(&a, &b) == &a);                  // equal is not "smaller", so the first wins
        a = 12;
        assert(FUN_14007d140(&a, &b) == &b);
    }

    // settling the overrun: the current pointer first absorbs the overrun at +0x2c, then the smaller of the limit at
    // +0x28 and the word at +0x30 decides. Still short of the consumed count means the difference becomes the new
    // overrun and is taken back off the pointer.
    {
        Coded c;
        std::memset(&c, 0, sizeof c);
        c.nEnd = 1000; c.nOverrun2 = 5;
        c.nLimitWord = 50; c.nOtherWord = 10; c.nConsumed = 30;
        FUN_14007c6a0((long long)&c);
        assert(c.nOverrun2 == 30 - 10);                        // the smaller word is 10
        assert(c.nEnd == 1000 + 5 - 20);                      // absorbed 5, then gave back the overrun

        // with the other word above the limit, the limit is the smaller one
        std::memset(&c, 0, sizeof c);
        c.nEnd = 1000; c.nOverrun2 = 0;
        c.nLimitWord = 10; c.nOtherWord = 50; c.nConsumed = 30;
        FUN_14007c6a0((long long)&c);
        assert(c.nOverrun2 == 20);
        assert(c.nEnd == 1000 - 20);

        // and once the consumed count is not above it, the overrun clears and the pointer keeps what it absorbed
        std::memset(&c, 0, sizeof c);
        c.nEnd = 1000; c.nOverrun2 = 4;
        c.nLimitWord = 50; c.nOtherWord = 10; c.nConsumed = 5;
        FUN_14007c6a0((long long)&c);
        assert(c.nOverrun2 == 0);
        assert(c.nEnd == 1004);
    }

    std::printf("NPCSERVER_D226_OK: coded-input bounds\n");
    return 0;
}
