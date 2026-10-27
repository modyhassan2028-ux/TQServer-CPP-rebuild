// ============================================================
// Peerage.dll port — unit T6/D22: the wire family
// verbatim. The buffer lives at *(msg+0x408); the
// header: +0x00 0xa8 (u16), +0x02 0x810 (u16),
// +0x04 the type (u16), +0x08 the id (u32), +0x0c
// the record count (u32). The packer sits at
// msg+0x410. The security-cookie locals of the
// original are stack-protector artifacts (skipped,
// as in D20).
// ============================================================
#include "PeerageMsgWire.h"
#include "PeeragePromote.h"
#include "PeerageModule.h"
#include <cstring>
#include <cstdio>
#include <cstdlib>

namespace peerage {

// ---- the seam defaults ----
bool (*g_fnCMsgCreate)(void*, char*, uint16_t) =
    [](void*, char*, uint16_t) -> bool {
        return true; };
void (*g_fnPackerAddString)(void*, char*) =
    [](void*, char*) {};
unsigned (*g_fnPackerGetSize)(void*) =
    [](void*) -> unsigned { return 0; };
uint64_t (*g_fnBuild1Arg4)() =
    []() -> uint64_t { return 0; };

// the raw buffer at *(msg+0x408)
static inline unsigned char* MsgBuf(void* pMsg) {
    return *(unsigned char**)
        ((char*)pMsg + 0x408);
}

// ---- FUN_1415571b0 ----
bool MsgLoginCreate(CMsgBase* p, char* pBuf,
                    uint16_t uLen) {
    bool bVar1 = g_fnCMsgCreate(p, pBuf, uLen);
    if (!bVar1) {
        return false;
    }
    // *(short*)(msg + 10) == 0x3ea
    return *(int16_t*)((char*)p + 10) == 0x3ea;
}

// ---- FUN_1415571e0 ----
void MsgLoginSend(void* pMsg, uint64_t uA,
                  void* pRecv) {
    if (pRecv == (void*)0) {
        g_fnInlineLogError();
        return;
    }
    // recipient vt+0x30
    void* pVt = *(void**)pRecv;
    auto fn = (void (*)(void*))*(void**)
        ((char*)pVt + 0x30);
    fn(pRecv);
}

// ---- FUN_141557240 ----
CMsgBase* MsgLoginDeletingDtor(CMsgBase* p,
                               uint8_t uFlags) {
    *(void**)p = (void*)1;   // CMsgLogin vftable
    *(void**)p = (void*)2;   // tq::CMsg vftable
    if ((uFlags & 1) != 0) {
        g_fnFree(p);
    }
    return p;
}

// ---- FUN_141557350 ----
// (param_1, param_2=id u32, param_3 u32, param_4
// u64, param_5 u64, param_6 i32): header {0xa8,
// 0x810, 1, id} then "%u %u %I64u %I64u %d" append.
// The visible locals: local_258=param_3 (%u),
// local_250=param_4 (%u), local_248=param_5 (%I64u),
// local_240=param_6 (%d) — the 4th spec's arg was
// DROPPED by Ghidra (the g_fnBuild1Arg4 seam).
char BuildMsgType1(CMsgBase* p, uint32_t uId,
                  uint32_t uA3, uint64_t uA4,
                  uint64_t uA5, int32_t nA6) {
    unsigned char* pBuf = MsgBuf(p);
    *(uint16_t*)(pBuf + 4) = 1;
    *(uint32_t*)(pBuf + 8) = uId;
    *(uint16_t*)(pBuf + 2) = 0x810;
    *(uint16_t*)(pBuf + 0) = 0xa8;
    // the original: local_238 (1 byte) + local_237
    // [511] contiguous = one 0x200 scratch buffer
    char local_238[0x200];
    local_238[0] = '\0';
    memset(local_238 + 1, 0, 0x1ff);
    // "%u %u %I64u %I64u %d" (MSVC); %I64u == %llu
    // on the port toolchain
    snprintf(local_238, 0x1ff, "%u %u %llu %llu %d",
             uA3, (uint32_t)uA4, uA5,
             (unsigned long long)g_fnBuild1Arg4(),
             nA6);
    // the msg vt+0x48 append — unified on the D20 seam
    // g_fnMsgAppend (returns the append result)
    return g_fnMsgAppend(p, local_238) ? 1 : 0;
}

// ---- FUN_141557440 ----
uint64_t BuildMsgType2(CMsgBase* p, uint16_t uA,
                       uint16_t uB) {
    unsigned char* pBuf = MsgBuf(p);
    *(uint16_t*)(pBuf + 4) = 2;
    *(uint16_t*)(pBuf + 8) = uA;
    *(uint16_t*)(pBuf + 10) = uB;
    *(uint32_t*)(pBuf + 0xc) = 0;
    *(uint16_t*)(pBuf + 2) = 0x810;
    *(uint16_t*)(pBuf + 0) = 0xa8;
    return (uint64_t)1;   // CONCAT71(..., 1)
}

// ---- FUN_141557580 ----
uint64_t BuildMsgType4(CMsgBase* p, uint64_t uA,
                       void* pSrc) {
    (void)uA;
    unsigned char* pBuf = MsgBuf(p);
    *(uint16_t*)(pBuf + 4) = 4;
    memcpy((void*)(pBuf + 8), pSrc, 0x60);
    *(uint16_t*)(pBuf + 2) = 0x810;
    *(uint16_t*)(pBuf + 0) = 0xa8;
    return (uint64_t)1;
}

// ---- FUN_1415575e0 ----
bool MsgPeerageCreate(CMsgBase* p, char* pBuf,
                      uint16_t uLen) {
    bool bVar1 = g_fnCMsgCreate(p, pBuf, uLen);
    if (!bVar1) {
        return false;
    }
    return *(int16_t*)((char*)p + 10) == 0x810;
}

// ---- FUN_141557610 ----
uint32_t AppendStringPacked(void* pMsg, char* pStr) {
    if (pStr == (char*)0) {
        g_fnInlineLogError();
        return (uint32_t)0;   // EAX & ~0xff
    }
    g_fnPackerAddString((char*)pMsg + 0x410, pStr);
    unsigned uVar2 = g_fnPackerGetSize(
        (char*)pMsg + 0x410);
    int16_t sVar1 = (int16_t)uVar2 + 0xa7;
    *(int16_t*)MsgBuf(pMsg) = sVar1;
    return 1u;   // CONCAT31(..., 1)
}

// ---- FUN_141557690 ----
void SendPeerageMsg(void* pMsg, uint64_t uA,
                    void* pRecv) {
    if (pRecv == (void*)0) {
        g_fnInlineLogError();
        return;
    }
    unsigned char* pBuf = MsgBuf(pMsg);
    int16_t sVar1 = *(int16_t*)(pBuf + 4);
    if (sVar1 == 1) {
        void* pVt = *(void**)pRecv;
        auto fn = (void (*)(void*, uint64_t, uint64_t,
                            uint16_t))* (void**)
            ((char*)pVt + 0x10);
        fn(pRecv, uA, *(uint64_t*)(pBuf + 8),
           *(uint16_t*)(pBuf + 0x68));
    } else {
        if (sVar1 == 2) {
            void* pVt = *(void**)pRecv;
            auto fn = (void (*)(void*, uint64_t,
                                uint16_t))* (void**)
                ((char*)pVt + 0x18);
            fn(pRecv, uA, *(uint16_t*)(pBuf + 8));
            return;
        }
        if (sVar1 == 3) {
            void* pVt = *(void**)pRecv;
            auto fn = (void (*)(void*))*(void**)
                ((char*)pVt + 0x20);
            fn(pRecv);
            return;
        }
        if (sVar1 == 4) {
            void* pVt = *(void**)pRecv;
            auto fn = (void (*)(void*))*(void**)
                ((char*)pVt + 0x38);
            fn(pRecv);
            return;
        }
    }
}

// ---- FUN_141557740 ----
uint64_t AppendPeerageRecord(CMsgBase* p,
                             uint32_t uId,
                             uint8_t uState,
                             uint32_t uA4,
                             char* pName,
                             uint64_t uA6,
                             uint32_t uA7,
                             uint32_t uA8) {
    unsigned char* pBuf = MsgBuf(p);
    // buf[0] = count(int at +0xc) * 0x30 + 0xa8
    *(uint16_t*)(pBuf + 0) =
        (uint16_t)(*(int32_t*)(pBuf + 0xc) * 0x30
                   + 0xa8);
    // the ORIGINAL's contiguous stack frame:
    // local_48, local_40, local_38, local_30, then
    // param_6 and local_20 stored into the record;
    // the strncpy spans local_40[4..7] + local_38 +
    // local_30[0..3] (16 bytes) — one array keeps
    // the layout contiguous
    uint64_t rec[6];
    rec[0] = ((uint64_t)uState << 32) | uId;
    rec[1] = (uint64_t)uA4;
    rec[2] = 0;   // local_38
    rec[3] = 0;   // local_30
    rec[5] = ((uint64_t)uA8 << 32) | uA7;
    if (pName != (char*)0) {
        strncpy((char*)&rec[1] + 4, pName, 0x10);
    }
    int64_t lVar3 = (int64_t)*(int32_t*)(pBuf + 0xc);
    *(uint64_t*)(pBuf + 0x78 + lVar3 * 0x30) =
        rec[0];
    *(uint64_t*)(pBuf + 0x80 + lVar3 * 0x30) =
        rec[1];
    *(uint64_t*)(pBuf + 0x88 + lVar3 * 0x30) =
        rec[2];
    *(uint64_t*)(pBuf + 0x90 + lVar3 * 0x30) =
        rec[3];
    *(uint64_t*)(pBuf + 0x98 + lVar3 * 0x30) = uA6;
    *(uint64_t*)(pBuf + 0xa0 + lVar3 * 0x30) =
        rec[5];
    *(int32_t*)(pBuf + 0xc) =
        *(int32_t*)(pBuf + 0xc) + 1;
    return (uint64_t)1;
}

// ---- FUN_141557880 ----
CMsgBase* MsgPeerageDeletingDtor(CMsgBase* p,
                                 uint8_t uFlags) {
    *(void**)p = (void*)3;   // CMsgPeerage vftable
    g_fnPackerDtor((char*)p + 0x410);
    *(void**)p = (void*)2;   // tq::CMsg vftable
    if ((uFlags & 1) != 0) {
        g_fnFree(p);
    }
    return p;
}

// ---- FUN_1415513c0 ----
uint16_t ModuleProcessMsg(CModule* p, uint32_t uId,
                          uint16_t* puHdr,
                          uint16_t uLen) {
    void* pMsg = GetModuleMsg(p, puHdr, uLen);
    uint16_t uVar1 = 0;
    if (pMsg != (void*)0) {
        void* pVt = *(void**)pMsg;
        auto fn = (void (*)(void*, uint32_t,
                            void*))*(void**)
            ((char*)pVt + 0x10);
        fn(pMsg, uId, *(void**)((char*)p + 0x18));
        // msg[1] as u16 (the msg's +0x08 qword low)
        uVar1 = *(uint16_t*)((char*)pMsg + 8);
    }
    return uVar1;
}

// ---- FUN_141551310 / 141551320 ----
void ModuleStubVoid() {}
uint64_t ModuleStubOne() { return 1; }

} // namespace peerage
