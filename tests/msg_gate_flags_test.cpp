// MsgServer unit M23 - the license gate
// family FUN_140508ca0/cd0/d00/eb0/b80/dc0
#include "../msgserver/MsgGateFlags.h"
#include <cassert>
#include <cstdio>
#include <cstring>
#include <string>
using namespace msg;

int main() {
    MsgGateFlagsData d;
    d.m_fnTimeGet = [&](int n) {
        assert(n == 1); return d.uNow; };
    d.m_fnRandGet = [](int n) {
        assert(n == 0x3c); return 30; };
    d.m_fnTick = []{ return 700000u; };
    d.m_fnTime64 = []{ return
        (int64_t)1780000000; };
    d.m_fnMktime = [](int* tm) {
        // mktime: y = tm[5]+1900 etc.
        // simple: return the captured stamp
        // as a unix time (fake but checked)
        int64_t y = tm[5] + 1900;
        (void)y;
        return (int64_t)tm[0];  // use [0]
    };
    d.m_fnGetMac = [](unsigned char* m) {
        m[0] = 0x1A; m[1] = 0x2B;
        m[2] = 0x3C; m[3] = 0x4D;
        m[4] = 0x5E; m[5] = 0x6F; };
    int nLastCh = -1;   // GetChannel
    // records which channel is
    // about to be used
    d.m_fnGetChannel = [&](int n) {
        nLastCh = n;
        return d.bChannelOk
            ? d.pChannel : nullptr; };
    d.m_fnChSend = [&](void* ch,
                       const void* p, int n) {
        assert(ch == d.pChannel);
        if (nLastCh == 1)
            d.sSent.assign(
                (const char*)p, n);
        else
            d.sShellSent.assign(
                (const char*)p, n);
    };
    d.m_fnChRelease = [](void*){};
    d.m_fnFopen = []{ return (void*)0x777; };
    d.m_fnFread = [](unsigned char* out,
                     void* f) {
        assert(f == (void*)0x777);
        std::memset(out, 0xCD, 0x400);
        return (size_t)0x200; };
    d.m_fnFclose = [](void*){};

    // injectors
    d.uNow = 4000;

    // ===== 1. the flag setters
    g_uGateFlags = 0;
    MsgGateSet4();
    assert(g_uGateFlags == 4);
    assert(MsgGateSet4Ret() == 1);
    assert(g_uGateFlags == 4);

    // ===== 2. the date gate
    g_uGateFlags = 0;
    g_uGateLastTick = 0;
    // stamp tm -> fake mktime returns
    // tm[0]; set tm[0] = now - 100
    d.m_tmStamp[0] = 1780000000 - 100;
    assert(MsgGateCheckDate(d) == 1);
    assert(g_uGateFlags == 0x10);  // set
    // throttled: the second call within
    // 600000 ticks skips the check
    d.m_tmStamp[0] = 1780000000 +
        100000;   // would fail
    assert(MsgGateCheckDate(d) == 1);
    assert(g_uGateFlags == 0x10);
    // after the throttle window: bad date
    g_uGateLastTick = 0;
    assert(MsgGateCheckDate(d) == 0);
    assert(g_uGateFlags == 0x10);
    // far past (> 0x794a00) also fails
    g_uGateLastTick = 0;
    d.m_tmStamp[0] = 1780000000 -
        0x794a00 - 1;
    assert(MsgGateCheckDate(d) == 0);
    // exactly at the boundary passes
    g_uGateLastTick = 0;
    d.m_tmStamp[0] = 1780000000 -
        0x794a00;
    assert(MsgGateCheckDate(d) == 1);

    // ===== 3. the master gate
    d.uStampTime = 0;
    // not elapsed: thresh = 30+0xeda
    // = 0xef8; 3000 <= thresh
    // -> thresh & ~0xff = 0xe00
    d.uNow = 3000;
    assert(MsgGateMaster(d) == 0xe00);
    // elapsed + no flags -> pass 1
    d.uNow = 0x10000;
    assert(MsgGateMaster(d) == 1);
    // elapsed + flags 2|4 -> (2|4) pass
    g_uGateFlags = 6;
    assert(MsgGateMaster(d) == 1);
    // elapsed + flags 2|4|0x10 (0x16,
    // bit 8 CLEAR) -> fail -> 0
    g_uGateFlags = 0x16;
    assert(MsgGateMaster(d) == 0);
    // + flag 8 -> pass again
    g_uGateFlags = 0x16 | 8;
    assert(MsgGateMaster(d) == 1);
    // (0x1c = 4|8|0x10 passes via bit 8)
    g_uGateFlags = 0x1c;
    assert(MsgGateMaster(d) == 1);
    // upper flag bits survive the return
    g_uGateFlags = 0x16 | 0x200;
    assert(MsgGateMaster(d) == 0x200);
    g_uGateFlags = 0x200;
    assert(MsgGateMaster(d) == 0x201);

    // ===== 4. the fingerprint reporter
    d.sSent.clear();
    d.sShellSent.clear();
    char out[25];
    MsgReportFingerprint(out, d);
    assert(std::strcmp(out,
        "1a2b3c-4d5e-6f") == 0);
    assert(d.sSent == "1a2b3c-4d5e-6f");
    assert(d.nSends == 1);
    // channel null: still fills the out
    d.bChannelOk = false;
    d.sSent.clear();
    MsgReportFingerprint(out, d);
    assert(std::strcmp(out,
        "1a2b3c-4d5e-6f") == 0);

    // ===== 5. the shell.dat loader
    d.bChannelOk = true;
    d.sSent.clear();
    std::memset(g_shellData, 0,
        sizeof(g_shellData));
    unsigned char* p =
        MsgLoadShellDat(d);
    assert(p == g_shellData);
    assert(g_shellData[0] == 0xCD);
    assert(g_shellData[0xc3] == 0xCD);
    assert(d.sShellSent.size() == 0x200);
    assert(d.sShellSent[0] == (char)0xCD);

    printf("MSG_GATE_FLAGS_OK: "
           "FUN_140508ca0/cd0/d00/eb0/b80/"
           "dc0 VERBATIM (the DAT_140976718 "
           "gate word: |=4 setters, the "
           "600s-throttled date gate over "
           "the M17 stamp tm with the "
           "0x794a00 window -> 0x10, the "
           "master gate with the exact asm "
           "returns (thresh&~0xff / flag|1 "
           "/ flag&~0xff) and the "
           "8/2/4/0x10 flag pattern, the "
           "%02x MAC fingerprint reporter "
           "over channel 1, the shell.dat "
           "loader -> channel 0 + the "
           "0xc4 DAT_1409765d0 copy)\n");
    return 0;
}
