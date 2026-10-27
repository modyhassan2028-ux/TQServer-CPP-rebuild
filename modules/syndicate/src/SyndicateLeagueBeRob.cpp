// SyndicateLeagueBeRob.cpp — D69
//
// The syndicate::CMsgLeagueBeRob family, verbatim from
// the decompile (Syndicate.dll.decompiled.c lines
// 148754-149023 and 156639-156676, 163087-163820).
// Layout + RAW notes: see the header banner.
#include "modules/syndicate/src/SyndicateLeagueBeRob.h"
#include "modules/syndicate/src/SyndicateModule.h"   // op new/delete + vft
#include "modules/syndicate/src/SyndicateCMsgCtors.h" // tq Init + PB consts
#include "modules/syndicate/src/SyndicateMeedFlow.h" // g_fnTqCMsgInit
#include <cstring>
#include <new>      // placement new for the real std::string
#include <string>

namespace syndicate {

// ---- the seams ----
void* g_pVtCMsgLeagueBeRob = nullptr;
void* g_pVtCMsgLeagueBeRobPB = nullptr;
void* g_pVtCMsgLeagueBeRobRePB = nullptr;
char (*g_fnPbSerializeToArray)(void*, void*, size_t) = nullptr;
const int* (*g_fnPbIntMax)(const int*, const int*) = nullptr;
const int* g_pPbReserveFloor = nullptr;
void (*g_fnOpDeleteArr)(void*) = nullptr;
void (*g_fnPbBaseDtor)(void*) = nullptr;
void (*g_fnLogBeRobSerializeErr)(const void*, const char*) = nullptr;
void (*g_fnLogBeRobSerializeFail)(const void*) = nullptr;

// ---- raw offset shorthands (msg = byte ptr) ----
static inline char* MsgPb(char* p)   { return p + 0x408; }
static inline void* PbVt(char* pMsg) {
    return *(void***)MsgPb(pMsg);
}
// the PB vtable slots used by the family
static inline void** PbVtSlots(char* pMsg) {
    return *(void***)MsgPb(pMsg);
}
static inline char* Rep(char* pMsg) { return pMsg + 0x450; }

// the rep layout (int32 at +8/+0xc/+0x10, entries @+0)
static inline int32_t& RepSize(char* pRep) {
    return *(int32_t*)(pRep + 8);
}
static inline int32_t& RepAlloc(char* pRep) {
    return *(int32_t*)(pRep + 0xc);
}
static inline int32_t& RepCap(char* pRep) {
    return *(int32_t*)(pRep + 0x10);
}
static inline void**& RepElems(char* pRep) {
    return *(void***)pRep;
}

// ================= 1417e89a0: entry ctor =================
void* EntryCtorLeagueBeRobRe(void* pEntry) {
    char* pc = (char*)pEntry;
    *(void**)pc = g_pVtPbMessageLite;          // store, then
    *(void**)pc = g_pVtCMsgLeagueBeRobRePB;     // store (verbatim)
    new (pc + 8) std::string();                 // +0x08 string
    *(uint32_t*)(pc + 0x34) = 0;                // cached
    *(uint32_t*)(pc + 0x38) = 0;                // value
    *(uint32_t*)(pc + 0x30) = 0;                // has-bits
    return pEntry;
}

// ================= 1417e89f0: entry +0x34 =================
uint32_t EntryGetCachedLeagueBeRobRe(void* pEntry) {
    return *(uint32_t*)((char*)pEntry + 0x34);
}

// ================= 1417d56b0: NewEntry =================
// op_new(0x40) + the entry ctor; null stays null.
void* NewLeagueBeRobRe() {
    void* p = g_fnOpNew(0x40);
    if (p == nullptr)
        return nullptr;
    return EntryCtorLeagueBeRobRe(p);
}

// ================= 1417e93b0: PB ctor =================
void* ProtoCtorLeagueBeRobPB(void* pPb) {
    char* pc = (char*)pPb;
    *(void**)pc = g_pVtPbMessageLite;
    *(void**)pc = g_pVtCMsgLeagueBeRobPB;
    new (pc + 8) std::string();                 // +0x08 string
    *(uint64_t*)(pc + 0x48) = 0;                // elements
    *(uint32_t*)(pc + 0x50) = 0;                // current size
    *(uint32_t*)(pc + 0x54) = 0;                // allocated
    *(uint32_t*)(pc + 0x58) = 0;                // capacity
    g_fnPbDefaultInit();                        // 1417e8050
    *(uint32_t*)(pc + 0x34) = 0;                // cached
    *(uint32_t*)(pc + 0x38) = 0;                // f1
    *(uint32_t*)(pc + 0x3c) = 0;                // f2
    *(uint32_t*)(pc + 0x60) = 0;                // f3
    *(void**)(pc + 0x40) = g_pPbDefaultInstance; // name slot
    *(uint32_t*)(pc + 0x30) = 0;                // has-bits
    return pPb;
}

// ================= 1417e9430: PB +0x34 =================
uint32_t ProtoGetCachedLeagueBeRobPB(void* pPb) {
    return *(uint32_t*)((char*)pPb + 0x34);
}

// ================= 1417e0110: ReserveEntries =================
// if cap < n: newCap = IntMax(&cap*2, &n);
//                 newCap = IntMax(&floor, &newCap);
//             op_new(8*newCap) (128-bit overflow ->
//             op_new(~0) verbatim); elements = new;
//             if src: memcpy(new, src, alloc*8);
//             delete[](src).
void ReserveEntriesLeagueBeRob(void* pRep, int nMin) {
    char* pc = (char*)pRep;
    if (RepCap(pc) < nMin) {
        int nDoubled = RepCap(pc) << 1;
        const int* pDoubled = &nDoubled;
        const int* pMin = &nMin;
        const int* pGrow = g_fnPbIntMax(pDoubled, pMin);
        pGrow = g_fnPbIntMax(g_pPbReserveFloor, pGrow);
        int nNewCap = *pGrow;
        // the raw 128-bit product check: high qword of
        // 8 * (sign-extended) newCap != 0 -> size = ~0
        __int128 prod = (__int128)8 *
                        (__int128)(int64_t)nNewCap;
        uint64_t uSize;
        if ((uint64_t)((uint64_t)((__int128)prod >> 64)) != 0)
            uSize = ~(uint64_t)0;
        else
            uSize = (uint64_t)prod;
        void* pNew = g_fnOpNew(uSize);
        void* pOld = *(void**)pc;               // src
        RepElems(pc) = (void**)pNew;            // store, THEN
        if (pOld != nullptr) {                  // copy+free
            memcpy(pNew, pOld,
                   (size_t)(uint64_t)(int64_t)RepAlloc(pc) << 3);
            g_fnOpDeleteArr(pOld);
        }
        *(int32_t*)(pc + 0x10) = *pGrow;        // cap = newCap
    }
}

// ================= 1417e9440: PB dtor =================
void ProtoDtorLeagueBeRobPB(void* pPb, uint64_t uA,
                            uint64_t uB, uint64_t uC) {
    (void)uA; (void)uB; (void)uC;  // the C++ dtor flags ride
    char* pc = (char*)pPb;
    *(void**)pc = g_pVtCMsgLeagueBeRobPB;
    // the name slot: neither the default instance nor
    // null -> real string: dtor + scalar delete
    std::string* pName = *(std::string**)(pc + 0x40);
    if (pName != (std::string*)g_pPbDefaultInstance &&
        pName != nullptr) {
        pName->~basic_string();
        g_fnOpDelete(pName);
    }
    // the constructed entries: vt[0](entry, 1)
    int64_t nAlloc = *(int32_t*)(pc + 0x54);
    void** pElems = *(void***)(pc + 0x48);
    for (int64_t i = 0; i < nAlloc; ++i) {
        void* pEntry = pElems[i];
        if (pEntry != nullptr) {
            void** vt = *(void***)pEntry;
            ((void (*)(void*, uint64_t))vt[0])(pEntry, 1);
        }
    }
    g_fnOpDeleteArr(*(void**)(pc + 0x48));       // elements
    ((std::string*)(pc + 8))->~basic_string(); // +0x08 str
    g_fnPbBaseDtor(pPb);                       // 1417de5a0
}

// ================= 1417d5460: CMsg ctor =================
void* CtorCMsgLeagueBeRob(void* pMsg) {
    char* pc = (char*)pMsg;
    *(void**)pc = g_pTqCMsgVft;
    g_fnTqCMsgInit(pc);
    *(void**)pc = g_pVtCMsgLeagueBeRob;
    ProtoCtorLeagueBeRobPB(pc + 0x408);
    g_fnTqCMsgInit(pc);          // verbatim: Init runs TWICE
    return pMsg;
}

// ================= 1417d54b0: CMsg dtor =================
void DtorCMsgLeagueBeRob(void* pMsg, uint64_t uA,
                         uint64_t uB, uint64_t uC) {
    char* pc = (char*)pMsg;
    *(void**)pc = g_pVtCMsgLeagueBeRob;
    ProtoDtorLeagueBeRobPB(pc + 0x408, uA, uB, uC);
    *(void**)pc = g_pTqCMsgVft;
}

// ================= 1417d5710: deleting dtor =================
uint64_t DeletingDtorCMsgLeagueBeRob(void* pMsg,
                                     uint64_t uFlags) {
    char* pc = (char*)pMsg;
    *(void**)pc = g_pVtCMsgLeagueBeRob;
    ProtoDtorLeagueBeRobPB(pc + 0x408, 0, 0, 0);
    *(void**)pc = g_pTqCMsgVft;
    if ((uFlags & 1) != 0)
        g_fnOpDelete(pMsg);
    return 0;
}

// ================= 1417d53f0: SetNamePB =================
// has-bits |= 8; lazy std::string at the +0x40 slot
// (the default instance marks empty); assign(psz).
void SetNameLeagueBeRobPB(void* pPb, const char* psz) {
    char* pc = (char*)pPb;
    *(uint32_t*)(pc + 0x30) |= 8;
    if (*(void**)(pc + 0x40) == g_pPbDefaultInstance) {
        void* p = g_fnOpNew(0x28);
        std::string* pStr = nullptr;
        if (p != nullptr) {
            pStr = new (p) std::string();
        }
        *(std::string**)(pc + 0x40) = pStr;
    }
    // the raw tail is the jumptable assign (the const
    // char* overload, collapsed by the decompiler)
    (*(std::string**)(pc + 0x40))->assign(psz);
}

// ================= 1417d54f0: Create =================
bool CreateLeagueBeRob(void* pMsg, uint32_t uType,
                       uint32_t uId, uint32_t uParam,
                       const char* pszName) {
    char* pc = (char*)pMsg;
    if (pszName == nullptr)
        return false;
    g_fnTqCMsgInit(pc);
    *(uint32_t*)(pc + 0x438) |= 1;             // PB has-bits
    *(uint32_t*)(pc + 0x440) = uType;           // PB f1
    *(uint32_t*)(pc + 0x438) |= 2;
    *(uint32_t*)(pc + 0x444) = uId;             // PB f2
    *(uint32_t*)(pc + 0x438) |= 4;
    *(uint32_t*)(pc + 0x468) = uParam;         // PB f3
    SetNameLeagueBeRobPB(pc + 0x408, pszName);
    *(uint16_t*)(pc + 0xa) = 0xa51;             // wire id
    // PB vt[8] (the +0x40 slot): cached size (the
    // decompile shows the call argless — the PB this
    // rides rcx)
    void** vt = PbVtSlots(pc);
    uint64_t uSize = ((uint64_t(*)(void*))vt[8])(pc + 0x408);
    *(uint16_t*)(pc + 8) = (uint16_t)uSize;
    return true;
}

// ================= 1417d55a0: Clear =================
void ClearLeagueBeRob(void* pMsg) {
    char* pc = (char*)pMsg;
    void** vt = PbVtSlots(pc);
    ((void (*)(void*))vt[3])(pc + 0x408);       // PB vt[3]
    uint64_t uSize = ((uint64_t(*)(void*))vt[8])(pc + 0x408);
    *(uint16_t*)(pc + 8) = (uint16_t)uSize;
}

// ================= 1417d5770: GetCount =================
uint16_t GetCountLeagueBeRob(void* pMsg) {
    return *(uint16_t*)((char*)pMsg + 0x458);
}

// ================= 1417d5780: GetOrAddEntry =================
void* GetOrAddEntryLeagueBeRob(void* pRep) {
    char* pc = (char*)pRep;
    int32_t nIdx = RepSize(pc);
    if (nIdx < RepAlloc(pc)) {
        // reuse a constructed entry
        void* pEntry = RepElems(pc)[nIdx];
        RepSize(pc) = nIdx + 1;
        return pEntry;
    }
    if (RepAlloc(pc) == RepCap(pc))
        ReserveEntriesLeagueBeRob(pc, RepCap(pc) + 1);
    void* pEntry = g_fnOpNew(0x40);
    if (pEntry != nullptr)
        EntryCtorLeagueBeRobRe(pEntry);
    RepAlloc(pc) = RepAlloc(pc) + 1;
    RepElems(pc)[RepSize(pc)] = pEntry;
    RepSize(pc) = RepSize(pc) + 1;
    return pEntry;
}

// ================= 1417d5820: AppendDword =================
uint64_t AppendDwordLeagueBeRob(void* pMsg, int32_t nVal) {
    char* pc = (char*)pMsg;
    uint64_t uStale = 0;   // raw rax rides; only AL gates
    if (nVal != 0) {
        void** vt = PbVtSlots(pc);
        // PB vt[8]: cached size (argless in the decompile;
        // the PB this rides rcx)
        uStale = ((uint64_t(*)(void*))vt[8])(pc + 0x408);
        if ((int64_t)(int64_t)(int32_t)uStale + 4 < 0x400) {
            void* pEntry = GetOrAddEntryLeagueBeRob(Rep(pc));
            *(uint32_t*)((char*)pEntry + 0x30) |= 1;
            *(int32_t*)((char*)pEntry + 0x38) = nVal;
            return 1;
        }
    }
    // the raw tail: rax & ~0xff (AL = 0 -> "failed")
    return uStale & ~(uint64_t)0xff;
}

// ================= 1417d55e0: Serialize =================
uint64_t SerializeLeagueBeRob(void* pMsg) {
    char* pc = (char*)pMsg;
    void** vt = PbVtSlots(pc);
    char cOk = g_fnPbSerializeToArray(pc + 0x408,
                                     pc + 0xc, 0x3fc);
    if (cOk == '\0') {
        // PB vt[4]: IsInitialized
        char cInit = ((char (*)(void*))vt[4])(pc + 0x408);
        if (cInit == '\0') {
            // PB vt[5] sret: fills the 40-byte buffer,
            // returns it in rax; the raw string shape:
            // qword@+0x20 < 0x10 -> inline@+8, else the
            // qword ptr@+8 (verbatim offsets)
            uint8_t abStr[0x28];
            memset(abStr, 0, sizeof(abStr));
            uint64_t uStr = ((uint64_t(*)(void*, void*))
                vt[5])(pc + 0x408, abStr);
            uint64_t uCStr;
            if (*(uint64_t*)(uStr + 0x20) < 0x10)
                uCStr = uStr + 8;
            else
                uCStr = *(uint64_t*)(uStr + 8);
            g_fnLogBeRobSerializeErr(
                (const void*)0x14183c0c0,   // DAT_14183c0c0
                (const char*)uCStr);
            // the raw tail destroys the sret string; the
            // exact string ABI behind the +0x20 shape is
            // TBD pending the archive raw-check
            ((std::string*)abStr)->~basic_string();
        } else {
            g_fnLogBeRobSerializeFail(
                (const void*)0x1417d5650 /* the literal */);
        }
        return 0;   // raw: rax & ~0xff
    }
    uint64_t uSize = ((uint64_t(*)(void*))vt[8])(pc + 0x408);
    *(uint16_t*)(pc + 8) = (uint16_t)uSize;
    return 1;
}

}  // namespace syndicate
