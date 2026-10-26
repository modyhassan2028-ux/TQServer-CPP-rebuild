// SyndicateMsgProcess.cpp — D59 (see the header
// for the address map and the seam list).
#include "Exe/Dll/Syndicate/Port/SyndicateMsgProcess.h"
#include "Exe/Dll/Syndicate/Port/SyndicateCrossMerit.h"   // g_fnGetGameMgr

namespace syndicate {

// ---- the seams ----
static void DefLogRecord(void*, uint32_t) {}
void (*g_fnLogRecord)(void*, uint32_t) =
    DefLogRecord;
static void DefLogRemove(void*, uint32_t) {}
void (*g_fnLogRemove)(void*, uint32_t) =
    DefLogRemove;
static uint64_t DefChgDomCheck(void*, uint32_t,
                               uint32_t, char*) {
    return 0;
}
uint64_t (*g_fnChgDomCheck)(void*, uint32_t,
    uint32_t, char*) = DefChgDomCheck;
static void DefD59LogError(const char*, ...) {}
void (*g_fnD59LogError)(const char*, ...) =
    DefD59LogError;
static void DefCMsgInitThunk(void*) {}
void (*g_fnCMsgInitThunk)(void*) =
    DefCMsgInitThunk;

// ================= FUN_1417d97c0 =================
// void CMsgLog::Process(this, uIdActor):
//   pLogic = FUN_1417b6210();
//   iVar1 = *(int *)(*(longlong *)(this + 0x408)
//                            + 8);
//   if (iVar1 == 0)      FUN_1417b7010(...);
//   else if (iVar1 == 1) FUN_1417ac620(...);
//   else log_InlineLogERROR(<the literal>);
void MsgLogProcess(void* pMsg, uint32_t uIdActor) {
    void* pLogic = g_fnGetGameMgr();
    // the PB obj at +0x408, its +8 = the Type
    int nMsgType =
        *(int*)(*(char**)((char*)pMsg + 0x408)
                + 8);
    if (nMsgType == 0) {
        g_fnLogRecord(pLogic, uIdActor);
    }
    else if (nMsgType == 1) {
        g_fnLogRemove(pLogic, uIdActor);
    }
    else {
        g_fnD59LogError(
            "syndicate::CMsgLog::Process(idActor),"
            " idActor:%d, Type:%d, MsgType:%d");
    }
}

// ================= FUN_1417dae90 =================
// the reply Init (the success ushort + the two
// literal header writes) — verbatim:
//   tq::CMsg::Init(param_1);
//   *(ushort *)(*(longlong *)(this+0x408)+0x18)
//            = param_2;
//   *(ushort *)(*(longlong *)(this+0x408)+2)
//            = 0x837;
//   *(ushort *)(*(longlong *)(this+0x408))
//            = 0x1c;
static void MsgChgDomNameReplyInit(void* pMsg,
                                   uint16_t uOk) {
    // tq::CMsg::Init — the base seam (already
    // ported in the D57 ctor unit as the vtable
    // Init; here the ORIGINAL calls the base
    // Init through the CMsg vt)
    // tq::CMsg::Init @ 1417e8016 — the shared
    // PB-runtime Init thunk (re-Init through the
    // PB runtime; kept as a seam — it touches the
    // protobuf core not yet ported).
    if (g_fnCMsgInitThunk) {
        g_fnCMsgInitThunk(pMsg);
    }
    char* pPb = *(char**)((char*)pMsg + 0x408);
    *(uint16_t*)(pPb + 0x18) = uOk;
    *(uint16_t*)(pPb + 0x02) = 0x837;
    *(uint16_t*)(pPb + 0x00) = 0x1c;
}

// ================= FUN_1417daee0 =================
// void CMsgSynChgDomName::Process(this, uActor):
//   pLogic = FUN_1417b6210();
//   uVar2 = FUN_1417afb20(pLogic, uActor,
//          *(uint *)(*(longlong *)(this+0x408)+4),
//          (char *)(*(longlong *)(this+0x408)+8));
//   FUN_1417dae90(this, (ushort)(uVar2 != 0));
//   FUN_1417ac7d0(pLogic);
void MsgChgDomNameProcess(void* pMsg,
                          uint32_t uIdActor) {
    void* pLogic = g_fnGetGameMgr();
    char* pPb = *(char**)((char*)pMsg + 0x408);
    uint64_t uOk = g_fnChgDomCheck(
        pLogic, uIdActor,
        *(uint32_t*)(pPb + 4),   // the syn id
        (char*)(pPb + 8));       // the name
    MsgChgDomNameReplyInit(
        pMsg, (uint16_t)((char)uOk != '\0'));
    // FUN_1417ac7d0 — verbatim (the disassembly:
    //   mov rcx,[rcx+8]; mov rax,[rcx]; jmp [rax+8])
    // = the object at logic+8, its vtable slot +8
    //   (index 1), this = the object
    void* pObj =
        *(void**)((char*)pLogic + 8);
    void** pVt = *(void***)pObj;
    ((void(*)())pVt[1])();
}

}  // namespace syndicate
