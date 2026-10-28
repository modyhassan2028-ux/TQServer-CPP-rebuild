// ============================================================
// CCheatingProgramMonitor — forwarding to the verified wave units.
// ============================================================
#include "cheatingprogrammonitor.h"
#include <cstring>
namespace msg {
CCheatingProgramMonitor::CCheatingProgramMonitor() : m_Inited(false) {
    memset(&m_State, 0, sizeof m_State);
}
CCheatingProgramMonitor::~CCheatingProgramMonitor() {
    for (size_t i = 0; i < MSG_CHEAT_MAX_CLIENTS; ++i) {
        if (m_State.slots[i] != nullptr) {
            delete m_State.slots[i];
            m_State.slots[i] = nullptr;
        }
    }
}
// 140003dc0 prologue
bool CCheatingProgramMonitor::Init(MsgCheatSeams& seams) {
    bool ok = MsgCheatMonitorInit(m_State, seams);
    m_Inited = ok;
    return ok;
}
// the loop pass
bool CCheatingProgramMonitor::Tick(MsgCheatSeams& seams) {
    return MsgCheatMonitorTick(m_State, seams);
}
// the shutdown path
void CCheatingProgramMonitor::Stop(MsgCheatSeams& seams) {
    MsgCheatMonitorStop(m_State, seams);
    m_Inited = false;
}
// 140002510
void CCheatingProgramMonitor::ProcessRecv(MsgCheatClientInfo* slot,
                                          MsgCheatSeams& seams) {
    MsgCheatProcessRecv(slot, seams);
}
// 140001c70
int CCheatingProgramMonitor::DecryptMsg(uint8_t* msg, long len, int* num,
                                        uint8_t* ivec,
                                        MsgCheatSeams& seams) {
    return MsgCheatDecryptMsg(msg, len, m_State.ks, num, ivec, seams);
}
// the packet layer
int CCheatingProgramMonitor::ParsePacket(uint8_t* p, int len, void* ks,
                                         void* ivec, void* keyState,
                                         const SMonPacketSeams& s) {
    return CheatMonitorParsePacket(p, len, ks, ivec, keyState, s);
}
void CCheatingProgramMonitor::ProcessPackets(SMonClient* c,
                                             const SMonPacketSeams& s) {
    CheatMonitorProcessPackets(c, s);
}
// 140001900
void CCheatingProgramMonitor::ProcessMsg30(void* frame,
                                           const SMonFrameSeams& s) {
    CheatMonitorHandle30(frame, s);
}
// 140001a50
void CCheatingProgramMonitor::ProcessMsg15(void* frame,
                                           const SMonFrameSeams& s) {
    CheatMonitorHandle15(frame, s);
}
// 14001f4c0
uint32_t CCheatingProgramMonitor::GetThreadState(void* port) {
    return CheatMonitorThreadState(port);
}
// 14050c340(5)
void* CCheatingProgramMonitor::GetPort(void* (*portObjGet)(int)) {
    if (portObjGet == nullptr) return nullptr;
    return portObjGet(5);
}
MsgCheatClientInfo** CCheatingProgramMonitor::Clients() {
    return m_State.slots;
}
int CCheatingProgramMonitor::ClientCount() const {
    return m_State.nclients;
}
MsgCheatMonitorState& CCheatingProgramMonitor::State() { return m_State; }
}
