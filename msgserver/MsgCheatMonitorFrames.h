#ifndef MSG_CHEAT_MONITOR_FRAMES_H
#define MSG_CHEAT_MONITOR_FRAMES_H
// ===== Path-A wave 9j: the two frame handlers + the state getter =====
// 140001900 (0x30 frame) — null frame -> noarg log; the port object
//   from 14050c340(5), null -> noarg log; the 0x30 bytes are copied
//   into a local block whose LAST byte is cleared (local_18 masked
//   with 0xffffffffffffff); when frame byte 0xf is 0 the 0x21 bytes
//   at +0xf are filled from IStringManager "STR_GENERAL_BOT_SIN";
//   then Post(port, 0xe, 0xea61, 0x30, block).
// 140001a50 (0xf frame) — null -> log; port null -> log;
//   operator_new(0x30) null -> log; six qwords zeroed, then
//   *(u32)=frame[0], *(u16)(+4)=frame+4 (the cheat kind),
//   strncpy(+6, frame+6, 9); the kind picks the string:
//     1 STR_GENERAL_BOT_SIN, 2 STR_KEY_BOT_SIN,
//     3 STR_SERIOUS_BOT_SIN, 4 STR_HACK_TOOL_SIN
//   (each strncpy to +0xf, 0x21); any other kind logs
//   "CCheatingProgramMonitor::ProcessMsg, wrong cheat type : %u"
//   and RETURNS WITHOUT deleting the block (RAW leak, preserved);
//   otherwise Post(port, 0xe, 0xea61, 0x30, block) + delete.
// 14001f4c0 — the thread state: return *(u32*)(p + 0x1fc).
#include <cstdint>
#include <cstddef>
namespace msg {
static const int kMonFrame30   = 0x30;
static const int kMonFrame15   = 0x0f;
static const int kMonSinMax    = 0x21;
static const int kMonPostId    = 0x0e;
static const int kMonPostMsg   = 0xea61;
static const int kMonThreadStateOff = 0x1fc;
struct SMonFrameSeams {
    void  (*LogErrNoArg)();
    void  (*LogErrFmt)(const char* fmt, ...);
    void* (*PortObjGet)(int idx);                 // 14050c340
    void  (*PostMsg)(void* port, int id, int msg, uint32_t len,
                     void* data);                 // vtable+0x50
    const char* (*GetString)(const char* key);    // IStringManager
    void* (*Alloc)(size_t n);
    void  (*Free)(void* p);
};
void CheatMonitorHandle30(void* frame, const SMonFrameSeams& s);
void CheatMonitorHandle15(void* frame, const SMonFrameSeams& s);
uint32_t CheatMonitorThreadState(void* p);
}
#endif
