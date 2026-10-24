// ORIGINAL: CMsgAiNpcInfo from NpcServer.exe
//   FUN_140061220 ctor (66 bytes, vtable assign + base)
//   FUN_140061270 dtor (sets CNetMsg vtable)
//   FUN_1400612a0 Create (247 bytes, ver==1, 0x38 record)
//   FUN_1400613a0 CreateFromBuffer (134 bytes)
//   FUN_140061430 SetBuffer (38 bytes)
//   FUN_140061490 deleting dtor (76 bytes)
//   FUN_1400614f0 Process (288 bytes)
// The class inherits CNetMsg (FUN_140034920/140034820/140034810):
//   +0x00 vtable, +0x08 msg id, +0x0c size,
//   +0x10..+0x410 = 0x400 buffer, +0x418 = buffer self-ptr
// Message id 0x4e21 (20001), record size 0x38.
#pragma once
#include <stdint.h>
#include <functional>
#include <string>
#include <vector>

namespace npc {

// the 0x38-byte AiNpcInfo record laid into the buffer
// (offsets are relative to the record start; the Create
// order and the word@+0x18==1 tag are verbatim):
//   +0x00 id (dword), +0x04, +0x08, +0x0c (zeroed),
//   +0x10 (zeroed), +0x14 (word), +0x16 (word),
//   +0x18 (word, == 1), +0x1a (word type), +0x1c (word),
//   +0x20, +0x24, +0x28, +0x2c (byte), +0x30, +0x34
struct AiNpcInfoRecord {
    uint32_t dw[0xe];                 // 0x38 bytes
    uint16_t w(uint32_t off) const {
        return *(const uint16_t*)((const uint8_t*)dw + off);
    }
    void setw(uint32_t off, uint16_t v) {
        *(uint16_t*)((uint8_t*)dw + off) = v;
    }
    uint8_t b(uint32_t off) const {
        return *((const uint8_t*)dw + off);
    }
    void setb(uint32_t off, uint8_t v) {
        *((uint8_t*)dw + off) = v;
    }
};

// CNpc object (allocated by FUN_14005d9c0:
// operator_new(0x158) + ctor FUN_14005ce80). The vtable
// calls in Process run on the +0x10 sub-object.
// Full 0x158 layout lives in NpcCreate.h (CNpcObject);
// here only the carrier seam.
struct CNpcObj {
    void* m_pSub10 = nullptr;          // npc + 0x10
};

class CMsgAiNpcInfo {
public:
    CMsgAiNpcInfo();                   // FUN_140061220
    ~CMsgAiNpcInfo();                  // FUN_140061270
    // FUN_140061490 (deleting dtor): bDeleteSelf
    void Destroy(uint32_t dwFlags);

    // ===== ORIGINAL FUN_1400612a0 =====
    // ver(param_2) must be 1; builds the 0x38 record.
    // p3=type word target, order verbatim.
    bool Create(int nVer,
                uint32_t dwField00, uint32_t dwField08,
                uint16_t wField1a, uint32_t dwField04,
                uint16_t wField14, uint16_t wField16,
                uint32_t dwField20, uint32_t dwField24,
                uint8_t bField2c, uint32_t dwField28,
                uint32_t dwField34);

    // ===== ORIGINAL FUN_1400613a0 =====
    // accepts an existing 0x38 record whose word@0x18==1
    bool CreateFromBuffer(const void* pBuf);

    // ===== ORIGINAL FUN_140061430 =====
    // memcpy(this+0x10, pBuf, cb); pBuf==0 -> false
    bool SetBuffer(const void* pBuf, uint32_t dwCb);

    // ===== ORIGINAL FUN_1400614f0 =====
    // pConn==0 -> return. Lookup npc by id; if found:
    // nothing. Else new + Create; Create false ->
    // vtable+0xf0(npc+0x10); Create true -> register
    // (vtable+0x28 on the set manager) and if record
    // +0x34 != 0 -> vtable+0x98(npc+0x10).
    void Process(void* pConn);

    // base (CNetMsg) fields - verbatim layout
    uint32_t m_dwMsgId = 0;            // +0x08
    uint32_t m_dwSize = 0;             // +0x0c
    AiNpcInfoRecord m_rec;             // +0x10 (0x38 used)

    // record accessor used by Process (this+0x418)
    AiNpcInfoRecord* Buf() { return &m_rec; }

    // ---------- seams (ORIGINAL callees) ----------
    // FUN_14001c7a0 -> FUN_140025c40 (instance +8
    // getter) then vtable+0x40(set, id): find npc
    std::function<void* (uint32_t)> m_fnFindNpcById;
    // FUN_14005d9c0: new CNpc (0x158) + ctor
    std::function<CNpcObj* ()> m_fnNewNpc;
    // FUN_14005e2e0: CNpc::Create(npc, id, ...) - the
    // 15-arg fill (UNIT-10 candidate; seam for now)
    std::function<bool(CNpcObj*, const AiNpcInfoRecord&)> m_fnNpcCreate;
    // vtable+0xf0 on npc+0x10 (Create failed path)
    std::function<void(CNpcObj*)> m_fnNpcFailF0;
    // vtable+0x28 on the set manager (register)
    std::function<void(CNpcObj*)> m_fnNpcRegister;
    // vtable+0x98 on npc+0x10 (record+0x34 != 0)
    std::function<void(CNpcObj*)> m_fnNpcNotify98;

    // error-log sink
    std::vector<std::string> m_vecLogs;
};

} // namespace npc
