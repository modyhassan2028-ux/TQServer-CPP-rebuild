#include "MsgNpcLogin.h"
#include <cstring>

namespace msg {

// ===== ORIGINAL FUN_14045b990 @ 14045b990 =====
// VERBATIM flow (the security-cookie frame elided):
//  1. plVar5 = *(FUN_140008520(*(dword*)(this+0x410))
//     + 0x80); if null -> log_InlineLogERROR(
//     &DAT_1406d9c10), plVar5 = 0 (the ORIGINAL then
//     dereferences the null on the success path -
//     LITERAL, not fixed here)
//  2. memcmp16(wire+4,  "NpcServer Tqdig")
//  3. memcmp16(wire+0x14,"skl8934##VJICW ") - the
//     trailing space is LITERAL
//  4. both match:
//     if key == 0x3ade68b1 (param_3):
//       send(plVar5, 0xe, 0x2720, 0xea65)
//     send(plVar5, 0xe, 0x2722, 0xea65)
//     record: init + INLINE descriptor fields (1,0,0,0,
//     0x835,0xffffff,0) + build SYSTEM/ALLUSERS/
//     ANSWER_OK; if built -> kernel vt+0x30(rec,0)
//     release; then "NPC server login OK." ->
//     send(plVar5, 0, 0x9c41, ~(uint)loopLen) and 1
//  5. any mismatch: the ERROR: login refuse! record
//     (same init + build; broadcast on success) and 0
// NOTE the strlen idiom: lVar3 starts -1 and decrements
// per char INCLUDING the NUL iteration, so ~(uint)lVar3
// = strlen+1 (the NUL rides along) - "NPC server login
// OK." (20 chars) sends 21.
static uint32_t InlineStrlen1(const char* sz) {
    // the ORIGINAL do/while (lVar3 = -1 loop)
    int64_t l = -1;
    const char* p = sz;
    for (;;) {
        if (l == 0) break;
        l = l + -1;
        char c = *p;
        p = p + 1;
        if (c == '\0') break;
    }
    return ~(uint32_t)l;
}

bool MsgNpcLoginB990(MsgNpcLoginData& rD,
                     const MsgLoginWire& rWire,
                     bool bKeyB1) {
    void* pKernel = rD.m_fnGetKernel();
    void* pSender = rD.m_fnGetSender(pKernel);
    if (pSender == nullptr) {
        rD.m_fnLogError();        // DAT_1406d9c10
        pSender = nullptr;        // VERBATIM: plVar5 = 0
    }
    if (std::memcmp(rWire.szPwd1, "NpcServer Tqdig",
                   16) == 0 &&
        std::memcmp(rWire.szPwd2, "skl8934##VJICW ",
                   16) == 0) {
        if (bKeyB1)
            rD.m_fnSend(pSender, 0xe, 0x2720, 0xea65);
        rD.m_fnSend(pSender, 0xe, 0x2722, 0xea65);

        MsgChatRecord rec;
        rD.m_fnRecInit(&rec);
        rec.bFlag = 1;
        rec.dwA = 0;
        rec.dwB = 0;
        rec.wC = 0;
        rec.wColor835 = 0x835;
        rec.dwColorFFFFFF = 0xffffff;
        rec.szText = nullptr;
        if (rD.m_fnRecBuild(&rec, "SYSTEM", "ALLUSERS",
                            "ANSWER_OK")) {
            rD.m_fnBroadcast(pKernel, &rec);
        }
        rD.m_fnRecRelease(&rec);

        rD.m_fnLog("NPC server login OK."); // local_4c8
        rD.m_fnSend(pSender, 0, 0x9c41,
            InlineStrlen1("NPC server login OK."));
        return 1;
    }
    MsgChatRecord rec;
    rD.m_fnRecInit(&rec);
    rec.bFlag = 1;
    rec.dwA = 0;
    rec.dwB = 0;
    rec.wC = 0;
    rec.wColor835 = 0x835;
    rec.dwColorFFFFFF = 0xffffff;
    rec.szText = nullptr;
    if (rD.m_fnRecBuild(&rec, "SYSTEM", "ALLUSERS",
                        "ERROR: login refuse!")) {
        rD.m_fnBroadcast(pKernel, &rec);
    }
    rD.m_fnRecRelease(&rec);
    return 0;
}

// ===== ORIGINAL FUN_14045bc00 @ 14045bc00 =====
// iVar1 = **(int**)(this+0x428);
// if (iVar1 == 0x3ade68b1 || iVar1 == 0x3ade68b2)
//     FUN_14045b990(this, param_2,
//                   iVar1 == 0x3ade68b1);
void MsgNpcLoginDispatch(MsgNpcLoginData& rD,
                         const MsgLoginWire& rWire) {
    uint32_t dwKey = rWire.dwKey;
    if (dwKey == 0x3ade68b1 || dwKey == 0x3ade68b2)
        MsgNpcLoginB990(rD, rWire, dwKey == 0x3ade68b1);
}

} // namespace msg
