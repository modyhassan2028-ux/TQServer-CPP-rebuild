// SyndicateLeagueRobOptClass.cpp — D71
//
// The syndicate::CMsgLeagueRobOpt family, verbatim from
// the decompile (Syndicate.dll.decompiled.c lines
// 150953-151290, 155819-156150, 162619-162650,
// 169936-170230, 170747-170860) and RAW-VERIFIED with
// capstone on the recovered original Syndicate.dll
// (Dec 2015 build). Layout + RAW notes: see the header
// banner.
#include "Exe/Dll/Syndicate/Port/SyndicateLeagueRobOptClass.h"
#include "Exe/Dll/Syndicate/Port/SyndicateModule.h"    // op new/delete + tq vft
#include "Exe/Dll/Syndicate/Port/SyndicateCMsgCtors.h" // tq Init + PB consts
#include "Exe/Dll/Syndicate/Port/SyndicateLeagueBeRob.h" // shared seams
#include "Exe/Dll/Syndicate/Port/SyndicateMeedFlow.h"  // g_fnTqCMsgInit
#include <cstring>
#include <new>      // placement new for the real std::string
#include <string>

namespace syndicate {

// ---- the new seams ----
char (*g_fnPbParseFromArray)(void*, const void*, int) = nullptr;
void (*g_fnLogRobOptErr)(const void*, const char*) = nullptr;
void (*g_fnLogRobOptFail)(const void*) = nullptr;
void* (*g_fnPbCheckBuild)(void*, int, const void*, int) = nullptr;
void* (*g_fnPbCheckText)(void*, const void*) = nullptr;
void (*g_fnPbCheckStream)(void*, void*) = nullptr;
void (*g_fnPbCheckDone)(void*) = nullptr;
// the entry class vftable seam (new for this family)
void* g_pVtCMsgLeagueRobOptServer = nullptr;

// ---- raw offset shorthands (msg = byte ptr) ----
static inline char* MsgPb(char* p)   { return p + 0x408; }
static inline void** PbVtSlots(char* pMsg) {
    return *(void***)MsgPb(pMsg);
}
// the rep header (PB+0x40 = msg+0x448):
//   {elements@+0, current@+8, allocated@+0xc, cap@+0x10}
static inline char* Rep(char* pMsg) { return pMsg + 0x448; }
static inline int32_t& RepSize(char* p) {
    return *(int32_t*)(p + 8);
}
static inline int32_t& RepAlloc(char* p) {
    return *(int32_t*)(p + 0xc);
}
static inline int32_t& RepCap(char* p) {
    return *(int32_t*)(p + 0x10);
}
static inline void**& RepElems(char* p) {
    return *(void***)p;
}

// ================= 1417d8220: SetStr1 =================
// has-bits |= 2; lazy std::string at the +0x38 slot
// (the default instance marks empty); assign(psz, n) —
// the import-verified assign(const char*, size_t).
void SetStr1EntryRobOpt(void* pEntry, const char* psz,
                        size_t n) {
    char* pc = (char*)pEntry;
    *(uint32_t*)(pc + 0x30) |= 2;
    if (*(void**)(pc + 0x38) == g_pPbDefaultInstance) {
        void* p = g_fnOpNew(0x28);
        std::string* pStr = nullptr;
        if (p != nullptr)
            pStr = new (p) std::string();
        *(std::string**)(pc + 0x38) = pStr;
    }
    // the raw tail is the (char*, size_t) assign thunk
    (*(std::string**)(pc + 0x38))->assign(psz, n);
}

// ================= 1417d82b0: SetStr2 =================
// has-bits |= 4; the same lazy dance at the +0x40 slot.
void SetStr2EntryRobOpt(void* pEntry, const char* psz,
                        size_t n) {
    char* pc = (char*)pEntry;
    *(uint32_t*)(pc + 0x30) |= 4;
    if (*(void**)(pc + 0x40) == g_pPbDefaultInstance) {
        void* p = g_fnOpNew(0x28);
        std::string* pStr = nullptr;
        if (p != nullptr)
            pStr = new (p) std::string();
        *(std::string**)(pc + 0x40) = pStr;
    }
    (*(std::string**)(pc + 0x40))->assign(psz, n);
}

// ================= 1417efbd0: entry ctor =================
void* EntryCtorLeagueRobOptServer(void* pEntry) {
    char* pc = (char*)pEntry;
    *(void**)pc = g_pVtPbMessageLite;
    *(void**)pc = g_pVtCMsgLeagueRobOptServer;
    new (pc + 8) std::string();                 // +0x08
    g_fnPbDefaultInit();                       // 1417e8050
    *(uint32_t*)(pc + 0x34) = 0;                // cached
    *(uint32_t*)(pc + 0x48) = 0;                // value
    *(void**)(pc + 0x38) = g_pPbDefaultInstance; // str1
    *(void**)(pc + 0x40) = g_pPbDefaultInstance; // str2
    *(uint32_t*)(pc + 0x30) = 0;                // has-bits
    return pEntry;
}

// ================= 1417efc40: entry +0x34 =================
uint32_t EntryGetCachedLeagueRobOptServer(void* pEntry) {
    return *(uint32_t*)((char*)pEntry + 0x34);
}

// ================= 1417efc50: entry copy ctor =================
// the ctor (verbatim) then CopyFrom(1417ef8f0).
void* EntryCopyCtorLeagueRobOptServer(void* pDst,
                                      void* pSrc) {
    EntryCtorLeagueRobOptServer(pDst);
    EntryCopyFromLeagueRobOptServer(pDst, pSrc);
    return pDst;
}

// ================= 1417efce0: entry dtor =================
void EntryDtorLeagueRobOptServer(void* pEntry) {
    char* pc = (char*)pEntry;
    *(void**)pc = g_pVtCMsgLeagueRobOptServer;
    // the two heap strings: neither the default instance
    // nor null -> real string: dtor + scalar delete
    std::string* pStr1 = *(std::string**)(pc + 0x38);
    if (pStr1 != (std::string*)g_pPbDefaultInstance &&
        pStr1 != nullptr) {
        pStr1->~basic_string();
        g_fnOpDelete(pStr1);
    }
    std::string* pStr2 = *(std::string**)(pc + 0x40);
    if (pStr2 != (std::string*)g_pPbDefaultInstance &&
        pStr2 != nullptr) {
        pStr2->~basic_string();
        g_fnOpDelete(pStr2);
    }
    ((std::string*)(pc + 8))->~basic_string();  // +0x08
    g_fnPbBaseDtor(pEntry);                    // 1417de5a0
}

// ================= 1417efd70: entry New =================
void* EntryNewLeagueRobOptServer() {
    void* p = g_fnOpNew(0x50);
    if (p == nullptr)
        return nullptr;
    return EntryCtorLeagueRobOptServer(p);
}

// ================= 1417efb90: deleting helper =================
void EntryDeletingHelperRobOpt(void* pEntry) {
    if (pEntry != nullptr) {
        void** vt = *(void***)pEntry;
        ((void (*)(void*, uint64_t))vt[0])(pEntry, 1);
    }
}

// ================= 1417ef430: str1 merge =================
// has-bits |= 2; lazy +0x38 slot; assign(const string&).
void EntryMergeStr1LeagueRobOptServer(void* pEntry,
                                      const void* pStr) {
    char* pc = (char*)pEntry;
    *(uint32_t*)(pc + 0x30) |= 2;
    if (*(void**)(pc + 0x38) == g_pPbDefaultInstance) {
        void* p = g_fnOpNew(0x28);
        std::string* pNew = nullptr;
        if (p != nullptr)
            pNew = new (p) std::string();
        *(std::string**)(pc + 0x38) = pNew;
    }
    // raw tail: assign(const string&) thunk
    (*(std::string**)(pc + 0x38))->assign(
        *(const std::string*)pStr);
}

// ================= 1417ef520: str2 merge =================
void EntryMergeStr2LeagueRobOptServer(void* pEntry,
                                      const void* pStr) {
    char* pc = (char*)pEntry;
    *(uint32_t*)(pc + 0x30) |= 4;
    if (*(void**)(pc + 0x40) == g_pPbDefaultInstance) {
        void* p = g_fnOpNew(0x28);
        std::string* pNew = nullptr;
        if (p != nullptr)
            pNew = new (p) std::string();
        *(std::string**)(pc + 0x40) = pNew;
    }
    (*(std::string**)(pc + 0x40))->assign(
        *(const std::string*)pStr);
}

// ================= 1417ef8f0: entry CopyFrom =================
// the CHECK(this != from) FATAL then the 3 has-bit
// merges, then the tail append of the message-level
// inline string field (this+8 <- from+8).
void EntryCopyFromLeagueRobOptServer(void* pDst,
                                      void* pSrc) {
    char* pA = (char*)pDst;
    char* pB = (char*)pSrc;
    if (pB == pA) {
        // the protobuf CHECK machinery (verbatim seq):
        // build(3, file, 0x120) -> text -> stream ->
        // destroy
        uint8_t buf[0x40];
        memset(buf, 0, sizeof(buf));
        void* pMsg = g_fnPbCheckBuild(buf, 3,
            (const void*)0x1417ef926 /* "msgleaguerobopt.pb.cc" */,
            0x120);
        void* pTxt = g_fnPbCheckText(pMsg,
            (const void*)0x1417ef943
            /* "CHECK failed: (&from) != (this): " */);
        g_fnPbCheckStream((void*)0, pTxt);
        g_fnPbCheckDone(buf);
    }
    if (*(unsigned char*)(pB + 0x30) != 0) {
        if ((*(uint8_t*)(pB + 0x30) & 1) != 0) {
            uint32_t uVal = *(uint32_t*)(pB + 0x48);
            *(uint32_t*)(pA + 0x30) |= 1;
            *(uint32_t*)(pA + 0x48) = uVal;
        }
        if (((*(uint32_t*)(pB + 0x30) >> 1) & 1) != 0)
            EntryMergeStr1LeagueRobOptServer(pA,
                *(void**)(pB + 0x38));
        if (((*(uint32_t*)(pB + 0x30) >> 2) & 1) != 0)
            EntryMergeStr2LeagueRobOptServer(pA,
                *(void**)(pB + 0x40));
    }
    // the raw tail: append(this+8, from+8) — the inline
    // string field merge (import-verified append(const
    // string&))
    ((std::string*)(pA + 8))->append(
        *(const std::string*)(pB + 8));
}

// ================= 1417efdb0: entry Swap =================
void EntrySwapLeagueRobOptServer(void* pA, void* pB) {
    char* p1 = (char*)pA;
    char* p2 = (char*)pB;
    if (pA == pB)
        return;
    // value@+0x48
    {
        uint32_t t = *(uint32_t*)(p1 + 0x48);
        *(uint32_t*)(p1 + 0x48) = *(uint32_t*)(p2 + 0x48);
        *(uint32_t*)(p2 + 0x48) = t;
    }
    // str1@+0x38
    {
        void* t = *(void**)(p1 + 0x38);
        *(void**)(p1 + 0x38) = *(void**)(p2 + 0x38);
        *(void**)(p2 + 0x38) = t;
    }
    // str2@+0x40
    {
        void* t = *(void**)(p1 + 0x40);
        *(void**)(p1 + 0x40) = *(void**)(p2 + 0x40);
        *(void**)(p2 + 0x40) = t;
    }
    // has-bits@+0x30
    {
        uint32_t t = *(uint32_t*)(p1 + 0x30);
        *(uint32_t*)(p1 + 0x30) = *(uint32_t*)(p2 + 0x30);
        *(uint32_t*)(p2 + 0x30) = t;
    }
    // cached@+0x34
    {
        uint32_t t = *(uint32_t*)(p1 + 0x34);
        *(uint32_t*)(p1 + 0x34) = *(uint32_t*)(p2 + 0x34);
        *(uint32_t*)(p2 + 0x34) = t;
    }
    // the inline string@+8 swap (std::swap shape)
    std::swap(*(std::string*)(p1 + 8), *(std::string*)(p2 + 8));
}

// ================= 1417f0650: PB +0x34 =================
uint32_t GetCachedLeagueRobOptPB(void* pPb) {
    return *(uint32_t*)((char*)pPb + 0x34);
}

// ================= 1417f0660: PB dtor =================
// loop to ALLOCATED (+0x4c) with the per-entry null
// check; each constructed entry deleted via vt[0](,1);
// then the elements array (scalar delete — raw calls
// the delete thunk), the +0x08 inline string, and the
// MessageLite base dtor tail.
void DtorLeagueRobOptPB(void* pPb) {
    char* pc = (char*)pPb;
    *(void**)pc = g_pVtCMsgLeagueRobOptPB;
    int32_t nBound = *(int32_t*)(pc + 0x4c);   // allocated
    void** pElems = *(void***)(pc + 0x40);
    for (int32_t i = 0; i < nBound; ++i) {
        void* pEntry = pElems[i];
        if (pEntry != nullptr) {
            void** vt = *(void***)pEntry;
            ((void (*)(void*, uint64_t))vt[0])(pEntry, 1);
        }
    }
    g_fnOpDeleteArr(*(void**)(pc + 0x40));     // elements
    ((std::string*)(pc + 8))->~basic_string(); // +0x08
    g_fnPbBaseDtor(pPb);                       // 1417de5a0
}

// ================= 1417f06f0: PB New =================
void* NewLeagueRobOptPB() {
    void* p = g_fnOpNew(0x58);
    if (p == nullptr)
        return nullptr;
    return CtorCMsgLeagueRobOptPB(p);
}

// ================= 1417d83e0: CMsg dtor =================
void DtorCMsgLeagueRobOpt(void* pMsg) {
    char* pc = (char*)pMsg;
    *(void**)pc = g_pVtCMsgLeagueRobOpt;
    DtorLeagueRobOptPB(pc + 0x408);
    *(void**)pc = g_pTqCMsgVft;
}

// ================= 1417d86a0: deleting dtor =================
void DeletingDtorCMsgLeagueRobOpt(void* pMsg,
                                  uint64_t uFlags) {
    char* pc = (char*)pMsg;
    *(void**)pc = g_pVtCMsgLeagueRobOpt;
    DtorLeagueRobOptPB(pc + 0x408);
    *(void**)pc = g_pTqCMsgVft;
    if ((uFlags & 1) != 0)
        g_fnOpDelete(pMsg);
}

// ================= 1417d84d0: Create =================
bool CreateLeagueRobOpt(void* pMsg, uint16_t uType,
                        uint32_t uF2) {
    char* pc = (char*)pMsg;
    g_fnTqCMsgInit(pc);
    char* pPb = pc + 0x408;
    *(uint32_t*)(pPb + 0x30) |= 1;             // has-bits
    *(uint32_t*)(pPb + 0x38) = uType;           // f1
    *(uint32_t*)(pPb + 0x30) |= 2;
    *(uint32_t*)(pPb + 0x3c) = uF2;             // f2
    *(uint16_t*)(pc + 0xa) = 0xa52;            // wire id
    void** vt = PbVtSlots(pc);
    uint64_t uSize = ((uint64_t(*)(void*))vt[8])(pPb);
    *(uint16_t*)(pc + 8) = (uint16_t)uSize;    // cached
    return true;
}

// ================= 1417d8530: Clear =================
void ClearLeagueRobOpt(void* pMsg) {
    char* pc = (char*)pMsg;
    void** vt = PbVtSlots(pc);
    ((void (*)(void*))vt[3])(pc + 0x408);       // PB vt[3]
    uint64_t uSize = ((uint64_t(*)(void*))vt[8])(pc + 0x408);
    *(uint16_t*)(pc + 8) = (uint16_t)uSize;
}

// ================= 1417d8570: Serialize =================
uint64_t SerializeLeagueRobOpt(void* pMsg) {
    char* pc = (char*)pMsg;
    void** vt = PbVtSlots(pc);
    char cOk = g_fnPbSerializeToArray(pc + 0x408,
                                      pc + 0xc, 0x3fc);
    if (cOk == '\0') {
        // PB vt[4]: IsInitialized
        char cInit = ((char (*)(void*))vt[4])(pc + 0x408);
        if (cInit == '\0') {
            // PB vt[5] sret: the raw string shape:
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
            g_fnLogRobOptErr(
                (const void*)0x14183cdd0,   // DAT_14183cdd0
                (const char*)uCStr);
            ((std::string*)abStr)->~basic_string();
        } else {
            g_fnLogRobOptFail((const void*)
                0x1417d85f9 /* the literal */);
        }
        return 0;   // raw: xor al,al
    }
    uint64_t uSize = ((uint64_t(*)(void*))vt[8])(pc + 0x408);
    *(uint16_t*)(pc + 8) = (uint16_t)uSize;
    return 1;
}

// ================= 1417d8420: CreateBufMsg =================
bool CreateBufMsgLeagueRobOpt(void* pMsg, const void* pBuf,
                              uint16_t uLen) {
    char* pc = (char*)pMsg;
    if (pBuf == nullptr)                // raw: test rdx,rdx
        return false;
    if (*(uint16_t*)(pc + 0xa) != 0xa52) // raw: cmp ax,[rcx+0xa]
        return false;
    // parse (pb, buf+4, len-4) — the wire header skip
    char cOk = g_fnPbParseFromArray(pc + 0x408,
        (const char*)pBuf + 4, (int)uLen - 4);
    if (cOk != '\0') {
        return true;                    // raw: mov al,1
    }
    void** vt = PbVtSlots(pc);
    // PB vt[4]: IsInitialized
    char cInit = ((char (*)(void*))vt[4])(pc + 0x408);
    if (cInit != '\0') {
        g_fnLogRobOptFail((const void*)
            0x1417d84b1 /* the literal */);
    } else {
        // PB vt[5] sret: the same raw string shape
        uint8_t abStr[0x28];
        memset(abStr, 0, sizeof(abStr));
        uint64_t uStr = ((uint64_t(*)(void*, void*))
            vt[5])(pc + 0x408, abStr);
        uint64_t uCStr;
        if (*(uint64_t*)(uStr + 0x20) < 0x10)
            uCStr = uStr + 8;
        else
            uCStr = *(uint64_t*)(uStr + 8);
        g_fnLogRobOptErr(
            (const void*)0x14183cd30,   // DAT_14183cd30
            (const char*)uCStr);
        ((std::string*)abStr)->~basic_string();
    }
    return false;                       // raw: xor al,al
}

// ================= 1417d8700: GetCount =================
uint16_t GetCountLeagueRobOpt(void* pMsg) {
    return *(uint16_t*)((char*)pMsg + 0x450);
}

// ================= 1417d8710: GetEntry =================
void* GetEntryLeagueRobOpt(void* pMsg, int i) {
    return RepElems(Rep((char*)pMsg))[i];
}

// ================= 1417d8640: NewEntry =================
void* NewEntryLeagueRobOpt() {
    void* p = g_fnOpNew(0x50);
    if (p == nullptr)
        return nullptr;
    return EntryCtorLeagueRobOptServer(p);
}

// ================= 1417d8730: GetOrAddEntry =================
// reuse path does NOT clear the reused entry (verbatim).
void* GetOrAddEntryLeagueRobOpt(void* pRep) {
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
    void* pEntry = NewEntryLeagueRobOpt();
    RepAlloc(pc) = RepAlloc(pc) + 1;
    RepElems(pc)[RepSize(pc)] = pEntry;
    RepSize(pc) = RepSize(pc) + 1;
    return pEntry;
}

// ================= 1417d8810: AppendDword =================
uint64_t AppendDwordLeagueRobOpt(void* pMsg, int32_t nVal) {
    char* pc = (char*)pMsg;
    uint64_t uStale = 0;   // raw rax rides; only AL gates
    if (nVal != 0) {
        void** vt = PbVtSlots(pc);
        // PB vt[8]: cached size (the decompile shows the
        // call argless; the PB this rides rcx)
        uStale = ((uint64_t(*)(void*))vt[8])(pc + 0x408);
        if ((int64_t)(int32_t)uStale + 4 < 0x400) {
            void* pEntry = GetOrAddEntryLeagueRobOpt(
                Rep(pc));
            *(uint32_t*)((char*)pEntry + 0x30) |= 1;
            *(int32_t*)((char*)pEntry + 0x48) = nVal;
            return 1;
        }
    }
    // the raw tail: xor al,al (AL = 0 -> "failed")
    return uStale & ~(uint64_t)0xff;
}

// ================= 1417d8870: AppendDwordString =================
// raw: str2 is skipped when EMPTY (the repne scasb len
// scan), not merely when null; str1 is assigned with the
// 0x10 cap by SetStr1 verbatim.
uint64_t AppendDwordStringLeagueRobOpt(void* pMsg,
        int32_t nVal, const char* psz1,
        const char* psz2) {
    char* pc = (char*)pMsg;
    uint64_t uStale = 0;
    if (nVal != 0 && psz1 != nullptr) {
        void** vt = PbVtSlots(pc);
        uStale = ((uint64_t(*)(void*))vt[8])(pc + 0x408);
        if ((int64_t)(int32_t)uStale + 0x24 < 0x400) {
            void* pEntry = GetOrAddEntryLeagueRobOpt(
                Rep(pc));
            *(uint32_t*)((char*)pEntry + 0x30) |= 1;
            *(int32_t*)((char*)pEntry + 0x48) = nVal;
            SetStr1EntryRobOpt(pEntry, psz1, 0x10);
            if (psz2 != nullptr && psz2[0] != '\0')
                SetStr2EntryRobOpt(pEntry, psz2, 0x10);
            return 1;
        }
    }
    return uStale & ~(uint64_t)0xff;
}

}  // namespace syndicate
