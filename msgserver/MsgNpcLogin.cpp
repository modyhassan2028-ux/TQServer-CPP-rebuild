#include "MsgNpcLogin.h"
#include <cstring>

namespace msg {

// the ORIGINAL do/while 16-byte compare idiom: the
// flag holds the LAST byte equality and the loop
// exits on the first mismatch (semantics: all 16
// bytes equal)
static bool InlineEq16(const void* p, const char* q) {
    int l = 0x10;
    bool b = true;
    const char* a = (const char*)p;
    for (;;) {
        if (l == 0) break;
        l = l + -1;
        b = (*a == *q);
        a = a + 1;
        q = q + 1;
        if (!b) break;
    }
    return b;
}

// the ORIGINAL strlen idiom: l starts -1, counts
// every char INCLUDING the NUL, so ~(uint)l =
// strlen+1 (the NUL rides along in the keepalive)
static uint32_t InlineStrlen1(const char* sz) {
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

// ===== ORIGINAL FUN_14045bc00 @ 14045bc00 =====
// iVar1 = **(int **)(conn + 0x428);  // wire +0
// if (b1 || b2) b990(conn, key == b1)
void MsgNpcLoginDispatch(MsgNpcLoginData& rD) {
    int iKey = (int)rD.pConn->Wire()->dwKey;
    if (iKey == 0x3ade68b1 || iKey == 0x3ade68b2)
        MsgNpcLoginB990(rD, iKey == 0x3ade68b1);
}

// ===== ORIGINAL FUN_14045b990 @ 14045b990 =====
// FULL VERBATIM (the security-cookie frame elided).
// LITERAL UB notes (documented, NOT fixed):
//  - an invalid group id: FUN_140008520 returns 0
//    and the ORIGINAL derefs *(0 + 0x80) -> crash
//    (the log fires inside the lookup first)
//  - a null sender: log DAT_1406d9c10, plVar5 = 0,
//    flow CONTINUES - the send paths then deref
//    the null (the refuse path survives cleanly)
int MsgNpcLoginB990(MsgNpcLoginData& rD, bool bFlag) {
    // 1. lVar3 = FUN_140008520(*(dword*)(conn+0x410))
    MsgKernelObj* pSlot = (MsgKernelObj*)
        MsgKernelGetSlot(*rD.pRegistry,
                        rD.pConn->GroupId());
    // 2. plVar5 = *(lVar3 + 0x80); if null:
    //    log + plVar5 = 0 (the flow keeps running)
    MsgSenderObj* pSend = pSlot->Sender();
    if (pSend == nullptr) {
        rD.m_fnLogError();          // DAT_1406d9c10
        pSend = nullptr;
    }
    // 3. lVar3 = *(conn + 0x428) - the wire
    MsgLoginWire* pWire = rD.pConn->Wire();
    // 4. the two 16-byte literal gates
    if (InlineEq16(pWire->szPwd1, "NpcServer Tqdig")) {
        if (InlineEq16(pWire->szPwd2,
                      "skl8934##VJICW ")) {
            // 5. the handshake (vt+0x50 = Send)
            if (bFlag)
                pSend->pvt->m_fnSend(
                    0xe, 0x2720, 0xea65);
            pSend->pvt->m_fnSend(
                0xe, 0x2722, 0xea65);
            // 6. the ANSWER_OK record (M2/M3 real
            //    family; the stack-arg rebuild:
            //    text null, 0xffffff, 0x835,
            //    0, 0, 0, byte 1)
            MsgTalkCtor(&rD.m_recTalk);
            if (MsgTalkCreate(&rD.m_recTalk, "SYSTEM",
                              "ALLUSERS", "ANSWER_OK",
                              nullptr, 0xffffff,
                              0x835, 0, 0, 0, 1)) {
                // 7. the SECOND kernel lookup
                //    (plVar4) - LITERAL, then the
                //    broadcast (vt+0x30)
                MsgKernelObj* pSlot2 = (MsgKernelObj*)
                    MsgKernelGetSlot(*rD.pRegistry,
                                    rD.pConn->GroupId());
                pSlot2->VT()->m_fnBcast(
                    0, &rD.m_recTalk);
            }
            MsgTalkDtor(&rD.m_recTalk);
            // 8. the keepalive: the strlen+1 idiom
            //    sends 21 for the 20-char literal
            pSend->pvt->m_fnSend(
                0, 0x9c41,
                InlineStrlen1("NPC server login OK."));
            return 1;
        }
    }
    // 9. the refuse record - same stack-arg rebuild
    //    with the ERROR string as the FROM
    MsgTalkCtor(&rD.m_recTalk);
    if (MsgTalkCreate(&rD.m_recTalk, "SYSTEM",
                      "ALLUSERS", "ERROR: login refuse!",
                      nullptr, 0xffffff, 0x835, 0,
                      0, 0, 1)) {
        MsgKernelObj* pSlot3 = (MsgKernelObj*)
            MsgKernelGetSlot(*rD.pRegistry,
                            rD.pConn->GroupId());
        pSlot3->VT()->m_fnBcast(0, &rD.m_recTalk);
    }
    MsgTalkDtor(&rD.m_recTalk);
    return 0;
}

} // namespace msg
