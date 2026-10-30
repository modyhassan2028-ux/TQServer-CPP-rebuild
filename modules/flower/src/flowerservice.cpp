// flowerservice.cpp — RAW Flower.dll v6159
#include "modules/flower/src/flowerservice.h"
#include <ctime>
#include <cstdio>
#include <cstring>
#include "modules/flower/src/todayflowermgr.h"
#include "modules/flower/src/msg/msgflower.h"

namespace flower {
void* (*g_pfnTheInstance)() = nullptr;
// the string manager answers a literal by key from its slot 0
const char* StrGet(const char* szKey) {
    void* pMgr = g_pfnTheInstance ? g_pfnTheInstance() : nullptr;
    if (pMgr == nullptr) return szKey;
    void** vt = *reinterpret_cast<void***>(pMgr);
    return ((const char* (*)(void*, const char*))vt[0])(pMgr, szKey);
}

// 0x140d91be0 — the whole gift path, transcribed branch by branch.
//   Slot numbers on the session object are the original's:
//   +0x18 mode/sex query · +0x20 last-send date · +0x28 store date
//   +0x30 current value · +0x38 store value · +0x40 level · +0x48 grade
//   +0x50 alive · +0x58 exists · +0x60 tell · +0x68/+0x70 record add
//   +0x78 GM notice · +0x88 store count · +0x90 flag · +0xb0 finish
static inline void* SessSlot(void* pSess, uint32_t uOff) {
    void** vt = *reinterpret_cast<void***>(pSess);
    return vt[uOff / 8];
}
static inline void SessTell(void* pSess, uint32_t idTo, const char* szText) {
    ((void (*)(void*, uint32_t, const char*, uint32_t))SessSlot(pSess, 0x60))(
        pSess, idTo, szText, 0xff0000);
}

uint8_t CFlowerService::Send(void* pThis, uint32_t idSender, uint32_t idReceiver,
                             int nArg) {
    unsigned char* p = (unsigned char*)pThis;
    if (idSender == 0 || idReceiver == 0) {
        g_pfnFlowerLog(kCheckFormat, "", "Send", "");
        return 0;
    }
    void* pSess = *reinterpret_cast<void**>(p + 8);
    std::map<uint32_t, CTodayFlower*>* pMap =
        *reinterpret_cast<std::map<uint32_t, CTodayFlower*>**>(p + 0x18);
    uint8_t uRet = 0;

    // the decompiler shows this call with no argument at all; the mode gate
    // only ever compares it with 1
    if (((int (*)(void*))SessSlot(pSess, 0x18))(pSess) != 1) {
        return 0;   // the original returns an uninitialised byte here
    }

    bool bSelf = false;
    uint8_t byFlag = 0;
    if (((uint8_t (*)(void*, uint32_t))SessSlot(pSess, 0x50))(pSess, idSender) ==
        0) {
        SessTell(pSess, idSender, StrGet("STR_FLOWER_SENDER_NOT_ALIVE"));
        return 0;
    }

    uint32_t uSlot = 0;      // local_a7c
    uint32_t uCount = 0;     // local_a84
    uint32_t uLast = 0;      // local_a80
    if (nArg == 0) {
        uLast = 1;
        bSelf = true;
        byFlag = 1;
        const uint32_t uLevel =
            ((uint32_t (*)(void*, uint32_t))SessSlot(pSess, 0x40))(pSess,
                                                                  idSender);
        if (uLevel < kMinSendLevel) {
            SessTell(pSess, idSender, StrGet("STR_FLOWER_LEVEL_TOO_LOW"));
            return 0;
        }
        const uint32_t uDate =
            ((uint32_t (*)(void*, uint32_t))SessSlot(pSess, 0x20))(pSess,
                                                                  idSender);
        if (IsExpiredDate(uDate) == 0) {
            const std::time_t tNow = std::time(nullptr);
            uLast = (uint32_t)tNow;      // local_a80 keeps the raw time value
            struct tm* pTm = std::localtime(&tNow);
            if (pTm == nullptr) {
                g_pfnFlowerLog(kCheckFormat, "", "Send", "");
                return 0;
            }
            char szBuf[0x400];
            std::snprintf(szBuf, sizeof szBuf, "%s",
                          StrGet("STR_FLOWER_HAVE_SENT_TODAY"));
            SessTell(pSess, idSender, szBuf);
            return 0;
        }
        uSlot = 0;
        uCount = 1;
    } else {
        ResolveFlowerSlot(pThis, nArg, &uSlot, (int*)&uCount);
        uLast = uCount;
        if (uCount == 0) return 0;
    }

    if (((uint8_t (*)(void*, uint32_t))SessSlot(pSess, 0x58))(pSess,
                                                             idReceiver) != 0) {
        if (((int (*)(void*, uint32_t))SessSlot(pSess, 0x18))(pSess,
                                                             idReceiver) == 2) {
            if (!bSelf) {
                if (nArg == 0) return 0;
                if (((uint8_t (*)(void*, uint32_t, int))SessSlot(pSess, 0))(
                        pSess, idSender, nArg) == 0) {
                    return 0;
                }
            }
            const int iOld = ((int (*)(void*, uint32_t, uint32_t))SessSlot(
                pSess, 0x30))(pSess, idReceiver, uSlot);
            bool bVip = false;
            uint32_t uAdd = uCount;
            const uint8_t byThird =
                ((uint8_t (*)(void*, uint32_t))SessSlot(pSess, 0x90))(pSess, 3);
            if (bSelf && byThird != 0) {
                const uint32_t uGrade =
                    ((uint32_t (*)(void*, uint32_t))SessSlot(pSess, 0x48))(
                        pSess, idSender);
                switch (uGrade) {
                    case 0: break;
                    case 1: bVip = true; uAdd = 2; break;
                    case 2: bVip = true; uAdd = 3; break;
                    case 3: bVip = true; uAdd = 5; break;
                    case 4: bVip = true; uAdd = 10; break;
                    case 5: bVip = true; uAdd = 0xf; break;
                    case 6: bVip = true; uAdd = 0x1e; break;
                    default: bVip = true; uAdd = 0x1e; break;
                }
            }
            const int iNew = iOld + (int)uAdd;
            ((void (*)(void*, uint32_t, uint32_t, int))SessSlot(pSess, 0x38))(
                pSess, idReceiver, uSlot, iNew);
            CTodayFlowerMgr::SetValue(pMap, idReceiver, uSlot, (int32_t)uAdd);

            unsigned char oMsg[0x410];
            CMsgFlower::Ctor(oMsg);
            const char* szReceiver =
                ((const char* (*)(void*, uint32_t))SessSlot(pSess, 8))(pSess,
                                                                      idReceiver);
            // the decompiler lost this call's argument; the GM block below
            // shows the same pair of lookups as (sender, receiver)
            const char* szSender =
                ((const char* (*)(void*, uint32_t))SessSlot(pSess, 8))(pSess,
                                                                      idSender);
            if (!CMsgFlower::Build(oMsg, 0, szSender, szReceiver, uAdd, uSlot,
                                   byFlag)) {
                g_pfnFlowerLog(kCheckFormat, "", "Send", "");
            } else if (uCount < kGmCount99) {
                ((void (*)(void*, uint32_t, void*))SessSlot(pSess, 0x68))(
                    pSess, idSender, oMsg);
                ((void (*)(void*, uint32_t, void*, uint32_t))SessSlot(
                    pSess, 0x70))(pSess, idReceiver, oMsg, idSender);
            } else {
                ((void (*)(void*, uint32_t, void*))SessSlot(pSess, 0x68))(
                    pSess, idSender, oMsg);
                ((void (*)(void*, uint32_t, void*, uint32_t))SessSlot(
                    pSess, 0x70))(pSess, idReceiver, oMsg, idSender);

                char szBuf[0x200];
                const char* szFmt = nullptr;
                const char* szA = nullptr;
                const char* szB = nullptr;
                if (uSlot == 0) {
                    if (uCount == kGmCount99) {
                        szFmt = StrGet("STR_FLOWER_GM_PROMPT_RED_99");
                        szA = szSender; szB = szReceiver;
                    } else if (uCount == kGmCount999) {
                        szFmt = StrGet("STR_FLOWER_GM_PROMPT_RED_999");
                        szA = szReceiver; szB = szSender;
                    }
                } else if (uSlot == 1) {
                    if (uCount == kGmCount99) {
                        szFmt = StrGet("STR_FLOWER_GM_PROMPT_WHITE_99");
                        szA = szSender; szB = szReceiver;
                    } else if (uCount == kGmCount999) {
                        szFmt = StrGet("STR_FLOWER_GM_PROMPT_WHITE_999");
                        szA = szReceiver; szB = szSender;
                    }
                } else if (uSlot == 2) {
                    if (uCount == kGmCount99) {
                        szFmt = StrGet("STR_FLOWER_GM_PROMPT_LILY_99");
                        szA = szSender; szB = szReceiver;
                    } else if (uCount == kGmCount999) {
                        szFmt = StrGet("STR_FLOWER_GM_PROMPT_LILY_999");
                        szA = szReceiver; szB = szSender;
                    }
                } else if (uSlot == 3) {
                    if (uCount == kGmCount99) {
                        szFmt = StrGet("STR_FLOWER_GM_PROMPT_TULIP_99");
                        szA = szSender; szB = szReceiver;
                    } else if (uCount == kGmCount999) {
                        szFmt = StrGet("STR_FLOWER_GM_PROMPT_TULIP_999");
                        szA = szReceiver; szB = szSender;
                    }
                }
                if (szFmt != nullptr) {
                    std::snprintf(szBuf, sizeof szBuf, szFmt, szA, szB);
                }
                // the GM notice carries the prompt buffer and 0xfc00d5/0x7db
                ((void (*)(void*, const char*, uint32_t, uint32_t))SessSlot(
                    pSess, 0x78))(pSess, szBuf, 0xfc00d5, 0x7db);

                std::snprintf(szBuf, sizeof szBuf, "%s",
                              StrGet("STR_FLOWER_GM_PROMPT_ALL"), szReceiver,
                              szSender);
                SessTell(pSess, idSender, szBuf);
                std::snprintf(szBuf, sizeof szBuf, "%s",
                              StrGet("STR_FLOWER_RECEIVER_PROMPT"));
                SessTell(pSess, idReceiver, szBuf);
                uSlot = uSlot;
            }

            if (byFlag != 0) {
                if (bVip) {
                    char szBuf[0x200];
                    std::snprintf(szBuf, sizeof szBuf, "%s",
                                  StrGet("STR_FLOWER_VIP_SYS_SEND"), szSender);
                    SessTell(pSess, idReceiver, szBuf);
                }
                const int iToday = TodayStamp();
                ((void (*)(void*, uint32_t, int))SessSlot(pSess, 0x28))(
                    pSess, idSender, iToday);
            }
            const uint32_t uValue = CTodayFlowerMgr::GetValue(pMap, idReceiver,
                                                             uSlot);
            ((void (*)(void*, uint32_t, uint32_t, uint32_t))SessSlot(pSess,
                                                                    0x88))(
                pSess, idReceiver, uSlot & 0xff, uValue);
            ((void (*)(void*, uint32_t))SessSlot(pSess, 0xb0))(pSess, idSender);
            CMsgFlower::BaseDtor(oMsg);
            uRet = 1;
        } else {
            SessTell(pSess, idSender, StrGet("STR_FLOWER_RECEIVER_NOT_FEMALE"));
            uRet = 0;
        }
    }
    (void)uLast;
    return uRet;
}


// 0x140d926c0 — the gift path. Same session contract as Send; the gift slot
// comes out of 0x140d91a70 (4..7) and the receiver must be male.
uint8_t CFlowerService::SendGift(void* pThis, uint32_t idSender,
                                 uint32_t idReceiver, int nArg) {
    unsigned char* p = (unsigned char*)pThis;
    if (idSender == 0 || idReceiver == 0) {
        g_pfnFlowerLog(kCheckFormat, "", "SendGift", "");
        return 0;
    }
    void* pSess = *reinterpret_cast<void**>(p + 8);
    if (pSess == nullptr) return 0;
    std::map<uint32_t, CTodayFlower*>* pMap =
        *reinterpret_cast<std::map<uint32_t, CTodayFlower*>**>(p + 0x18);
    uint8_t uRet = 0;
    const uint32_t uReceiverIn = idReceiver;   // local_c78

    if (((int (*)(void*))SessSlot(pSess, 0x18))(pSess) != 2) return 0;

    bool bSelf = false;
    uint8_t byFlag = 0;
    if (((uint8_t (*)(void*, uint32_t))SessSlot(pSess, 0x50))(pSess, idSender) ==
        0) {
        SessTell(pSess, idSender, StrGet("STR_GIFT_SENDER_NOT_ALIVE"));
        return 0;
    }
    uint32_t uSlot = 4;      // local_c80
    uint32_t uCount = 0;     // local_c7c
    if (nArg == 0) {
        uSlot = 4;
        uCount = 1;
        bSelf = true;
        byFlag = 1;
        const uint32_t uLevel =
            ((uint32_t (*)(void*, uint32_t))SessSlot(pSess, 0x40))(pSess,
                                                                  idSender);
        if (uLevel < kMinSendLevel) {
            SessTell(pSess, idSender, StrGet("STR_GIFT_LEVEL_TOO_LOW"));
            return 0;
        }
        const uint32_t uDate =
            ((uint32_t (*)(void*, uint32_t))SessSlot(pSess, 0x20))(pSess,
                                                                  idSender);
        if (IsExpiredDate(uDate) == 0) {
            const std::time_t tNow = std::time(nullptr);
            struct tm* pTm = std::localtime(&tNow);
            if (pTm == nullptr) {
                g_pfnFlowerLog(kCheckFormat, "", "SendGift", "");
                return 0;
            }
            char szBuf[0x400];
            std::snprintf(szBuf, sizeof szBuf, "%s",
                          StrGet("STR_GIFT_HAVE_SENT_TODAY"));
            SessTell(pSess, idSender, szBuf);
            return 0;
        }
        uCount = 1;
        uSlot = 4;
    } else {
        uint32_t uResolved = 4;
        int iCount = 0;
        if (g_pfnResolveGift) g_pfnResolveGift(pThis, nArg, &uResolved, &iCount);
        uSlot = uResolved;
        uCount = (uint32_t)iCount;
        if (uCount == 0) return 0;
    }

    if (((uint8_t (*)(void*, uint32_t))SessSlot(pSess, 0x58))(pSess,
                                                             idReceiver) == 0) {
        return 0;   // uRet stays 0
    }
    if (((int (*)(void*, uint32_t))SessSlot(pSess, 0x18))(pSess, idReceiver) !=
        1) {
        SessTell(pSess, idSender, StrGet("STR_GIFT_RECEIVER_NOT_MALE"));
        return 0;
    }
    if (!bSelf) {
        if (nArg == 0) return 0;
        if (((uint8_t (*)(void*, uint32_t, int))SessSlot(pSess, 0))(
                pSess, idSender, nArg) == 0) {
            return 0;
        }
    }
    const int iOld = ((int (*)(void*, uint32_t, uint32_t))SessSlot(pSess,
                                                                  0x30))(
        pSess, idReceiver, uSlot);
    bool bVip = false;
    uint32_t uAdd = uCount;
    if (byFlag != 0 &&
        ((uint8_t (*)(void*, uint32_t))SessSlot(pSess, 0x90))(pSess, 3) != 0) {
        const uint32_t uGrade =
            ((uint32_t (*)(void*, uint32_t))SessSlot(pSess, 0x48))(pSess,
                                                                  idSender);
        switch (uGrade) {
            case 0: break;
            case 1: bVip = true; uAdd = 2; break;
            case 2: bVip = true; uAdd = 3; break;
            case 3: bVip = true; uAdd = 5; break;
            case 4: bVip = true; uAdd = 10; break;
            case 5: bVip = true; uAdd = 0xf; break;
            case 6: bVip = true; uAdd = 0x1e; break;
            default: bVip = true; uAdd = 0x1e; break;
        }
    }
    const int iNew = iOld + (int)uAdd;
    ((void (*)(void*, uint32_t, uint32_t, int))SessSlot(pSess, 0x38))(
        pSess, idReceiver, uSlot, iNew);
    CTodayFlowerMgr::SetValue(pMap, idReceiver, uSlot, (int32_t)uAdd);

    unsigned char oMsg[0x410];
    CTodayFlowerMgr_LogCheck;   // placeholder keeps the CHECKF blob unreferenced
    std::memset(oMsg, 0, sizeof oMsg);
    CMsgFlower::Ctor(oMsg);
    const char* szReceiver =
        ((const char* (*)(void*, uint32_t))SessSlot(pSess, 8))(pSess,
                                                              idReceiver);
    const char* szSender =
        ((const char* (*)(void*, uint32_t))SessSlot(pSess, 8))(pSess, idSender);
    if (!CMsgFlower::Build(oMsg, 1, szSender, szReceiver, uAdd, uSlot,
                           byFlag)) {
        g_pfnFlowerLog(kCheckFormat, "", "SendGift", "");
    } else if (uCount < kGiftGm99) {
        ((void (*)(void*, uint32_t, void*))SessSlot(pSess, 0x68))(
            pSess, idSender, oMsg);
        ((void (*)(void*, uint32_t, void*, uint32_t))SessSlot(pSess, 0x70))(
            pSess, idReceiver, oMsg, idSender);
    } else {
        ((void (*)(void*, uint32_t, void*))SessSlot(pSess, 0x68))(
            pSess, idSender, oMsg);
        ((void (*)(void*, uint32_t, void*, uint32_t))SessSlot(pSess, 0x70))(
            pSess, idReceiver, oMsg, idSender);

        char szGm[0x200];
        szGm[0] = '\0';
        const char* szFmt = nullptr;
        const char* szA = nullptr;
        const char* szB = nullptr;
        // the four gift slots, each with its own 99 and 999 prompt; the
        // argument order differs per literal and is kept exactly
        if (uSlot == 4) {
            if (uCount == kGiftGm99) {
                szFmt = StrGet("STR_GIFT_GM_PROMPT_A_99");
                szA = szReceiver; szB = szSender;
            } else if (uCount == kGiftGm999) {
                szFmt = StrGet("STR_GIFT_GM_PROMPT_A_999");
                szA = szReceiver; szB = szSender;
            }
        } else if (uSlot == 5) {
            if (uCount == kGiftGm99) {
                szFmt = StrGet("STR_GIFT_GM_PROMPT_B_99");
                szA = szSender; szB = szReceiver;
            } else if (uCount == kGiftGm999) {
                szFmt = StrGet("STR_GIFT_GM_PROMPT_B_999");
                szA = szReceiver; szB = szSender;
            }
        } else if (uSlot == 6) {
            if (uCount == kGiftGm99) {
                szFmt = StrGet("STR_GIFT_GM_PROMPT_C_99");
                szA = szSender; szB = szReceiver;
            } else if (uCount == kGiftGm999) {
                szFmt = StrGet("STR_GIFT_GM_PROMPT_C_999");
                szA = szSender; szB = szReceiver;
            }
        } else if (uSlot == 7) {
            if (uCount == kGiftGm99) {
                szFmt = StrGet("STR_GIFT_GM_PROMPT_D_99");
                szA = szSender; szB = szReceiver;
            } else if (uCount == kGiftGm999) {
                szFmt = StrGet("STR_GIFT_GM_PROMPT_D_999");
                szA = szSender; szB = szReceiver;
            }
        }
        if (szFmt != nullptr) std::snprintf(szGm, sizeof szGm, szFmt, szA, szB);
        ((void (*)(void*, const char*, uint32_t, uint32_t))SessSlot(pSess,
                                                                    0x78))(
            pSess, szGm, 0xfc00d5, 0x7db);

        // the service object's own slot +0x48 takes the gift slot here
        if (*(void***)pThis != nullptr) {
            ((void (*)(void*, uint32_t))(*reinterpret_cast<void***>(pThis))
                 [0x48 / 8])(pThis, uSlot);
        }
        std::snprintf(szGm, sizeof szGm, "%s",
                      StrGet("STR_GIFT_GM_PROMPT_ALL"));
        SessTell(pSess, idSender, szGm);
        std::snprintf(szGm, sizeof szGm, "%s",
                      StrGet("STR_GIFT_RECEIVER_PROMPT"));
        idReceiver = uReceiverIn;
        SessTell(pSess, uReceiverIn, szGm);
        uSlot = uSlot;
    }

    if (byFlag != 0) {
        if (bVip) {
            char szBuf[0x200];
            std::snprintf(szBuf, sizeof szBuf, "%s",
                          StrGet("STR_GIFT_VIP_SYS_SEND"), szSender);
            SessTell(pSess, idReceiver, szBuf);
        }
        const int iToday = TodayStamp();
        ((void (*)(void*, uint32_t, int))SessSlot(pSess, 0x28))(pSess, idSender,
                                                               iToday);
    }
    const uint32_t uValue = CTodayFlowerMgr::GetValue(pMap, idReceiver, uSlot);
    ((void (*)(void*, uint32_t, uint32_t, uint32_t))SessSlot(pSess, 0x88))(
        pSess, idReceiver, uSlot & 0xff, uValue);
    ((void (*)(void*, uint32_t))SessSlot(pSess, 0xb0))(pSess, idSender);
    CMsgFlower::BaseDtor(oMsg);
    uRet = 1;
    return uRet;
}

}  // namespace flower

namespace flower {

void* (*g_pfnFlowerCreateHelper)() = nullptr;
uint8_t (*g_pfnFlowerAttachInit)(void*, void*) = nullptr;

// 0x140d93630 — complete destruction, then the heap release on bit 0
void* CFlowerService::DeleteDtorFull(void* self, uint64_t uFlag, void* pB,
                                    void* pC) {
    CModule::Complete(self, uFlag, pB, pC);
    if ((uFlag & 1) != 0) ::operator delete(self);
    return self;
}

// 0x140d93360 — the decompiled body masks RAX down to a byte, i.e. it returns
// the boolean result of the object's own slot 0
uint8_t CFlowerService::Release(void* self) {
    if (self == nullptr) return 0;
    void** vt = *reinterpret_cast<void***>(self);
    ((void (*)(void*, uint64_t))vt[0])(self, 1);
    return 1;
}

// 0x140d93380
//   kernel->slot(+0x30)(kernel, 9)      -> the mode-9 processor
//   this->+0x420                        -> the owned object
//   Attach(this->+0x420, processor)
uint8_t CFlowerService::Initialize(void* self) {
    unsigned char* p = (unsigned char*)self;
    unsigned char* pKernel = *reinterpret_cast<unsigned char**>(p + 0x840);
    void** vt = *reinterpret_cast<void***>(pKernel);
    void* pProc = ((void* (*)(void*, uint32_t))vt[0x30 / 8])(pKernel, 9);
    if (pProc == nullptr) {
        CTodayFlowerMgr_LogCheck();
        return 0;
    }
    unsigned char* pOwned = *reinterpret_cast<unsigned char**>(p + 0x420);
    if (pOwned == nullptr) {
        CTodayFlowerMgr_LogCheck();
        return 0;
    }
    if (Attach(pOwned, pProc) == 0) {
        CTodayFlowerMgr_LogCheck();
        return 0;
    }
    return 1;
}

// 0x140d934e0 — `(***(this+0x420))()`: the owned object's slot 0, no args
void CFlowerService::ReleaseOwned(void* self) {
    unsigned char* pOwned = *reinterpret_cast<unsigned char**>(
        (unsigned char*)self + 0x420);
    void** vt = *reinterpret_cast<void***>(pOwned);
    ((void (*)(void*))vt[0])(pOwned);
}

// 0x140d93460
//   record[0] > uCount            -> 0
//   type = record[1]
//     type < 0x3ea                -> 0
//     0x3ea <= type < 0x3ec       -> the CMsgLog member at +0x010
//     type == 0x47e               -> the CMsgFlower member at +0x428
//     anything else               -> 0
//   and the chosen member must accept it through its own slot 1
void* CFlowerService::Lookup(void* self, uint16_t* pRecord, uint16_t uCount) {
    if (pRecord == nullptr || *pRecord > uCount) return nullptr;
    const uint16_t uType = pRecord[1];
    unsigned char* pNode;
    if (uType < 0x3ea) {
        return nullptr;
    } else if (uType < 0x3ec) {
        pNode = (unsigned char*)self + 0x010;
    } else if (uType == 0x47e) {
        pNode = (unsigned char*)self + 0x428;
    } else {
        return nullptr;
    }
    void** vt = *reinterpret_cast<void***>(pNode);
    if (((uint8_t (*)(unsigned char*))vt[1])(pNode) == 0) return nullptr;
    return pNode;
}

// 0x140d93660 — route through the member's slot 2, answer the record's u16
uint16_t CFlowerService::Process(void* self, uint32_t dwArg, uint16_t* pRecord,
                                uint16_t uCount) {
    unsigned char* pNode = (unsigned char*)Lookup(self, pRecord, uCount);
    if (pNode == nullptr) return 0;
    void** vt = *reinterpret_cast<void***>(pNode);
    void* pOwned = *reinterpret_cast<void**>((unsigned char*)self + 0x420);
    ((void (*)(unsigned char*, uint32_t, void*))vt[0x10 / 8])(pNode, dwArg,
                                                             pOwned);
    return *reinterpret_cast<uint16_t*>(pNode + 8);
}

// 0x140d91490
//   pSecond == 0                        -> CHECKF, 0
//   *(pOwned + 8) = pSecond
//   *(pOwned + 0x18) = helper()
//   helper() == 0                       -> CHECKF, 0
//   else AttachInit(helper, *(pOwned + 8))
uint8_t CFlowerService::Attach(void* pOwned, void* pSecond) {
    if (pSecond == nullptr) {
        CTodayFlowerMgr_LogCheck();
        return 0;
    }
    unsigned char* p = (unsigned char*)pOwned;
    *reinterpret_cast<void**>(p + 0x08) = pSecond;
    void* pHelper = g_pfnFlowerCreateHelper();
    *reinterpret_cast<void**>(p + 0x18) = pHelper;
    if (pHelper == nullptr) {
        CTodayFlowerMgr_LogCheck();
        return 0;
    }
    return g_pfnFlowerAttachInit(pHelper,
                                 *reinterpret_cast<void**>(p + 0x08));
}

// 0x140d91050 — (year*100 + 0x2e631 + month)*100 + day on the local clock
int CFlowerService::TodayStamp() {
    std::time_t t = std::time(nullptr);
    struct tm* pTm = std::localtime(&t);
    if (pTm == nullptr) {
        CTodayFlowerMgr_LogCheck();
        return 0;
    }
    return (pTm->tm_year * 100 + 0x2e631 + pTm->tm_mon) * 100 + pTm->tm_mday;
}

// 0x140d910c0 — rebuild the stamp as a local tm and compare with the clock
uint8_t CFlowerService::IsExpiredDate(uint32_t dwDate) {
    struct tm t;
    t.tm_sec = 0x3b;
    t.tm_min = 0x3b;
    t.tm_hour = 0x17;
    t.tm_isdst = 0;
    t.tm_mday = (int)(uint16_t)((int16_t)dwDate +
                                (int16_t)((uint64_t)dwDate / 100) * -100);
    t.tm_mon = (int)(dwDate % 10000) / 100 - 1;
    t.tm_year = (int)(dwDate / 10000 & 0xffff) - 0x76c;
    std::time_t built = std::mktime(&t);
    std::time_t now = std::time(nullptr);
    return built < now ? 1 : 0;
}

// 0x140d91980
//   *(ctx+8) == 0 or nArg == 0 -> both outputs zero (the original then falls
//   through, so the slot query decides the answer anyway)
//   raw = (*(*(ctx+8))+0xa0)(ctx+8)      (no arguments are passed)
//   raw/1000: 0x2ef -> type 0, 0x2f0 -> 1, 0x2f1 -> 2, 0x2f2 -> 3, else 0
//   count = raw - {0xb7598, 0xb7980, 0xb7d68, 0xb8150} or zero
uint32_t CFlowerService::ResolveFlowerSlot(void* pCtx, int nArg,
                                           uint32_t* pOutType, int* pOutCount) {
    unsigned char* p = (unsigned char*)pCtx;
    if (*reinterpret_cast<void**>(p + 8) == nullptr || nArg == 0) {
        *pOutType = 0;
        *pOutCount = 0;
    }
    unsigned char* pSession = *reinterpret_cast<unsigned char**>(p + 8);
    void** vt = *reinterpret_cast<void***>(pSession);
    uint32_t raw = ((uint32_t (*)(void*))vt[0xa0 / 8])(pSession);
    const uint32_t uSlot = raw / 1000;
    if (uSlot == 0x2ef) {
        *pOutType = 0;
        *pOutCount = (int)(raw - 0xb7598);
        return raw - 0xb7598;
    }
    if (uSlot == 0x2f0) {
        *pOutType = 1;
        *pOutCount = (int)(raw - 0xb7980);
        return raw - 0xb7980;
    }
    if (uSlot != 0x2f1) {
        if (uSlot != 0x2f2) {
            *pOutType = 0;
            *pOutCount = 0;
            return raw * 0x10624dd3u;   // the original's leftover multiply
        }
        *pOutType = 3;
        *pOutCount = (int)(raw - 0xb8150);
        return raw - 0xb8150;
    }
    *pOutType = 2;
    *pOutCount = (int)(raw - 0xb7d68);
    return raw - 0xb7d68;
}

// 0x140d91a70 — the raw value the session reports at +0xa0 packs the gift
// band and the count: raw = band * 1000 + count, bands 0x2f3..0x2f6 being
// the four gift slots 4..7.
uint32_t CFlowerService::ResolveGiftSlot(void* pThis, int nArg,
                                         uint32_t* pSlot, int* pCount) {
    void* pSess = *reinterpret_cast<void**>((unsigned char*)pThis + 8);
    if (pSess == nullptr || nArg == 0) {
        *pSlot = 4;
        *pCount = 0;
        // the original keeps going here rather than returning
    }
    const uint32_t uRaw = ((uint32_t (*)(void*))SessSlot(pSess, 0xa0))(pSess);
    const uint32_t uBand = uRaw / 1000;
    if (uBand == 0x2f3) {                     // 755000 — gift A
        *pSlot = 4;
        *pCount = (int)(uRaw - 0xb8538);
        return uRaw - 0xb8538;
    }
    if (uBand == 0x2f4) {                     // 756000 — gift B
        *pSlot = 5;
        *pCount = (int)(uRaw - 0xb8920);
        return uRaw - 0xb8920;
    }
    if (uBand == 0x2f5) {                     // 757000 — gift C
        *pSlot = 6;
        *pCount = (int)(uRaw - 0xb8d08);
        return uRaw - 0xb8d08;
    }
    if (uBand == 0x2f6) {                     // 758000 — gift D
        *pSlot = 7;
        *pCount = (int)(uRaw - 0xb90f0);
        return uRaw - 0xb90f0;
    }
    *pSlot = 4;
    *pCount = 0;
    // the decompiler shows the original computing uRaw * 0x10624dd3 here,
    // the magic-multiply residue of a division it could not resolve
    return uRaw * 0x10624dd3u;
}

uint32_t (*g_pfnResolveGift)(void*, int, uint32_t*, int*) =
    &CFlowerService::ResolveGiftSlot;

}  // namespace flower
