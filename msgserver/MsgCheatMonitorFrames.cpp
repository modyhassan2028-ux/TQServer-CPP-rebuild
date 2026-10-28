// ===== Path-A wave 9j: 140001900 / 140001a50 / 14001f4c0 =====
#include "MsgCheatMonitorFrames.h"
#include <cstring>
#include <cstdarg>
namespace msg {
// 140001900 — the 0x30 frame
void CheatMonitorHandle30(void* frame, const SMonFrameSeams& s) {
    if (frame == nullptr) {
        s.LogErrNoArg();
        return;
    }
    void* port = s.PortObjGet(5);
    if (port == nullptr) {
        s.LogErrNoArg();
        return;
    }
    uint8_t block[kMonFrame30];
    memcpy(block, frame, kMonFrame30);
    block[kMonFrame30 - 1] = 0;             // local_18 &= 0xff..
    if (((uint8_t*)frame)[0x0f] == 0) {
        const char* sin = s.GetString("STR_GENERAL_BOT_SIN");
        if (sin != nullptr) {
            strncpy((char*)block + 0x0f, sin, kMonSinMax);
        }
    }
    s.PostMsg(port, kMonPostId, kMonPostMsg, kMonFrame30, block);
}
// 140001a50 — the 0xf frame
void CheatMonitorHandle15(void* frame, const SMonFrameSeams& s) {
    if (frame == nullptr) {
        s.LogErrNoArg();
        return;
    }
    void* port = s.PortObjGet(5);
    if (port == nullptr) {
        s.LogErrNoArg();
        return;
    }
    uint8_t* b = (uint8_t*)s.Alloc(kMonFrame30);
    if (b == nullptr) {
        s.LogErrNoArg();
        return;
    }
    memset(b, 0, kMonFrame30);
    memcpy(b, frame, 4);                    // *(u32) = frame[0]
    memcpy(b + 4, (char*)frame + 4, 2);     // the cheat kind
    strncpy((char*)b + 6, (const char*)frame + 6, 9);
    uint16_t kind = *(uint16_t*)((char*)frame + 4);
    const char* key = nullptr;
    switch (kind) {
        case 1: key = "STR_GENERAL_BOT_SIN"; break;
        case 2: key = "STR_KEY_BOT_SIN";     break;
        case 3: key = "STR_SERIOUS_BOT_SIN"; break;
        case 4: key = "STR_HACK_TOOL_SIN";   break;
        default:
            s.LogErrFmt("CCheatingProgramMonitor::ProcessMsg,"
                        " wrong cheat type : %u", (unsigned)kind);
            return;                          // RAW: the block leaks
    }
    const char* sin = s.GetString(key);
    if (sin != nullptr) {
        strncpy((char*)b + kMonFrame15, sin, kMonSinMax);
    }
    s.PostMsg(port, kMonPostId, kMonPostMsg, kMonFrame30, b);
    s.Free(b);
}
// 14001f4c0 — the thread state
uint32_t CheatMonitorThreadState(void* p) {
    return *(uint32_t*)((char*)p + kMonThreadStateOff);
}
}
