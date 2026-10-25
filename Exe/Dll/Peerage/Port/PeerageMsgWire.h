// ============================================================
// Peerage.dll port — unit T6/D22: the CMsgLogin /
// CMsgPeerage wire family + the module's ProcessMsg.
// Addresses verbatim: 1415571b0 (login Create +
// 0x3ea gate), 1415571e0 (login send), 141557240
// (login deleting dtor), 141557350 (type-1 build),
// 141557440 (type-2 build), 141557580 (type-4 build),
// 1415575e0 (peerage Create + 0x810 gate), 141557610
// (the packer AddString + the size header),
// 141557690 (the send dispatcher by the type at
// buf+4), 141557740 (the 0x30 record append),
// 141557880 (peerage deleting dtor), 141551310/320
// (the module vtable stubs), 1415513c0 (ProcessMsg).
// ============================================================
#pragma once
#include <cstdint>

namespace peerage {

struct CMsgBase;      // PeerageModule.h
struct CModule;       // PeerageModule.h

// ---- the new seams ----
// tq::CMsg::Create: (msg, buf, len) -> bool
extern bool (*g_fnCMsgCreate)(void*, char*, uint16_t);
// tq::CStringPacker::AddString (packer at msg+0x410)
extern void (*g_fnPackerAddString)(void*, char*);
// tq::CStringPacker::GetSize -> uint
extern unsigned (*g_fnPackerGetSize)(void*);
// TBD-350-ARG4: the 4th vararg (%I64u) of the
// 141557350 _snprintf — Ghidra drops the varargs;
// only 4 locals are visible for 5 specifiers.
extern uint64_t (*g_fnBuild1Arg4)();

// FUN_1415571b0: Create + the 0x3ea gate
bool MsgLoginCreate(CMsgBase* p, char* pBuf,
                    uint16_t uLen);
// FUN_1415571e0: (msg, a, recipient) — null -> log;
// else recipient vt+0x30
void MsgLoginSend(void* pMsg, uint64_t uA,
                  void* pRecv);
// FUN_141557240: the login deleting dtor
CMsgBase* MsgLoginDeletingDtor(CMsgBase* p,
                               uint8_t uFlags);
// FUN_141557350: the type-1 build (the header
// {0xa8,0x810,1,id} + the "%u %u %I64u %I64u %d"
// append via the msg vt+0x48)
char BuildMsgType1(CMsgBase* p, uint32_t uId,
                  uint32_t uA3, uint64_t uA4,
                  uint64_t uA5, int32_t nA6);
// FUN_141557440: the type-2 build — {0xa8, 0x810,
// 2, u16, u16, 0} — returns 1 (AL)
uint64_t BuildMsgType2(CMsgBase* p, uint16_t uA,
                       uint16_t uB);
// FUN_141557580: the type-4 build — {0xa8, 0x810,
// 4} + memcpy(buf+8, src, 0x60) — returns 1 (AL)
uint64_t BuildMsgType4(CMsgBase* p, uint64_t uA,
                       void* pSrc);
// FUN_1415575e0: Create + the 0x810 gate
bool MsgPeerageCreate(CMsgBase* p, char* pBuf,
                      uint16_t uLen);
// FUN_141557610: AddString + buf[0] = size + 0xa7
// (returns AL=1)
uint32_t AppendStringPacked(void* pMsg, char* pStr);
// FUN_141557690: the send dispatcher (buf+4: 1 ->
// recv vt+0x10(msg, a, buf+8, *(u16*)(buf+0x68));
// 2 -> vt+0x18(a, *(u16*)(buf+8)); 3 -> vt+0x20;
// 4 -> vt+0x38)
void SendPeerageMsg(void* pMsg, uint64_t uA,
                    void* pRecv);
// FUN_141557740: the 0x30 record append at
// buf+0x78+idx*0x30, count at buf+0xc, header
// size = count*0x30 + 0xa8 — returns 1 (AL)
uint64_t AppendPeerageRecord(CMsgBase* p,
                             uint32_t uId,
                             uint8_t uState,
                             uint32_t uA4,
                             char* pName,
                             uint64_t uA6,
                             uint32_t uA7,
                             uint32_t uA8);
// FUN_141557880: the peerage deleting dtor
CMsgBase* MsgPeerageDeletingDtor(CMsgBase* p,
                                  uint8_t uFlags);
// FUN_1415513c0: (module, id, hdr, len) — GetMsg ->
// msg vt+0x10(id, svc) -> msg[1] as u16
uint16_t ModuleProcessMsg(CModule* p, uint32_t uId,
                          uint16_t* puHdr,
                          uint16_t uLen);
// FUN_141551310 / 141551320: the module vtable
// stubs (void / return 1)
void ModuleStubVoid();
uint64_t ModuleStubOne();

} // namespace peerage
