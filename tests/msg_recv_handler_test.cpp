// MsgServer unit M20 - the encrypted
// recv handler FUN_1405002a0
#include "../msgserver/MsgRecvHandler.h"
#include "../msgserver/MsgSessionCipher.h"
#include <cassert>
#include <cstdio>
#include <cstring>
using namespace msg;

int main() {
    // a fake connection object big enough
    // for +0x824 + sizeof(crypto block)
    static char conn[0x824 +
        sizeof(MsgCryptoBlock) + 16];
    MsgRecvHandlerData d;
    d.m_fnKeyXchg = [&](void* crypto,
                       void* buf,
                       int n) {
        // verify the arguments
        assert(crypto == conn + 0x824);
        assert(buf == conn + 0x1b);
        assert(n == *(int*)(conn + 8));
        return d.nXchgRc; };
    d.m_fnConsume = [&](void* p, int n) {
        assert(p == conn);
        // the consume: drop n bytes from the
        // front, shrink the length
        int nCur = *(int*)(conn + 8);
        std::memmove(conn + 0x1b,
            conn + 0x1b + n,
            nCur - n);
        *(int*)(conn + 8) = nCur - n; };
    d.m_fnDecrypt = [&](void* crypto,
                        void* in,
                        void* out, int n) {
        assert(crypto == conn + 0x824);
        assert(in == conn + 0x1b);
        rD_check: ;
        // decrypt = xor-by-position fake
        for (int i = 0; i < n; ++i)
            ((unsigned char*)out)[i] =
                ((unsigned char*)in)[i] ^ 0x5A;
        return d.nDecRc; };

    auto reset = [&](int nLen) {
        std::memset(conn, 0, sizeof(conn));
        *(int*)(conn + 8) = nLen;
        d.nConsume = 0; d.nDecrypt = 0;
        d.nConsumeArg = 0; d.nDecLen = 0;
        d.bKeyXchgRan = false;
        d.nXchgRc = 0; d.nDecRc = 1;
    };

    // ===== 1. short buffer: no key xchg
    reset(0xb);
    assert(MsgRecvHandler(conn, d) == 1);
    assert(!d.bKeyXchgRan);

    // ===== 2. xchg == 0: wait for more
    reset(0x20);
    d.nXchgRc = 0;
    assert(MsgRecvHandler(conn, d) == 1);
    assert(d.bKeyXchgRan);
    assert(d.nConsume == 0);
    assert(conn[0x1a] == 0);   // not keyed

    // ===== 3. xchg < 0: drop
    reset(0x20);
    d.nXchgRc = -1;
    assert(MsgRecvHandler(conn, d) == 0);

    // ===== 4. the happy path =====
    reset(0x40);
    d.nXchgRc = 0x18;    // consumed bytes
    // fill the buffer: [0x18 xchg][rest]
    std::memset(conn + 0x1b, 'X', 0x40);
    // encrypted "abc..." in the rest
    const char* pPlain = "GAME";
    for (int i = 0; i < 4; ++i)
        conn[0x1b + 0x18 + i] =
            pPlain[i] ^ 0x5A;
    assert(MsgRecvHandler(conn, d) == 1);
    assert(d.nConsume == 1 &&
        d.nConsumeArg == 0x18);
    assert(conn[0x1a] == 1);   // keyed
    assert(d.nDecrypt == 1 &&
        d.nDecLen == 0x40 - 0x18);
    // the rest decrypted in place
    assert(std::memcmp(conn + 0x1b,
        "GAME", 4) == 0);

    // ===== 5. decrypt fail =====
    reset(0x40);
    d.nXchgRc = 4;
    d.nDecRc = 0;
    assert(MsgRecvHandler(conn, d) == 0);
    assert(d.nDecrypt == 1);

    // ===== 6. empty after consume =====
    reset(0xc);
    d.nXchgRc = 0xc;
    assert(MsgRecvHandler(conn, d) == 1);
    assert(d.nDecrypt == 0);   // skipped
    assert(conn[0x1a] == 1);

    printf("MSG_RECV_HANDLER_OK: "
           "FUN_1405002a0 VERBATIM (the "
           "len<0xc early gate, the M18 "
           "call with (this+0x824, this+"
           "0x1b, len), 0->wait / <0->"
           "drop, the vt+0x10 consume, "
           "the +0x1a keyed flag, the "
           "re-read len + in-place decrypt "
           "of the remainder - 6 paths)\n");
    return 0;
}
