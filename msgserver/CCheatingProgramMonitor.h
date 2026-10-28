#ifndef C_CHEATING_PROGRAM_MONITOR_H
#define C_CHEATING_PROGRAM_MONITOR_H
// ============================================================
// CCheatingProgramMonitor — the complete unit, one class / one file.
//
// Every method body lives in a wave that was ported from the RAW
// disassembly and locked by its own regression unit; this class is
// the ORIGINAL unit those bodies belong to, with the RAW member
// layout and the RAW method names where the binary proves them:
//
//   RAW name evidence (log literals inside the binary):
//     "CCheatingProgramMonitor::ProcessMsg, wrong cheat type : %u"
//        -> 140001a50 is ProcessMsg (the 0xf frame).
//     140001900 (the 0x30 frame) carries no class-name literal, so
//     it is exposed as ProcessMsg30 (named by frame size, stated as
//     such rather than invented).
//     14001f4c0 is the thread-state read at +0x1fc -> GetThreadState.
//     14050c340(5) is the port binding -> GetPort.
//
// Layout, from the RAW: the monitor owns one MsgCheatMonitorState
// (the 64 slots, the DES schedule, the key "df29duw", ivec, num)
// plus the frame/packet seam sets. Slot stride is 0x8020
// (MsgCheatClientInfo), 0x40 slots, max 0x14 bound IPs, port 0x23be.
//
// The wave files stay the single source of behaviour; this class
// forwards to them verbatim so nothing is duplicated or rewritten.
// ============================================================
#include "MsgCheatMonitor.h"
#include "MsgCheatMonitorPackets.h"
#include "MsgCheatMonitorFrames.h"
#include "MsgCheatMonitorThread.h"
namespace msg {
class CCheatingProgramMonitor {
public:
    CCheatingProgramMonitor();
    ~CCheatingProgramMonitor();
    // --- lifecycle: 140003dc0 (the thread prologue / loop / exit)
    bool Init(MsgCheatSeams& seams);
    bool Tick(MsgCheatSeams& seams);
    void Stop(MsgCheatSeams& seams);
    // --- packet layer: 140002510 (recv demux) + 140001c70 (decrypt)
    void ProcessRecv(MsgCheatClientInfo* slot, MsgCheatSeams& seams);
    int  DecryptMsg(uint8_t* msg, long len, int* num, uint8_t* ivec,
                    MsgCheatSeams& seams);
    int  ParsePacket(uint8_t* p, int len, void* ks, void* ivec,
                     void* keyState, const SMonPacketSeams& s);
    void ProcessPackets(SMonClient* c, const SMonPacketSeams& s);
    // --- the two frame handlers
    void ProcessMsg30(void* frame, const SMonFrameSeams& s);
    void ProcessMsg15(void* frame, const SMonFrameSeams& s);
    // --- 14001f4c0
    static uint32_t GetThreadState(void* port);
    // --- 14050c340(5)
    static void* GetPort(void* (*portObjGet)(int));
    // --- the slot pool
    MsgCheatClientInfo** Clients();
    int  ClientCount() const;
    MsgCheatMonitorState& State();
private:
    MsgCheatMonitorState m_State;          // the RAW thread state block
    bool                 m_Inited;
};
}
#endif
