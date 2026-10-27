// D85 seams: CCountry::OnLeagueOnStage (FUN_141736d40)
#ifndef COUNTRY_LEAGUE_ON_STAGE_H
#define COUNTRY_LEAGUE_ON_STAGE_H
#include <cstdint>
namespace syndicate {
// MSVC _Tree node (RAW layout: +0x00 left, +0x08 parent,
// +0x10 right, +0x18 key(u32), +0x20 value, +0x29 isNil)
struct CountryTreeNode {
    CountryTreeNode* m_left;    // +0x00
    CountryTreeNode* m_parent;  // +0x08
    CountryTreeNode* m_right;   // +0x10
    uint32_t m_key;             // +0x18
    uint8_t  m_pad;             // +0x1c
    uint8_t  m_bHead;           // +0x1d (temp-map walk flag)
    uint8_t  m_pad2[2];         // +0x1e
    void* m_value;              // +0x20
    uint8_t  m_pad3[8];         // +0x21..+0x28
    uint8_t  m_bNil;            // +0x29 (country-map walk flag)
    uint8_t  m_pad4[6];         // +0x2a..+0x2f
    uint8_t  m_pad5[0x19];      // +0x30..+0x48
    uint8_t  m_bNilH;           // +0x49 (harem-map walk flag)
    CountryTreeNode() : m_left(nullptr), m_parent(nullptr),
        m_right(nullptr), m_key(0), m_pad(0), m_bHead(0),
        m_pad2{0,0}, m_value(nullptr), m_pad3{}, m_bNil(0),
        m_pad4{}, m_pad5{}, m_bNilH(0) {}
};
// tree anchor pair: [0] = wrapper, wrapper[0] = root/parent head,
// the end-head lives at wrapper+0x30
extern void*    (*g_fnC85CreateKing)(void**, uint32_t, uint32_t, uint32_t); // 141721be0
extern void     (*g_fnC85AfterKing)(void**, uint32_t);          // 141721780
extern void     (*g_fnC85Enthrone)(void**, uint32_t);            // 141731d50
extern void*    (*g_fnC85MapFind)(void**, void*, void**);        // 14172b160
extern void     (*g_fnC85MapInsert)(void**, void*, void*);       // 14172b870
extern void     (*g_fnC85SetRank4000)(void**, uint32_t);         // 14172f500
extern void     (*g_fnC85MoveKing)(void**, void*, void*, const char*); // 1417360a0
extern void*    (*g_fnC85NewTreeHead)(void);                     // 141726c30
extern void     (*g_fnC85FillTempMap)(void**, void**, void*);       // 14172f970
extern uint32_t (*g_fnC85MemberRank)(void**, uint32_t);          // 14172ecb0
extern void     (*g_fnC85TempMapClear)(void**, void*, void*, void*); // 14172a410
extern void     (*g_fnC85UpdateMember)(void*, int32_t, int32_t);  // 1417524d0
extern void     (*g_fnC85LeagueName)(void*, uint32_t);            // 141768020
extern void     (*g_fnC85LogErr)(const char*, uint64_t, uint64_t);
extern void*    (*g_fnC85StrMgr)(void);
extern const char* (*g_fnC85GetStr)(void*, const char*);
extern void     (*g_fnC85Snprintf)(char*, uint64_t, const char*);
extern void*    (*g_fnC85VtCall)(void*, uint32_t, uint32_t);      // value vt+0x10
extern uint32_t (*g_fnC85VtGetId)(void*);                        // vt+0x40
extern uint32_t (*g_fnC85VtGetLeaderName)(void*);                // vt+0x30 (rank/leader)
extern void     (*g_fnC85Broadcast)(void**, uint32_t, const char*, uint32_t); // vt+0x28
extern char s_szCountryPath85[];
void CountryLeagueOnStage(void** apCountry, uint32_t idLeague,
    const char* szName);
} // namespace syndicate
#endif
