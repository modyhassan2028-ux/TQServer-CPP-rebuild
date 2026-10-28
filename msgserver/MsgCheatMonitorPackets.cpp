// ===== Path-A wave 9i: 140001c70 + 140002510 =====
#include "MsgCheatMonitorPackets.h"
#include <cstring>
#include <cstdarg>
namespace msg {
// 140001c70 — the DES-CFB64 in-place decrypt
int CheatMonitorParsePacket(uint8_t* p, int len, void* ks,
                            void* ivec, void* keyState,
                            const SMonPacketSeams& s) {
    if (p == nullptr) {
        s.LogMessage("Cheating Program Monitor invalid msg");
        return 0;
    }
    if ((unsigned)(len - 1) < 0x30) {   // len in 1..0x30
        if (keyState == nullptr) {
            return 0;
        }
        s.DesCfb64(p, len, ks, ivec, keyState, 0);  // decrypt
        return 1;
    }
    return 0;
}
// 140002510 — the frame splitter
void CheatMonitorProcessPackets(SMonClient* c,
                                const SMonPacketSeams& s) {
    if (c == nullptr) {
        s.LogErrNoArg();
        return;
    }
    for (uint32_t guard = 1; guard < 0x3e9; ++guard) {  // 1..1000
        int used = c->used;                             // +0x1c
        if (used < 8) {
            return;
        }
        uint8_t* dst = c->data;                         // +0x20
        uint16_t kind = *(uint16_t*)((char*)c + 0x24);  // buf+4
        if (kind == 0) {
            if (used < 0x30) {
                return;
            }
            s.Handle30(dst);                            // 140001900
            // RAW: memmove(dst, p+0x50, used - 0x30)
            memmove(dst, (char*)c + 0x50, (size_t)(used - 0x30));
            c->used = c->used - 0x30;
        } else {
            if ((unsigned)(kind - 1) > 3) {             // 1..4 only
                return;
            }
            if (used < 0xf) {
                return;
            }
            s.Handle15(dst);                            // 140001a50
            // RAW: memmove(dst, p+0x2f, used - 0xf)
            memmove(dst, (char*)c + 0x2f, (size_t)(used - 0xf));
            c->used = c->used - 0xf;
        }
    }
    s.LogErrNoArg();
}
}
