// MsgServer unit M8 - the CAccountClient family
// FUN_140503610 / FUN_140506e80 / FUN_140506480
#include "../msgserver/MsgClientSocket.h"
#include <cassert>
#include <cstdio>
#include <cstring>
using namespace msg;

int main() {
    MsgClientSock s;
    std::memset(s.ab, 0xAA, sizeof(s.ab));
    MsgAccountClientCtor(&s, []{ return 123456789u; });

    // the vftable chain: base then CAccountClient
    assert(s.At<void*>(0) == (void*)0x2);
    // the literal field writes
    assert(s.At<uint8_t>(8) == 0);
    assert(s.At<uint32_t>(0x18) == 0);
    assert(s.At<int64_t>(0x20) == -1);
    assert(s.At<uint32_t>(0x828) == 0);
    assert(s.At<uint32_t>(0x102c) == 0);
    assert(s.At<uint32_t>(0x1030) == 0);
    assert(s.At<uint8_t>(0x1034) == 1);
    assert(s.At<uint32_t>(0x1038) == 0xffffffff);
    assert(s.At<uint32_t>(0x1040) == 1);   // 0 then 1
    assert(s.At<uint64_t>(0x1048) == 0);
    assert(s.At<uint32_t>(0x1054) == 123456);  // Time/1000
    assert(s.At<uint32_t>(0x1058) == 0);
    assert(s.At<uint32_t>(0x105c) == 0);
    assert(s.At<uint32_t>(0x1260) == 0);
    assert(s.At<uint32_t>(0x1264) == 0);
    // the two 0x800 buffers zeroed
    for (int i = 0x28; i < 0x828; ++i)
        assert(s.ab[i] == 0);
    for (int i = 0x82c; i < 0x102c; ++i)
        assert(s.ab[i] == 0);

    // the cipher tables (independent replication)
    char tA[0x100]; char c = '~';
    for (int i = 0; i < 0x100; ++i) {
        tA[i] = c;
        c = (char)((c * 0x12 - 0x69) * c + 0x19);
    }
    char tB[0x100]; c = (char)0xd3;
    for (int i = 0; i < 0x100; ++i) {
        tB[i] = c;
        c = (char)((c * 0x48 + 0x51) * c + 0x1b);
    }
    for (int i = 0; i < 0x100; ++i) {
        assert((char)s.ab[0x1060 + i] == tA[i]);
        assert((char)s.ab[0x1060 + 0x100 + i] == tB[i]);
        assert((char)s.ab[0x1268 + i] == tA[i]);
        assert((char)s.ab[0x1268 + 0x100 + i] == tB[i]);
    }
    // the table bytes are non-trivial (LCG spread)
    int nDif = 0;
    for (int i = 0; i < 0x100; ++i)
        if (tA[i] != tB[i]) ++nDif;
    assert(nDif > 0x40);

    // the base ctor alone keeps the base vftable
    MsgClientSock s2;
    std::memset(s2.ab, 0xAA, sizeof(s2.ab));
    MsgClientSockCtorBase(&s2, []{ return 1000u; });
    assert(s2.At<void*>(0) == (void*)0x1);
    assert(s2.At<uint32_t>(0x1054) == 1);

    // M9: the three sibling ctors - identical base,
    // distinct vftables (the M6 +0xe0/+0xe8/+0xf0)
    MsgClientSock s3, s4, s5;
    std::memset(s3.ab, 0xAA, sizeof(s3.ab));
    std::memset(s4.ab, 0xAA, sizeof(s4.ab));
    std::memset(s5.ab, 0xAA, sizeof(s5.ab));
    MsgChangeSvrClientCtor(&s3, []{ return 5000u; });
    MsgIpadSvrClientCtor(&s4, []{ return 5000u; });
    MsgCrossSvrClientCtor(&s5, []{ return 5000u; });
    assert(s3.At<void*>(0) == (void*)0x3);
    assert(s4.At<void*>(0) == (void*)0x4);
    assert(s5.At<void*>(0) == (void*)0x5);
    assert(s3.At<uint32_t>(0x1054) == 5);   // base ran
    assert(s5.At<uint32_t>(0x1038) == 0xffffffff);

    printf("MSG_CLIENT_SOCK_OK: FUN_140503610 "
           "(CAccountClient ctor, vftable chain) + "
           "FUN_140506e80 (the 0x1468 CClientSocket "
           "base: recv/send 0x800 buffers, the -1 "
           "qword, the 0xffffffff dword, the LITERAL "
           "double cipher-init on +0x1060/+0x1268, "
           "the 0-then-1 write at +0x1040, and "
           "TimeGet/1000 at +0x1054) + FUN_140506480 "
           "(the two LCG cipher tables '~' -> "
           "(c*0x12-0x69)*c+0x19 and 0xd3 -> "
           "(c*0x48+0x51)*c+0x1b)\n");
    return 0;
}
