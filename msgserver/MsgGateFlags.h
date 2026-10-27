// ============================================================
// MsgServer strict port - unit M23
// The license/anti-tamper gate family
// over DAT_140976718 (the flag word):
//  FUN_140508ca0 @ 140508ca0: flag |= 4
//  FUN_140508cd0 @ 140508cd0: flag |= 4,
//    return 1
//  FUN_140508d00 @ 140508d00: the DATE
//    gate - GetTickCount throttled
//    0x927bf ticks (600s); copies the
//    stamp tm (DAT_1409766dc from M17)
//    into a local tm; now - mktime(tm)
//    must be in [0, 0x794a00] (92 days)
//    -> flag |= 0x10, return 1; else 0
//  FUN_140508eb0 @ 140508eb0: the MASTER
//    gate (from the asm):
//    elapsed = TimeGet(1) - stampTime;
//    thresh = RandGet(0x3c) + 0xeda;
//    if (elapsed <= thresh) return
//      (uint)thresh & 0xffffff00;
//    pass = (flag&8) || !(flag&2) ||
//           !(flag&4) || !(flag&0x10);
//    pass -> (flag & 0xffffff00) | 1
//    else -> flag & 0xffffff00
//  FUN_140508b80 @ 140508b80: the
//    fingerprint reporter - 6 bytes from
//    FUN_140507e50 -> sprintf "%02x%02x"
//    "%02x-%02x%02x-%02x" -> the channel
//    (FUN_140509280(1)) vt+8(str,len) +
//    vt+0 release; the 25-byte out
//  FUN_140508dc0 @ 140508dc0: the
//    shell.dat loader - fread 0x400 ->
//    channel(0) vt+0x10(data,len) ->
//    memcpy 0xc4 to DAT_1409765d0
// ============================================================
#pragma once
#include <cstdint>
#include <functional>
#include <string>

namespace msg {

extern uint32_t g_uGateFlags;   // 0x140976718
extern uint32_t g_uGateLastTick;  // 0x140976724
extern unsigned char g_shellData[0xc4];  // 0x1409765d0

struct MsgGateFlagsData {
    // tq::TimeGet(1) / tq::RandGet(0x3c)
    std::function<uint32_t(int)>
        m_fnTimeGet;
    std::function<int(int)>
        m_fnRandGet;
    // GetTickCount
    std::function<uint32_t()> m_fnTick;
    // the stamp tm (DAT_1409766dc) and
    // the stamp time (DAT_140976710)
    int m_tmStamp[9];
    uint32_t uStampTime = 0;
    // _time64 / _mktime64
    std::function<int64_t()> m_fnTime64;
    std::function<int64_t(int* /*tm9*/)>
        m_fnMktime;
    // FUN_140507e50 - the 6-byte MAC
    std::function<void(unsigned char*)>
        m_fnGetMac;
    // FUN_140509280(ch, &obj) - the
    // reporting channel getter
    std::function<void*(int)>
        m_fnGetChannel;
    // the channel's vt+8 / vt+0x10 send +
    // the vt+0 release
    std::function<void(void*, const
        void*, int)> m_fnChSend;
    std::function<void(void*)>
        m_fnChRelease;
    // fopen/fread/fclose for shell.dat
    std::function<void*()> m_fnFopen;
    std::function<size_t(unsigned char*,
        void*)> m_fnFread;
    std::function<void(void*)>
        m_fnFclose;
    // captures
    std::string sSent;   // what vt+8 got
    std::string sShellSent;
    int nSends = 0;
    // injectors
    void* pChannel = (void*)0x999;
    bool bChannelOk = true;
    uint32_t uNow = 0;
};

// ===== FUN_140508ca0
void MsgGateSet4(void);
// ===== FUN_140508cd0
int MsgGateSet4Ret(void);
// ===== FUN_140508d00
int MsgGateCheckDate(MsgGateFlagsData& rD);
// ===== FUN_140508eb0
uint32_t MsgGateMaster(MsgGateFlagsData& rD);
// ===== FUN_140508b80
void MsgReportFingerprint(char* pOut,
                          MsgGateFlagsData& rD);
// ===== FUN_140508dc0
unsigned char* MsgLoadShellDat(
    MsgGateFlagsData& rD);

} // namespace msg
