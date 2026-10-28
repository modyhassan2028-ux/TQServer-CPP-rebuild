#ifndef MSG_CHEAT_MONITOR_PACKETS_H
#define MSG_CHEAT_MONITOR_PACKETS_H
// ===== Path-A wave 9i: the monitor packet layer =====
// 140001c70 ParsePacket  — p==0 -> "Cheating Program Monitor
//                          invalid msg"; else only len in 1..0x30
//                          is accepted and, when the key state is
//                          non-null, DES_cfb64_encrypt(p,p,len,ks,
//                          ivec,state,0) decrypts IN PLACE and
//                          returns 1 (other lengths return 0)
// 140002510 ProcessPackets — up to 1000 frames per call:
//                          used(+0x1c) < 8 -> return; u16 at
//                          buf+4 == 0 -> a 0x30 frame (handler
//                          140001900, shift by 0x30); else only
//                          values 1..4 -> a 0xf frame (handler
//                          140001a50, shift by 0xf); anything else
//                          returns; over 1000 frames -> noarg log
// 140005d20 Close        — identical to AuthClientClose (sock=-1,
//                          state/szA/szB=0); already ported, so the
//                          auth unit owns it
// 140002c50 / 140003cf0  — tr1::_Ref_count construction and vector
//                          push_back for the shared_ptr slots: MFC
//                          bookkeeping, documented out of scope
#include <cstdint>
#include "MsgCheatMonitorThread.h"
namespace msg {
struct SMonPacketSeams {
    void (*LogErrNoArg)();
    void (*LogErrStr)(const char* s);
    void (*LogMessage)(const char* fmt, ...);
    void (*DesCfb64)(uint8_t* buf, int len, void* ks, void* ivec,
                     void* state, int mode);
    void (*Handle30)(void* frame);      // 140001900
    void (*Handle15)(void* frame);      // 140001a50
};
int  CheatMonitorParsePacket(uint8_t* p, int len, void* ks,
                             void* ivec, void* keyState,
                             const SMonPacketSeams& s);
void CheatMonitorProcessPackets(SMonClient* c,
                                const SMonPacketSeams& s);
}
#endif
