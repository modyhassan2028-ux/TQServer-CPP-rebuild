// ============================================================================
// cmsg.h — RAW CQBase.dll v6159 · tq::CMsg
//   the message base every module of the family derives from. The sixteen
//   bodies below are 0x140b9d3a0..0x140b9d650 of CQBase.dll:
//     +0x000 vftable            (the address is a symbol in the dump, no VA)
//     +0x008 the buffer: [0] wSize, [2] wType, [4..] payload
//     the buffer is 0x400 bytes and GetHeadSize answers 4
// ============================================================================
#ifndef CQBASE_MSG_CMSG_H
#define CQBASE_MSG_CMSG_H

#include <cstdint>

namespace tq {

// 0x140b9d3a0 — the four byte head: length then type
struct MsgHead {
    uint16_t wSize;
    uint16_t wType;
    MsgHead& operator=(const MsgHead& r);          // 0x140b9d3a0
};

class CMsg {
public:
    static constexpr uint32_t kBufSize = 0x400;    // memset(this+8,0,0x400)
    static constexpr uint16_t kHeadSize = 4;       // 0x140b9d3f0 answers 4

    void** pVft;                                   // +0x000
    uint8_t abBuf[kBufSize];                       // +0x008

    CMsg();                                        // 0x140b9d650
    CMsg(const CMsg& r);                           // 0x140b9d430
    virtual ~CMsg();                               // 0x140b9d3b0
    CMsg& operator=(const CMsg& r);                // 0x140b9d480

    void Init();                                   // 0x140b9d580  (protected)
    bool IsValid();                                // 0x140b9d5c0
    const char* GetBuf() const;                     // 0x140b9d3c0
    uint16_t GetSize() const;                       // 0x140b9d3d0
    uint16_t GetType() const;                       // 0x140b9d3e0
    uint16_t GetHeadSize();                         // 0x140b9d3f0

    // 0x140b9d5e0 — copy the four byte head then wSize payload bytes from pBody
    bool Create(const MsgHead& head, const char* pBody);
    // 0x140b9d610 — the buffer must carry its own length, and a zero type fails
    bool Create(const char* pBuf, uint16_t wBufSize);

    virtual void Process(void* pInfo);              // 0x140b9d400
    virtual void Process(uint32_t idActor);         // 0x140b9d410
    virtual void Process(uint32_t idActor, void* pInfo);  // 0x140b9d420
};

// the vftable: the dump names it `vftable` and gives no address, so the host
// installs it; every constructor stores exactly this word.
extern void* g_pVftCMsg;
// log_InlineLogERROR, the same seam shape the other modules use
extern void (*g_pfnCQBaseLog)(const char* fmt, ...);

}  // namespace tq
#endif
