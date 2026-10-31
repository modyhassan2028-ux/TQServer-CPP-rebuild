// CQBase.dll v6159 — tq::CMsg, transcribed from 0x140b9d3a0..0x140b9d650.
#include "modules/cqbase/src/cmsg.h"

#include <cstring>

namespace tq {

void* g_pVftCMsg = nullptr;
static void DefLog(const char*, ...) {}
void (*g_pfnCQBaseLog)(const char* fmt, ...) = DefLog;

MsgHead& MsgHead::operator=(const MsgHead& r) {
    *reinterpret_cast<uint32_t*>(this) = *reinterpret_cast<const uint32_t*>(&r);
    return *this;
}

// 0x140b9d650 — the vftable goes in, the whole buffer is cleared, and the
// length and type words are written again.
CMsg::CMsg() {
    pVft = (void**)g_pVftCMsg;
    std::memset(abBuf, 0, kBufSize);
    *reinterpret_cast<uint16_t*>(abBuf) = 0;
    *reinterpret_cast<uint16_t*>(abBuf + 2) = 0;
}

// 0x140b9d430 — the copy construction copies all 0x400 bytes and then rewrites
// the first four of them.
CMsg::CMsg(const CMsg& r) {
    pVft = (void**)g_pVftCMsg;
    std::memcpy(abBuf, r.abBuf, kBufSize);
    *reinterpret_cast<uint32_t*>(abBuf) = *reinterpret_cast<const uint32_t*>(r.abBuf);
}

// 0x140b9d3b0 — the destructor only restores the vftable; the buffer is a
// plain array and nothing is freed.
CMsg::~CMsg() {
    pVft = (void**)g_pVftCMsg;
}

// 0x140b9d480 — the original walks the buffer two bytes at a time for 0x200
// steps (0x400 bytes) and then copies the first four bytes once more. Kept as
// the byte pair loop rather than a memcpy so the shape matches.
CMsg& CMsg::operator=(const CMsg& r) {
    uint8_t* pDst = abBuf;
    const uint8_t* pSrc = r.abBuf + 1;
    long long n = 0x200;
    do {
        n = n - 1;
        pDst[0] = pSrc[-1];
        pDst[1] = pSrc[0];
        pDst += 2;
        pSrc += 2;
    } while (n != 0);
    *reinterpret_cast<uint32_t*>(abBuf) = *reinterpret_cast<const uint32_t*>(r.abBuf);
    return *this;
}

// 0x140b9d580 — clear the buffer, then both head words.
void CMsg::Init() {
    std::memset(abBuf, 0, kBufSize);
    *reinterpret_cast<uint16_t*>(abBuf) = 0;
    *reinterpret_cast<uint16_t*>(abBuf + 2) = 0;
}

// 0x140b9d5c0 — a message needs at least five bytes and a non-zero type.
bool CMsg::IsValid() {
    if (*reinterpret_cast<uint16_t*>(abBuf) < 5) return false;
    return *reinterpret_cast<int16_t*>(abBuf + 2) != 0;
}

// 0x140b9d3c0 — the buffer address itself.
const char* CMsg::GetBuf() const { return (const char*)abBuf; }

// 0x140b9d3d0 / 0x140b9d3e0 / 0x140b9d3f0
uint16_t CMsg::GetSize() const { return *reinterpret_cast<const uint16_t*>(abBuf); }
uint16_t CMsg::GetType() const {
    return *reinterpret_cast<const uint16_t*>(abBuf + 2);
}
uint16_t CMsg::GetHeadSize() { return kHeadSize; }

// 0x140b9d5e0 — a null body fails before anything is written; the head goes in
// as one dword and the body follows at +0x0c for head.wSize bytes.
bool CMsg::Create(const MsgHead& head, const char* pBody) {
    if (pBody == nullptr) return false;
    *reinterpret_cast<uint32_t*>(abBuf) = *reinterpret_cast<const uint32_t*>(&head);
    std::memcpy(abBuf + 4, pBody, (uint64_t)head.wSize);
    return true;
}

// 0x140b9d610 — the declared size must equal the size word inside the buffer;
// a zero type copies nothing and answers false, otherwise the whole thing is
// copied and true is returned.
bool CMsg::Create(const char* pBuf, uint16_t wBufSize) {
    if ((pBuf != nullptr) && (wBufSize == *reinterpret_cast<const uint16_t*>(pBuf))) {
        int16_t sType = *reinterpret_cast<const int16_t*>(pBuf + 2);
        if (sType != 0) {
            std::memcpy(abBuf, pBuf, (uint64_t)wBufSize);
        }
        return sType != 0;
    }
    return false;
}

// 0x140b9d400 / 0x140b9d410 / 0x140b9d420 — the three virtuals report
// themselves and do nothing else.
void CMsg::Process(void*) {
    g_pfnCQBaseLog("tq::CMsg::Process(void* pInfo) error");
}
void CMsg::Process(uint32_t) {
    g_pfnCQBaseLog("tq::CMsg::Process(OBJID idActor) error");
}
void CMsg::Process(uint32_t, void*) {
    g_pfnCQBaseLog("tq::CMsg::Process(OBJID idActor, void* pInfo) error");
}

}  // namespace tq
