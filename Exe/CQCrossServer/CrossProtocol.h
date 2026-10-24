// Cross-server wire protocol (v1), reconstructed from the decompiled
// CQCrossServer.exe (CCrossServerKernel / crossshell.cpp model):
// the hub accepts game-server connections, records them by server id and
// relays messages between servers (SendMsgToOtherServer / BroadcastOtherServerMsg).
// This header is pure encode/decode - shared by the hub binary and the
// MsgServer-side client, and unit-testable on any platform.
#pragma once
#include <cstdint>
#include <cstring>
#include <string>
#include <vector>
#include "Network/MsgHead.h"

namespace cross {

// wire message types (MsgHead.type)
enum : uint16_t {
    MsgType_Hello     = 9001, // server -> hub: register id + name
    MsgType_Talk      = 9002, // server -> hub: relay a chat line to every other server
    MsgType_Roster    = 9003, // server -> hub: full player roster snapshot
    MsgType_Heartbeat = 9004, // server -> hub: keepalive + online count
    MsgType_WhoReq    = 9005, // server -> hub: request the aggregated cross roster
    MsgType_WhoResp   = 9006, // hub -> server: every server's roster in one packet
    MsgType_ServerUp  = 9007, // hub -> all: a server connected
    MsgType_ServerDown= 9008, // hub -> all: a server went away

    // ---- COUNTRY system (crossmsgserveraction.cpp switch, the
    // hub-side handlers keyed on MsgHead.type offset +0x430) ----
    // case 0 (~29462): country status query. Reads m_pCountrySysMgr
    //   name (FUN_14001a6a0), leader/title (FUN_14001a6d0) and the
    //   country_date (FUN_14001bc50) for (idserver, idleague), packs
    //   them with CStringPacker::AddString x2 and writes the
    //   country_date back at msg+8.
    // case 1 (~29507): country war state + score update (FUN_14000d620
    //   country lookup, FUN_1400218f0 score write, reply packed via
    //   FUN_1400246a0 and sent with FUN_14000a0b0) - TBD wire format.
    // case 2 (~29579): FUN_14001ee50(countryMgr, .., idserver) - the
    //   plunder-war join flow - TBD.
    // case 4 (~29589): FUN_14001a240(countryMgr, ..) + direct reply.
    // case 5 (~29605): FUN_14000a310(kernel, buf, 0, 0xffffff, 0x961)
    //   - cross-server broadcast of a system talk (type 0x961).
    // case 6 (~29609): FUN_14001d790(countryMgr, .., idserver) - TBD.
    MsgType_CountryStatusReq  = 9009, // server -> hub: case 0 query
    MsgType_CountryStatusResp = 9010, // hub -> server: name/title/date
    MsgType_CountryBroadcast  = 9011, // hub -> all: case 5 system talk
    // case 1 (~29507): war score query. The original first resolves
    //   FUN_14000d620(kernel, msg+0x420) - the member's country id
    //   (0xffffffff when absent) - and only members WITH a country
    //   get the packed reply (FUN_1400246a0 packs the country id,
    //   FUN_14000a0b0 sends it, ~20268 shows the same -1 gate).
    MsgType_CountryScoreReq  = 9012, // server -> hub: case 1 query
    MsgType_CountryScoreResp = 9013, // hub -> server: country + score
    // case 4 (~29589): UpdateCountryDate. The original reads
    //   idserver from msg+0x420 and the kernel-state date from
    //   kernel+0x430[+8]; on success (FUN_14001a240 returns true)
    //   it refreshes that state to now and echoes the message
    //   back with FUN_14000a0b0(kernel, 0, msg+0x414, ...).
    MsgType_CountryDateUpd  = 9014, // server -> hub: case 4 update
    MsgType_CountryDateAck  = 9015, // hub -> server: state refreshed
    // case 2 (~29579): OnChooseNewCountryLeague - switch the
    //   server's league to (server, league); no reply payload
    //   beyond the original message echo in the binary.
    MsgType_CountryChooseReq  = 9016, // server -> hub: case 2
    MsgType_CountryChooseAck  = 9017, // hub -> server: installed
    // case 6 (~29609): OnProduceFirstCountryLeague - the packed
    //   reply id is server*1000000 + key (FUN_1400243b0), with
    //   the touch timestamp now (TimeGet(2)/10000).
    MsgType_CountryFirstReq  = 9018, // server -> hub: case 6
    MsgType_CountryFirstAck = 9019, // hub -> server: packed id + now
    // plunder war wire types (see the plunder section below)
    MsgType_PlunderWarInfo   = 40041, // ORIGINAL 0x9c69
    MsgType_PlunderWarStatus = 40042, // ORIGINAL 0x9c6a

// ---- LEAGUE messages (CCrossMsgLeagueInfo / LeagueStr / LeagueBrick) ----
// ORIGINAL wire types: CCrossMsgLeagueInfo  = 0x9c62 (40066, ctor
// FUN_140023990, obj 0x438), CCrossMsgLeagueStr = 0x9c63 (40067, ctor
// FUN_140024260, obj 0x450), CCrossMsgLeagueBrick = 0x9c61 (40065,
// ctor FUN_140024040). All three reach the hub through the message
// factory FUN_140022990 (LeagueStr/LeagueInfo) or are hub-built
// outbound (LeagueBrick, in FUN_14001c990 OnBrickChange).
    MsgType_ServerName   = 40015, // ORIGINAL 0x9c4f (CCrossMsgServerName)
    MsgType_EnterOSUserSocketOpt = 40021, // ORIGINAL 0x9c55
    MsgType_OSConnectInfo = 40023, // ORIGINAL 0x9c57
    MsgType_LeagueRank  = 40036, // ORIGINAL 0x9c64 (CCrossMsgLeagueRank)
    MsgType_LeagueList  = 40040, // ORIGINAL 0x9c68 (CCrossMsgLeagueList)
    MsgType_LeagueInfo  = 40066, // ORIGINAL 0x9c62
    MsgType_LeagueStr  = 40067, // ORIGINAL 0x9c63
    MsgType_LeagueBrick = 40065, // ORIGINAL 0x9c61

};

// case 0 query/response payloads (see CCountrySysMgr accessors)
struct CountryStatusReq {
    uint32_t dwIdServer;   // msg+8 in the original layout
    uint32_t dwIdLeague;   // msg+0x10
};
// case 1 payload: uid is read from msg+0x420 in the original
struct CountryScoreReq {
    uint32_t dwUserId;    // FUN_14000d620 key
    uint32_t dwIdServer;  // FUN_14001bc50 arg
    uint32_t dwIdLeague;   // FUN_14001bc50 arg
};
struct CountryScoreResp {
    uint32_t dwCountryId;  // FUN_14000d620 result (never -1 here)
    uint32_t dwCountryDate; // FUN_14001bc50 -> FUN_140022ce0
};
// case 4 payload: idserver comes from msg+0x420; the date being
// confirmed is the hub's tracked country date state
struct CountryDateUpd { uint32_t dwIdServer; uint32_t dwDate; };
struct CountryDateAck { uint32_t dwIdServer; uint32_t dwDate; };
// case 2: install (server, league) as the server's league
struct CountryChooseReq { uint32_t dwIdServer; uint32_t dwIdLeague; };
struct CountryChooseAck { uint32_t dwIdServer; uint32_t dwIdLeague; };
// case 6: first league for a country; the ack carries the packed
// id (server*1000000 + key) and the touch timestamp
struct CountryFirstReq { uint32_t dwIdServer; uint32_t dwKey; };
struct CountryFirstAck { uint64_t ullPackedId; uint32_t dwTouch; };
struct CountryStatusResp {
    char szLeagueName[64];  // AddString #1 ("" when league unknown)
    char szLeaderTitle[64]; // AddString #2
    uint32_t dwCountryDate; // written back to the request msg+8
};


// ---- plunder war (CCrossMsgPlunderWarInfo / CCrossMsgPlunderWarStatus) ----
// ORIGINAL wire types: CCrossMsgPlunderWarInfo  = 0x9c69 (40041),
// CCrossMsgPlunderWarStatus = 0x9c6a (40042).
// ORIGINAL CCrossMsgPlunderWarStatus::Create (FUN_140023410): payload
// +0 = action (u16), +4 = param (u32); MsgHead size = 8.
// Actions seen in the binary: 0 = war-start countdown (param = the
// FUN_14001a400 formula), 1 = war ended, 2 = new day, 3 = signup ended.
#pragma pack(push, 1)
struct PlunderWarStatusData {
    uint16_t usAction;  // payload+0
    uint16_t usPad;     // payload+2 (unwritten by Create, kept zero)
    uint32_t dwParam;   // payload+4
};
// ORIGINAL CCrossMsgPlunderWarInfo::Create (FUN_140023730): payload
// +0 = action (u16), +4 = id (u32), +0xc = target count (u8, starts 0),
// targets appended from +0x10 (FUN_140023790, +4 each); bytes +8..+0xb
// are never written by Create/Append - kept zero here. Size = 0x10 +
// 4*count, capped at 0x3ff (beyond the cap Append fails -> the caller
// logs "msg size error").
struct PlunderWarInfoData {
    uint16_t usAction;      // payload+0
    uint16_t usPad0;        // payload+2 (unwritten, zero)
    uint32_t dwId;          // payload+4
    uint32_t dwPad8;        // payload+8..0xb (unwritten, zero)
    uint8_t  byCount;       // payload+0xc
    uint8_t  usPad13[3];    // payload+0xd..0xf (unwritten, zero)
    uint32_t dwTargets[10]; // payload+0x10.. (max 10 in the flows)
};
#pragma pack(pop)
constexpr uint16_t PLUNDER_WIRE_CAP = 0x3ff; // ORIGINAL AppendTarget size gate

// ORIGINAL CCrossMsgLeagueInfo wire (encoders FUN_140023a40 header /
// FUN_140023a90 first entry / FUN_140023b60 append):
// info+0 usAction, info+2 usCount, entries 0x3c each from info+4.
// Entry: id +0x00, amount +0x04 (read as param_3[1] in the create),
// country_date +0x08 (param_3[2]), league_name +0x0c (param_3+3),
// leader_name +0x1c (param_3+7), title +0x2c (param_3+0xb - append
// only). StrCopy caps are 0x10. Size = 4 + 0x3c*count, capped at
// 0x3ff by the append gate; a reply carries usAction 2 (FUN_140023a40
// writes action 2 before the entry fills).
#pragma pack(push, 1)
struct LeagueInfoEntry {
    uint32_t dwIdLeague;      // +0x00 (request: idleague; reply: idleague + idserver*1000000)
    uint32_t dwAmount;        // +0x04 (request: amount; reply: country_date)
    uint32_t dwCountryDate;   // +0x08 (request: country_date)
    char szName[0x10];        // +0x0c league_name
    char szLeader[0x10];     // +0x1c leader_name
    char szTitle[0x10];      // +0x2c title
};
struct LeagueInfoData {
    uint16_t usAction;               // +0
    uint16_t usCount;                // +2
    LeagueInfoEntry entries[16];     // +4, max (0x3ff-4)/0x3c = 16
};
// ORIGINAL CCrossMsgLeagueStr wire (encoders FUN_140024350 with
// string / FUN_1400243b0 without): info+0 usAction, +4 dwIdServer,
// +8 dwIdLeague, then ONE CStringPacker string (GetString cap 0x10
// in Process FUN_1400243f0). Msg size = packerSize + 0xf, or 0x10
// with no string. TBD: CStringPacker byte framing is a separate
// porting unit (hub-internal fixed 0x10 slot here).
#pragma pack(pop)
#pragma pack(push, 1)
struct LeagueStrData {
    uint16_t usAction;     // +0
    uint16_t usPad2;       // +2 (unwritten, zero)
    uint32_t dwIdServer;   // +4
    uint32_t dwIdLeague;   // +8
    char szText[0x10];     // +0xc packer string #1
};
// ORIGINAL CCrossMsgLeagueBrick wire (FUN_1400240f0 header, size 0x10;
// FUN_140024170 entries, +8 each): info+0 usMode, +4 dwIdLeague,
// +8 dwCountryDate, +0xc usCount, entries {dwIdLeague, dwAmount} from
// +0x10. The append gate fails past 0x3ff and FUN_14001c990 flushes
// the full brick first (FUN_14000a0b0) and re-encodes the header.
#pragma pack(pop)
#pragma pack(push, 1)
struct LeagueBrickEntry { uint32_t dwIdLeague; uint32_t dwAmount; };
struct LeagueBrickData {
    uint16_t usMode;                // +0
    uint16_t usPad2;                // +2 (unwritten, zero)
    uint32_t dwIdLeague;           // +4
    uint32_t dwCountryDate;         // +8
    uint16_t usCount;               // +0xc
    uint16_t usPadE;                // +0xe
    LeagueBrickEntry entries[125];  // +0x10, max (0x3ff-0x10)/8 = 125
};
#pragma pack(pop)
constexpr uint16_t LEAGUE_INFO_WIRE_CAP = 0x3ff; // append gate
// variable-length encode, ORIGINAL size = 4 + 0x3c*count
inline std::vector<uint8_t> EncodeLeagueInfo(uint16_t usAction,
        const LeagueInfoEntry* pEntries, uint16_t usCount) {
    const uint16_t usSize = (uint16_t)(4 + 0x3cu * usCount);
    tq::MsgHead head;
    head.type = MsgType_LeagueInfo;
    head.length = static_cast<uint16_t>(sizeof(tq::MsgHead) + usSize);
    std::vector<uint8_t> pkt(head.length, 0);
    std::memcpy(pkt.data(), &head, sizeof(head));
    uint8_t* p = pkt.data() + sizeof(tq::MsgHead);
    std::memcpy(p + 0, &usAction, 2);
    std::memcpy(p + 2, &usCount, 2);
    for (uint16_t i = 0; i < usCount; ++i)
        std::memcpy(p + 4 + 0x3cu * i, pEntries + i, sizeof(LeagueInfoEntry));
    return pkt;
}

// forward declaration (the template lives below)
template <typename T>
std::vector<uint8_t> Encode(uint16_t usType, const T& data);

// ---- ORIGINAL CCrossMsgOSConnectInfo wire (0x9c57, ctor
// FUN_140022370, obj 0x438): append-target resets by FUN_140022420
// (action u16 @0, count BYTE @2, size 4) and appends u32 entries at
// 4 + count*4 (FUN_1400224b0, gate 0x3ff -> InlineLogERROR
// "create failed" style log + FALSE); FUN_140022560 clears
// (size 4, count 0); FUN_1400225b0 reads the byte count.
#pragma pack(push, 1)
struct OSConnectInfoData {
    uint16_t usAction;     // +0 (0 = connect notify, 1 = disconnect)
    uint8_t  byCount;      // +2 (BYTE count, unlike the u16 counts)
    uint8_t  byPad3;       // +3
    uint32_t dwSockets[63]; // +4, max (0x3ff-4)/4 = 255 -> clamped
};
#pragma pack(pop)
// variable-length encode, ORIGINAL size = 4 + 4*count
inline std::vector<uint8_t> EncodeOSConnectInfo(uint16_t usAction,
        const uint32_t* pdwSockets, uint8_t byCount) {
    const uint16_t usSize = (uint16_t)(4 + 4u * byCount);
    tq::MsgHead head;
    head.type = MsgType_OSConnectInfo;
    head.length = static_cast<uint16_t>(sizeof(tq::MsgHead) + usSize);
    std::vector<uint8_t> pkt(head.length, 0);
    std::memcpy(pkt.data(), &head, sizeof(head));
    uint8_t* p = pkt.data() + sizeof(tq::MsgHead);
    std::memcpy(p + 0, &usAction, 2);
    p[2] = byCount;
    for (uint8_t i = 0; i < byCount; ++i)
        std::memcpy(p + 4 + 4u * i, pdwSockets + i, 4);
    return pkt;
}
// ---- ORIGINAL CCrossMsgServerName wire (0x9c4f, ctor FUN_140022620):
// FUN_1400226d0(msg, id, name): name[0x10] @0 (strncpy), id u32 @0x10,
// size 0x14; FUN_140022780 reads id from +0x10, name from +0.
#pragma pack(push, 1)
struct ServerNameData {
    char     szName[0x10]; // +0
    uint32_t dwIdServer;   // +0x10
};
#pragma pack(pop)
inline std::vector<uint8_t> EncodeServerName(uint32_t dwIdServer,
                                             const char* szName) {
    ServerNameData d{};
    if (szName) std::strncpy(d.szName, szName, sizeof(d.szName) - 1);
    d.dwIdServer = dwIdServer;
    return Encode(MsgType_ServerName, d);
}
// ---- ORIGINAL CCrossMsgEnterOSUserSocketOpt wire (0x9c55, ctor
// FUN_140048f40): FUN_140048ff0(msg, a, b, c): u16 @0, u32 @4,
// u32 @8, size 0xc; FUN_140049090 reads them back. No hub-side
// Process caller in CQCrossServer.exe (game-server side owns it).
#pragma pack(push, 1)
struct EnterOSUserSocketOptData {
    uint16_t usAction;      // +0
    uint16_t usPad2;        // +2
    uint32_t dwParam1;      // +4
    uint32_t dwParam2;      // +8
};
#pragma pack(pop)
inline std::vector<uint8_t> EncodeEnterOSUserSocketOpt(
        uint16_t usAction, uint32_t dwParam1, uint32_t dwParam2) {
    EnterOSUserSocketOptData d{};
    d.usAction = usAction; d.dwParam1 = dwParam1; d.dwParam2 = dwParam2;
    return Encode(MsgType_EnterOSUserSocketOpt, d);
}
// ---- ORIGINAL CCrossMsgLeagueList wire (0x9c68, ctor FUN_1400234b0):
// FUN_140023560(msg, action): u16 @0, flag BYTE @2 = 1, count u16 @4,
// size 8; FUN_1400235c0 appends u32 at 8 + count*4 (gate 0x3ff);
// FUN_140023610 clears (flag 0, count 0, size 8).
#pragma pack(push, 1)
struct LeagueListData {
    uint16_t usAction;     // +0
    uint8_t  byFlag;       // +2 (1 while appending, 0 after clear)
    uint8_t  byPad3;       // +3
    uint16_t usCount;      // +4
    uint16_t usPad6;       // +6
    uint32_t dwLeagues[63]; // +8, max (0x3ff-8)/4 = 255 -> clamped
};
#pragma pack(pop)
inline std::vector<uint8_t> EncodeLeagueList(uint16_t usAction,
        const uint32_t* pdwLeagues, uint16_t usCount) {
    const uint16_t usSize = (uint16_t)(8 + 4u * usCount);
    tq::MsgHead head;
    head.type = MsgType_LeagueList;
    head.length = static_cast<uint16_t>(sizeof(tq::MsgHead) + usSize);
    std::vector<uint8_t> pkt(head.length, 0);
    std::memcpy(pkt.data(), &head, sizeof(head));
    uint8_t* p = pkt.data() + sizeof(tq::MsgHead);
    std::memcpy(p + 0, &usAction, 2);
    p[2] = 1;
    std::memcpy(p + 4, &usCount, 2);
    for (uint16_t i = 0; i < usCount; ++i)
        std::memcpy(p + 8 + 4u * i, pdwLeagues + i, 4);
    return pkt;
}
// ---- ORIGINAL CCrossMsgLeagueRank wire (0x9c64, ctor FUN_140023de0):
// FUN_140023e90(msg, action): u16 @0, flag BYTE @2 = 1, count u16 @4,
// size 8; FUN_140023ef0 appends 0x2c entries from +8:
//   +0/+4/+8 u32s, str@+0x14 (from ptr+0xc, cap 0x10),
//   str@+0x24 (from ptr+0x1c, cap 0x10) - NOTE: the original stride
//   is 0x2c, so the second 0x10 string slot OVERLAPS the next
//   entry by 8 bytes (kept verbatim); FUN_140023fd0 clears.
#pragma pack(push, 1)
struct LeagueRankEntry {
    uint32_t dwParam0;     // +0 (from ptr[0])
    uint32_t dwParam4;     // +4 (from ptr[1])
    uint32_t dwParam8;     // +8 (from ptr[2])
    char     szPad[8];     // +0xc (unwritten gap)
    char     szStr1[0x10]; // +0x14 (from ptr+0xc, cap 0x10)
    // NOTE: entry stride is 0x2c - szStr2@0x24 overlaps this entry
};
struct LeagueRankData {
    uint16_t usAction;     // +0
    uint8_t  byFlag;       // +2
    uint8_t  byPad3;       // +3
    uint16_t usCount;      // +4
    uint16_t usPad6;       // +6
    uint8_t  entries[1];   // +8, 0x2c each (opaque: stride overlap)
};
#pragma pack(pop)
// raw entry append exactly like FUN_140023ef0, 0x2c stride
inline bool LeagueRankAppend(std::vector<uint8_t>& pkt,
        uint32_t a, uint32_t b, uint32_t c,
        const char* s1, const char* s2) {
    // pkt excludes MsgHead; size gate = 0x3ff total message
    if (pkt.size() + 0x2c > 0x3ff) return false;
    const size_t nCount = (pkt.size() - 8) / 0x2c;
    const size_t nBase = 8 + 0x2cu * nCount;
    // the ORIGINAL message buffer is 0x3ff+ with room beyond the
    // logical end - szStr2@+0x24 (cap 0x10) writes 8 bytes past the
    // 0x2c stride. Grow with slack, write, then trim to logical.
    pkt.resize(nBase + 0x2c + 8, 0);
    uint8_t* p = pkt.data() + nBase;
    std::memcpy(p + 0, &a, 4); std::memcpy(p + 4, &b, 4);
    std::memcpy(p + 8, &c, 4);
    if (s1) std::strncpy((char*)p + 0x14, s1, 0x10);
    if (s2) std::strncpy((char*)p + 0x24, s2, 0x10); // overlaps next
    pkt.resize(nBase + 0x2c);
    // count up (u16 @4)
    uint16_t n; std::memcpy(&n, pkt.data() + 4, 2); ++n;
    std::memcpy(pkt.data() + 4, &n, 2);
    return true;
}
// one rank record = the 0x2c-stride append inputs
struct LeagueRankRec {
    uint32_t dwA, dwB, dwC;
    char szStr1[0x10], szStr2[0x10];
};
// chunked encode at the 0x3ff gate; returns one wire packet per
// chunk (msg without head - head is added by the caller, or use
// LeagueRankWrap)
inline std::vector<std::vector<uint8_t>> EncodeLeagueRank(
        uint16_t usAction, const std::vector<LeagueRankRec>& recs) {
    std::vector<std::vector<uint8_t>> out;
    std::vector<uint8_t> body(8, 0);
    std::memcpy(body.data(), &usAction, 2);
    body[2] = 1;
    for (const auto& r : recs) {
        if (!LeagueRankAppend(body, r.dwA, r.dwB, r.dwC,
                              r.szStr1, r.szStr2)) {
            out.push_back(body);
            body.assign(8, 0);
            std::memcpy(body.data(), &usAction, 2);
            body[2] = 1;
            LeagueRankAppend(body, r.dwA, r.dwB, r.dwC,
                            r.szStr1, r.szStr2);
        }
    }
    out.push_back(body);
    return out;
}
inline std::vector<uint8_t> LeagueRankWrap(
        std::vector<uint8_t>& body) {
    tq::MsgHead head;
    head.type = MsgType_LeagueRank;
    head.length = static_cast<uint16_t>(sizeof(tq::MsgHead) +
                                        body.size());
    std::vector<uint8_t> pkt(head.length, 0);
    std::memcpy(pkt.data(), &head, sizeof(head));
    std::memcpy(pkt.data() + sizeof(tq::MsgHead), body.data(),
                body.size());
    return pkt;
}

// forward declaration (the template lives below)
template <typename T>
std::vector<uint8_t> Encode(uint16_t usType, const T& data);
// ORIGINAL CCrossMsgLeagueStr encode with one packer string
// (FUN_140024350: size = packer size + 0xf; fixed 0x1c slot here)
inline std::vector<uint8_t> EncodeLeagueStr(uint16_t usAction,
        uint32_t dwIdServer, uint32_t dwIdLeague, const char* szText) {
    LeagueStrData d{};
    d.usAction = usAction;
    d.dwIdServer = dwIdServer;
    d.dwIdLeague = dwIdLeague;
    if (szText) std::strncpy(d.szText, szText, sizeof(d.szText) - 1);
    return Encode(MsgType_LeagueStr, d);
}
// ORIGINAL CCrossMsgLeagueBrick encode (header 0x10 + 8*count)
inline std::vector<uint8_t> EncodeLeagueBrick(uint16_t usMode,
        uint32_t dwIdLeague, uint32_t dwCountryDate,
        const LeagueBrickEntry* pEntries, uint16_t usCount) {
    const uint16_t usSize = (uint16_t)(0x10 + 8u * usCount);
    tq::MsgHead head;
    head.type = MsgType_LeagueBrick;
    head.length = static_cast<uint16_t>(sizeof(tq::MsgHead) + usSize);
    std::vector<uint8_t> pkt(head.length, 0);
    std::memcpy(pkt.data(), &head, sizeof(head));
    uint8_t* p = pkt.data() + sizeof(tq::MsgHead);
    std::memcpy(p + 0, &usMode, 2);
    std::memcpy(p + 4, &dwIdLeague, 4);
    std::memcpy(p + 8, &dwCountryDate, 4);
    std::memcpy(p + 0xc, &usCount, 2);
    for (uint16_t i = 0; i < usCount; ++i)
        std::memcpy(p + 0x10 + 8u * i, pEntries + i, sizeof(LeagueBrickEntry));
    return pkt;
}

constexpr uint8_t  PLUNDER_MAX_TARGETS = 10; // gate in the war flows

// forward declaration: Encode<T> is defined below
template <typename T>
std::vector<uint8_t> Encode(uint16_t usType, const T& data);

// variable-length encode: ORIGINAL size = 0x10 + 4*count (PlunderWarInfo)
inline std::vector<uint8_t> EncodePlunderWarInfo(uint16_t usAction,
        uint32_t dwId, const uint32_t* pTargets, uint8_t byCount) {
    const uint16_t usSize = (uint16_t)(0x10 + 4u * byCount);
    tq::MsgHead head;
    head.type = MsgType_PlunderWarInfo;
    head.length = static_cast<uint16_t>(sizeof(tq::MsgHead) + usSize);
    std::vector<uint8_t> pkt(head.length, 0);
    std::memcpy(pkt.data(), &head, sizeof(head));
    uint8_t* p = pkt.data() + sizeof(tq::MsgHead);
    std::memcpy(p + 0x0, &usAction, 2);
    std::memcpy(p + 0x4, &dwId, 4);
    *(p + 0xc) = byCount;
    for (uint8_t i = 0; i < byCount; ++i)
        std::memcpy(p + 0x10 + 4u * i, pTargets + i, 4);
    return pkt;
}
// ORIGINAL CCrossMsgPlunderWarStatus: fixed size 8
inline std::vector<uint8_t> EncodePlunderWarStatus(uint16_t usAction,
                                                   uint32_t dwParam) {
    PlunderWarStatusData d{};
    d.usAction = usAction;
    d.dwParam = dwParam;
    return Encode(MsgType_PlunderWarStatus, d);
}

constexpr uint32_t MAX_ROSTER = 64;
constexpr uint32_t NAME_LEN = 24;
constexpr uint32_t PLAYER_LEN = 16;
constexpr uint32_t TEXT_LEN = 160;

#pragma pack(push, 1)
struct HelloData { uint32_t dwServerId; char szName[NAME_LEN]; };
struct TalkData  { uint32_t dwServerId; char szFrom[PLAYER_LEN]; char szText[TEXT_LEN]; };
struct RosterEntry { char szName[PLAYER_LEN]; uint16_t usLevel; };
struct RosterData { uint32_t dwServerId; uint32_t dwCount; RosterEntry entries[MAX_ROSTER]; };
struct HeartbeatData { uint32_t dwServerId; uint32_t dwOnline; };
struct WhoRespServer { char szServer[NAME_LEN]; uint32_t dwOnline; RosterEntry entries[MAX_ROSTER]; };
struct WhoRespData { uint32_t dwServers; WhoRespServer servers[8]; };
struct ServerUpDownData { uint32_t dwServerId; char szName[NAME_LEN]; };
#pragma pack(pop)

template <typename T>
inline std::vector<uint8_t> Encode(uint16_t usType, const T& data) {
    static_assert(sizeof(T) >= 1, "empty payload not supported");
    tq::MsgHead head;
    head.type = usType;
    head.length = static_cast<uint16_t>(sizeof(tq::MsgHead) + sizeof(T));
    std::vector<uint8_t> pkt(sizeof(tq::MsgHead) + sizeof(T));
    std::memcpy(pkt.data(), &head, sizeof(head));
    std::memcpy(pkt.data() + sizeof(head), &data, sizeof(T));
    return pkt;
}

// frame decoder state: feed bytes, get (type, payload) per complete packet
class FrameDecoder {
public:
    // returns true when a full packet was decoded into outType/outPayload
    bool Feed(const uint8_t* pData, uint32_t dwLen, uint16_t& outType,
              std::vector<uint8_t>& outPayload) {
        m_buf.insert(m_buf.end(), pData, pData + dwLen);
        return Drain(outType, outPayload);
    }
    // drain the next already-buffered packet (no new bytes)
    bool Drain(uint16_t& outType, std::vector<uint8_t>& outPayload) {
        for (;;) {
            if (m_buf.size() < sizeof(tq::MsgHead)) return false;
            tq::MsgHead head;
            std::memcpy(&head, m_buf.data(), sizeof(head));
            if (head.length < sizeof(tq::MsgHead) || head.length > 8192) {
                m_buf.clear(); // poisoned stream: resync is impossible, drop
                return false;
            }
            if (m_buf.size() < head.length) return false;
            outType = head.type;
            outPayload.assign(m_buf.begin() + sizeof(tq::MsgHead),
                              m_buf.begin() + head.length);
            m_buf.erase(m_buf.begin(), m_buf.begin() + head.length);
            return true;
        }
    }
private:
    std::vector<uint8_t> m_buf;
};

inline void CopyStr(char* pDst, uint32_t dwCap, const std::string& str) {
    std::memset(pDst, 0, dwCap);
    std::strncpy(pDst, str.c_str(), dwCap - 1);
}

} // namespace cross
