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
