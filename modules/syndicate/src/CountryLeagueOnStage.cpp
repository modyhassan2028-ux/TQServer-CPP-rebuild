// D85: RAW-verbatim port of FUN_141736d40
// (CCountry::OnLeagueOnStage). Source: country.cpp.
#include "modules/syndicate/src/CountryLeagueOnStage.h"
#include <cstring>
#include <cstdlib>
namespace syndicate {
void*    (*g_fnC85CreateKing)(void**, uint32_t, uint32_t, uint32_t);
void     (*g_fnC85AfterKing)(void**, uint32_t);
void     (*g_fnC85Enthrone)(void**, uint32_t);
void*    (*g_fnC85MapFind)(void**, void*, void**);
void     (*g_fnC85MapInsert)(void**, void*, void*);
void     (*g_fnC85SetRank4000)(void**, uint32_t);
void     (*g_fnC85MoveKing)(void**, void*, void*, const char*);
void*    (*g_fnC85NewTreeHead)(void);
void     (*g_fnC85FillTempMap)(void**, void**, void*);
uint32_t (*g_fnC85MemberRank)(void**, uint32_t);
void     (*g_fnC85TempMapClear)(void**, void*, void*, void*);
void     (*g_fnC85UpdateMember)(void*, int32_t, int32_t);
void     (*g_fnC85LeagueName)(void*, uint32_t);
void     (*g_fnC85LogErr)(const char*, uint64_t, uint64_t);
void*    (*g_fnC85StrMgr)(void);
const char* (*g_fnC85GetStr)(void*, const char*);
void     (*g_fnC85Snprintf)(char*, uint64_t, const char*);
void*    (*g_fnC85VtCall)(void*, uint32_t, uint32_t);
uint32_t (*g_fnC85VtGetId)(void*);
uint32_t (*g_fnC85VtGetLeaderName)(void*);
void     (*g_fnC85Broadcast)(void**, uint32_t, const char*, uint32_t);
char s_szCountryPath85[] =
    "f:\\version\\cqserver-78.0.11-1204\\modules\\syndicate\\src\\country.cpp";
static const char s_szIter85[] = "iterInfo != m_mapHaremInfo.end()";
// the inlined MSVC _Tree successor walk (RAW +0x29 flag)
static CountryTreeNode* NodeNext85(CountryTreeNode* pNode) {
    if (pNode->m_bNil != 0) abort();          // RAW: _invalid_parameter_noinfo
    if (pNode->m_right->m_bNil == 0) {
        CountryTreeNode* pCur = pNode->m_right;
        CountryTreeNode* pNext = pCur->m_left;
        while (pNext->m_bNil == 0) {
            pCur = pNext;
            pNext = pNext->m_left;
        }
        return pCur;
    }
    CountryTreeNode* pUp = pNode->m_parent;
    CountryTreeNode* pPrev = pNode;
    while (pUp->m_bNil == 0 && pPrev == pUp->m_right) {
        pPrev = pUp;
        pUp = pUp->m_parent;
    }
    return pUp;
}
// the temp-map walk uses the RAW +0x1d flag
static CountryTreeNode* NodeNext85Inner2(CountryTreeNode* pNode,
        uint8_t CountryTreeNode::* pFlag) {
    if ((pNode->*pFlag) != 0) abort();
    if ((pNode->m_right->*pFlag) == 0) {
        CountryTreeNode* pCur = pNode->m_right;
        CountryTreeNode* pNext = pCur->m_left;
        while ((pNext->*pFlag) == 0) {
            pCur = pNext;
            pNext = pNext->m_left;
        }
        return pCur;
    }
    CountryTreeNode* pUp = pNode->m_parent;
    CountryTreeNode* pPrev = pNode;
    while ((pUp->*pFlag) == 0 && pPrev == pUp->m_right) {
        pPrev = pUp;
        pUp = pUp->m_parent;
    }
    return pUp;
}
static CountryTreeNode* NodeNext85Temp(CountryTreeNode* pNode)
    { return NodeNext85Inner2(pNode, &CountryTreeNode::m_bHead); }
// RAW anchors: slot = the MSVC _Tree HEAD NODE;
// FIRST = *(slot) = head->_Left; END = the head node itself
static CountryTreeNode* TreeFirst85(void** apCountry, int idxHead)
    { return ((CountryTreeNode*)apCountry[idxHead])->m_left; }
static CountryTreeNode* TreeEnd85(void** apCountry, int idxHead)
    { return (CountryTreeNode*)apCountry[idxHead]; }
// the RAW harem lower_bound walk (flag +0x49, root at head+8)
static CountryTreeNode* HaremLowerBound85(void** apCountry, uint32_t uKey) {
    CountryTreeNode* pH = (CountryTreeNode*)apCountry[0x40];
    CountryTreeNode* pTrack = pH;
    CountryTreeNode* pNode = pH->m_parent;    // RAW: [1] of the head
    while (pNode->m_bNilH == 0) {
        if (pNode->m_key < uKey)
            pNode = pNode->m_right;           // RAW keeps the old track
        else {
            pTrack = pNode;
            pNode = pNode->m_left;
        }
    }
    return pTrack;
}
void CountryLeagueOnStage(void** apCountry, uint32_t idLeague,
        const char* szName) {
    // ---- stage 1: the king-creation gate (RAW line 49) ----
    if (apCountry[0xb] == 0) {
        void* pKing = g_fnC85CreateKing(apCountry,
            *(uint32_t*)(apCountry + 10),
            *(uint32_t*)((uint8_t*)apCountry + 0x54), 1000);
        apCountry[0xb] = pKing;
        if (pKing == nullptr) {
            g_fnC85LogErr(
                "CCountry::OnLeagueOnStage, create king fail, idLeague[%lu].",
                0, 0);
            return;
        }
        g_fnC85AfterKing(apCountry, 0);
    }
    bool bStaged = false;
    if (idLeague != 0) {
        void** apMemberMap = (void**)(apCountry + 0x22);
        CountryTreeNode* pEnd = TreeEnd85(apCountry, 0x28);
        // ---- walk A (RAW 61): find the CANDIDATE by member id ----
        void* pCand = nullptr;
        CountryTreeNode* pIt = TreeFirst85(apCountry, 0x28);
        while (pIt != pEnd) {
            void* pVal = pIt->m_value;
            if (pVal == nullptr) {
                // RAW line 0x246
                g_fnC85LogErr(&s_szCountryPath85[0], 0x246, 0);
            } else {
                uint32_t uId = g_fnC85VtGetId(
                    g_fnC85VtCall(pVal, 1, 0x10));
                if (uId == idLeague) { pCand = pVal; break; }
            }
            pIt = NodeNext85(pIt);
        }
        // ---- post-A: candidate found and NOT already king ----
        if (pIt != pEnd && pCand != nullptr) {
            uint32_t uRankC = g_fnC85VtGetLeaderName(
                g_fnC85VtCall(pCand, 3, 0x10));
            if (uRankC != 4000) {
                // RAW: FUN_14172b160 (member-map op with the iter)
                g_fnC85MapFind(apMemberMap, nullptr, nullptr);
                uint32_t uCandId = g_fnC85VtGetId(
                    g_fnC85VtCall(pCand, 1, 0x10));
                CountryTreeNode* pH = (CountryTreeNode*)apCountry[0x40];
                CountryTreeNode* pFound = HaremLowerBound85(apCountry, uCandId);
                void* pHaremIter = nullptr;
                if (pFound == pH || uCandId < pFound->m_key) {
                    // RAW line 0x254, verbatim message
                    g_fnC85LogErr(s_szIter85, 0x254,
                        (uint64_t)(uintptr_t)&s_szCountryPath85[0]);
                } else {
                    pHaremIter = pFound;
                    g_fnC85MapInsert((void**)(apCountry + 0x3a),
                        nullptr, pFound);
                }
                uint32_t uRankC2 = g_fnC85VtGetLeaderName(
                    g_fnC85VtCall(pCand, 3, 0x10));
                g_fnC85SetRank4000(apCountry, uRankC2);
                g_fnC85MoveKing(apCountry, pCand, pHaremIter, szName);
                // RAW: no enthrone here — falls through to walk B
            }
        }
        // ---- walk B (RAW 197): find the CURRENT KING by rank 4000 ----
        void* pKing = nullptr;
        CountryTreeNode* pIt2 = TreeFirst85(apCountry, 0x28);
        while (pIt2 != pEnd) {
            void* pVal = pIt2->m_value;
            if (pVal == nullptr) {
                // RAW line 0x262
                g_fnC85LogErr(&s_szCountryPath85[0], 0x262, 0);
            } else {
                uint32_t uRank = g_fnC85VtGetLeaderName(
                    g_fnC85VtCall(pVal, 3, 0x10));
                if (uRank == 4000) { pKing = pVal; break; }
            }
            pIt2 = NodeNext85(pIt2);
        }
        if (pIt2 == pEnd) {
            // no king: enthrone the candidate directly
            g_fnC85Enthrone(apCountry, idLeague);
            bStaged = true;
        } else if (pKing != nullptr) {
            uint32_t uKingId = g_fnC85VtGetId(
                g_fnC85VtCall(pKing, 1, 0x10));
            if (uKingId != idLeague) {
                // ---- the replacement path (RAW 260-355) ----
                g_fnC85MapFind(apMemberMap, nullptr, nullptr);
                CountryTreeNode* pH = (CountryTreeNode*)apCountry[0x40];
                CountryTreeNode* pFound = HaremLowerBound85(apCountry, uKingId);
                void* pHaremIter = nullptr;
                if (pFound == pH || uKingId < pFound->m_key) {
                    // RAW line 0x276, verbatim message
                    g_fnC85LogErr(s_szIter85, 0x276,
                        (uint64_t)(uintptr_t)&s_szCountryPath85[0]);
                } else {
                    pHaremIter = pFound;
                    g_fnC85MapInsert((void**)(apCountry + 0x3a),
                        nullptr, pFound);
                }
                g_fnC85SetRank4000(apCountry, 4000);
                g_fnC85MoveKing(apCountry, pKing, pHaremIter, szName);
                g_fnC85Enthrone(apCountry, idLeague);
                bStaged = true;
                goto Stage3;      // RAW: goto LAB_1417373ed
            }
            bStaged = false;
        } else {
            bStaged = false;
        }
    }
Stage3:
    // ---- stage 3: the LAB entry (RAW line 358) ----
    g_fnC85UpdateMember(apCountry[1],
        *(int32_t*)(apCountry + 10), 1);
    // ---- stage 4: the temp proxy map (RAW 360-380) ----
    void** pProxy = (void**)operator new(8);
    *pProxy = (void*)pProxy;
    CountryTreeNode* pHead = (CountryTreeNode*)g_fnC85NewTreeHead();
    pHead->m_bHead = 1;                 // RAW: +0x1d sentinel byte
    pHead->m_parent = pHead;
    pHead->m_left = pHead;
    pHead->m_right = pHead;
    g_fnC85FillTempMap(apCountry, (void**)pProxy, pHead);
    // ---- stage 5: sweep the temp map (RAW 382-430) ----
    {
        CountryTreeNode* pIt = pHead->m_left;
        CountryTreeNode* pEnd = pHead;
        while (pIt != pEnd) {
            if (pIt->m_key != idLeague || !bStaged) {
                uint32_t uRank = g_fnC85MemberRank(apCountry, pIt->m_key);
                g_fnC85UpdateMember(apCountry[1],
                    (int32_t)pIt->m_key, (int32_t)uRank);
            }
            pIt = NodeNext85Temp(pIt);
        }
    }
    // the STR_LEAGUE_COUNTRY_AGAIN broadcast sweep body (RAW 447-460)
    auto Broadcast85 = [&](void* pVal) {
        char buf[0x200];
        memset(buf, 0, 0x200);
        void* pThree = g_fnC85VtCall(pVal, 3, 0x10);
        uint32_t uLeader = g_fnC85VtGetLeaderName(pThree);
        g_fnC85LeagueName(apCountry[1], uLeader);
        const char* psz = g_fnC85GetStr(g_fnC85StrMgr(),
            "STR_LEAGUE_COUNTRY_AGAIN");
        g_fnC85Snprintf(buf, 0x200, psz);
        void* pOne = g_fnC85VtCall(pVal, 1, 0x10);
        uint32_t uId = g_fnC85VtGetId(pOne);
        g_fnC85Broadcast(apCountry, uId, buf, 0xffff00);
    };
    // ---- stage 6: map [0x1a] sweep — RAW error line 0x299 ----
    {
        void** apMap = (void**)(apCountry + 0x1a);
        CountryTreeNode* pIt = TreeFirst85(apCountry, 0x20);
        CountryTreeNode* pEnd = TreeEnd85(apCountry, 0x20);
        while (pIt != pEnd) {
            if (pIt->m_value == nullptr)
                g_fnC85LogErr(&s_szCountryPath85[0], 0x299, 0);
            else
                Broadcast85(pIt->m_value);
            pIt = NodeNext85(pIt);
        }
    }
    // ---- stage 7: map [0x12] sweep — RAW error line 0x2a7 ----
    {
        void** apMap = (void**)(apCountry + 0x12);
        CountryTreeNode* pIt = TreeFirst85(apCountry, 0x18);
        CountryTreeNode* pEnd = TreeEnd85(apCountry, 0x18);
        while (pIt != pEnd) {
            if (pIt->m_value == nullptr)
                g_fnC85LogErr(&s_szCountryPath85[0], 0x2a7, 0);
            else
                Broadcast85(pIt->m_value);
            pIt = NodeNext85(pIt);
        }
    }
    // ---- stage 8: member-map sweep — RAW error line 0x2b5; ----
    // the staged id is skipped only when bStaged
    {
        void** apMap = (void**)(apCountry + 0x22);
        CountryTreeNode* pIt = TreeFirst85(apCountry, 0x28);
        CountryTreeNode* pEnd = TreeEnd85(apCountry, 0x28);
        while (pIt != pEnd) {
            void* pVal = pIt->m_value;
            if (pVal == nullptr) {
                g_fnC85LogErr(&s_szCountryPath85[0], 0x2b5, 0);
            } else {
                uint32_t uId = g_fnC85VtGetId(
                    g_fnC85VtCall(pVal, 1, 0x10));
                if (uId != idLeague || !bStaged)
                    Broadcast85(pVal);
            }
            pIt = NodeNext85(pIt);
        }
    }
    // ---- stage 9: the RAW cleanup ----
    g_fnC85TempMapClear((void**)pProxy, nullptr, nullptr, nullptr);
    operator delete(pHead);
    operator delete(pProxy[0]);
}
} // namespace syndicate
