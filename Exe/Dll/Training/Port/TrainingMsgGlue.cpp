// ============================================================
// Training.dll port — the CMsg wire-glue family.
// VERBATIM from the Ghidra listing (addresses in the
// header). The vftable writes use the marker strings;
// the buffer = the msg's +0x40 node (the +0x408 tail
// points at it, per the D13 module model).
// ============================================================
#include "TrainingMsgGlue.h"
#include "TrainingMgr.h"

namespace training {

std::function<bool(void*, const char*, uint16_t)>
    g_fnCMsgCreate = [](void*, const char*, uint16_t) {
        return true;
    };
std::function<void(uint32_t)> g_fnMgrvt28 =
    [](uint32_t) {};
std::function<void(uint32_t)> g_fnMgrvt30 =
    [](uint32_t) {};
std::function<void(uint32_t)> g_fnMgrvt38 =
    [](uint32_t) {};
std::function<void(uint32_t)> g_fnMgrvt40 =
    [](uint32_t) {};

// the buffer view: *(msg + 0x408) = the node; the wire
// fields are the node's first qwords (+0/+2/+4/+8/+0xc)
static inline uint8_t* MsgBuf(CMsgBase* p) {
    return (uint8_t*)*(void**)((uint8_t*)p + 0x408);
}

// ============ FUN_1419e50b0 ============
CMsgBase* CtorCMsgBase(CMsgBase* p) {
    p->m_pVftable = (void*)"tq::CMsg";
    // tq::CMsg::Init — the D13 model: the +0x40 queue
    // head node link
    p->m_pListHead40 = (void*)&p->m_pListHead40;
    return p;
}

// ============ CMsgLogin (0x3ea) ============

// FUN_1419e51a0
void DtorMsgLogin(CMsgBase* p) {
    p->m_pVftable =
        (void*)"training::CMsgLogin::vftable";
    p->m_pVftable = (void*)"tq::CMsg";
}

// FUN_1419e51d0
bool TryCreateMsgLogin(CMsgBase* p, const char* pBuf,
                       uint16_t uLen) {
    if (!g_fnCMsgCreate(p, pBuf, uLen))
        return false;
    // *(short *)(param_1 + 10) == 0x3ea (the +0x50
    // type field)
    return *(uint16_t*)((uint8_t*)p + 0x50)
        == 0x3ea;
}

// FUN_1419e5240
CMsgBase* DtorDeletingMsgLogin(CMsgBase* p,
                               uint8_t uDel) {
    DtorMsgLogin(p);
    if ((uDel & 1) != 0)
        g_fnFree(p);
    return p;
}

// ============ CMsgLogout (0x3eb) ============

// FUN_1419e52e0
void DtorMsgLogout(CMsgBase* p) {
    p->m_pVftable =
        (void*)"training::CMsgLogout::vftable";
    p->m_pVftable = (void*)"tq::CMsg";
}

// FUN_1419e5310
bool TryCreateMsgLogout(CMsgBase* p, const char* pBuf,
                       uint16_t uLen) {
    if (!g_fnCMsgCreate(p, pBuf, uLen))
        return false;
    return *(uint16_t*)((uint8_t*)p + 0x50)
        == 0x3eb;
}

// FUN_1419e5380
CMsgBase* DtorDeletingMsgLogout(CMsgBase* p,
                                uint8_t uDel) {
    DtorMsgLogout(p);
    if ((uDel & 1) != 0)
        g_fnFree(p);
    return p;
}

// ============ CMsgTraining (0x7fc, len 0xc) ============

// FUN_1419e5420
void DtorMsgTraining(CMsgBase* p) {
    p->m_pVftable =
        (void*)"training::CMsgTraining::vftable";
    p->m_pVftable = (void*)"tq::CMsg";
}

// FUN_1419e5450
bool MakeMsgTraining(CMsgBase* p, uint16_t uAction,
                     uint32_t uParam) {
    uint8_t* pNode = MsgBuf(p);
    *(uint16_t*)(pNode + 4) = uAction;
    *(uint32_t*)(pNode + 8) = uParam;
    *(uint16_t*)(pNode + 2) = 0x7fc;
    *(uint16_t*)pNode = 0xc;
    return true;
}

// FUN_1419e5490
bool TryCreateMsgTraining(CMsgBase* p, const char* pBuf,
                         uint16_t uLen) {
    if (!g_fnCMsgCreate(p, pBuf, uLen))
        return false;
    return *(uint16_t*)((uint8_t*)p + 0x50)
        == 0x7fc;
}

// FUN_1419e5560
CMsgBase* DtorDeletingMsgTraining(CMsgBase* p,
                                  uint8_t uDel) {
    DtorMsgTraining(p);
    if ((uDel & 1) != 0)
        g_fnFree(p);
    return p;
}

// FUN_1419e54c0 — the action DISPATCHER
void DispatchMsgTraining(CMsgBase* p, uint32_t uId) {
    CTrainingMgr* pMgr = GetTrainingMgr();
    int16_t nAction =
        *(int16_t*)(MsgBuf(p) + 4);
    if (nAction == 0) {
        // mgr vt+0x30
        g_fnMgrvt30(uId);
    } else {
        if (nAction == 1) {
            // mgr vt+0x40 (the unrecovered jumptable at
            // 1419e5538 — the literal slot)
            g_fnMgrvt40(uId);
            return;
        }
        if (nAction == 3) {
            // mgr vt+0x28 (jumptable 1419e5522)
            g_fnMgrvt28(uId);
            return;
        }
        if (nAction == 4) {
            // mgr vt+0x38 (jumptable 1419e550c)
            g_fnMgrvt38(uId);
            return;
        }
    }
    return;
}

// ============ CMsgTrainingInfo (0x7fb, len 0x10) ========

// FUN_1419e55b0
CMsgBase* CtorMsgTrainingInfo(CMsgBase* p) {
    // CMsg vftable + Init
    p->m_pVftable = (void*)"tq::CMsg";
    p->m_pListHead40 = (void*)&p->m_pListHead40;
    // the derived vftable + Init
    p->m_pVftable =
        (void*)"training::CMsgTrainingInfo::vftable";
    p->m_pListHead40 = (void*)&p->m_pListHead40;
    // *(CMsg**)(param_1 + 0x408) = param_1 + 8?? —
    // per the D13 module model: the +0x408 tail points
    // at the +0x40 buffer node
    p->m_ppTail408 = &p->m_pListHead40;
    return p;
}

// FUN_1419e5600
void DtorMsgTrainingInfo(CMsgBase* p) {
    p->m_pVftable =
        (void*)"training::CMsgTrainingInfo::vftable";
    p->m_pVftable = (void*)"tq::CMsg";
}

// FUN_1419e5630
bool MakeMsgTrainingInfo(CMsgBase* p, uint16_t uA,
                        uint16_t uB, uint16_t uC,
                        uint32_t uD) {
    uint8_t* pNode = MsgBuf(p);
    *(uint16_t*)pNode = 0x10;
    *(uint16_t*)(pNode + 2) = 0x7fb;
    *(uint16_t*)(pNode + 4) = uA;
    *(uint16_t*)(pNode + 6) = uB;
    *(uint16_t*)(pNode + 8) = uC;
    *(uint32_t*)(pNode + 0xc) = uD;
    return true;
}

// FUN_1419e5690
bool TryCreateMsgTrainingInfo(CMsgBase* p,
                              const char* pBuf,
                              uint16_t uLen) {
    if (!g_fnCMsgCreate(p, pBuf, uLen))
        return false;
    return *(uint16_t*)((uint8_t*)p + 0x50)
        == 0x7fb;
}

// FUN_1419e56c0
CMsgBase* DtorDeletingMsgTrainingInfo(CMsgBase* p,
                                     uint8_t uDel) {
    DtorMsgTrainingInfo(p);
    if ((uDel & 1) != 0)
        g_fnFree(p);
    return p;
}

} // namespace training
