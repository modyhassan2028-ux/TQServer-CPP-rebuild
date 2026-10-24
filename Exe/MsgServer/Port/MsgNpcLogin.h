// ============================================================
// MsgServer strict port - unit M1
// ORIGINAL: MsgServer.exe FUN_14045bc00 (the +0x428 key
// dispatcher) + FUN_14045b990 (the NpcServer login
// handler). The MsgServer side of the NpcServer login
// (NpcServer sends key 0x3ade68b1/b2 with the two
// literal passwords; MsgServer answers ANSWER_OK and
// the 0x9c41 keepalive).
// ============================================================
#pragma once
#include <cstdint>
#include <functional>
#include <string>
#include <vector>

namespace msg {

// FUN_14015b240..14015b2c0 record family (the
// SYSTEM/ALLUSERS chat record; 0x450 buffer + the
// descriptor fields written INLINE by FUN_14045b990:
// local_498=1, _4a0=0, _4a8=0, _4b0=0,
// _4b8=0x835, _4c0=0xffffff, _4c8=0)
struct MsgChatRecord {
    uint8_t  bFlag = 0;        // local_498 (1)
    uint32_t dwA = 0;           // local_4a0
    uint32_t dwB = 0;           // local_4a8
    uint16_t wC = 0;            // local_4b0
    uint16_t wColor835 = 0;      // local_4b8 (0x835)
    uint32_t dwColorFFFFFF = 0; // local_4c0
    const char* szText = nullptr; // local_4c8
    char buf[0x450] = {0};      // local_478 (1104)
};

// the login wire record at param_1+0x428
// (+0 dword key 0x3ade68b1/b2, +4 "NpcServer Tqdig"
//  16 bytes, +0x14 "skl8934##VJICW " 16 bytes -
//  the trailing space is LITERAL in the binary)
struct MsgLoginWire {
    uint32_t dwKey = 0;         // +0
    char szPwd1[16] = {0};       // +4
    char szPwd2[16] = {0};       // +0x14
};

// seams = the not-yet-ported callees:
//  FUN_140008520(*(dword*)(this+0x410)) - the kernel
//  singleton accessor: returns the kernel object whose
//  +0x80 holds the npc-server connection sender and
//  whose vtable holds +0x30(rec,0) broadcast
struct MsgNpcLoginData {
    // FUN_140008520 -> +0x80 sender (null -> the
    // log_InlineLogERROR(&DAT_1406d9c10) path,
    // plVar5 = 0 - VERBATIM: the success path then
    // dereferences the null sender)
    std::function<void*()> m_fnGetKernel;
    std::function<void*(void*)> m_fnGetSender; // +0x80
    // log_InlineLogERROR(&DAT_1406d9c10)
    std::function<void()> m_fnLogError;
    // the inline log register (local_4c8 stores the
    // message before the +0x50 sends - the inlined
    // log_InlineLogMessage pattern)
    std::function<void(const char*)> m_fnLog;
    // the +0x50 sender vcall: (type, id, param)
    std::function<void(void*, int, uint32_t, uint32_t)>
        m_fnSend;
    // the +0x30 kernel broadcast: (rec, 0)
    std::function<void(void*, void*)> m_fnBroadcast;
    // FUN_14015b240(rec) - record init
    std::function<void(MsgChatRecord*)> m_fnRecInit;
    // FUN_14015b300(rec,"SYSTEM","ALLUSERS",s) -> bool
    std::function<bool(MsgChatRecord*, const char*,
                       const char*, const char*)>
        m_fnRecBuild;
    // FUN_14015b2c0(rec) - release
    std::function<void(MsgChatRecord*)> m_fnRecRelease;
};

// FUN_14045b990(this, param_2, key==0x3ade68b1)
// returns 1 on success, 0 on refuse
bool MsgNpcLoginB990(MsgNpcLoginData& rD,
                     const MsgLoginWire& rWire,
                     bool bKeyB1);
// FUN_14045bc00: the +0x428 key dispatcher
void MsgNpcLoginDispatch(MsgNpcLoginData& rD,
                         const MsgLoginWire& rWire);

} // namespace msg
