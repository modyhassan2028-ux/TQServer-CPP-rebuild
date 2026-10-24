#include "MsgAiNpcInfo.h"
#include <cstring>

namespace npc {

// ===== ORIGINAL FUN_140061220 (ctor) =====
// FUN_140034920 base ctor: *(this+0x410)=0, vtable=
// CNetMsg::vftable, memset(this+0x10,0,0x400),
// *(this+0xc)=0, *(this+8)=0; then *this =
// CMsgAiNpcInfo::vftable; FUN_140034820: memset
// (this+0x10,0,0x400), +0xc=0, +8=0;
// *(this+0x418) = this+0x10 (buffer self-ptr)
CMsgAiNpcInfo::CMsgAiNpcInfo() {
    m_dwMsgId = 0;                     // +8
    m_dwSize = 0;                     // +0xc
    memset(&m_rec, 0, sizeof(m_rec)); // 0x400 buffer
    // *(this+0x418) = this+0x10 -> Buf()
}

// ===== ORIGINAL FUN_140061270 (dtor) =====
// *this = CMsgAiNpcInfo::vftable; FUN_140034810:
// *this = CNetMsg::vftable
CMsgAiNpcInfo::~CMsgAiNpcInfo() {
    // vtable swaps only - no field work
}

// ===== ORIGINAL FUN_140061490 (deleting dtor) =====
// *this = CMsgAiNpcInfo::vftable; FUN_140034810
// (CNetMsg vtable); if (flags & 1) operator_delete(this)
void CMsgAiNpcInfo::Destroy(uint32_t dwFlags) {
    if ((dwFlags & 1) != 0) delete this;
}

// ===== ORIGINAL FUN_1400612a0 (Create) =====
// if (ver != 1) { log_InlineLogERROR(&DAT_1400be0b0);
//   return 0; }
// FUN_140034820(this);                 // reset
// p = *(this+0x418);                   // buffer
// *(this+0xc) = 0x38;  *(this+8) = 0x4e21;
// *(word*)(p+0x1a) = param_5;  p[3] = 0;
// *(word*)(p+7) = 0;   p[4] = 0;      // 0x1c / 0x10
// p[1] = param_6;      p[8] = param_9;
// *(word*)(p+5) = param_7;  p[9] = param_10;
// p[10] = param_12;  *(byte*)(p+0xb) = param_11;
// *p = param_3;  *(word*)(p+0x16) = param_8;
// *(word*)(p+6) = 1;                   // tag @0x18
// p[0xd] = param_13;  p[2] = param_4;
// return 1;
bool CMsgAiNpcInfo::Create(int nVer,
        uint32_t dwField00, uint32_t dwField08,
        uint16_t wField1a, uint32_t dwField04,
        uint16_t wField14, uint16_t wField16,
        uint32_t dwField20, uint32_t dwField24,
        uint8_t bField2c, uint32_t dwField28,
        uint32_t dwField34) {
    if (nVer != 1) {
        m_vecLogs.push_back(
            "log_InlineLogERROR(&DAT_1400be0b0) !%s(%s)! in %s, %d");
        return false;
    }
    // FUN_140034820: reset buffer/size/id
    m_dwMsgId = 0; m_dwSize = 0;
    memset(&m_rec, 0, sizeof(m_rec));
    AiNpcInfoRecord* p = &m_rec;        // *(this+0x418)
    m_dwSize = 0x38;                    // *(this+0xc)
    m_dwMsgId = 0x4e21;                 // *(this+8)
    p->setw(0x1a, wField1a);            // *(word*)(p+0x1a)
    p->dw[3] = 0;                       // p[3]
    p->setw(0x1c, 0);                   // *(word*)(p+7)
    p->dw[4] = 0;                       // p[4]
    p->dw[1] = dwField04;               // p[1] = param_6
    p->dw[8] = dwField20;               // p[8] = param_9
    p->setw(0x14, wField14);            // *(word*)(p+5) = param_7
    p->dw[9] = dwField24;               // p[9] = param_10
    p->dw[10] = dwField28;             // p[10] = param_12
    p->setb(0x2c, bField2c);            // *(byte*)(p+0xb) = param_11
    p->dw[0] = dwField00;               // *p = param_3
    p->setw(0x16, wField16);            // *(word*)(p+0x16) = param_8
    p->setw(0x18, 1);                   // *(word*)(p+6) = 1
    p->dw[0xd] = dwField34;             // p[0xd] = param_13
    p->dw[2] = dwField08;               // p[2] = param_4
    return true;
}

// ===== ORIGINAL FUN_1400613a0 (CreateFromBuffer) =====
// if (*(short*)(buf+0x18) != 1) {
//   log_InlineLogERROR(&DAT_1400be0b0); return 0; }
// FUN_140034820(this); *(this+0xc)=0x38; *(this+8)=0x4e21;
// memcpy(*(this+0x418), buf, 0x38); return 1;
bool CMsgAiNpcInfo::CreateFromBuffer(const void* pBuf) {
    if (*(const uint16_t*)((const uint8_t*)pBuf + 0x18) != 1) {
        m_vecLogs.push_back(
            "log_InlineLogERROR(&DAT_1400be0b0) !%s(%s)! in %s, %d");
        return false;
    }
    m_dwMsgId = 0; m_dwSize = 0;
    memset(&m_rec, 0, sizeof(m_rec));
    m_dwSize = 0x38;
    m_dwMsgId = 0x4e21;
    memcpy(&m_rec, pBuf, 0x38);
    return true;
}

// ===== ORIGINAL FUN_140061430 (SetBuffer) =====
// if (pBuf == 0) return 0;
// memcpy(this+0x10, pBuf, cb); return 1;
bool CMsgAiNpcInfo::SetBuffer(const void* pBuf, uint32_t dwCb) {
    if (pBuf == nullptr) return false;
    memcpy(&m_rec, pBuf, dwCb);
    return true;
}

// ===== ORIGINAL FUN_1400614f0 (Process) =====
// if (conn == 0) return;
// rec = *(this+0x418);
// set = FUN_140025c40(FUN_14001c7a0());  // instance +8
// npc = vtable+0x40(set, rec[0]);        // find by id
// if (npc == 0):
//   npc = FUN_14005d9c0();               // new CNpc
//   if (npc != 0):
//     ok = FUN_14005e2e0(npc, rec[0], (word)rec+0x1a,
//            rec[1], (word)rec+0x14, (word)rec+0x16,
//            rec[2], rec[3], (word)rec+0x1c, rec[4],
//            rec[9], rec[8], (byte)rec[0xb], rec[10],
//            rec[0xc]);
//     if (!ok) vtable+0xf0(npc+0x10);
//     else:
//       set2 = FUN_140025c40(FUN_14001c7a0());
//       vtable+0x28(set2, npc+0x10);
//       if (rec[0xd] != 0) vtable+0x98(npc+0x10);
void CMsgAiNpcInfo::Process(void* pConn) {
    if (pConn == nullptr) return;
    AiNpcInfoRecord* pRec = Buf();
    void* pvSet = nullptr;              // FUN_14001c7a0 ->
                                        // FUN_140025c40
    void* pvNpc = m_fnFindNpcById(pRec->dw[0]);
    if (pvNpc != nullptr) return;       // exists: nothing
    CNpcObj* pNpc = m_fnNewNpc();        // FUN_14005d9c0
    if (pNpc == nullptr) return;
    bool bOk = m_fnNpcCreate(pNpc, *pRec);
    if (!bOk) {
        m_fnNpcFailF0(pNpc);            // vtable+0xf0
    } else {
        (void)pvSet;
        m_fnNpcRegister(pNpc);          // vtable+0x28
        if (pRec->dw[0xd] != 0)         // record +0x34
            m_fnNpcNotify98(pNpc);      // vtable+0x98
    }
}

} // namespace npc
