#include "MsgTalkRecord.h"
#include <cstring>

namespace msg {

// the ORIGINAL strlen idiom: uVar8 starts -1 and
// decrements per char INCLUDING the NUL, so
// uVar8 = -(len+2), ~uVar8 = len+1 and
// ~uVar8 - 1 = len (the gates compare the BARE
// length: name/to < 0x10, from < 0x100)
static uint32_t InlineStrlenMinus1(const char* sz) {
    int64_t l = -1;
    const char* p = sz;
    for (;;) {
        if (l == 0) break;
        l = l + -1;
        char c = *p;
        p = p + 1;
        if (c == '\0') break;
    }
    return (uint32_t)(~l) - 1;
}

// ===== ORIGINAL FUN_1402ba1c0 @ 1402ba1c0 =====
// the CNetMsg base ctor (Ghidra: the +0x83/+0x84
// qword steps are +0x418/+0x420 bytes):
//  *this = CNetMsg::vftable; *(dword*)(this+8)=0;
//  *(dword*)(this+0xc)=0; memset(this+0x10,0,0x400);
//  +0x418=+0x41c=+0x420=+0x424=0 (dwords)
void MsgTalkNetCtor(MsgTalkRecord* p) {
    p->At<void*>(0) = (void*)0x1;  // CNetMsg::vftable
    p->At<uint32_t>(8) = 0;
    p->At<uint32_t>(0xc) = 0;
    std::memset(p->ab + 0x10, 0, 0x400);
    p->At<uint32_t>(0x418) = 0;
    p->At<uint32_t>(0x41c) = 0;
    p->At<uint32_t>(0x420) = 0;
    p->At<uint32_t>(0x424) = 0;
}

// ===== ORIGINAL FUN_1402b5600 @ 1402b5600 =====
// memset(this+0x10,0,0x400); +0xc = 0; +8 = 0
// (LITERAL double clear after 2ba1c0 in 15b240)
void MsgTalkBaseClear(MsgTalkRecord* p) {
    std::memset(p->ab + 0x10, 0, 0x400);
    p->At<uint32_t>(0xc) = 0;
    p->At<uint32_t>(8) = 0;
}

// ===== ORIGINAL FUN_1402b55f0 @ 1402b55f0 =====
// *this = CNetMsg::vftable
void MsgTalkBaseDtor(MsgTalkRecord* p) {
    p->At<void*>(0) = (void*)0x1;  // CNetMsg::vftable
}

// ===== ORIGINAL FUN_14015b240 @ 14015b240 =====
// FUN_1402ba1c0(); *this = CMsgTalk::vftable;
// CStringPacker ctor at this+0x86 (qwords) = +0x430;
// FUN_1402b5600(this); *(this+0x85) = this + 2
//  (i.e. +0x428 = this + 0x10 - the inner header);
// SetBuf(this + 0x2d, 0x3e1, true)
void MsgTalkCtor(MsgTalkRecord* p) {
    MsgTalkNetCtor(p);            // FUN_1402ba1c0
    p->m_pVftable = (void*)0x2;    // CMsgTalk::vftable
    p->At<void*>(0) = p->m_pVftable;
    p->m_fnPackerCtor();          // at +0x430
    MsgTalkBaseClear(p);          // FUN_1402b5600
    p->At<void*>(0x428) = p->ab + 0x10;
    p->m_fnPackerSetBuf(
        (char*)p->ab + 0x2d, 0x3e1, true);
}

// ===== ORIGINAL FUN_14015b300 @ 14015b300 =====
bool MsgTalkCreate(MsgTalkRecord* p,
                   const char* szName,
                   const char* szTo,
                   const char* szFrom,
                   const char* szText,
                   uint32_t dw6, uint16_t w7, uint16_t w8,
                   uint32_t dw9, uint32_t dw10,
                   uint8_t b11) {
    // the VERBATIM nested gates (bare lengths):
    //   name/to: len < 0x10; from: len < 0x100;
    //   text (non-null): !(0xf < len)
    if (szName != nullptr) {
        if (InlineStrlenMinus1(szName) < 0x10) {
            if (szTo != nullptr) {
                if (InlineStrlenMinus1(szTo) < 0x10) {
                    if (szFrom != nullptr) {
                        if (InlineStrlenMinus1(szFrom)
                                < 0x100) {
                            if (szText != nullptr) {
                                if (0xf <
                                    InlineStrlenMinus1(
                                        szText))
                                    return false;
                            }
                            // ---- the writes ----
                            // inner header via +0x428
                            char* h = (char*)p->At<void*>(
                                0x428);
                            *(uint32_t*)(h + 4) = dw6;
                            *(uint16_t*)(h + 8) = w7;
                            *(uint16_t*)(h + 10) = w8;
                            *(uint32_t*)(h + 0xc) =
                                p->m_fnSysTime();
                            *(uint32_t*)(h + 0x14) = dw9;
                            *(uint32_t*)(h + 0x18) = dw10;
                            *(uint8_t*)(h + 0x1c) = b11;
                            // AddString x4 LITERAL order:
                            // name, to, TEXT, from
                            bool b1 = p->m_fnPackerAdd(
                                szName);
                            bool b2 = p->m_fnPackerAdd(
                                szTo);
                            bool b3 = p->m_fnPackerAdd(
                                szText);
                            bool b4 = p->m_fnPackerAdd(
                                szFrom);
                            *(uint32_t*)h =
                                p->m_fnTimeGet();
                            p->At<uint32_t>(8) = 0x3ec;
                            p->At<uint32_t>(0xc) =
                                p->m_fnPackerGetSize()
                                + 0x1f;
                            return (b1 && b2) && b3 && b4;
                        }
                    }
                }
            }
        }
    }
    return false;
}

// ===== ORIGINAL FUN_14015b2c0 @ 14015b2c0 =====
// *this = CMsgTalk::vftable; packer dtor at +0x430;
// FUN_1402b55f0(this) - the CNetMsg::vftable write
void MsgTalkDtor(MsgTalkRecord* p) {
    p->m_pVftable = (void*)0x2;    // CMsgTalk::vftable
    p->At<void*>(0) = p->m_pVftable;
    p->m_fnPackerDtor();
    MsgTalkBaseDtor(p);           // FUN_1402b55f0
}

} // namespace msg
