// ============================================================
// MsgServer strict port - unit M2
// ORIGINAL: the CMsgTalk record family
//  FUN_14015b240 (ctor) / FUN_14015b300 (Create)
//  / FUN_14015b2c0 (dtor)
// Object layout (from the ctor):
//  +0x000 CMsgTalk::vftable
//  +0x008 dword = 0x3ec (the msg id, written by Create)
//  +0x00c dword = packer size + 0x1f
//  +0x010 the inner talk header (the +0x428 target:
//         ctor stores this+0x10 there)
//           +0x00 TimeGet(0)
//           +0x04 dword (param_6)
//           +0x08 word (param_7)  +0x0a word (param_8)
//           +0x0c SysTimeGet()
//           +0x14 dword (param_9) +0x18 dword (param_10)
//           +0x1c byte (param_11)
//  +0x02d the packer buffer (0x3e1 bytes)
//  +0x430 the tq::CStringPacker (a SHARED-DLL import -
//          not decompiled in MsgServer.exe; seam)
// ============================================================
#pragma once
#include <cstdint>
#include <functional>

namespace msg {

struct MsgTalkRecord {
    // the object body (0x450 stack slot in the
    // FUN_14045b990 frame: local_478 [1104])
    uint8_t ab[0x450];
    // ---- packer seams (the tq DLL import) ----
    std::function<void()> m_fnPackerCtor;   // +0x86 slot
    std::function<void()> m_fnPackerDtor;
    // SetBuf(buf = this+0x2d, 0x3e1, true)
    std::function<void(char*, uint32_t, bool)>
        m_fnPackerSetBuf;
    // AddString(s) -> bool (the position advances)
    std::function<bool(const char*)> m_fnPackerAdd;
    // GetSize() -> uint (0 when nothing packed)
    std::function<uint32_t()> m_fnPackerGetSize;
    // tq::TimeGet(0) / tq::SysTimeGet()
    std::function<uint32_t()> m_fnTimeGet;
    std::function<uint32_t()> m_fnSysTime;
    // the ctor's vtable marker write (+0)
    void* m_pVftable = nullptr;

    template <typename T>
    T& At(uint32_t off) {
        return *(T*)((char*)ab + off); }
    template <typename T>
    T At(uint32_t off) const {
        return *(const T*)((const char*)ab + off); }
};

// FUN_1402ba1c0: the CNetMsg base ctor
//  (+0 vftable, +8 dword 0, +0xc dword 0,
//   +0x10..0x410 the 0x400 msg buffer zeroed,
//   +0x418/+0x41c/+0x420/+0x424 dwords 0)
void MsgTalkNetCtor(MsgTalkRecord* p);
// FUN_1402b5600: the base clear (memset +0x10
//  0x400, +0xc = 0, +8 = 0 - NOTE the LITERAL
//  DOUBLE CLEAR: 15b240 calls 2ba1c0 first,
//  then this one re-clears the same fields)
void MsgTalkBaseClear(MsgTalkRecord* p);
// FUN_1402b55f0: *this = CNetMsg::vftable
void MsgTalkBaseDtor(MsgTalkRecord* p);
// FUN_14015b240: ctor (2ba1c0, CMsgTalk::vftable,
// packer ctor, 2b5600, +0x428 = this+0x10,
// SetBuf(this+0x2d,0x3e1,true))
void MsgTalkCtor(MsgTalkRecord* p);
// FUN_14015b300: Create
//  gates (the idiom ~(-len-2) - 1 = len, so these
//  are bare lengths): name len < 0x10, to len <
//  0x10, from len < 0x100, text (non-null)
//  !(0xf < len) - else FALSE
//  writes: the inner header, then AddString in the
//  LITERAL order name, to, TEXT, from; TimeGet(0) at
//  header+0; +8 = 0x3ec; +0xc = GetSize()+0x1f;
//  returns all four AddStrings ANDed
bool MsgTalkCreate(MsgTalkRecord* p,
                   const char* szName,
                   const char* szTo,
                   const char* szFrom,
                   const char* szText,
                   uint32_t dw6, uint16_t w7, uint16_t w8,
                   uint32_t dw9, uint32_t dw10,
                   uint8_t b11);
// FUN_14015b2c0: dtor (vftable, packer dtor, the
// 1402b55f0 base)
void MsgTalkDtor(MsgTalkRecord* p);

} // namespace msg
